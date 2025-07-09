#include "Test/stabilizationsystem_test.h"

void StabilizationSystemTest::initTestCase(){
    init();
}

void StabilizationSystemTest::cleanupTestCase(){
    cleanup();
}

void StabilizationSystemTest::init(){
    //Stabilization Sensor
    AccelSensor* accelSensor = new AccelSensor();
    Magnetometer* magMeter = new Magnetometer();
    Gyroscope* gyrScope = new Gyroscope();

    cut_ = new StabilizationSystem(magMeter, gyrScope, accelSensor);

    //Mockups benötigt!
}

void StabilizationSystemTest::cleanup(){
    delete cut_;
    cut_ = 0;
}
