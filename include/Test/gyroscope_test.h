#pragma once

#include <QObject>
#include <QTest>
#include "gyroscope.h"

class GyroscopeTest : public QObject {
    Q_OBJECT

    Gyroscope * cut_; //Class under Test

public:
    explicit GyroscopeTest(QObject* parent = nullptr) : QObject(parent){}

private slots:

    //Executed by QtTest before and after test suite
    void initTestCase();
    void cleanupTestCase();

    //Executed by QtTest before and after each test
    void init();
    void cleanup();
};
