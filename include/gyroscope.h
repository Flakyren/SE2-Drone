#pragma once
#include "globalstructs.h"
#include <QObject>

class Gyroscope : public QObject
{
    Q_OBJECT
public:
    Gyroscope();
    ~Gyroscope();

    Vec3d getRotation();
    Vec3d getCalculatedRotation();
    void setRotation(Vec3d givenRotation);
    void setCalculatedRotation(Vec4d givenRPM);
    Vec3d measureRotation();

private:
    Vec3d rotationReadings = {0,0,0};
    Vec3d calculatedRotation;

public slots:
    void getGyroscopeValues(double x, double y, double z);
};
