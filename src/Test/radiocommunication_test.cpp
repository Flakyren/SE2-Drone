#include "Test/radiocommunication_test.h"
void RadioCommunicationTest::initTestCase(){
    init();
}

void RadioCommunicationTest::cleanupTestCase(){
    cleanup();
}

void RadioCommunicationTest::init(){
    // Joystick Control
    JoystickControl JoystickHR(1);
    JoystickControl JoystickN(2);

    //Start Land Button
    StartLandButton startLandButton;

    // HandController
    HandController PSPcontroller(JoystickHR, JoystickN, startLandButton);

    cut_ = new RadioCommunication(PSPcontroller);
    //Mockups benätigt!
}

void RadioCommunicationTest::cleanup(){
    delete cut_;
    cut_ = 0;
}
