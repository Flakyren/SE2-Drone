#pragma once
#include "globalstructs.h"

class GimbalControl
{
public:
    GimbalControl();
    ~GimbalControl();
    // verstehe noch nicht den Sinn dieser Funktion
    void positionAdjust(Vec3d);

    Vec3d getMotorDegree();
    void setMotorDegree(Vec3d x);

private:
    Vec3d motorDegree;
};
