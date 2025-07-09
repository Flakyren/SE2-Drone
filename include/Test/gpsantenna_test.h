#pragma once

#include <QObject>
#include <QTest>
#include "gpsantenna.h"

class GPSAntennaTest: public QObject {
    Q_OBJECT
    GPSAntenna * cut_; //Class under Test

public:
    explicit GPSAntennaTest(QObject* parent = nullptr) : QObject(parent){}

private slots:

    //Executed by QtTest before and after test suite
    void initTestCase();
    void cleanupTestCase();

    //Executed by QtTest before and after each test
    void init();
    void cleanup();
};
