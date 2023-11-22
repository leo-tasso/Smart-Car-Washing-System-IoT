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
    if (Serial.availableForWrite()) {
        DynamicJsonDocument doc(128);
        doc["Temp"] = carWasher->temp;
        doc["WashedCars"] = carWasher->washedCars;
        doc["RequiringMaint"] = carWasher->requiringManteinance;
        doc["WashingPercentage"] = carWasher->washingPercentage;
        serializeJson(doc, Serial);
        Serial.println();
        Serial.flush();
    }
    if (Serial.available() > 0) {
        carWasher->requiringManteinance = false;
    }
};