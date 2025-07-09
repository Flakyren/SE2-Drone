#pragma once

class SwitchButton
{
public:
    SwitchButton();
    ~SwitchButton();

    void setPushed(bool status);
    bool getPushed();

private:
    bool pushed;
};
