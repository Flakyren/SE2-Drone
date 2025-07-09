#pragma once

class Battery
{
public:
    Battery();
    Battery(bool givenIsOn, double givenCapacity);
    ~Battery();

    double getCapacity();
    bool getIsOn();

    void setIsOn(bool givenIsOn);
    void setCapacity(double givenCapacity);

    void togglePowerStatus();

private:
    bool isOn;
    double capacity;
};
