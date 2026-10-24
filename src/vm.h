#ifndef VM_H
#define VM_H

#include <stdbool.h>

#define MAX_INSTRUCTIONS 256

typedef struct {
    char op[16];
    int arg1;
    int arg2;
} Instruction;

typedef struct {
    Instruction code[MAX_INSTRUCTIONS];
    int size;
    int pc;       
    int regs[4]; 
    int acc;      
} VirtualMachine;

bool vm_load_program(const char *filepath, VirtualMachine *vm);
bool vm_execute(VirtualMachine *vm);

#endif