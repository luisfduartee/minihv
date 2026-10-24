#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool config_load(const char *filepath, HvConfig *config) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        printf("Erro ao abrir o ficheiro de configuração: %s\n", filepath);
        return false;
    }

    config->pcpus = 1;
    config->max_vms = 4;
    config->max_ticks = 5000;
    config->seed = 2026;
    strcpy(config->policy, "LOTTERY");
    config->quantum = 5;
    strcpy(config->mem_model, "PAG");
    config->phys_words = 1024;
    config->page_words = 64;
    strcpy(config->replacement, "NRU");
    strcpy(config->repl_scope, "LOCAL");
    config->pf_penalty = 3;
    strcpy(config->disk_algorithm, "LOOK");
    config->disk_cylinders = 200;
    config->disk_head = 50;
    config->seek_rate = 25;
    strcpy(config->log_format, "JSONL");
    strcpy(config->log_level, "INFO");
    strcpy(config->log_file, "out/minihv.jsonl");
    config->ext_enabled = true;

    fclose(file);
    return true;
}