#include "UI/drone.h"
#include <QBrush>
#include <QtMath>
#include <iostream>

Drone::Drone()
{

    body = new QGraphicsRectItem(0, 0, 20, 40);
    body->setBrush(QBrush(Qt::gray));
    addToGroup(body);


    frontSensor = new Sensor(20, this);
    frontSensor->setPos(10, 0);
    addToGroup(frontSensor);

    leftSensor = new Sensor(20, this);
    leftSensor->setRotation(-90);
    leftSensor->setPos(0, 20);
    addToGroup(leftSensor);

    rightSensor = new Sensor(20, this);
    rightSensor->setRotation(90);
    rightSensor->setPos(20, 20);
    addToGroup(rightSensor);


    centerIndicator = new QGraphicsEllipseItem(-2.5, -2.5, 5, 5);
    centerIndicator->setBrush(QBrush(Qt::green));
    centerIndicator->setPos(10, 20);
    addToGroup(centerIndicator);


    rotor1 = new Rotor(0, 0, 0, this);
    rotor2 = new Rotor(0, 40, 0, this);
    rotor3 = new Rotor(20, 0, 0, this);
    rotor4 = new Rotor(20, 40, 0, this);


    setTransformOriginPoint(body->rect().center());


    rotorTimer = new QTimer(this);
    connect(rotorTimer, &QTimer::timeout, this, &Drone::rotateRotors);
    rotorTimer->start(50);

    heightTimer = new QTimer(this);
    connect(heightTimer, &QTimer::timeout, this, &Drone::updateHeight);

}


void Drone::updateHeight()
{
    // Berechne die durchschnittliche RPM der Rotoren
    qreal averageRPM = (rotor1->getRPM() + rotor2->getRPM() + rotor3->getRPM() + rotor4->getRPM()) / 4;

    // Berechne die Höhe basierend auf der durchschnittlichen RPM
    if (averageRPM > flyOnSpotRPM && getHeight() < flyOnSpotRPM) {
        height += 5;
        emit heightChanged(height); // Signal emittieren, wenn sich die Höhe ändert
    } else if(averageRPM < flyOnSpotRPM && getHeight() > 0){
        height -= 5;
        emit heightChanged(height); // Signal emittieren, wenn sich die Höhe ändert
    } else {
        heightTimer->stop();
    }
}



void Drone::moveDrone(int dx, int dy)
{


    qreal angle = rotation();
    qreal rad = qDegreesToRadians(angle);
    qreal cosAngle = qCos(rad);
    qreal sinAngle = qSin(rad);

    qreal deltaX = dx * cosAngle - dy * sinAngle;
    qreal deltaY = dx * sinAngle + dy * cosAngle;
    if (height)
        moveBy(deltaX, deltaY);
}

int Drone::getHeight()
{
    return height;
}

void Drone::setHeight(int h)
{
    height = h;
}

void Drone::rotateDrone(int angle)
{
    if (height)
        setRotation(rotation() + angle);
}

int Drone::checkForObstacleFront(const QList<QGraphicsItem *> &obstacles)
{
    return frontSensor->checkForObstacle(obstacles);
}

int Drone::checkForObstacleLeft(const QList<QGraphicsItem *> &obstacles)
{
    return leftSensor->checkForObstacle(obstacles);
}

int Drone::checkForObstacleRight(const QList<QGraphicsItem *> &obstacles)
{
    return rightSensor->checkForObstacle(obstacles);
}

void Drone::rotateRotors()
{
    rotor1->rotate();
    rotor2->rotate();
    rotor3->rotate();
    rotor4->rotate();
}

void Drone::setRotorRPM(int rotorIndex, qreal rpm) /////////
{
    switch (rotorIndex) {
    case 1:
        rotor1->setRPM(rpm);
        break;
    case 2:
        rotor2->setRPM(rpm);
        break;
    case 3:
        rotor3->setRPM(rpm);
        break;
    case 4:
        rotor4->setRPM(rpm);
        break;
    }
    heightTimer->start(20);
    emit rotorRPMChanged(rotorIndex, rpm);
}

void Drone::changeLED(QString color)
{
    rotor1->changeLED(color);
    rotor2->changeLED(color);
    rotor3->changeLED(color);
    rotor4->changeLED(color);

}
