#pragma once

#include "switchbutton.h"

class DisplayButton: public SwitchButton {

public:
    DisplayButton();
    DisplayButton(bool givenIsOn, double x, double y);
    ~DisplayButton();

    void setIsOn(bool givenIsOn);
    void setPosX(double x);
    void setPosY(double y);

    bool getIsOn();
    double getPosX();
    double getPosY();

private:
    bool isOn;
    double posX;
    double posY;
};
