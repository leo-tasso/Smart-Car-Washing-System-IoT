#include <Arduino.h>
#include "system/scheduler.h"

Scheduler sched;


void setup() {
// Initialize tasks and add to the scheduler.
}

void loop() {
    sched.schedule();
}