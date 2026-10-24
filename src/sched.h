#ifndef SCHED_H
#define SCHED_H

#include <stdbool.h>
#include <stdint.h>
#include "vm.h"

typedef struct {
    Vcb *queue[4];
    int count;
    int quantum;
    int current_ticks;
    uint32_t prng_state;
} SchedLottery;

void sched_init(SchedLottery *sched, int quantum, uint32_t seed);
void sched_enqueue(SchedLottery *sched, Vcb *vm);
Vcb* sched_pick_next(SchedLottery *sched);
bool sched_on_tick(SchedLottery *sched, Vcb *running);

#endif
