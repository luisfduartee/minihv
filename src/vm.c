#include "vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool vm_load_program(const char *filepath, VirtualMachine *vm) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        printf("ERRO: Nao foi possivel abrir %s\n", filepath);
        return false;
    }

    vm->size = 0;
    vm->pc = 0;

    char line[128];
    while (fgets(line, sizeof(line), file) && vm->size < MAX_INSTRUCTIONS) {
        if (line[0] == '\n' || line[0] == '\r' || line[0] == '#') continue;

        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == ',') line[i] = ' ';
        }

        Instruction *ins = &vm->code[vm->size];
        strcpy(ins->op, "");
        ins->arg1 = 0;
        ins->arg2 = 0;

        if (sscanf(line, "%15s R%d R%d", ins->op, &ins->arg1, &ins->arg2) >= 2) {
            vm->size++;
        } 

        else if (sscanf(line, "%15s R%d %d", ins->op, &ins->arg1, &ins->arg2) >= 2) {
            vm->size++;
        } 
      
        else if (sscanf(line, "%15s R%d", ins->op, &ins->arg1) >= 1) {
            vm->size++;
        } 
      
        else if (sscanf(line, "%15s %d %d", ins->op, &ins->arg1, &ins->arg2) >= 1) {
            vm->size++;
        } 
      
        else if (sscanf(line, "%15s %d", ins->op, &ins->arg1) >= 1) {
            vm->size++;
        } 
      
        else if (sscanf(line, "%15s", ins->op) >= 1) {
            vm->size++;
        }
    }

    fclose(file);
    printf("\n>>> TOTAL DE INSTRUCOES LIDAS: %d <<<\n", vm->size);
    for (int i = 0; i < vm->size; i++) {
        printf("INSTR [%d] -> OP: '%s' | ARG1: %d | ARG2: %d\n", i, vm->code[i].op, vm->code[i].arg1, vm->code[i].arg2);
    }
    printf("----------------------------------------\n");
    return true;
}

bool vm_execute(VirtualMachine *vm) {
    printf("\n--- A iniciar execução da VM ---\n");
    vm->pc = 0;
    vm->acc = 0;
    for (int i = 0; i < 4; i++) vm->regs[i] = 0;

    int passos = 0;
    while (vm->pc < vm->size && passos < 1000) {
        Instruction *ins = &vm->code[vm->pc];
        
        printf("[EXEC] PC=%d | Op=%s | Arg1=%d | Arg2=%d | R0=%d\n", 
               vm->pc, ins->op, ins->arg1, ins->arg2, vm->regs[0]);

        if (strcmp(ins->op, "MOV") == 0) {
            vm->regs[ins->arg1] = ins->arg2;
        } else if (strcmp(ins->op, "ADD") == 0) {
            vm->regs[ins->arg1] += vm->regs[ins->arg2];
        } else if (strcmp(ins->op, "SUB") == 0) {
            vm->regs[ins->arg1] -= vm->regs[ins->arg2];
        } else if (strcmp(ins->op, "DEC") == 0) {
            vm->regs[ins->arg1]--;
        } else if (strcmp(ins->op, "JZ") == 0) {
            if (vm->regs[ins->arg1] == 0) {
                vm->pc = ins->arg2;
                continue;
            }
        } else if (strcmp(ins->op, "JNZ") == 0) {
            if (vm->regs[ins->arg1] != 0) {
                vm->pc = ins->arg2;
                continue;
            }
        } else if (strcmp(ins->op, "JMP") == 0) {
            vm->pc = ins->arg1;
            continue;
        } else if (strcmp(ins->op, "OUT") == 0) {
            printf("[VM OUT] Registo R0 = %d\n", vm->regs[ins->arg1]);
        } else if (strcmp(ins->op, "HALT") == 0) {
            printf("[VM] Instrução HALT alcançada.\n");
            break;
        }

        vm->pc++;
        passos++;
    }

    printf("--- Execução terminada ---\n");
    return true;
}