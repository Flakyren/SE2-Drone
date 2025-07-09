#include "startlandbutton.h"

StartLandButton::StartLandButton(){}

StartLandButton::~StartLandButton() {}

void StartLandButton::startLandPressed(){
    emit sendStartLandSignal();
}
