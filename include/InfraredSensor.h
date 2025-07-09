#pragma once

#include <QObject>

class InfraredSensor : public QObject {
    Q_OBJECT

public:
    InfraredSensor(int id);
    ~InfraredSensor();

    float getReadings();
    short getSensorID();

public slots:
    void setReadings(int newReading);

signals:
    void infraredReadingUpdated(int newReading);

private:
    short sensorID; // 1 -> Vorne, 2 -> Rechts, 3 -> Links, 4 -> Unten
    float reading;
};
