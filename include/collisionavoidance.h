#pragma once

#include <QObject>
#include <QTimer>
#include <vector>
#include "visionsensor.h"
#include "InfraredSensor.h"
#include "radiocommunikation.h"
#include "gpsantenna.h"

class CollisionAvoidance : public QObject
{
    Q_OBJECT

public:
    CollisionAvoidance() {};
    CollisionAvoidance(QObject *parent, VisionSensor* VS1, VisionSensor* VS2, VisionSensor* VS3, VisionSensor* VS4, InfraredSensor* IS1, InfraredSensor* IS2, InfraredSensor* IS3, InfraredSensor* IS4, RadioCommunication *radio, GPSAntenna* gps);
    ~CollisionAvoidance();

    int getInfraredSensorReadings(int ID);
    int getVisionSensorReadings(int ID);

    void setInfraredSensorReadings(int index, int reading);
    void setVisionSensorReadings(int index, int reading);
    void setCounter(int);

    void detectCollision();
    void moveCheckDroneFunktion();

signals:
    void emergencyStop(int crashID);
    void StopNav();
    void StopWayNav();
    //void flyToNewPos(Vec3d position);
    void startFlyToWayNav();
    void moveDroneX(int move);
    void startFlyHome();


public slots:
    void updateInfraredReading1V(int newReading);
    void updateInfraredReading2R(int newReading);
    void updateInfraredReading3L(int newReading);
    void updateInfraredReading4D(int newReading);

    void updateVisionReading1V(int newReading);
    void updateVisionReading2R(int newReading);
    void updateVisionReading3L(int newReading);
    void updateVisionReading4D(int newReading);

private:
    std::vector<VisionSensor*> visionSensors;
    std::vector<InfraredSensor*> infraredSensors;
    QTimer *timer;
    QTimer *moveCheckDrone;
    int distanceInfrared[4];
    int distanceVision[4];
    double minDistance = 0.5;
    RadioCommunication* radio;
    GPSAntenna* gps;
    int counter = 0;
};
