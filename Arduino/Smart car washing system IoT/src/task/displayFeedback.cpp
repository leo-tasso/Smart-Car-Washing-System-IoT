#include "displayFeedback.h"

#include "actuators/Lcd.h"

DisplayFeedback::DisplayFeedback(int period, CarWasher *carWasher, uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
    : Task(period), carWasher(carWasher), lcd(new Lcd(lcd_Addr, lcd_cols, lcd_rows)) {
    this->lcd->clear();
}

void DisplayFeedback::tick() {
    if (this->carWasher->activeScenario != this->prevScenario) {
        this->lcd->clear();
        switch (this->carWasher->activeScenario) {
            case WELCOME:
                this->lcd->show("Welcome");
                break;
            case ENTER:
                this->lcd->show("Proceed to the Washing Area");
                break;
            case FULL_ENTERED:
                this->lcd->show("Ready to Wash");
                break;
            case COMPLETE:
                this->lcd->show("Washing complete, you can leave the area");
                break;
            case MAINT_REQ:
                this->lcd->show("Detected a Problem - Please Wait");
                break;
            default:
                break;
        }
    }
}
