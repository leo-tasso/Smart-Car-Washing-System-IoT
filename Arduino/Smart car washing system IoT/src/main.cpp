#include <Arduino.h>
#include "config.h"
#include "system/scheduler.h"
#include "CarWasher.h"
#include "task/checkInPresenceDetection.h"
#include "task/displayFeedback.h"
#include "task/communicator.h"

Scheduler *sched;
CarWasher carWasher;

void setup()
{
    sched = new Scheduler(BASE_PERIOD);
    // Test value
    carWasher.temp = 15;
    // Initialize tasks and add to the scheduler.
    sched->addTask(new CheckInPresenceDetion(500, &carWasher, PIR_PIN, L1_PIN));
    sched->addTask(new DisplayFeedback(1000, &carWasher, 0x27, 16, 2));
    sched->addTask(new Communicator(1000, &carWasher));
}

void loop()
{
    sched->schedule();
}