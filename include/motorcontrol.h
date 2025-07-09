#pragma once
#include "motor.h"
#include "mposition.h"
#include <vector>

class MotorControl
{
public:
    MotorControl();
    // reihenfolge VR, VL , HR, HL
    MotorControl(Motor& motor1, Motor& motor2, Motor& motor3, Motor& motor4);
    ~MotorControl();

    void setMotorRPM(int givenRPM, mPosition);
    void setAllRPM(int givenRPM);
    void addMotor(Motor& motor);
    void removeMotor(Motor*);

    short calibrateMotors();
    short emergencyStop();
    Motor* getMotorByPosition(mPosition position);


private:
    std::vector<Motor*> motors;
};
