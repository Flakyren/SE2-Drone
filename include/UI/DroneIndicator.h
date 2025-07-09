#ifndef DRONEINDICATOR_H
#define DRONEINDICATOR_H

#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include "sensor.h"
#include <QBrush>
#include <QPen>

class DroneIndicator : public QGraphicsItemGroup
{
public:
    DroneIndicator();
    int checkForObstacle(QGraphicsItem &obstacle);

private:
    QGraphicsRectItem *body;
    QGraphicsEllipseItem *rotor1;
    QGraphicsEllipseItem *rotor2;
    QGraphicsLineItem *rotorBlade1;
    QGraphicsLineItem *rotorBlade2;
    Sensor *downSensor;


};

#endif // DRONEINDICATOR_H
