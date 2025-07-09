#include "Test/display_test.h"

void DisplayTest::initTestCase(){
    init();
}

void DisplayTest::cleanupTestCase(){
    cleanup();
}

void DisplayTest::init(){
    cut_ = new Display();
}

void DisplayTest::cleanup(){
    delete cut_;
    cut_ = 0;
}
