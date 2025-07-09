#include "accelsensor.h"
#include <cmath>

const double g = 9.81; // Earths Gravitational Acceleration in m/s^2

AccelSensor::AccelSensor() {}

AccelSensor::~AccelSensor() {}

Vec3d AccelSensor::getAcceleration() {
    return accelerationReadings;
}

void AccelSensor::setAcceleration(Vec3d givenAcceleration) {
    accelerationReadings = givenAcceleration;
}

Vec3d AccelSensor::getCalculatedAccelReadings(){
    return calculatedAccelReadings;
}

void AccelSensor::setCalculatedAccelReadings(Vec4d inputRPM){
    Vec3d calcAccelSensor;
    double mass = 1; // 1kg

    // Calculate thrust for every motor
    double thrust1 = 0.1 * sqrt(abs(inputRPM.w));
    double thrust2 = 0.1 * sqrt(abs(inputRPM.x));
    double thrust3 = 0.1 * sqrt(abs(inputRPM.y));
    double thrust4 = 0.1 * sqrt(abs(inputRPM.z));

    // simplified Calculation for the Accelsensor
    calcAccelSensor.x = (-thrust1 - thrust2 + thrust3 + thrust4) / mass; // Acceleration in x-direction
    calcAccelSensor.y = (-thrust1 + thrust2 + thrust3 - thrust4) / mass; // Acceleration in y-direction
    calcAccelSensor.z = (thrust1 + thrust2 + thrust3 + thrust4) / mass - g; // Acceleration in z-direction

    calculatedAccelReadings = calcAccelSensor;
}

void AccelSensor::getAccelarationValues(double x, double y, double z){
    accelerationReadings.x = x;
    accelerationReadings.y = y;
    accelerationReadings.z = z;
}

