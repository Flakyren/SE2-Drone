#pragma once
#include <QObject>
#include "globalstructs.h"
#include "handController.h"

class RadioCommunication : public QObject
{
    Q_OBJECT
public:
    RadioCommunication(HandController &PSPcontroller);
    ~RadioCommunication();

    double getFrequency();
    double getSignalStrength();

    void setFrequency(double givenFrequency);
    void setSignalStrength(double givenSignalStrength);

    void setCurrentState(int state);
    int getCurrentState();

    void connecting(int);
    //void disconnecting();
    void receiving();
    // Input is "Data", not yet defined
    void sendData();

public slots:
    void buttonSendsDisconnect();
    void FlyHomeFromController();
    void joyInputsFromHandController(Vec4d joyInputs);
    void getSaveWaypointSingal();
    void getFlyToWaypointsRadio();
    void getStartLand();
    void getToggleRecordingFromHandController();

signals:
    void changeCurrentState(int state);
    void changeSignalStrength(double strength);
    void FlyHome();
    void setJoyInputsForFlyControl(Vec4d joyInputs);
    void sendWaypointSaveSignal();
    void sendFlyToWaypoints();
    void sendStartLand();
    void stopWayNav();
    void stopHomeNav();
    void sendRecordSignalToCamera();

private:
    int currentState; // 0 landed, 1 inAir, 2 Disconnected&Landed, 3 FlyToHome, 4 FlyToWayPoint
    double signalStrength;
    double frequency;
    // Should be an enum, not specified
    int connectionState;
    // Should be something else (need to determine)
    int receivedData;
};
