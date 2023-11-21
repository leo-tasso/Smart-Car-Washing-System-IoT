#include "communicator.h"

#include <Arduino.h>
#include <ArduinoJson.h>

#include "CarWasher.h"

Communicator::Communicator(int period, CarWasher *carWasher)
    : Task(period),
      carWasher(carWasher) {
    Serial.begin(9600);
}

void Communicator::tick() {
    if(Serial.availableForWrite()){    
    DynamicJsonDocument doc(128);
    switch (carWasher->activeScenario) {
        case SLEEP:
            doc["Scenario"] = "Sleep";
            break;
        case WELCOME:
            doc["Scenario"] = "Welcome";
            break;
        case ENTER:
            doc["Scenario"] = "Enter";
            break;
        case FULL_ENTERED:
            doc["Scenario"] = "FULL_ENTERED";
            break;
        case WASHING:
            doc["Scenario"] = "Washing";
            break;
        case COMPLETE:
            doc["Scenario"] = "Complete";
            break;
        case MAINT_REQ:
            doc["Scenario"] = "Maintainece Required!";
            break;
        default:
            break;
    }
    doc["Temp"] = carWasher->temp;
    doc["WashedCars"] = carWasher->washedCars;
    doc["RequiringMaint"] = carWasher->requiringManteinance;
    doc["WashingPercentage"] = carWasher->washingPercentage;
    serializeJson(doc, Serial);
    Serial.flush();
    }
};