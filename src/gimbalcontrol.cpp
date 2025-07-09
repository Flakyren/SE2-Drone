#include "gimbalcontrol.h"

GimbalControl::GimbalControl() {}

Vec3d GimbalControl::getMotorDegree() {
    return motorDegree;
}

void GimbalControl::setMotorDegree(Vec3d givenMotorDegree) {
    motorDegree = givenMotorDegree;
}
