#include "Test/gyroscope_test.h"

void GyroscopeTest::initTestCase(){
    init();
}

void GyroscopeTest::cleanupTestCase(){
    cleanup();
}

void GyroscopeTest::init(){
    cut_ = new Gyroscope();
}

void GyroscopeTest::cleanup(){
    delete cut_;
    cut_ = 0;
}
