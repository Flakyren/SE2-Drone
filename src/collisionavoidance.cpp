#include"collisionavoidance.h"
#include <iostream>

CollisionAvoidance::CollisionAvoidance(QObject *parent, VisionSensor* VS1, VisionSensor* VS2, VisionSensor* VS3, VisionSensor* VS4, InfraredSensor* IS1, InfraredSensor* IS2, InfraredSensor* IS3, InfraredSensor* IS4, RadioCommunication* radio, GPSAntenna *gps) :
    QObject(parent),
    timer(new QTimer(this)),
    radio(radio),
    gps(gps)
{
    visionSensors.push_back(VS1);
    visionSensors.push_back(VS2);
    visionSensors.push_back(VS3);
    visionSensors.push_back(VS4);

    infraredSensors.push_back(IS1);
    infraredSensors.push_back(IS2);
    infraredSensors.push_back(IS3);
    infraredSensors.push_back(IS4);

    // Initialize the distance arrays with value 1
    for (int var = 0; var < 4; ++var) {
        this->distanceInfrared[var] = 1;
        this->distanceVision[var] = 1;
    }

    // Connect sensors to the corresponding slots
    connect(IS1, &InfraredSensor::infraredReadingUpdated, this, &CollisionAvoidance::updateInfraredReading1V);
    connect(IS2, &InfraredSensor::infraredReadingUpdated, this, &CollisionAvoidance::updateInfraredReading2R);
    connect(IS3, &InfraredSensor::infraredReadingUpdated, this, &CollisionAvoidance::updateInfraredReading3L);
    connect(IS4, &InfraredSensor::infraredReadingUpdated, this, &CollisionAvoidance::updateInfraredReading4D);

    connect(VS1, &VisionSensor::visionReadingUpdated, this, &CollisionAvoidance::updateVisionReading1V);
    connect(VS2, &VisionSensor::visionReadingUpdated, this, &CollisionAvoidance::updateVisionReading2R);
    connect(VS3, &VisionSensor::visionReadingUpdated, this, &CollisionAvoidance::updateVisionReading3L);
    connect(VS4, &VisionSensor::visionReadingUpdated, this, &CollisionAvoidance::updateVisionReading4D);

    // connecting Timeout-Signals with the triggered functions
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CollisionAvoidance::detectCollision);

    moveCheckDrone = new QTimer(this);
    connect(moveCheckDrone, &QTimer::timeout, this, &CollisionAvoidance::moveCheckDroneFunktion);

    // starting the timer for Collision detection
    timer->start(25);
}

CollisionAvoidance::~CollisionAvoidance() {
    delete timer;
}

void CollisionAvoidance::detectCollision() {
    for(int i = 1; i <= 4; i++){
        // Check sensor readings and trigger an emergency stop if a collision is detected
        if ((getInfraredSensorReadings(i) == 1) || (getVisionSensorReadings(i) == 1)) {
            emit emergencyStop(i);
            // Check if in WaypoinNav currently
            if(radio->getCurrentState() == 4 ){
                emit StopWayNav();
                emit StopNav();
                moveCheckDrone->start(10);
            }
            // Check if in HomeNav currently
            else if(radio->getCurrentState() == 3){
                emit StopNav();
                moveCheckDrone->start(10);
            }
        }
    }
}

//function for moving the drone in the desired direction depending on the sensor readings
void CollisionAvoidance::moveCheckDroneFunktion(){
    if(getInfraredSensorReadings(2) == 1)
        emit moveDroneX(1);
    else if(getInfraredSensorReadings(3) == 1)
        emit moveDroneX(-1);
    else if(getInfraredSensorReadings(4) == 1)
        emit moveDroneX(1);

    counter++;
    // stoping the timer for the correction and resuming the home navigation or waypoint navigation
    if(counter >= 50 && getInfraredSensorReadings(4) != 1 && getInfraredSensorReadings(2) != 1 && getInfraredSensorReadings(3) != 1){
        moveCheckDrone->stop();
        if(radio->getCurrentState() == 4)
            emit startFlyToWayNav();
        else if(radio->getCurrentState() == 3)
            emit startFlyHome();

        counter = 0;
    }
}
// Function to get the Sensor readings Updated:
int CollisionAvoidance::getInfraredSensorReadings(int ID){
    return distanceInfrared[ID];
}

int CollisionAvoidance::getVisionSensorReadings(int ID){
    return distanceVision[ID];
}

void CollisionAvoidance::setInfraredSensorReadings(int index, int reading) {
    distanceInfrared[index] = reading;
}

void CollisionAvoidance::setVisionSensorReadings(int index, int reading) {
    distanceVision[index] = reading;
}

void CollisionAvoidance::setCounter(int count) {
    counter = count;
}

void CollisionAvoidance::updateInfraredReading1V(int newReading) {
    distanceInfrared[0] = newReading;
}

void CollisionAvoidance::updateInfraredReading2R(int newReading) {
    distanceInfrared[1] = newReading;
}

void CollisionAvoidance::updateInfraredReading3L(int newReading) {
    distanceInfrared[2] = newReading;
}

void CollisionAvoidance::updateInfraredReading4D(int newReading) {
    distanceInfrared[3] = newReading;
}

void CollisionAvoidance::updateVisionReading1V(int newReading) {
    distanceVision[0] = newReading;
}

void CollisionAvoidance::updateVisionReading2R(int newReading) {
    distanceVision[1] = newReading;
}

void CollisionAvoidance::updateVisionReading3L(int newReading) {
    distanceVision[2] = newReading;
}

void CollisionAvoidance::updateVisionReading4D(int newReading) {
    distanceVision[3] = newReading;
}
