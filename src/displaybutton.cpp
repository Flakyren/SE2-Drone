#include "displaybutton.h"

// Default constructor
DisplayButton::DisplayButton() {}

// Parameterized constructor to initialize the button state and position
DisplayButton::DisplayButton(bool givenIsOn, double x, double y) {
    isOn = givenIsOn;
    posX = x;
    posY = y;
}

// Setter for the button state
void DisplayButton::setIsOn(bool givenIsOn) {
    isOn = givenIsOn;
}

// Setter for the button's X position
void DisplayButton::setPosX(double x) {
    posX = x;
}

// Setter for the button's Y position
void DisplayButton::setPosY(double y) {
    posY = y;
}

// Getter for the button state
bool DisplayButton::getIsOn() {
    return isOn;
}

// Getter for the button's X position
double DisplayButton::getPosX() {
    return posX;
}

// Getter for the button's Y position
double DisplayButton::getPosY() {
    return posY;
}
