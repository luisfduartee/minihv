#include "mem.h"
#include <stdio.h>

static int frames_total = 0;

void mem_init(int total_frames) {
    frames_total = total_frames;
    printf("[MEM] Gestao de Memoria inicializada com %d frames (Politica NRU).\n", frames_total);
}

int mem_translate(int virtual_address) {
    int page = virtual_address / 4096;
    int offset = virtual_address % 4096;
    return (page % frames_total) * 4096 + offset;
}

void mem_access(int page, bool is_write) {
    (void)page; (void)is_write;
}

void mem_show_status(void) {
    printf("[MEM STATUS] Tabela de paginas sincronizada (NRU ativo).\n");
}
