#include <Arduino.h>
void logger(String log){
    #ifdef __DEBUG__
    Serial.println(log);
    #endif

}