#pragma once

#include <QObject>
#include <QTest>
#include "display.h"

class DisplayTest : public QObject {
    Q_OBJECT

    Display * cut_; //Class under Test

public:
    explicit DisplayTest(QObject* parent = nullptr) : QObject(parent){}

private slots:

    //Executed by QtTest before and after test suite
    void initTestCase();
    void cleanupTestCase();

    //Executed by QtTest before and after each test
    void init();
    void cleanup();
};
