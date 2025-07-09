#include "UI/sensor.h"

Sensor::Sensor(qreal segmentLength, QGraphicsItem *parent)
    : QGraphicsItemGroup(parent)
{
    qreal firstSegmentLength = segmentLength * 2;

    segment1 = new QGraphicsLineItem(0, 0, 0, -firstSegmentLength, this);
    segment2 = new QGraphicsLineItem(0, -firstSegmentLength, 0, -firstSegmentLength - segmentLength, this);
    segment3 = new QGraphicsLineItem(0, -firstSegmentLength - segmentLength, 0, -firstSegmentLength - 2 * segmentLength, this);
    segment4 = new QGraphicsLineItem(0, -firstSegmentLength - 2 * segmentLength, 0, -firstSegmentLength - 3 * segmentLength, this);

    QPen pen1(Qt::red);
    pen1.setWidth(2);
    segment1->setPen(pen1);

    QPen pen2(Qt::yellow);
    pen2.setWidth(2);
    segment2->setPen(pen2);

    QPen pen3(Qt::green);
    pen3.setWidth(2);
    segment3->setPen(pen3);

    QPen pen4(Qt::blue);
    pen4.setWidth(2);
    segment4->setPen(pen4);

    addToGroup(segment1);
    addToGroup(segment2);
    addToGroup(segment3);
    addToGroup(segment4);
}

int Sensor::checkForObstacle(QList<QGraphicsItem *> obstacles)
{
    for (QGraphicsItem *obstacle : obstacles) {
        if (segment1->collidesWithItem(obstacle)) {
            return 1;
        } else if (segment2->collidesWithItem(obstacle)) {
            return 2;
        } else if (segment3->collidesWithItem(obstacle)) {
            return 3;
        } else if (segment4->collidesWithItem(obstacle)) {
            return 4;
        }
    }
    return 0;
}
