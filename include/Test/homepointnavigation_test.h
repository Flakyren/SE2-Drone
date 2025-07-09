#pragma once

#include <QObject>
#include <QTest>
#include "homepointnavigation.h"

class HomepointNavigationTest : public QObject {
    Q_OBJECT

    HomepointNavigation * cut_; //Class under Test

public:
    explicit HomepointNavigationTest(QObject* parent = nullptr) : QObject(parent){}

private slots:

    //Executed by QtTest before and after test suite
    void initTestCase();
    void cleanupTestCase();

    //Executed by QtTest before and after each test
    void init();
    void cleanup();
};
