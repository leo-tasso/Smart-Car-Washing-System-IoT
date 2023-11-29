#include "communicator.h"

#include <Arduino.h>
#include <ArduinoJson.h>

#include "CarWasher.h"
#include "system/logger.h"

Communicator::Communicator(int period, CarWasher *carWasher)
    : Task(period),
      carWasher(carWasher) {
    Serial.begin(115200);
}

void Communicator::tick() {
    if (Serial.availableForWrite()) {
        DynamicJsonDocument doc(128);
        doc["carInCheckIn"] = carWasher->carInCheckIn;
        doc["carInWashingArea"] = carWasher->carInWashingArea;
        doc["temp"] = carWasher->temp;
        doc["requiringMaintenance"] = carWasher->requiringManteinance;
        doc["gateOpen"] = carWasher->gateOpen;
        doc["washing"] = carWasher->washing;
        doc["washingComplete"] = carWasher->washingComplete;
        doc["washingPercentage"] = carWasher->washingPercentage;
        doc["washedCars"] = carWasher->washedCars;
        serializeJson(doc, Serial);
        Serial.println();
        Serial.flush();
    }
    if (Serial.available() > 0) {
        String recived = Serial.readStringUntil('!');
        //logger(recived);
        if (recived == "maintenanceDone") {
            carWasher->requiringManteinance = false;
            //logger("Arduino reciving");
        }
    }
};