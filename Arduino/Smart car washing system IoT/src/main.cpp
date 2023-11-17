#include <Arduino.h>
#include "config.h"
#include "system/scheduler.h"
#include "CarWasher.h"
#include "task/checkInPresenceDetection.h"

Scheduler sched(BASE_PERIOD);
CarWasher carWasher;

void setup()
{
    // Initialize tasks and add to the scheduler.
    sched.addTask(new CheckInPresenceDetector(500, &carWasher, PIR_PIN, L1_PIN));
}

void loop()
{
    sched.schedule();
}