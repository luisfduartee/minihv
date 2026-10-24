#ifndef MEM_H
#define MEM_H

#include <stdbool.h>

void mem_init(int total_frames);
int mem_translate(int virtual_address);
void mem_access(int page, bool is_write);
void mem_show_status(void);

#endif
