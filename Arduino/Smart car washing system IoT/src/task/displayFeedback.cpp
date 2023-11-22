#include "displayFeedback.h"

#include "actuators/Lcd.h"

DisplayFeedback::DisplayFeedback(int period, CarWasher *carWasher, uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
    : Task(period), carWasher(carWasher), lcd(new Lcd(lcd_Addr, lcd_cols, lcd_rows)) {
    this->lcd->clear();
}

void DisplayFeedback::tick() {
    if (this->carWasher->requiringManteinance) {
        this->lcd->clear();
        this->lcd->show("Detected a Problem - Please Wait");
    } else if (this->carWasher->washingComplete && this->carWasher->gateOpen) {
        this->lcd->clear();
        this->lcd->show("Washing complete");
        this->lcd->ln();
        this->lcd->show(" you can leave");
    } else if (this->carWasher->washing || this->carWasher->washingComplete) {
        this->lcd->clear();
        this->lcd->show("Washing...");
    } else if (this->carWasher->carInWashingArea) {
        this->lcd->clear();
        this->lcd->show("Ready to Wash");
    } else if (this->carWasher->gateOpen) {
        this->lcd->clear();
        this->lcd->show("Proceed to the Washing Area");
    } else {
        this->lcd->clear();
        this->lcd->show("Welcome");
    }
}
