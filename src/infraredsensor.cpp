#include "InfraredSensor.h"

InfraredSensor::InfraredSensor(int i) : sensorID(i), reading(0) {}

InfraredSensor::~InfraredSensor() {}

float InfraredSensor::getReadings() {
    return reading;
}

short InfraredSensor::getSensorID() {
    return sensorID;
}

// Slot for getting Readings
void InfraredSensor::setReadings(int newReading) {
    reading = newReading;
    emit infraredReadingUpdated(reading);
}
