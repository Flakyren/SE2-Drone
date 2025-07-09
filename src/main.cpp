#include "collisionavoidance.h"
#include "flycontrolmodul.h"
#include <QApplication>
#include <QGraphicsScene>
#include "UI/drone.h"
#include "UI/obstacle.h"
#include "UI/mainwindow.h"
#include "led.h"
#include "radiocommunikation.h"
#include "homepointnavigation.h"
#include "handController.h"
#include "gpsantenna.h"
#include "gpsNavigation.h"
#include "waypointnavigation.h"
#include "startlandbutton.h"
#include <QDebug>
#include "camera.h"


#define CHECK_CONNECT(sender, signal, receiver, slot) \
if (!QObject::connect(sender, signal, receiver, slot)) { \
        qDebug() << "Connection failed:" << #sender << #signal << "to" << #receiver << #slot; \
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialisierung aller Objekte

    // Motoren
    Motor M1(mPosition::VR);
    Motor M2(mPosition::VL);
    Motor M3(mPosition::HR);
    Motor M4(mPosition::HL);

    //LEDs
    LED LED1;
    LED LED2;
    LED LED3;
    LED LED4;

    // MotorControll
    MotorControl motorControl(M1, M2, M3, M4);

    // Visionsensor
    VisionSensor VS1(1);
    VisionSensor VS2(2);
    VisionSensor VS3(3);
    VisionSensor VS4(4);

    // Infraredsensor
    InfraredSensor IS1(1);
    InfraredSensor IS2(2);
    InfraredSensor IS3(3);
    InfraredSensor IS4(4);

    // GpsAntenna
    GPSAntenna GPS;

    // Joystick Control
    JoystickControl JoystickHR(1);
    JoystickControl JoystickN(2);

    //Start Land Button
    StartLandButton startLandButton;

    // HandController
    HandController PSPcontroller(JoystickHR, JoystickN, startLandButton);

    // Radio
    RadioCommunication RDrone(PSPcontroller);

    // HomepointNav
    HomepointNavigation homepointNav;
    WaypointNavigation wayNav;

    // Gps Nav
    GPSNavigation gpsNav;

    // Colision Avoidance
    CollisionAvoidance collisionAvoidance(nullptr, &VS1, &VS2, &VS3, &VS4, &IS1, &IS2, &IS3, &IS4, &RDrone, &GPS);
    //Stabilization Sensor
    AccelSensor* accelSensor = new AccelSensor();
    Magnetometer* magMeter = new Magnetometer();
    Gyroscope* gyrScope = new Gyroscope();
    //Stabilizationcontrol
    StabilizationSystem stabilazationSystem(magMeter, gyrScope, accelSensor);

    // FlycontrolModul
    FlyControlModul flyControlModul(stabilazationSystem, wayNav, RDrone , motorControl, collisionAvoidance, GPS);

    Camera camera;

    // Simulation
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsScene *heightScene = new QGraphicsScene();
    Drone *drone = new Drone();
    scene->addItem(drone);
    QList<Obstacle*> obstacles;
    obstacles.append(new Obstacle(100, 100, 30));
    obstacles.append(new Obstacle(-200, 150, 20));
    obstacles.append(new Obstacle(300, -200, 15));
    obstacles.append(new Obstacle(-400, 250, 25));
    obstacles.append(new Obstacle(500, -300, 30));
    for (Obstacle *obstacle : obstacles) {
        scene->addItem(obstacle);
    }

    // MainWindow
    MainWindow w(scene, heightScene, drone, obstacles);
    w.show();

    CHECK_CONNECT(drone, &Drone::rotorRPMChanged, &w, &MainWindow::updateSlider);

    // UI to Logic
    CHECK_CONNECT(&w, &MainWindow::setGyroscopeValues, gyrScope, &Gyroscope::getGyroscopeValues);
    CHECK_CONNECT(&w, &MainWindow::setAccelerationValues, accelSensor, &AccelSensor::getAccelarationValues);
    CHECK_CONNECT(&w, &MainWindow::setMagnetometerValues, magMeter, &Magnetometer::getMagnetometerValues);
    CHECK_CONNECT(&w, &MainWindow::joystickRotation, &JoystickHR, &JoystickControl::setPosX);
    CHECK_CONNECT(&w, &MainWindow::joystickHeight, &JoystickHR, &JoystickControl::setPosY);
    CHECK_CONNECT(&w, &MainWindow::joystickLeftRight, &JoystickN, &JoystickControl::setPosX);
    CHECK_CONNECT(&w, &MainWindow::joystickFrontBack, &JoystickN, &JoystickControl::setPosY);
    CHECK_CONNECT(&w, &MainWindow::infraredReadingsV, &IS1, &InfraredSensor::setReadings);
    CHECK_CONNECT(&w, &MainWindow::infraredReadingsL, &IS3, &InfraredSensor::setReadings);
    CHECK_CONNECT(&w, &MainWindow::infraredReadingsR, &IS2, &InfraredSensor::setReadings);
    CHECK_CONNECT(&w, &MainWindow::infraredReadingsD, &IS4, &InfraredSensor::setReadings);
    CHECK_CONNECT(&w, &MainWindow::infraredReadingsV, &VS1, &VisionSensor::setReading);
    CHECK_CONNECT(&w, &MainWindow::infraredReadingsL, &VS3, &VisionSensor::setReading);
    CHECK_CONNECT(&w, &MainWindow::infraredReadingsR, &VS2, &VisionSensor::setReading);
    CHECK_CONNECT(&w, &MainWindow::infraredReadingsD, &VS4, &VisionSensor::setReading);
    CHECK_CONNECT(&w, &MainWindow::sendGPStoGPSAntenna, &GPS, &GPSAntenna::gpsDataFromUI);
    CHECK_CONNECT(&w, &MainWindow::sendSignalLost, &RDrone, &RadioCommunication::buttonSendsDisconnect);
    CHECK_CONNECT(&w, &MainWindow::flybackSingalForController, &PSPcontroller, &HandController::FlyBackSignalFromUI);
    CHECK_CONNECT(&w, &MainWindow::sendLandTakeOff, &startLandButton, &StartLandButton::startLandPressed);
    CHECK_CONNECT(&w, &MainWindow::setSaveWaypointSignalToHandController, &PSPcontroller, &HandController::getSaveWaypointSignal);
    CHECK_CONNECT(&w, &MainWindow::FlyAllWaypoints, &PSPcontroller, &HandController::getFlyAllWaypoints);
    CHECK_CONNECT(&w, &MainWindow::toggleRecording, &PSPcontroller, &HandController::getToggleRecording);

    // Logic to UI
    CHECK_CONNECT(&camera, &Camera::updateTimer, &w, &MainWindow::getCurrentRecordTimer);
    CHECK_CONNECT(&wayNav, &WaypointNavigation::deleteWinUI, &w, &MainWindow::getdeleteWinUI);
    CHECK_CONNECT(&flyControlModul, &FlyControlModul::sendInAirData, &w, &MainWindow::getInAirDataFromLogic);
    CHECK_CONNECT(&RDrone, &RadioCommunication::changeCurrentState, &w, &MainWindow::getCurrentState);
    CHECK_CONNECT(&RDrone, &RadioCommunication::changeSignalStrength, &w, &MainWindow::getSignalstrength);
    CHECK_CONNECT(&flyControlModul, &FlyControlModul::rotateDrone, &w, &MainWindow::rotateDrone);
    CHECK_CONNECT(&flyControlModul, &FlyControlModul::moveDrone, &w, &MainWindow::moveDrone);
    CHECK_CONNECT(&M1, &Motor::setRotorRPMUI, &w, &MainWindow::setRotorRPMFromLogic);
    CHECK_CONNECT(&M2, &Motor::setRotorRPMUI, &w, &MainWindow::setRotorRPMFromLogic);
    CHECK_CONNECT(&M3, &Motor::setRotorRPMUI, &w, &MainWindow::setRotorRPMFromLogic);
    CHECK_CONNECT(&M4, &Motor::setRotorRPMUI, &w, &MainWindow::setRotorRPMFromLogic);

    CHECK_CONNECT(&LED1, &LED::changeLEDInUI, &w, &MainWindow::changeLED);
    CHECK_CONNECT(&LED2, &LED::changeLEDInUI, &w, &MainWindow::changeLED);
    CHECK_CONNECT(&LED3, &LED::changeLEDInUI, &w, &MainWindow::changeLED);
    CHECK_CONNECT(&LED4, &LED::changeLEDInUI, &w, &MainWindow::changeLED);

    // Logic zu Logic
    CHECK_CONNECT(&gpsNav, &GPSNavigation::sendDataToFlyControl, &flyControlModul, &FlyControlModul::getDataFromGPSNav);
    CHECK_CONNECT(&GPS, &GPSAntenna::sendDataToHomePoint, &homepointNav, &HomepointNavigation::getGPSData);
    CHECK_CONNECT(&GPS, &GPSAntenna::sendDataToWayPoint, &wayNav, &WaypointNavigation::getGPSData);
    CHECK_CONNECT(&homepointNav, &HomepointNavigation::askForGPSData, &GPS, &GPSAntenna::getDataRequest);
    CHECK_CONNECT(&homepointNav, &HomepointNavigation::flyMeTo, &gpsNav, &GPSNavigation::getFlyMeToSignal);
    CHECK_CONNECT(&homepointNav, &HomepointNavigation::homepointReached, &flyControlModul, &FlyControlModul::startLandInitiate);
    CHECK_CONNECT(&wayNav, &WaypointNavigation::flyToWaypoint, &gpsNav, &GPSNavigation::getFlyMeToSignal);
    CHECK_CONNECT(&wayNav, &WaypointNavigation::askForGPSData, &GPS, &GPSAntenna::getDataRequest);
    CHECK_CONNECT(&wayNav, &WaypointNavigation::lastWaypointReached, &flyControlModul, &FlyControlModul::gotlastWaypointReached);

    CHECK_CONNECT(&flyControlModul, &FlyControlModul::LED, &LED1, &LED::setGlow);
    CHECK_CONNECT(&flyControlModul, &FlyControlModul::LED, &LED2, &LED::setGlow);
    CHECK_CONNECT(&flyControlModul, &FlyControlModul::LED, &LED3, &LED::setGlow);
    CHECK_CONNECT(&flyControlModul, &FlyControlModul::LED, &LED4, &LED::setGlow);


    CHECK_CONNECT(&PSPcontroller, &HandController::FlybackSignalForRadio, &RDrone, &RadioCommunication::FlyHomeFromController);
    CHECK_CONNECT(&PSPcontroller, &HandController::sendSaveWaypointSignalToRadio, &RDrone, &RadioCommunication::getSaveWaypointSingal);
    CHECK_CONNECT(&PSPcontroller, &HandController::sendFlyToWaypointsRadio, &RDrone, &RadioCommunication::getFlyToWaypointsRadio);
    CHECK_CONNECT(&PSPcontroller, &HandController::sendRecordSignalToRadio, &RDrone, &RadioCommunication::getToggleRecordingFromHandController);
    CHECK_CONNECT(&PSPcontroller, &HandController::sendStartLand, &RDrone, &RadioCommunication::getStartLand);
    CHECK_CONNECT(&collisionAvoidance, &CollisionAvoidance::StopWayNav, &wayNav, &WaypointNavigation::getStopTimer);
    CHECK_CONNECT(&collisionAvoidance, &CollisionAvoidance::startFlyToWayNav, &wayNav, &WaypointNavigation::getStartTimer);
    CHECK_CONNECT(&collisionAvoidance, &CollisionAvoidance::StopNav, &flyControlModul, &FlyControlModul::stopNavigation);
    CHECK_CONNECT(&collisionAvoidance, &CollisionAvoidance::moveDroneX, &flyControlModul, &FlyControlModul::getMoveDroneX);
    CHECK_CONNECT(&collisionAvoidance, &CollisionAvoidance::startFlyHome, &flyControlModul, &FlyControlModul::startNavigation);
    CHECK_CONNECT(&RDrone, &RadioCommunication::FlyHome, &homepointNav, &HomepointNavigation::getFlyBackSignal);
    CHECK_CONNECT(&RDrone, &RadioCommunication::sendFlyToWaypoints, &wayNav, &WaypointNavigation::getFlyBackSignal);
    CHECK_CONNECT(&RDrone, &RadioCommunication::stopWayNav, &wayNav, &WaypointNavigation::getStopTimer);
    CHECK_CONNECT(&RDrone, &RadioCommunication::sendWaypointSaveSignal, &wayNav, &WaypointNavigation::getSaveWaypointSignal);
    CHECK_CONNECT(&RDrone, &RadioCommunication::stopWayNav, &flyControlModul, &FlyControlModul::stopNavigation);
    CHECK_CONNECT(&RDrone, &RadioCommunication::stopHomeNav, &flyControlModul, &FlyControlModul::stopNavigation);
    CHECK_CONNECT(&RDrone, &RadioCommunication::sendStartLand, &flyControlModul, &FlyControlModul::startLandInitiate);
    CHECK_CONNECT(&RDrone, &RadioCommunication::sendRecordSignalToCamera, &camera, &Camera::getToggleRecordingFromRadio);


    return a.exec();
}
