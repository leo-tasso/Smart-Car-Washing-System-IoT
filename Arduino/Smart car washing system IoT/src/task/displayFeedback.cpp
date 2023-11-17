#include "displayFeedback.h"

#include "actuators/Lcd.h"

DisplayFeedback::DisplayFeedback(int period, CarWasher *CarWasher, uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
    : Task(period), carWasher(CarWasher), lcd(new Lcd(lcd_Addr, lcd_cols, lcd_rows)) {
    this->lcd->clear();
}

void DisplayFeedback::tick() {
    if (carWasher->carInCheckIn && !carWasher->carInWashingArea) {
        this->lcd->show("Get In");
    }
}

// TODO the rest of the scenarios, maybe implement scenario enum in CarWasher?