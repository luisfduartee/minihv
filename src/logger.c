#include "logger.h"
#include <time.h>

void log_event(const char *event_type, const char *details) {
    FILE *f = fopen("minihv_output.jsonl", "a");
    if (!f) return;
    time_t now = time(NULL);
    fprintf(f, "{\"timestamp\": %ld, \"event\": \"%s\", \"details\": \"%s\"}\n", (long)now, event_type, details);
    fclose(f);
}

void log_snapshot(Vcb *vms, int count, int tick) {
    FILE *f = fopen("minihv_snapshot.jsonl", "a");
    if (!f) return;
    fprintf(f, "{\"tick\": %d, \"vms_active\": %d}\n", tick, count);
    for (int i = 0; i < count; i++) {
        fprintf(f, "  {\"id\": %d, \"name\": \"%s\", \"state\": \"%s\", \"pc\": %d}\n",
                vms[i].id, vms[i].name, vm_state_to_string(vms[i].state), vms[i].pc);
    }
    fclose(f);
}