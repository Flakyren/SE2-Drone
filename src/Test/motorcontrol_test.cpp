#include "Test/motorcontrol_test.h"

void MotorControlTest::initTestCase(){
    init();
}

void MotorControlTest::cleanupTestCase(){
    cleanup();
}

void MotorControlTest::init(){
    cut_ = new MotorControl();
    cut_->addMotor(MotorControlTest::motor1);
    cut_->addMotor(MotorControlTest::motor2);
    cut_->addMotor(MotorControlTest::motor3);
    MotorControlTest::motor1.setMotorPosition(mPosition::VL);
    MotorControlTest::motor2.setMotorPosition(mPosition::VR);
    MotorControlTest::motor3.setMotorPosition(mPosition::HL);
    //Motor-Mockup für setRPM noch machen
    MotorControlTest::motor1.setRPM(MotorControlTest::startRPM);
    MotorControlTest::motor2.setRPM(MotorControlTest::startRPM);
    MotorControlTest::motor3.setRPM(MotorControlTest::startRPM);
}

void MotorControlTest::cleanup(){
    delete cut_;
    cut_ = 0;
}

void MotorControlTest::getMotorByPosition3(){
    Motor * testMotor = cut_->getMotorByPosition(mPosition::VR);
    QVERIFY(testMotor->getMotorPosition() == mPosition::VR);
}

void MotorControlTest::getMotorByPositionInvalidPosition(){
    Motor * testMotor = cut_->getMotorByPosition(mPosition::HR);
    QVERIFY(testMotor == NULL);
}

void MotorControlTest::setMotorRPMPosition3(){
    cut_->setMotorRPM(MotorControlTest::givenTestRPM, mPosition::VR);
    QVERIFY(MotorControlTest::motor2.getRPM() == givenTestRPM);
}

void MotorControlTest::setMotorRPMInvalidPosition(){
    cut_->setMotorRPM(MotorControlTest::givenTestRPM, mPosition::HR);
    QVERIFY(MotorControlTest::motor2.getRPM() == MotorControlTest::startRPM);
}

void MotorControlTest::setAllRPMTest(){
    cut_->setAllRPM(MotorControlTest::givenTestRPM);
    QVERIFY(MotorControlTest::motor1.getRPM() == givenTestRPM &&
            MotorControlTest::motor2.getRPM() == givenTestRPM &&
            MotorControlTest::motor3.getRPM() == givenTestRPM);
}


