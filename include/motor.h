#pragma once
#include "mposition.h"
#include <QObject>


class Motor : public QObject
{
    Q_OBJECT
public:
    Motor();
    Motor(mPosition position);
    ~Motor();

    double getRPM();
    mPosition getMotorPosition();
    double getTemperature();

    void setRPM(double givenRPM);
    void setMotorPosition(mPosition givenMotorPosition);
    void setTemperature(double givenTemperatur);

    double measureTemperature(); // muss geklärt werden mit simulation

signals:
    void setRotorRPMUI(int rpm, int rotorIndex);

private:
    double RPM;
    mPosition motorPosition;
    int rotorIndex;
    const double maxRPM = 10000;
    double temperature;
};
