#include <QtTest/QTest>
#include "Test/testrunner.h"
#include "Test/motorcontrol_test.h"
#include "Test/collisionavoidance_test.h"
#include "Test/display_test.h"
#include "Test/flycontrolmodul_test.h"
#include "Test/gpsantenna_test.h"
#include "Test/gyroscope_test.h"
#include "Test/homepointnavigation_test.h"
#include "Test/radiocommunication_test.h"
#include "Test/stabilizationsystem_test.h"
#include "Test/waypointnavigation_test.h"

int main(int argc, char**argv) {
    int status = 0;

    MotorControlTest motorControlTest;
    status = QTest::qExec(&motorControlTest, argc, argv);
    runTests<CollisionAvoidanceTest>(argc, argv, &status);
    runTests<DisplayTest>(argc, argv, &status);
    runTests<FlyControlModulTest>(argc, argv, &status);
    runTests<GPSAntennaTest>(argc, argv, &status);
    runTests<GyroscopeTest>(argc, argv, &status);
    runTests<HomepointNavigationTest>(argc, argv, &status);
    runTests<RadioCommunicationTest>(argc, argv, &status);
    runTests<StabilizationSystemTest>(argc, argv, &status);
    runTests<WaypointNavigationTest>(argc, argv, &status);

    return status;
}
