#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

typedef struct {
    int pcpus;
    int max_vms;
    int max_ticks;
    int seed;
    char policy[32];
    int quantum;
    char mem_model[16];
    int phys_words;
    int page_words;
    char replacement[16];
    char repl_scope[16];
    int pf_penalty;
    char disk_algorithm[16];
    int disk_cylinders;
    int disk_head;
    int seek_rate;
    char log_format[16];
    char log_level[16];
    char log_file[64];
    bool ext_enabled;
} HvConfig;

bool config_load(const char *filepath, HvConfig *config);

#endif