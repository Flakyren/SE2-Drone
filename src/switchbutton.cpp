#include "switchbutton.h"

SwitchButton::SwitchButton() {}

SwitchButton::~SwitchButton() {}

void SwitchButton::setPushed(bool status){
    pushed = status;
}

bool SwitchButton::getPushed(){
    return pushed;
}
