#ifndef __DISPLAY_FEEDBACK__
#define __DISPLAY_FEEDBACK__

#include "CarWasher.h"
#include "actuators/Display.h"
#include "system/task.h"

class DisplayFeedback : public Task {
   private:
    CarWasher *carWasher;
    Display *lcd;
   public:
    DisplayFeedback(int period, CarWasher *CarWasher, uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
    void tick() override;
};
#endif