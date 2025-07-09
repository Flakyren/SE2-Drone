#include "stabilizationsystem.h"

StabilizationSystem::StabilizationSystem(Magnetometer* magMeter, Gyroscope* gyroscope, AccelSensor* accelSensor):
    magnetMeter(magMeter), gyroscope(gyroscope), accelSensor(accelSensor)
{}

StabilizationSystem::~StabilizationSystem(){}
Vec4d StabilizationSystem::stabilize(Vec4d RPMInputs) {
    Vec4d RPMOutput = RPMInputs;
    gyroscope->setCalculatedRotation(RPMInputs);
    accelSensor->setCalculatedAccelReadings(RPMInputs);
    //Neigung nach rechts ungewollt
    if(gyroscope->getRotation().x == 1 || accelSensor->getAcceleration().x == 1 || magnetMeter->getMagnetWaveReadings().x == 1 ){
        RPMOutput.w += 1000; // w -> VR
        RPMOutput.y += 1000; // y -> HR
        RPMOutput.x -= 1000; // x -> VL
        RPMOutput.z -= 1000; // z -> HL
    }
    //Neigung nach links ungewollt
    if(gyroscope->getRotation().x == -1 || accelSensor->getAcceleration().x == -1 || magnetMeter->getMagnetWaveReadings().x == -1 ){
        RPMOutput.x += 1000;
        RPMOutput.z += 1000;
        RPMOutput.w -= 1000;
        RPMOutput.y -= 1000;
    }
    //Neigung nach vorne ungewollt
    if(gyroscope->getRotation().y == 1 || accelSensor->getAcceleration().y == 1 || magnetMeter->getMagnetWaveReadings().y == 1 ){
        RPMOutput.w += 1000;
        RPMOutput.x += 1000;
        RPMOutput.z -= 1000;
        RPMOutput.y -= 1000;
    }
    //Neigung nach hinten ungewollt
    if(gyroscope->getRotation().y == -1 || accelSensor->getAcceleration().y == -1 || magnetMeter->getMagnetWaveReadings().y == -1 ){
        RPMOutput.y += 1000;
        RPMOutput.z += 1000;
        RPMOutput.w -= 1000;
        RPMOutput.x -= 1000;
    }
    //Geht nach oben ungewollt
    if(gyroscope->getRotation().z == 1 || accelSensor->getAcceleration().z == 1 || magnetMeter->getMagnetWaveReadings().z == 1 ){
        RPMOutput.w -= 1000;
        RPMOutput.x -= 1000;
        RPMOutput.y -= 1000;
        RPMOutput.z -= 1000;
    }
    //geht nach unten ungewollt
    if(gyroscope->getRotation().z == -1 || accelSensor->getAcceleration().z == -1 || magnetMeter->getMagnetWaveReadings().z == -1 ){
        RPMOutput.w += 1000;
        RPMOutput.x += 1000;
        RPMOutput.y += 1000;
        RPMOutput.z += 1000;
    }
    return RPMOutput;
}
