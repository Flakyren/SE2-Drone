#ifndef ROTOR_H
#define ROTOR_H

#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QBrush> // Füge diese Zeile hinzu

class Rotor
{
public:
    Rotor(qreal x, qreal y, qreal rpm, QGraphicsItemGroup *parent);
    void rotate();
    void setRPM(qreal newRPM);
    qreal getRPM() const;
    void changeLED(QString color);

private:
    QGraphicsEllipseItem *base;
    QGraphicsEllipseItem *led;
    QGraphicsRectItem *blade;
    qreal angle;
    qreal rpm;
};

#endif // ROTOR_H
