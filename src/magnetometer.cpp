#include "magnetometer.h"

Magnetometer::Magnetometer() {}

Magnetometer::~Magnetometer() {}

Vec3d Magnetometer::getMagnetWaveReadings() {
    return magnetWaveReadings;
}

void Magnetometer::setMagnetWaveReadings(Vec3d givenMagnetWaveReadings) {
    magnetWaveReadings = givenMagnetWaveReadings;
}

Vec3d Magnetometer::measureMagnetWaveReadings() {
    Vec3d tmp;
    return tmp;
}

void Magnetometer::getMagnetometerValues(double x, double y, double z){
    magnetWaveReadings.x = x;
    magnetWaveReadings.y = y;
    magnetWaveReadings.z = z;
}
