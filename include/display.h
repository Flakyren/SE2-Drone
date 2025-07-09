#pragma once

class Display
{
public:
    Display();
    Display(bool givenIsOn);
    ~Display();

    bool getIsOn();
    void setIsOn(bool givenIsOn);

    void togglePowerStatus();

private:
    bool isOn;
};
