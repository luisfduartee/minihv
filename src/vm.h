#ifndef VM_H
#define VM_H

#include <stdbool.h>
#include <stdint.h>

#define MAX_PROGRAM_SIZE 256
#define NUM_REGS 4

typedef enum {
    VM_STATE_NEW,
    VM_STATE_READY,
    VM_STATE_RUNNING,
    VM_STATE_BLOCKED,
    VM_STATE_PAUSED,
    VM_STATE_TERMINATED
} VmState;

typedef enum {
    TERM_NONE,
    TERM_HALT,
    TERM_PROTECTION_FAULT,
    TERM_INVALID_INSTRUCTION,
    TERM_KILLED,
    TERM_MAX_TICKS
} VmExitReason;

typedef struct {
    char op[8];
    int arg1;
    int arg2;
} Instruction;

typedef struct {
    int id;
    char name[32];
    VmState state;
    int priority;
    int registers[NUM_REGS];
    int pc;
    Instruction program[MAX_PROGRAM_SIZE];
    int program_size;
    int mem_words;
    uint64_t arrival_tick;
    uint64_t first_dispatch_tick;
    uint64_t exit_tick;
    VmExitReason exit_reason;
} Vcb;

void vm_init(Vcb *vm, int id, const char *name, int priority, int mem_words, uint64_t arrival_tick);
bool vm_set_state(Vcb *vm, VmState new_state);
bool vm_load_program(const char *filename, Vcb *vm);
void vm_execute_step(Vcb *vm);
const char* vm_state_to_string(VmState state);
const char* vm_reason_to_string(VmExitReason reason);

#endif
