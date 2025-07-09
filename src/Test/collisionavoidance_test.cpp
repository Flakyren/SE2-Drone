#include "Test/collisionavoidance_test.h"

void CollisionAvoidanceTest::initTestCase(){
    init();
}

void CollisionAvoidanceTest::cleanupTestCase(){
    cleanup();
}

void CollisionAvoidanceTest::init(){
    // Visionsensor
    VisionSensor VS1(1);
    VisionSensor VS2(2);
    VisionSensor VS3(3);
    VisionSensor VS4(4);

    // Infraredsensor
    InfraredSensor IS1(1);
    InfraredSensor IS2(2);
    InfraredSensor IS3(3);
    InfraredSensor IS4(4);

    // GpsAntenna
    GPSAntenna GPS;

    // Joystick Control
    JoystickControl JoystickHR(1);
    JoystickControl JoystickN(2);

    //Start Land Button
    StartLandButton startLandButton;

    // HandController
    HandController PSPcontroller(JoystickHR, JoystickN, startLandButton);

    // Radio
    RadioCommunication RDrone(PSPcontroller);

    cut_ = new CollisionAvoidance(nullptr, &VS1, &VS2, &VS3, &VS4, &IS1, &IS2, &IS3, &IS4, &RDrone, &GPS);
    //Mockups potentiell noch nötig?
}

void CollisionAvoidanceTest::cleanup(){
    delete cut_;
    cut_ = 0;
}
