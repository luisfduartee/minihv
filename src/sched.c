#include "sched.h"
#include <stdio.h>
#include <stdlib.h>

static uint32_t next_prng(uint32_t *state) {
    *state = (1103515245U * (*state) + 12345U) & 0x7FFFFFFF;
    return *state;
}

void sched_init(SchedLottery *sched, int quantum, uint32_t seed) {
    sched->count = 0;
    sched->quantum = quantum;
    sched->current_ticks = 0;
    sched->prng_state = seed;
    for (int i = 0; i < 4; i++) sched->queue[i] = NULL;
}

void sched_enqueue(SchedLottery *sched, Vcb *vm) {
    if (sched->count < 4) {
        sched->queue[sched->count++] = vm;
        vm_set_state(vm, VM_STATE_READY);
    }
}

Vcb* sched_pick_next(SchedLottery *sched) {
    if (sched->count == 0) return NULL;

    int total_tickets = 0;
    for (int i = 0; i < sched->count; i++) {
        int tickets = 10 - sched->queue[i]->priority;
        if (tickets < 1) tickets = 1;
        total_tickets += tickets;
    }

    uint32_t r = next_prng(&sched->prng_state) % (uint32_t)total_tickets;
    int sum = 0;
    int winner_idx = 0;
    for (int i = 0; i < sched->count; i++) {
        int tickets = 10 - sched->queue[i]->priority;
        if (tickets < 1) tickets = 1;
        sum += tickets;
        if ((uint32_t)sum > r) {
            winner_idx = i;
            break;
        }
    }

    Vcb *winner = sched->queue[winner_idx];
    for (int i = winner_idx; i < sched->count - 1; i++) {
        sched->queue[i] = sched->queue[i + 1];
    }
    sched->count--;
    sched->current_ticks = 0;
    vm_set_state(winner, VM_STATE_RUNNING);
    return winner;
}

bool sched_on_tick(SchedLottery *sched, Vcb *running) {
    if (!running) return false;
    sched->current_ticks++;
    if (sched->current_ticks >= sched->quantum) {
        printf("[LOG] PREEMPT | VM %s (q=%d esgotado)\n", running->name, sched->quantum);
        sched->current_ticks = 0;
        return true;
    }
    return false;
}
