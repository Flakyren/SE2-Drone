#include "Test/gpsantenna_test.h"

void GPSAntennaTest::initTestCase(){
    init();
}

void GPSAntennaTest::cleanupTestCase(){
    cleanup();
}

void GPSAntennaTest::init(){
    cut_ = new GPSAntenna();
}

void GPSAntennaTest::cleanup(){
    delete cut_;
    cut_ = 0;
}
