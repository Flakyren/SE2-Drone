#include "handController.h"
// Hanndling Inputs from Controler and Sending them to the Radio
HandController::HandController(JoystickControl& hrJoystick, JoystickControl& nJoystick, StartLandButton& startLandButton)  : startLandButton(startLandButton), joystickHR(hrJoystick), joystickN(nJoystick) {
    connect(&joystickHR, &JoystickControl::sendXToHandController, this, &HandController::getXFromjoystickHR);
    connect(&joystickHR, &JoystickControl::sendYToHandController, this, &HandController::getYFromjoystickHR);

    connect(&joystickN, &JoystickControl::sendXToHandController, this, &HandController::getXFromjoystickN);
    connect(&joystickN, &JoystickControl::sendYToHandController, this, &HandController::getYFromjoystickN);

    connect(&startLandButton, &StartLandButton::sendStartLandSignal, this, &HandController::getStartLand);
}

HandController::~HandController() {}

void HandController::setJoyInputs(Vec4d Inputs){
    joyInputs = Inputs;
}

Vec4d HandController::getJoyInputs(){
    return joyInputs;
}

void HandController::FlyBackSignalFromUI(){
    emit FlybackSignalForRadio();
}

void HandController::getXFromjoystickHR(double x){
    joyInputs.y = x;
    emit joyInputsChanged(joyInputs);
}

void HandController::getYFromjoystickHR(double y){
    joyInputs.x = y;
    emit joyInputsChanged(joyInputs);
}

void HandController::getXFromjoystickN(double x){
    joyInputs.w = x;
    emit joyInputsChanged(joyInputs);
}

void HandController::getYFromjoystickN(double y){
    joyInputs.z = y;
    emit joyInputsChanged(joyInputs);
}


void HandController::getSaveWaypointSignal(){
    emit sendSaveWaypointSignalToRadio();
}

void HandController::getFlyAllWaypoints(){
    emit sendFlyToWaypointsRadio();
}

void HandController::getStartLand(){
    emit sendStartLand();
}

void HandController::getToggleRecording(){
    emit sendRecordSignalToRadio();
}
