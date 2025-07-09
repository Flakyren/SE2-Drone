#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsEllipseItem>

class Obstacle : public QGraphicsEllipseItem
{
public:
    Obstacle(qreal x, qreal y, qreal diameter);
};

#endif // OBSTACLE_H
