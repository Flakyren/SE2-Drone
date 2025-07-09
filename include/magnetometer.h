#pragma once
#include "globalstructs.h"
#include <QObject>

class Magnetometer : public QObject
{
    Q_OBJECT
public:
    Magnetometer();
    ~Magnetometer();

    Vec3d getMagnetWaveReadings();
    void setMagnetWaveReadings(Vec3d givenMagnetWaveReadings);
    Vec3d measureMagnetWaveReadings();

private:
    Vec3d magnetWaveReadings = {0,0,0};

public slots:
    void getMagnetometerValues(double x, double y, double z);
};
