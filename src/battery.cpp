#include "battery.h"

//Initiiere Standard-Batterie im ausgeschalteten Zustand im vollaufgeladenen Zustand
Battery::Battery(){
    isOn = false;
    capacity = 100;
}

Battery::Battery(bool givenIsOn, double givenCapacity) {
    isOn = givenIsOn;
    capacity = givenCapacity;
}

double Battery::getCapacity(){
    return capacity;
}

bool Battery::getIsOn(){
    return isOn;
}

void Battery::setIsOn(bool givenIsOn){
    isOn = givenIsOn;
}

void Battery::setCapacity(double givenCapacity){
    capacity = givenCapacity;
}

// Schaltet die Batterie an bzw aus.
void Battery::togglePowerStatus(){
    isOn = !isOn;
}
