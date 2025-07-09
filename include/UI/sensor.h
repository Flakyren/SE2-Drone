#ifndef SENSOR_H
#define SENSOR_H

#include <QGraphicsLineItem>
#include <QBrush>
#include <QPen>

class Sensor : public QGraphicsItemGroup
{
public:
    Sensor(qreal segmentLength, QGraphicsItem *parent = nullptr);
    int checkForObstacle(QList<QGraphicsItem *> obstacles);
    QGraphicsLineItem *segment1;
    QGraphicsLineItem *segment2;
    QGraphicsLineItem *segment3;
    QGraphicsLineItem *segment4;
};

#endif // SENSOR_H
