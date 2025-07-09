#pragma once
#include "globalstructs.h"
#include "motorcontrol.h"
#include "collisionavoidance.h"
#include "radiocommunikation.h"
#include "stabilizationsystem.h"
#include "waypointnavigation.h"
#include "gpsantenna.h"
#include  <QObject>
#include <QTimer>

class FlyControlModul : public QObject
{
    Q_OBJECT

public:
    FlyControlModul(){};
    ~FlyControlModul();
    FlyControlModul(StabilizationSystem &stabilizationSystem, WaypointNavigation &wayNav, RadioCommunication &radio, MotorControl &motors, CollisionAvoidance &collisionAvoid, GPSAntenna &GPS);

    bool getInAir();
    double getCurrenSpeed();

    void setInAir(bool givenInAir);
    void setCurrentSpeed(double givenCurrentSpeed);

    void Start();
    void Land();
    void calculateSpeed();
    void Adjust(); // Manipuliert die Motoren um gewünschte bewegung zu erreichen
    void getControlInputs();

public slots:
    void handleEmergencyStop(int crashID);
    void startLandInitiate();
    void getDataFromGPSNav(Vec3d destinationPosition);
    void setJoyInputsFromRadio(Vec4d radioInput);
    void gotlastWaypointReached();
    void stopNavigation();
    void getMoveDroneX(int move);
    void startNavigation();

signals:
    void moveToPositionInUI(int x, int y);
    void sendInAirData(bool Data);
    void rotateDrone(int angle);
    void moveDrone(int x, int y);
    void LED(QString color);

private:

    void flyBackTimerFunktion();
    int calcRotationToPosition(int x, int y);
    void checkStart();
    void checkLand();
    void checkLEDFunktion();

    bool inAir = false;
    double currentSpeed;
    QTimer* moveToPosTimer;
    QTimer* getControlInputsTimer;
    QTimer* startTimer;
    QTimer* landTimer;
    QTimer* checkLED;
    Vec4d joyInputs;
    Vec3d targetPosition;

    WaypointNavigation *wayNav;
    MotorControl* motors;
    CollisionAvoidance* collisionAvoid;
    StabilizationSystem* stabilizationSystem;
    RadioCommunication* radio;
    GPSAntenna* gps;

};
