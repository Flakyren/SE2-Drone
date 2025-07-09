#include "display.h"

// Default constructor initializes display to off state
Display::Display() {
    isOn = false;
}

// Parameterized constructor initializes display to given state
Display::Display(bool givenIsOn) {
    isOn = givenIsOn;
}

Display::~Display(){}

// Getter for the display power status
bool Display::getIsOn() {
    return isOn;
}

// Setter for the display power status
void Display::setIsOn(bool givenIsOn) {
    isOn = givenIsOn;
}

// Toggles the power status of the display
void Display::togglePowerStatus() {
    isOn = !isOn;
}
