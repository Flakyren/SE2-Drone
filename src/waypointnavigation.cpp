#include "waypointnavigation.h"
#include "iostream"

WaypointNavigation::WaypointNavigation() {
    gpsQueryTimer = new QTimer(this);
    connect(gpsQueryTimer, &QTimer::timeout, this, &WaypointNavigation::navigateToWaypoint);
}

WaypointNavigation::~WaypointNavigation() {
    gpsQueryTimer->stop();
    delete gpsQueryTimer;
}

// Saving Waypoint
void WaypointNavigation::getSaveWaypointSignal(){
    emit askForGPSData(2);

    if(waypointList.length() < 5){
        waypointList.append(currentPosition);
        wMarkedOrNot.append(1);
    }

}

// Check if at waypoint if get to next if last stop
void WaypointNavigation::navigateToWaypoint(){
    emit askForGPSData(2);

    if(!waypointList.empty())
        currentWaypoint = waypointList.last();

    if((waypointList.length() == 1) && (currentWaypoint.x <= currentPosition.x+tolerance && currentWaypoint.x >= currentPosition.x-tolerance && currentWaypoint.y <= currentPosition.y+tolerance && currentWaypoint.y >= currentPosition.y-tolerance)){
        gpsQueryTimer->stop();
        if(wMarkedOrNot.last())
            emit deleteWinUI();
        waypointList.removeLast();
        wMarkedOrNot.removeLast();
        emit lastWaypointReached();
    }else if(currentWaypoint.x <= currentPosition.x+tolerance && currentWaypoint.x >= currentPosition.x-tolerance && currentWaypoint.y <= currentPosition.y+tolerance && currentWaypoint.y >= currentPosition.y-tolerance){
        if(wMarkedOrNot.last())
            emit deleteWinUI();
        waypointList.removeLast();
        wMarkedOrNot.removeLast();
        currentWaypoint = waypointList.last();
        emit flyToWaypoint(currentWaypoint);
    }
}


void WaypointNavigation::getGPSData(Vec3d positionGPS){
    currentPosition = positionGPS;
}

// Start Flying to every Waypoint
void WaypointNavigation::getFlyBackSignal(){
    //waypoint = 1;
    if(waypointList.empty()){
        std::cout << "Keine Waypoints zum abfliegen vorhanden!" << std::endl;
        gpsQueryTimer->stop();
        emit lastWaypointReached();
    } else {
        emit flyToWaypoint(waypointList.last());
        gpsQueryTimer->start(20);
    }
}

// Remove Waypoint incase Landed
void WaypointNavigation::getSignalLanded(){
    if(waypointList.length() != 0){
        while(waypointList.length() != 0){
            if(wMarkedOrNot.last())
                emit deleteWinUI();
            waypointList.removeLast();
            wMarkedOrNot.removeLast();
        }
    }
}

// Stoping and Starting the WayNavTimer incase something is in the way
void WaypointNavigation::getStopTimer(){
    gpsQueryTimer->stop();
}

void WaypointNavigation::getStartTimer(){
    getFlyBackSignal();
}
