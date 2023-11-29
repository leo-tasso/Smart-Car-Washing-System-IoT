#include "task/sleepTask.h"
#include "config.h"

#include <Arduino.h>
#include <avr/sleep.h>
SleepTask::SleepTask(int period,
                     CarWasher *carWasher,
                     int wakePin)
    : Task(period),
      carWasher(carWasher), wakePin(wakePin) {
}

void SleepTask::tick() {
    if (!this->carWasher->carInCheckIn || !this->carWasher->carInWashingArea) {
        if (millis() > this->timer) {
            attachInterrupt(digitalPinToInterrupt(this->wakePin), {}, RISING); 
            set_sleep_mode(SLEEP_MODE_PWR_DOWN);
            sleep_enable();
            sleep_mode();

            sleep_disable();
            detachInterrupt(digitalPinToInterrupt(this->wakePin)); 

        }
    } else {
        timer = millis() + SLEEP_TIME;
    }
};