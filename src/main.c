#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "vm.h"
#include "mem.h"

int main(void) {
    Config cfg;
    if (!load_config("config.ini", &cfg)) {
        printf("Aviso: A carregar configuracao por omissao.\n");
    }
    printf("== MiniHV | Escopo 25 | Policy=%s (q=%d) | Mem=%s ==\n", cfg.scheduling_policy, cfg.quantum, cfg.memory_policy);
    mem_init(16);
    VirtualMachine vm;
    if (vm_load_program("progs/contador.mv", &vm)) {
        printf("Maquina Virtual inicializada com o programa contador.mv\n");
        vm_execute(&vm);
    }
    mem_show_status();
    return 0;
}

