#include "gpsNavigation.h"
// ProperRPM Brauchen wir ja eigentlich nicht right?
GPSNavigation::GPSNavigation() {
    properRPM.x = 3000;
    properRPM.y = 3000;
    properRPM.z = 3000;
    properRPM.w = 3000;
}

GPSNavigation::~GPSNavigation() {

}

void GPSNavigation::setProperRPM(Vec4d RPM){
    properRPM = RPM;
}

void GPSNavigation::setDestinationPosition(Vec3d Pos){
    destinationPosition = Pos;
}

Vec4d GPSNavigation::getProperRPM(){
    return properRPM;
}

Vec3d GPSNavigation::getDestinationPosition(){
    return destinationPosition;
}

void GPSNavigation::getFlyMeToSignal(Vec3d gpsPosition){
    emit sendDataToFlyControl(gpsPosition);
}
