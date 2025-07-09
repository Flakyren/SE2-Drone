#include "UI/Rotor.h"
#include <QColor>
#include <QtMath>

Rotor::Rotor(qreal x, qreal y, qreal rpm, QGraphicsItemGroup *parent)
    : angle(0), rpm(rpm)
{
    base = new QGraphicsEllipseItem(-5, -5, 10, 10, parent);
    base->setBrush(QBrush(Qt::black));
    base->setPos(x, y);

    led = new QGraphicsEllipseItem(-2, -2, 4, 4, parent);
    led->setBrush(QBrush(Qt::yellow));
    led->setPos(x, y);

    blade = new QGraphicsRectItem(-1.25, -12.5, 2.5, 25, base);
    blade->setBrush(QBrush(Qt::black));
}

void Rotor::rotate()
{
    angle += rpm / 60.0; // Rotate in degrees, as the timer is called every 50ms
    if (angle >= 360) angle -= 360;
    blade->setRotation(angle);
}

void Rotor::setRPM(qreal newRPM)
{
    rpm = newRPM;
}

qreal Rotor::getRPM() const
{
    return rpm;
}

void Rotor::changeLED(QString color)
{
    QColor customOrange(255, 165, 0); // RGB for orange
    if(color == "yellow")
        led->setBrush(QBrush(Qt::yellow));
    else if(color == "green")
        led->setBrush(QBrush(Qt::green));
    else if(color == "red")
        led->setBrush(QBrush(Qt::red));
    else if(color == "orange")
        led->setBrush(QBrush(QBrush(customOrange)));
    else if(color == "blue")
        led->setBrush(QBrush(Qt::blue));
}
