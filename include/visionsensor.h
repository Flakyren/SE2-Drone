#pragma once

#include <QObject>

class VisionSensor: public QObject {
    Q_OBJECT
public:
    VisionSensor(int i);
    ~VisionSensor();

    float getReading();
    short getSensorID();

public slots:
    void setReading(int newReading);

signals:
    void visionReadingUpdated(int newReading);

private:
    short sensorID; // 1 -> Vorne, 2 -> Rechts, 3 -> Links, 4 -> Unten
    float reading;
};
