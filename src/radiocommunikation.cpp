#include "radiocommunikation.h"

RadioCommunication::RadioCommunication(HandController &PSPcontroller) {
    setSignalStrength(100);
    setCurrentState(0);
    connect(&PSPcontroller, &HandController::joyInputsChanged, this, &RadioCommunication::joyInputsFromHandController);
}

RadioCommunication::~RadioCommunication() {
    // destructor implementation
}
double RadioCommunication::getFrequency() {
    return frequency;
}

void RadioCommunication::setFrequency(double givenFrequency) {
    frequency = givenFrequency;
}

void RadioCommunication::receiving() {
    return;
}

// Input is "Data", not yet defined
void RadioCommunication::sendData() {
    return;
}

void RadioCommunication::setSignalStrength(double givenSignalStrength) {
    signalStrength = givenSignalStrength;
    emit changeSignalStrength(signalStrength);
}

double RadioCommunication::getSignalStrength() {
    return signalStrength;
}

void RadioCommunication::setCurrentState(int state){
    this->currentState = state;
    emit changeCurrentState(currentState);
}

int RadioCommunication::getCurrentState(){
    return currentState;
}

void RadioCommunication::buttonSendsDisconnect(){
    if(getCurrentState() == 4){
        emit stopWayNav();
    }else if(getCurrentState() == 3){
        emit stopHomeNav();
    }


    if(signalStrength)
    {
        setSignalStrength(0.0);
        if(!(currentState == 0)){
            emit FlyHome();
        }
        setCurrentState(2);
    }
    else{
        setSignalStrength(100.0);
        setCurrentState(0);
    }
}

void RadioCommunication::FlyHomeFromController(){
    if(signalStrength > 0.0 && currentState == 1){
        setCurrentState(3);
        emit FlyHome();
    }
}

void RadioCommunication::joyInputsFromHandController(Vec4d joyInputs){
    if(signalStrength > 0.0 && currentState == 1)
        emit setJoyInputsForFlyControl(joyInputs);
}

void RadioCommunication::getSaveWaypointSingal(){
    if(signalStrength > 0.0)
        emit sendWaypointSaveSignal();
}

void RadioCommunication::getFlyToWaypointsRadio(){
    if(signalStrength > 0.0 && currentState == 1){
        setCurrentState(4);
        emit sendFlyToWaypoints();
    }
}

void RadioCommunication::getStartLand(){
    if(signalStrength > 0.0 && (currentState == 1 || currentState == 0) )
        emit sendStartLand();
}

void RadioCommunication::getToggleRecordingFromHandController(){
    if(signalStrength > 0.0)
        emit sendRecordSignalToCamera();
}

