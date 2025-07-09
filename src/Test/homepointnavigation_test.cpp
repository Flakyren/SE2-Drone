#include "Test/homepointnavigation_test.h"

void HomepointNavigationTest::initTestCase(){
    init();
}

void HomepointNavigationTest::cleanupTestCase(){
    cleanup();
}

void HomepointNavigationTest::init(){
    cut_ = new HomepointNavigation();
}

void HomepointNavigationTest::cleanup(){
    delete cut_;
    cut_ = 0;
}
