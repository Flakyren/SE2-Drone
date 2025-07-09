#ifndef DRONE_H
#define DRONE_H

#include <QGraphicsItemGroup>
#include <QObject>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QBrush>
#include "sensor.h"
#include "Rotor.h"

class Drone : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    Drone();
    void moveDrone(int dx, int dy);
    void rotateDrone(int angle);
    int checkForObstacleFront(const QList<QGraphicsItem *> &obstacles);
    int checkForObstacleLeft(const QList<QGraphicsItem *> &obstacles);
    int checkForObstacleRight(const QList<QGraphicsItem *> &obstacles);
    void setRotorRPM(int rotorIndex, qreal rpm);
    bool areRotorsSpinning() const;
    bool areSlidersAboveThreshold() const;
    int getHeight();
    void setHeight(int h);
    void updateHeight(); /////////
    void changeLED(QString color);

signals:
    void heightChanged(int newHeight); // Signal hinzufügen
    void rotorRPMChanged(int rotorIndex, int rpm);

private slots:
    void rotateRotors();

private:
    QGraphicsRectItem *body;
    Sensor *frontSensor;
    Sensor *leftSensor;
    Sensor *rightSensor;
    QGraphicsEllipseItem *centerIndicator;
    QTimer *rotorTimer;
    QTimer *heightTimer;
    Rotor *rotor1;
    Rotor *rotor2;
    Rotor *rotor3;
    Rotor *rotor4;
    int height = 0;
    int flyOnSpotRPM = 5000;
};

#endif // DRONE_H
