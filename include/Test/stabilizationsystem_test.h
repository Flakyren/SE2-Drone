#pragma once

#include <QObject>
#include <QTest>
#include "stabilizationsystem.h"

class StabilizationSystemTest : public QObject {
    Q_OBJECT

    StabilizationSystem * cut_; //Class under Test

public:
    explicit StabilizationSystemTest(QObject* parent = nullptr) : QObject(parent){}

private slots:

    //Executed by QtTest before and after test suite
    void initTestCase();
    void cleanupTestCase();

    //Executed by QtTest before and after each test
    void init();
    void cleanup();
};
