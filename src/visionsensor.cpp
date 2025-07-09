#include "visionsensor.h"

VisionSensor::VisionSensor(int i) {
    sensorID = i;
}

VisionSensor::~VisionSensor(){
    //könnte noch logik enthalten wenn nötig
}

float VisionSensor::getReading(){
    return reading;
}
short VisionSensor::getSensorID(){
    return sensorID;
}

void VisionSensor::setReading(int newReading){
    reading = newReading;
    emit visionReadingUpdated(reading);
}
