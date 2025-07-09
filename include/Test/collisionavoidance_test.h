#pragma once

#include <QObject>
#include <QTest>
#include "collisionavoidance.h"

class CollisionAvoidanceTest : public QObject {
    Q_OBJECT

    CollisionAvoidance * cut_; //Class under Test

public:
    explicit CollisionAvoidanceTest(QObject* parent = nullptr) : QObject(parent){}

private slots:

    //Executed by QtTest before and after test suite
    void initTestCase();
    void cleanupTestCase();

    //Executed by QtTest before and after each test
    void init();
    void cleanup();
};
