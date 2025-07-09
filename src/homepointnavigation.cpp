#include "homepointnavigation.h"
#include <iostream>

HomepointNavigation::HomepointNavigation() {
    gpsQueryTimer = new QTimer(this);
    connect(gpsQueryTimer, &QTimer::timeout, this, &HomepointNavigation::queryGPS);

    setHomepoint();
    // Print the homepoint coordinates for debugging Optinal
     std::cout << "Homepoint x: " << homepoint.x << std::endl;
     std::cout << "Homepoint y: " << homepoint.y << std::endl;
     std::cout << "Homepoint z: " << homepoint.z << std::endl;

}

HomepointNavigation::~HomepointNavigation() {
    if (gpsQueryTimer)
    {
        gpsQueryTimer->stop();
        delete gpsQueryTimer;
    }
}

Vec3d HomepointNavigation::getHomepoint() {
    return homepoint;
}

void HomepointNavigation::setHomepoint() {
    emit askForGPSData(1);
    homepoint = currentPosition;
}

void HomepointNavigation::setCurrentPosition(Vec3d position){
    currentPosition = position;
}

// Handle the signal to fly back to the homepoint
void HomepointNavigation::getFlyBackSignal(){
    gpsQueryTimer->start(20); // Start the timer to check if at Home
    emit flyMeTo(homepoint); // Emit signal to fly to the homepoint for GPSNav
}

// Receive and update GPS data from GPSAntenna
void HomepointNavigation::getGPSData(Vec3d positionGPS){
    currentPosition = positionGPS;

}

// Query the GPS data to check if the homepoint is reached
void HomepointNavigation::queryGPS()
{
    emit askForGPSData(1); // 1 ist Homepoint senden, 2 ist Waypoint senden

    // Check if current position is within the tolerance range of the homepoint
    if(homepoint.x <= currentPosition.x+tolerance && homepoint.x >= currentPosition.x-tolerance)
    {
        weAreHome = true;
        gpsQueryTimer->stop();
        emit homepointReached();
    }
    else
    {
        weAreHome = false;
    }
}
