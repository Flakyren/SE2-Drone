#include "flycontrolmodul.h"
#include "iostream"

int const flyOnSpotRPM = 5000; //RPM at which the drone should hover
int const vMax = 70; // maximum km/h, used for simplified speed calculation

// Konstruktor
FlyControlModul::FlyControlModul(StabilizationSystem &stabilizationSystem, WaypointNavigation &wayNav, RadioCommunication &radio, MotorControl &motors, CollisionAvoidance &collisionAvoid, GPSAntenna &GPS)
    :
    inAir(false),
    currentSpeed(0.0),
    wayNav(&wayNav),
    motors(&motors),
    collisionAvoid(&collisionAvoid),
    stabilizationSystem(&stabilizationSystem),
    radio(&radio),
    gps(&GPS)

{
    //connecting timer with the functions and starting them
    checkLED = new QTimer(this);
    connect(checkLED, &QTimer::timeout, this, &FlyControlModul::checkLEDFunktion);
    checkLED->start();

    getControlInputsTimer = new QTimer(this);
    connect(getControlInputsTimer, &QTimer::timeout, this, &FlyControlModul::getControlInputs);

    startTimer = new QTimer(this);
    connect(startTimer, &QTimer::timeout, this, &FlyControlModul::checkStart);

    landTimer = new QTimer(this);
    connect(landTimer, &QTimer::timeout, this, &FlyControlModul::checkLand);

    moveToPosTimer = new QTimer(this);
    connect(moveToPosTimer, &QTimer::timeout, this, &FlyControlModul::flyBackTimerFunktion);


    connect(&radio, &RadioCommunication::setJoyInputsForFlyControl, this, &FlyControlModul::setJoyInputsFromRadio);
    getControlInputsTimer->start(30);
}

// Destruktor
FlyControlModul::~FlyControlModul() {
    delete getControlInputsTimer;
    delete checkLED;
    delete startTimer;
    delete landTimer;
    delete moveToPosTimer;
}

double FlyControlModul::getCurrenSpeed(){
    return currentSpeed;
}

bool FlyControlModul::getInAir(){
    return inAir;
}

void FlyControlModul::setInAir(bool var){
    inAir = var;
    emit sendInAirData(inAir);
}

void FlyControlModul::setCurrentSpeed(double givenCurrentSpeed){
    currentSpeed = givenCurrentSpeed;
}

// Starten der Drohne
void FlyControlModul::Start() {
    motors->setAllRPM(flyOnSpotRPM + 500);
}

// Landen der Drohne
void FlyControlModul::Land() {
    motors->setAllRPM(4500);
}

void FlyControlModul::Adjust() {
    if(inAir){
        //the Inputs are simplified and reach from -1 to 1
        int adjustmentHeight = 500 * joyInputs.x;
        int adjustmentRotation = 500 * joyInputs.y;
        int adjustmentX = 1250 * joyInputs.z;
        int adjustmentY = 1250 * joyInputs.w;
        //Calculation the RPM for every Motor
        Vec4d mRPMs;
        mRPMs.w = flyOnSpotRPM + adjustmentHeight - adjustmentX - adjustmentY + adjustmentRotation; //the RPM for the front right motor
        mRPMs.x = flyOnSpotRPM + adjustmentHeight - adjustmentX + adjustmentY - adjustmentRotation; //the RPM for the front left motor
        mRPMs.y = flyOnSpotRPM + adjustmentHeight + adjustmentX - adjustmentY - adjustmentRotation; //the RPM for the back right motor
        mRPMs.z = flyOnSpotRPM + adjustmentHeight + adjustmentX + adjustmentY + adjustmentRotation; //the RPM for the back left motor
        //checking if any adjustments are needed and return the RPM with the adjustment if needed
        mRPMs = stabilizationSystem->stabilize(mRPMs);
        //setting the RPM for every motor
        motors->setMotorRPM(mRPMs.w, mPosition::VR);
        motors->setMotorRPM(mRPMs.x, mPosition::VL);
        motors->setMotorRPM(mRPMs.y, mPosition::HR);
        motors->setMotorRPM(mRPMs.z, mPosition::HL);
    }
    //calculateSpeed() funktion possible here if needed
}

//triggered function for when the obstacle detections notices something
//sets all rpm on the emergency stop
void FlyControlModul::handleEmergencyStop(int crashID){
    switch (crashID) {
    case 1: while(getCurrenSpeed() != 0){
            motors->setMotorRPM(9000, mPosition::VR);  // sensor vorne
            motors->setMotorRPM(9000, mPosition::VL);
            motors->setMotorRPM(4000, mPosition::HR);
            motors->setMotorRPM(4000, mPosition::HL);
            }
            motors->setAllRPM(flyOnSpotRPM);
            break;
    case 2: while(getCurrenSpeed() != 0){
            motors->setMotorRPM(9000, mPosition::VR);  // sensor rechts
            motors->setMotorRPM(4000, mPosition::VL);
            motors->setMotorRPM(9000, mPosition::HR);
            motors->setMotorRPM(4000, mPosition::HL);
            }
            motors->setAllRPM(flyOnSpotRPM);
            break;
    case 3: while(getCurrenSpeed() != 0){
            motors->setMotorRPM(4000, mPosition::VR);  // sesor links
            motors->setMotorRPM(9000, mPosition::VL);
            motors->setMotorRPM(4000, mPosition::HR);
            motors->setMotorRPM(9000, mPosition::HL);
            }
            motors->setAllRPM(flyOnSpotRPM);
            break;
    case 4:
            motors->setAllRPM(flyOnSpotRPM);
            break;
    default:
            break;
    }
    setCurrentSpeed(0);
}

