#pragma once
#include "globalstructs.h"
#include <QObject>

class AccelSensor : public QObject //acceleration sensor
{
    Q_OBJECT
public:
    AccelSensor();
    ~AccelSensor();

    Vec3d getAcceleration();
    Vec3d getCalculatedAccelReadings();

    void setCalculatedAccelReadings(Vec4d InputRPM);
    void setAcceleration(Vec3d givenAcceleration);

private:
    Vec3d accelerationReadings = {0,0,0};
    Vec3d calculatedAccelReadings;

public slots:
    void getAccelarationValues(double x, double y, double z);
};
