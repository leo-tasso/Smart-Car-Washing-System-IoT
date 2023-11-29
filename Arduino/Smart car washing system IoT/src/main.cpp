#include <Arduino.h>

#include "CarWasher.h"
#include "config.h"
#include "system/scheduler.h"
#include "task/checkInPresenceDetection.h"
#include "task/communicator.h"
#include "task/displayFeedback.h"
#include "task/manageAccess.h"
#include "task/manageTemperature.h"
#include "task/sleepTask.h"
#include "task/washer.h"
#include "task/washingAreaPresenceDetection.h"

Scheduler *sched;
CarWasher carWasher;

void setup() {
    sched = new Scheduler(BASE_PERIOD);
    // Initialize tasks and add to the scheduler.
    sched->addTask(new CheckInPresenceDetion(500, &carWasher, PIR_PIN, L1_PIN));
    sched->addTask(new DisplayFeedback(1000, &carWasher, 0x27, 16, 2));
    sched->addTask(new Communicator(1000, &carWasher));
    sched->addTask(new Washer(50, &carWasher, L2_PIN, L3_PIN, START_BUTTON_PIN));
    sched->addTask(new WashingAreaPresenceDetection(500, &carWasher, SONAR_ECHO_PIN, SONAR_TRIG_PIN));
    sched->addTask(new ManageAccess(100, &carWasher, SERVO_PIN));
    sched->addTask(new ManageTemperature(500, &carWasher, TMP_PIN));
    sched->addTask(new SleepTask(500, &carWasher, PIR_PIN));
}

void loop() {
    sched->schedule();
}