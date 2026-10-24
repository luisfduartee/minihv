#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "vm.h"
#include "mem.h"
#include "sched.h"
#include "logger.h"

int main(void) {
    HvConfig cfg;
    config_load("config.ini", &cfg);

    printf("== MiniHV | Escopo 25 | Policy=%s (q=%d) | Mem=%s/%s ==\n",
           cfg.policy, cfg.quantum, cfg.mem_model, cfg.replacement);

    log_event("HV_START", "MiniHV inicializado com sucesso no Escopo 25");

    mem_init(16);

    Vcb vm;
    vm_init(&vm, 1, "contador", 2, 512, 0);
    if (vm_load_program("progs/contador.mv", &vm)) {
        printf("[VM] Programa carregado com sucesso (%d instrucoes).\n", vm.program_size);
    }

    vm_set_state(&vm, VM_STATE_READY);
    vm_set_state(&vm, VM_STATE_RUNNING);

    printf("\n--- A iniciar execucao da VM ---\n");
    while (vm.state == VM_STATE_RUNNING) {
        vm_execute_step(&vm);
    }
    printf("--- Execucao terminada com sucesso ---\n");

    log_event("HV_STOP", "Execucao terminada, gerando snapshot final");
    log_snapshot(&vm, 1, 10);

    mem_show_status();
    printf("\n[LOGS] Ficheiros 'minihv_output.jsonl' e 'minihv_snapshot.jsonl' gerados!\n");
    return 0;
}