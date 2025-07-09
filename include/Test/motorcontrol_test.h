#pragma once

#include <QObject>
#include <QTest>
#include "motorcontrol.h"

class MotorControlTest : public QObject {
    Q_OBJECT

    MotorControl * cut_; //Class under Test

public:
    explicit MotorControlTest(QObject* parent = nullptr) : QObject(parent){}
    Motor motor1;
    Motor motor2;
    Motor motor3;
    Motor motor4;
    int givenTestRPM = 7000;
    int startRPM = 5000;

private slots:

    //Executed by QtTest before and after test suite
    void initTestCase();
    void cleanupTestCase();

    //Executed by QtTest before and after each test
    void init();
    void cleanup();

    //Teste ob der Motor an Position 3 gefunden wird
    void getMotorByPosition3();
    //Teste ob ein Nullpointer zurückgegeben wird, wenn keine Position passt
    void getMotorByPositionInvalidPosition();
    //Teste ob die RPM vom Motor an Position 3 gesetzt wird
    void setMotorRPMPosition3();
    //Teste ob die RPM gleich bleibt, wenn der Motor nicht gefunden werden kann
    void setMotorRPMInvalidPosition();
    //Teste ob alle RPMs gesetzt werden
    void setAllRPMTest();
};
