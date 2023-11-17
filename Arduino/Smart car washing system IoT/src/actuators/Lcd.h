#ifndef __DISPLAY__
#define __DISPLAY__

#include "Display.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h> 

class Lcd: public Display{
private:
LiquidCrystal_I2C * lcd;

public:
    Lcd(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
    void clear();
    void show(String msg);
};


#endif