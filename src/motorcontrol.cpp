#include "motorcontrol.h"
#include <algorithm>


// Konstruktor
MotorControl::MotorControl() {

}

// Konstruktor with motors
MotorControl::MotorControl(Motor& motor1, Motor& motor2, Motor& motor3, Motor& motor4) {
    motors.push_back(&motor1);
    motors.push_back(&motor2);
    motors.push_back(&motor3);
    motors.push_back(&motor4);
}

// Destruktor
MotorControl::~MotorControl() {

}

//getting the right motor depending on position
Motor* MotorControl::getMotorByPosition(mPosition position) {
    for (auto motor : motors) {
        if (motor->getMotorPosition() == position) {
            return motor;
        }
    }
    return nullptr;
}

// setting RPM for a specific motor
void MotorControl::setMotorRPM(int givenRPM, mPosition position) {
    for (auto& motor : motors) {
        if (motor->getMotorPosition() == position) {
            motor->setRPM(givenRPM);
            break;
        }
    }
}

// setting RPM for every Motor
void MotorControl::setAllRPM(int givenRPM) {
    for (auto& motor : motors) {
        motor->setRPM(givenRPM);

    }
}

void MotorControl::addMotor(Motor& motor) {
    motors.push_back(&motor);
}

void MotorControl::removeMotor(Motor* motor) {
    motors.erase(std::remove(motors.begin(), motors.end(), motor), motors.end());
}

short MotorControl::calibrateMotors() {
    setAllRPM(0);
    return 0;
}

short MotorControl::emergencyStop() {
    setAllRPM(0);
    return 0;
}
