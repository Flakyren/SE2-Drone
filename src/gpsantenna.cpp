#include "gpsantenna.h"

// Constructor
GPSAntenna::GPSAntenna() {}

// Destructor
GPSAntenna::~GPSAntenna() {}

// Get the number of satellites the GPS antenna is connected to
int GPSAntenna::getSatelliteCount() {
    return satellites;
}

// Get the current GPS position
Vec3d GPSAntenna::getGPSPosition() {
    return positionGPS;
}

// Set the number of satellites the GPS antenna is connected to
void GPSAntenna::setSatellitesCount(int givenSatellitesCount) {
    satellites = givenSatellitesCount;
}

// Set the GPS position for Extern functions
void GPSAntenna::setPositionGPS(Vec3d givenPositionGPS) {
    positionGPS = givenPositionGPS;
}

// Update the GPS position from the UI inputs
void GPSAntenna::gpsDataFromUI(double x, double y, double z) {
    positionGPS.x = x;
    positionGPS.y = y;
    positionGPS.z = z;
}

// Handle data request and emit the appropriate signal based on the request type
void GPSAntenna::getDataRequest(int i) {
    if (i == 1)
        emit sendDataToHomePoint(positionGPS); // Send data to home point
    else if (i == 2)
        emit sendDataToWayPoint(positionGPS); // Send data to waypoint
}

