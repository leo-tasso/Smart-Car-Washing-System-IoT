#include "Lcd.h"
#include <Arduino.h>

Lcd::Lcd(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : lcd(new LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows))
{
    lcd->init();
    lcd->backlight();
}
void Lcd::clear()
{
    col = 0;
    lcd->clear();
    lcd->setCursor(0, col);
}
void Lcd::show(String msg)
{    
    lcd->print(msg);
}

void Lcd::ln(){
    col ++;
    lcd->setCursor(0, col);
}