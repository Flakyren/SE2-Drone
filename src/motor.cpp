#include "motor.h"

// Konstruktor
Motor::Motor()
    : RPM(0), temperature(0) {}

Motor::Motor(mPosition position): RPM(0), motorPosition(position),  temperature(0){}

// Destruktor
Motor::~Motor() {}

double Motor::getRPM() {
    return RPM;
}

mPosition Motor::getMotorPosition() {
    return motorPosition;
}

double Motor::getTemperature() {
    return temperature;
}

// Setter for RPM but with a check for maxRPM
void Motor::setRPM(double givenRPM) {
    if (givenRPM < 0) {
        RPM = 0; // Prevent negative RPM
    } else if (givenRPM >= maxRPM) {
        RPM = maxRPM; // Cap RPM at maxRPM
    } else {
        RPM = givenRPM; // Set RPM to given value
    }
    rotorIndex = static_cast<int>(motorPosition); // Update rotor index based on motor position
    emit setRotorRPMUI(RPM, rotorIndex); // Emit signal to update UI with new RPM
}

void Motor::setMotorPosition(mPosition givenMotorPosition) {
    motorPosition = givenMotorPosition;
}


void Motor::setTemperature(double givenTemperatur) {
    temperature = givenTemperatur;
}

double Motor::measureTemperature() {
    return temperature;
}
