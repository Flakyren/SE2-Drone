#include "gyroscope.h"
#include <cmath>

const double PI = 3.141592653589793;
const double g = 9.81; // Acceleration due to gravity in m/s^2

Gyroscope::Gyroscope() {}

Gyroscope::~Gyroscope() {}

Vec3d Gyroscope::getRotation() {
    return rotationReadings;
}

void Gyroscope::setRotation(Vec3d givenRotation) {
    rotationReadings = givenRotation;
}

void Gyroscope::setCalculatedRotation(Vec4d givenRPM){
    Vec3d calcRotation;

    // Estimates for mass and radius of the rotor
    double mass = 0.03;  // Mass of the rotor in kg (30 grams)
    double radius = 0.1; // Radius of the rotor in m (10 cm)

    // Calculation of angular velocities
    double omega1 = givenRPM.w * 2 * PI / 60.0;
    double omega2 = givenRPM.x * 2 * PI / 60.0;
    double omega3 = givenRPM.y * 2 * PI / 60.0;
    double omega4 = givenRPM.z * 2 * PI / 60.0;

    // Calculation of average angular velocity for roll (x-direction) and pitch (y-direction)
    double omega_roll = (omega1 + omega3 - omega2 - omega4) / 4.0;
    double omega_pitch = (omega1 + omega2 - omega3 - omega4) / 4.0;

    // Calculation of the Moment of Inertia for a Cylindrical Rotor
    double I = 0.5 * mass * radius * radius;

    // Calculation of the roll and pitch
    double L_roll = I * omega_roll;
    double L_pitch = I * omega_pitch;

    double M_roll = mass * g * radius; // for the roll
    double M_pitch = mass * g * radius; // for the pitch

    // Calculation of precession rates for roll and pitch
    double Omega_p_roll = M_roll / L_roll;
    double Omega_p_pitch = M_pitch / L_pitch;

    // Simplified guess of how the rotation should be
    calcRotation.x = asin(Omega_p_roll * L_roll / (mass * g * radius)) * 180 / PI;
    calcRotation.y = asin(Omega_p_pitch * L_pitch / (mass * g * radius)) * 180 / PI;
    calcRotation.z = 0; // Can't calculate the rotation

    calculatedRotation = calcRotation;
}

Vec3d Gyroscope::getCalculatedRotation(){
    return calculatedRotation;
}

Vec3d Gyroscope::measureRotation() {
    Vec3d measuredRotation;
    return measuredRotation;
}

void Gyroscope::getGyroscopeValues(double x, double y, double z){
    rotationReadings.x = x;
    rotationReadings.y = y;
    rotationReadings.z = z;
}
