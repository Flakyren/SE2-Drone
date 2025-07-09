#pragma once
#include "globalstructs.h"
#include <QObject>
#include <QTimer>

class WaypointNavigation : public QObject
{
    Q_OBJECT
public:
    WaypointNavigation();
    ~WaypointNavigation();
    void getSignalLanded();
    void addWaypoint(Vec3d);
    void flyTo(Vec3d Pos);
    void checkWaypointReached(); // Inputs need to be defined here, I didn't understand the diagram
    void navigateToWaypoint(); // Inputs need to be defined here, I didn't understand the diagram
    void setCurrentWaypoint(Vec3d x);    // Replace 'void' later with "waypoint" from the diagram, same issue as before & Name changed to avoid repetition
public slots:
    void getSaveWaypointSignal();
    void getGPSData(Vec3d positionGPS);
    void getFlyBackSignal();
    void getStopTimer();
    void getStartTimer();
signals:
    void askForGPSData(int i);
    void flyToWaypoint(Vec3d GPSData);
    void lastWaypointReached();
    void deleteWinUI();
private:
    QList<Vec3d> waypointList; // 5 is our max number of waypoints to be stored (modifiable, 5 is just an example)
    QList<int> wMarkedOrNot;
    Vec3d currentWaypoint;
    Vec3d nextWaypoint;
    int waypoint;
    QTimer* gpsQueryTimer;
    double tolerance = 10.0;
    Vec3d currentPosition;

};
