#pragma once

#include <QObject>
#include <QTest>
#include "waypointnavigation.h"

class WaypointNavigationTest : public QObject {
    Q_OBJECT

    WaypointNavigation * cut_; //Class under Test

public:
    explicit WaypointNavigationTest(QObject* parent = nullptr) : QObject(parent){}

private slots:

    //Executed by QtTest before and after test suite
    void initTestCase();
    void cleanupTestCase();

    //Executed by QtTest before and after each test
    void init();
    void cleanup();
};
