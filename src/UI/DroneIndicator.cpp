#include "UI/DroneIndicator.h"

DroneIndicator::DroneIndicator()
{
    // Größerer Körper der Drohne
    body = new QGraphicsRectItem(0, 0, 40, 20);
    body->setBrush(QBrush(Qt::gray));
    addToGroup(body);


    downSensor = new Sensor(1, this);
    downSensor->setRotation(-180);
    downSensor->setPos(20, 20);
    //QPen transPen(Qt::transparent);
    //downSensor->segment1->setPen(transPen);
    //downSensor->segment2->setPen(transPen);
    //downSensor->segment3->setPen(transPen);
    //downSensor->segment4->setPen(transPen);
    downSensor->setParentItem(body);


    // Größere Rotoren
    rotor1 = new QGraphicsEllipseItem(-10, -10, 20, 20);
    rotor1->setBrush(QBrush(Qt::black));
    rotor1->setPos(0, 0);
    addToGroup(rotor1);

    rotor2 = new QGraphicsEllipseItem(-10, -10, 20, 20);
    rotor2->setBrush(QBrush(Qt::black));
    rotor2->setPos(40, 0);
    addToGroup(rotor2);



    // Setze Transformationsursprung für die Drehung
    setTransformOriginPoint(body->boundingRect().center());
}

int DroneIndicator::checkForObstacle(QGraphicsItem &obstacle)
{
    if (downSensor->segment1->collidesWithItem(&obstacle)) {
        return 1;
    } else if (downSensor->segment2->collidesWithItem(&obstacle)) {
        return 2;
    } else if (downSensor->segment3->collidesWithItem(&obstacle)) {
        return 3;
    } else if (downSensor->segment4->collidesWithItem(&obstacle)) {
        return 4;
    }
    return 0;
}
