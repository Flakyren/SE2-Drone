#pragma once

#include <QObject>
#include <QTest>
#include "flycontrolmodul.h"

class FlyControlModulTest : public QObject {
    Q_OBJECT

    FlyControlModul * cut_; //Class under Test

public:
    explicit FlyControlModulTest(QObject* parent = nullptr) : QObject(parent){}
    Motor motor1;
    Motor motor2;
    Motor motor3;
    Motor motor4;
    AccelSensor* accelSensor;
    Magnetometer* magMeter;
    Gyroscope* gyrScope;
    WaypointNavigation wayNav;
    JoystickControl JoystickHR = new JoystickControl(1);
    JoystickControl JoystickN = new JoystickControl(2);
    VisionSensor * VS1 = new VisionSensor(1);
    VisionSensor * VS2 = new VisionSensor(2);
    VisionSensor * VS3 = new VisionSensor(3);
    VisionSensor * VS4 = new VisionSensor(4);
    InfraredSensor * IS1 = new InfraredSensor(1);
    InfraredSensor * IS2 = new InfraredSensor(2);
    InfraredSensor * IS3 = new InfraredSensor(3);
    InfraredSensor * IS4 = new InfraredSensor(4);
    StartLandButton startLandButton;
    GPSAntenna GPS;
    const int startRPM = 5000;

private slots:

    //Executed by QtTest before and after test suite
    void initTestCase();
    void cleanupTestCase();

    //Executed by QtTest before and after each test
    void init();
    void cleanup();

    // Teste ob die erwartete mRPM berechnet wird
    // joyInputs.x = 1, joyInputs.y = -1, joyInputs.z = -1, joyInputs.x = 0
    //
    void AdjustGivenValues();
};
