#include "led.h"

LED::LED() {}

LED::~LED() {}

int LED::getGlow() {
    return glow;
}

void LED::setGlow(QString color) {
    emit changeLEDInUI(color);
}
