#include "UI/obstacle.h"
#include <QBrush>

Obstacle::Obstacle(qreal x, qreal y, qreal diameter)
{
    setRect(x, y, diameter, diameter);
    setBrush(QBrush(Qt::blue));
}
