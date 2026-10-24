#ifndef LOGGER_H
#define LOGGER_H

#include "vm.h"
#include <stdio.h>

void log_event(const char *event_type, const char *details);
void log_snapshot(Vcb *vms, int count, int tick);

#endif