#include "Test/waypointnavigation_test.h"
void WaypointNavigationTest::initTestCase(){
    init();
}

void WaypointNavigationTest::cleanupTestCase(){
    cleanup();
}

void WaypointNavigationTest::init(){
    cut_ = new WaypointNavigation();
}

void WaypointNavigationTest::cleanup(){
    delete cut_;
    cut_ = 0;
}
