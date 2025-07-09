#pragma once
#include "globalstructs.h"
#include <QObject>

class GPSAntenna : public QObject
{
    Q_OBJECT
public:
    GPSAntenna();
    ~GPSAntenna();

    int getSatelliteCount();
    Vec3d getGPSPosition();

    void setSatellitesCount(int givenSatellitesCount);
    void setPositionGPS(Vec3d givenPositionGPS);

public slots:
    void gpsDataFromUI(double x, double y, double z);
    void getDataRequest(int i);

signals:
    void sendDataToHomePoint(Vec3d positionGPS);
    void sendDataToWayPoint(Vec3d positionGPS);

private:
    int satellites;
    Vec3d positionGPS;
};