void FlyControlModul::getMoveDroneX(int move){
    qreal stepY = 0;
    emit moveDrone(move, stepY);
}

//simplified calculation of the speed based on the RPM
void FlyControlModul::calculateSpeed(){
    double speed;
    double averageRPM = (motors->getMotorByPosition(mPosition::VR)->getRPM() +
                        motors->getMotorByPosition(mPosition::VL)->getRPM() +
                        motors->getMotorByPosition(mPosition::HR)->getRPM() +
                        motors->getMotorByPosition(mPosition::HL)->getRPM()) / 4;
    if (averageRPM > 5000) {
        speed = vMax/5000 * (averageRPM - 4000);
    } else {
        speed = 0;
    }
    setCurrentSpeed(speed);

}

//Initiating the land or start sequenz based on the curren statsu
void FlyControlModul::startLandInitiate(){
    if(inAir){
        setInAir(false);
        if(radio->getSignalStrength() > 10.0)
            radio->setCurrentState(0);
        else
            radio->setCurrentState(2);
        Land();
        wayNav->getSignalLanded();
        landTimer->start(20);
    } else {
        Start();
        startTimer->start(20);
        radio->setCurrentState(1);
        getControlInputsTimer->start(30);
    }
}

// Getting Target GPS position from GPSNav
void FlyControlModul::getDataFromGPSNav(Vec3d destinationPosition){
    targetPosition.x = destinationPosition.x;
    targetPosition.y = destinationPosition.y;
    getControlInputsTimer->stop();
    motors->setMotorRPM(3750, mPosition::VR);
    motors->setMotorRPM(3750, mPosition::VL);
    motors->setMotorRPM(6250, mPosition::HR);
    motors->setMotorRPM(6250, mPosition::HL);
    moveToPosTimer->start(16);
}

void FlyControlModul::flyBackTimerFunktion(){

    Vec3d currentPosition = gps->getGPSPosition();

    // get drone delta
    int deltaX = targetPosition.x - currentPosition.x;
    int deltaY = targetPosition.y - currentPosition.y;

    // set drone rotation to target
    int targetRotation = calcRotationToPosition(deltaX, deltaY);
    emit rotateDrone(targetRotation+180);

    // calc distance
    int distance = qSqrt(deltaX * deltaX + deltaY * deltaY);

    // distance under 5 (target reached)
    if (distance < 5) { // Drohne hat die Zielposition erreicht
        moveToPosTimer->stop();
        emit rotateDrone(0); // Ausrichtung auf 0 Grad
        return;
    }

    qreal stepX = 0;
    qreal stepY = -5;
    emit moveDrone(stepX, stepY);
}

void FlyControlModul::stopNavigation(){
    moveToPosTimer->stop();
}

void FlyControlModul::startNavigation(){
    moveToPosTimer->start(16);
}

int FlyControlModul::calcRotationToPosition(int x, int y){

    double angle;
    double a = (asin(std::fabs(y) / sqrt(pow(std::fabs(x), 2) + pow(std::fabs(y), 2))) * 180.0 / M_PI);  // Winkel in Grad umrechnen

    if (x == 0 && y < 0) {
        angle = 180;
    } else if (x == 0 && y > 0) {
        angle = 0;
    } else if (x < 0 && y == 0) {
        angle = -90;
    } else if (x > 0 && y == 0) {
        angle = 90;
    } else {
        if (x < 0 && y > 0) {
            angle = -90 + a;
        } else if (x < 0 && y < 0) {
            angle = -90 - a;
        } else if (x > 0 && y > 0) {
            angle = 90 - a;
        } else if (x > 0 && y < 0) {
            angle = 90 + a;
        } else {
            angle = 0.0;
        }
    }

    return angle;
}

void FlyControlModul::setJoyInputsFromRadio(Vec4d radioInput) {
    joyInputs = radioInput; // Set the joystick inputs from radio

    // Print the joystick inputs for debugging Optional
     std::cout << "Height: " << joyInputs.x << std::endl;
     std::cout << "Rotation: " << joyInputs.y << std::endl;
     std::cout << "Front Back: " << joyInputs.z << std::endl;
     std::cout << "Left Right: " << joyInputs.w << std::endl;
}

void FlyControlModul::getControlInputs() {
    Adjust(); // Adjust control inputs
}

void FlyControlModul::checkStart() {
    // Check if the infrared sensor readings indicate that the drone can start
    if(collisionAvoid->getInfraredSensorReadings(3) == 4 || collisionAvoid->getInfraredSensorReadings(3) == 0) {
        startTimer->stop(); // Stop the start timer
        motors->setAllRPM(flyOnSpotRPM); // Set motors RPM for flying on the spot
        setInAir(true); // Set the drone status to in air
    }
}

void FlyControlModul::checkLand() {
    // Check if the infrared sensor readings indicate that the drone should land
    if(collisionAvoid->getInfraredSensorReadings(3) == 1) {
        landTimer->stop(); // Stop the land timer
        motors->setAllRPM(0); // Stop the motors
    }
}

void FlyControlModul::gotlastWaypointReached() {
    radio->setCurrentState(1); // Set the radio state to 1 (idle)
    // Start the control inputs timer if it's not already active
    if(!getControlInputsTimer->isActive())
        getControlInputsTimer->start(30);
}

void FlyControlModul::checkLEDFunktion() {
    int state = radio->getCurrentState(); // Get the current state from the radio
    // Emit the corresponding LED color based on the state
    switch(state) {
    case 0:
        emit LED("yellow");
        break;
    case 1:
        emit LED("green");
        break;
    case 2:
        emit LED("red");
        break;
    case 3:
        emit LED("orange");
        break;
    case 4:
        emit LED("blue");
        break;
    default:
        break;
    }
}


