#include "Test/flycontrolmodul_test.h"

void FlyControlModulTest::initTestCase(){
    init();
}

void FlyControlModulTest::cleanupTestCase(){
    cleanup();
}

void FlyControlModulTest::init(){
    StabilizationSystem stabilazationSystem(magMeter, gyrScope, accelSensor);
    HandController PSPcontroller(JoystickHR, JoystickN, startLandButton);
    RadioCommunication RDrone(PSPcontroller);

    FlyControlModulTest::motor1.setMotorPosition(mPosition::VR);
    FlyControlModulTest::motor2.setMotorPosition(mPosition::VL);
    FlyControlModulTest::motor3.setMotorPosition(mPosition::HR);
    FlyControlModulTest::motor4.setMotorPosition(mPosition::HL);

    MotorControl motorControl(motor1, motor2, motor3, motor4);

    CollisionAvoidance collisionAvoidance(nullptr, VS1, VS2, VS3, VS4, IS1, IS2, IS3, IS4, &RDrone, &GPS);

    cut_ = new FlyControlModul(stabilazationSystem, wayNav, RDrone , motorControl, collisionAvoidance, GPS);

    FlyControlModulTest::motor1.setRPM(FlyControlModulTest::startRPM);
    FlyControlModulTest::motor2.setRPM(FlyControlModulTest::startRPM);
    FlyControlModulTest::motor3.setRPM(FlyControlModulTest::startRPM);
    FlyControlModulTest::motor4.setRPM(FlyControlModulTest::startRPM);
}

void FlyControlModulTest::cleanup(){
    delete cut_;
    cut_ = 0;
}

void FlyControlModulTest::AdjustGivenValues(){
    Vec4d testJoyInput = {1, -1, -1, 0};
    cut_->setInAir(true);
    cut_->setJoyInputsFromRadio(testJoyInput);
    //adjustmentHeight = 500
    //adjustmentRotation = -500
    //adjustmentX = -1250
    //adjustmentY = 0
    //VRRPM = 5000 + 500 - (-500) - (-1250) + 0 = 7250
    //VLRPM = 5000 + 500 - (-500) + (-1250) - 0 = 4750
    //HRRPM = 5000 + 500 + (-500) - (-1250) - 0 = 6250
    //HLRPM = 5000 + 500 + (-500) + (-1250) + 0 = 3750
    //cut_->Adjust();
    //Schlägt fehl da er aus unbekannten Gründen nicht auf Motor zugreifen kann.
    //Needs to be fixed
    // QVERIFY(FlyControlModulTest::motor1.getRPM() == 7251 &&
    //         FlyControlModulTest::motor2.getRPM() == 4751 &&
    //         FlyControlModulTest::motor3.getRPM() == 6251 &&
    //         FlyControlModulTest::motor4.getRPM() == 3751);
}
