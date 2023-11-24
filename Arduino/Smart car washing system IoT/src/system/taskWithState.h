#ifndef __TASK_WITH_STATE__
#define __TASK_WITH_STATE__

#include <Arduino.h>

#include "system/task.h"

class TaskWithState : public Task {
   public:
    TaskWithState(int period)
        : Task(period) {
    }

   protected:
    void setState(int s) {
        state = s;
        stateTimestamp = millis();
    }

    int getState() {
        return this->state;
    }

    unsigned long elapsedTimeInState() {
        return millis() - stateTimestamp;
    }

   private:
    int state{0};
    unsigned long stateTimestamp{0};
};

#endif
