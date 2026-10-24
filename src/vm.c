#include "vm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const bool TRANSITION_TABLE[6][6] = {
    { false, true,  false, false, false, true },
    { false, false, true,  false, true,  true },
    { false, true,  false, true,  true,  true },
    { false, true,  false, false, false, true },
    { false, true,  false, false, false, true },
    { false, false, false, false, false, false }
};

const char* vm_state_to_string(VmState state) {
    switch (state) {
        case VM_STATE_NEW: return "NEW";
        case VM_STATE_READY: return "READY";
        case VM_STATE_RUNNING: return "RUNNING";
        case VM_STATE_BLOCKED: return "BLOCKED";
        case VM_STATE_PAUSED: return "PAUSED";
        case VM_STATE_TERMINATED: return "TERMINATED";
        default: return "UNKNOWN";
    }
}

void vm_init(Vcb *vm, int id, const char *name, int priority, int mem_words, uint64_t arrival_tick) {
    memset(vm, 0, sizeof(Vcb));
    vm->id = id;
    strncpy(vm->name, name, sizeof(vm->name) - 1);
    vm->state = VM_STATE_NEW;
    vm->priority = priority;
    vm->mem_words = mem_words;
    vm->arrival_tick = arrival_tick;
    vm->exit_reason = TERM_NONE;
}

bool vm_set_state(Vcb *vm, VmState new_state) {
    if (!vm) return false;
    if (vm->state == new_state) return true;
    if (!TRANSITION_TABLE[vm->state][new_state]) return false;
    vm->state = new_state;
    return true;
}

bool vm_load_program(const char *filename, Vcb *vm) {
    FILE *f = fopen(filename, "r");
    if (!f) return false;
    char line[128];
    vm->program_size = 0;
    while (fgets(line, sizeof(line), f) && vm->program_size < MAX_PROGRAM_SIZE) {
        char *comment = strchr(line, ';');
        if (comment) *comment = '\0';
        char op[8];
        int arg1 = 0, arg2 = 0;
        int matches = sscanf(line, "%7s %d %d", op, &arg1, &arg2);
        if (matches > 0) {
            strncpy(vm->program[vm->program_size].op, op, 7);
            vm->program[vm->program_size].arg1 = arg1;
            vm->program[vm->program_size].arg2 = arg2;
            vm->program_size++;
        }
    }
    fclose(f);
    return true;
}

void vm_execute_step(Vcb *vm) {
    if (vm->pc >= vm->program_size) {
        vm->exit_reason = TERM_HALT;
        vm_set_state(vm, VM_STATE_TERMINATED);
        return;
    }
    Instruction ins = vm->program[vm->pc];
    if (strcmp(ins.op, "MOV") == 0) {
        vm->registers[ins.arg1] = ins.arg2;
        vm->pc++;
    } else if (strcmp(ins.op, "SUB") == 0) {
        vm->registers[ins.arg1] -= vm->registers[ins.arg2];
        vm->pc++;
    } else if (strcmp(ins.op, "JNZ") == 0) {
        if (vm->registers[ins.arg1] != 0) {
            vm->pc = ins.arg2;
        } else {
            vm->pc++;
        }
    } else if (strcmp(ins.op, "OUT") == 0) {
        printf("[VM OUT] Registo R%d = %d\n", ins.arg1, vm->registers[ins.arg1]);
        vm->pc++;
    } else if (strcmp(ins.op, "HALT") == 0) {
        vm->exit_reason = TERM_HALT;
        vm_set_state(vm, VM_STATE_TERMINATED);
    } else {
        vm->exit_reason = TERM_INVALID_INSTRUCTION;
        vm_set_state(vm, VM_STATE_TERMINATED);
    }
}