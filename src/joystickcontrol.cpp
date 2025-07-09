#include "joystickcontrol.h"

JoystickControl::JoystickControl(QObject* parent)
    : QObject(parent), joystickID(0)
{
}

JoystickControl::~JoystickControl()
{
}

JoystickControl::JoystickControl(int joystickID, QObject* parent)
    : QObject(parent), joystickID(joystickID)
{
}

double JoystickControl::getPosX() const
{
    return posX;
}

double JoystickControl::getPosY() const
{
    return posY;
}

// Get Reading from UI and Send Readings to HandController
void JoystickControl::setPosX(double reading)
{
    posX = reading;
    emit sendXToHandController(reading);
}

// Get Reading from UI and Send Readings to HandController
void JoystickControl::setPosY(double reading)
{
    posY = reading;
    emit sendYToHandController(reading);
}
