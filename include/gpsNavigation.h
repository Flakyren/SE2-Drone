#pragma once
#include "globalstructs.h"
#include <QObject>
#include <QTimer>

class GPSNavigation : public QObject
{
    Q_OBJECT
public:
    GPSNavigation();
    ~GPSNavigation();

    void setProperRPM(Vec4d RPM);
    void setDestinationPosition(Vec3d Pos);

    Vec4d getProperRPM();
    Vec3d getDestinationPosition();

public slots:
    void getFlyMeToSignal(Vec3d gpsPosition);

signals:
    void sendDataToFlyControl(Vec3d destinationPosition);

private:
    Vec3d destinationPosition;
    Vec4d properRPM;
};
