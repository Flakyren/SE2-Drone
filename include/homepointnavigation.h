#pragma once
#include "globalstructs.h"
#include <QObject>
#include <QTimer>

class HomepointNavigation : public QObject
{
    Q_OBJECT
public:
    HomepointNavigation();
    ~HomepointNavigation();

    Vec3d getHomepoint();
    void setHomepoint();
    void setCurrentPosition(Vec3d position);

public slots:
    void getFlyBackSignal();
    void getGPSData(Vec3d positionGPS);

signals:
    void askForGPSData(int i);
    void flyMeTo(Vec3d gpsPosition);
    void homepointReached();

private:
    bool weAreHome;
    QTimer *gpsQueryTimer;
    double tolerance = 5.0;
    Vec3d currentPosition;
    Vec3d homepoint;

    void queryGPS();
};
