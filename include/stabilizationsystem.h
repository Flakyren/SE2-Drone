#pragma once
#include "globalstructs.h"
#include "accelsensor.h"
#include "gyroscope.h"
#include "magnetometer.h"
class StabilizationSystem
{
public:
    StabilizationSystem(Magnetometer* magMeter, Gyroscope* gyroScope, AccelSensor* accelSensor);
    ~StabilizationSystem();

    Vec3d getTargetPosition();
    Vec3d getTargetOrientation();
    Vec3d getCurrentPosition();
    Vec3d getCurrentOrientation();

    void setTargetPosition(Vec3d givenTargetPosition);
    void setTargetOrientation(Vec3d givenTargetOrientation);
    void setCurrentPosition(Vec3d givenCurrentPosition);
    void setCurrentOrientation(Vec3d givenCurrentOrientation);

    Vec4d stabilize(Vec4d RPMInputs); // exceptions machen

private:
    Magnetometer* magnetMeter;
    Gyroscope* gyroscope;
    AccelSensor * accelSensor;
};
