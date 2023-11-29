#include "displayFeedback.h"

#include "actuators/Lcd.h"

DisplayFeedback::DisplayFeedback(int period, CarWasher *carWasher, uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
    : Task(period), carWasher(carWasher),  lcd(new Lcd(lcd_Addr, lcd_cols, lcd_rows)), colDisplay(lcd_cols){
    this->lcd->clear();
}

void DisplayFeedback::tick() {
    if (this->carWasher->requiringManteinance) {
        this->lcd->show("Detected ProblemPlease Wait");
    } else if (this->carWasher->washingComplete && this->carWasher->gateOpen) {
        this->lcd->show("Washing completeyou can leave");
    } else if (this->carWasher->washing || this->carWasher->washingComplete) {
        String message = "Washing...      ";
        if (carWasher->washingPercentage != 0) {
            for (size_t i = 0; i < this->colDisplay * carWasher->washingPercentage / 100; i++) {
                message += "-";
            }
            message+=">";
        }
        this->lcd->show(message);
    } else if (this->carWasher->carInWashingArea) {
        this->lcd->show("Ready to Wash");
    } else if (this->carWasher->gateOpen) {
        this->lcd->show("Proceed to the  Washing Area");
    } else {
        this->lcd->show("Welcome");
    }
}
