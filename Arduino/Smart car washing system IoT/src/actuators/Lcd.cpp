#include "Lcd.h"

#include <Arduino.h>

Lcd::Lcd(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
    : lcd(new LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows)),
      total_rows(lcd_rows) {
    lcd->init();
    lcd->backlight();
}
void Lcd::clear() {
    col = 0;
    lcd->clear();
    lcd->setCursor(0, col);
}
void Lcd::show(String msg) {
    String padding = "";
    for (size_t i = msg.length(); i < total_rows; i++) {
        padding = padding + " ";
    }

    String paddedMessage = msg + padding;
    lcd->print(msg.substring(0,total_rows));
    this->ln();
    lcd->print(msg.substring(total_rows));
    lcd->setCursor(0,0);
}

void Lcd::ln() {
    col++;
    lcd->setCursor(0, col);
}