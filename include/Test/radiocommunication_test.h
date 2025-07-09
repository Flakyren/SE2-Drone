#pragma once

#include <QObject>
#include <QTest>
#include "radiocommunikation.h"

class RadioCommunicationTest : public QObject {
    Q_OBJECT

    RadioCommunication * cut_; //Class under Test

public:
    explicit RadioCommunicationTest(QObject* parent = nullptr) : QObject(parent){}

private slots:

    //Executed by QtTest before and after test suite
    void initTestCase();
    void cleanupTestCase();

    //Executed by QtTest before and after each test
    void init();
    void cleanup();
};
