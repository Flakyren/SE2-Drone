#pragma once
#include "globalstructs.h"
#include <QObject>
#include "joystickcontrol.h"
#include "startlandbutton.h"

class HandController : public QObject
{
    Q_OBJECT
public:
    HandController(JoystickControl& hrJoystick, JoystickControl& nJoystick, StartLandButton& startLandButton);
    ~HandController();

public slots:
    void FlyBackSignalFromUI();

    // get X Y from joysticks
    void getXFromjoystickHR(double x);
    void getYFromjoystickHR(double y);

    void getXFromjoystickN(double x);
    void getYFromjoystickN(double y);

    void setJoyInputs(Vec4d Inputs);
    Vec4d getJoyInputs();

    void getSaveWaypointSignal();
    void getFlyAllWaypoints();
    void getStartLand();
    void getToggleRecording();


signals:
    void sendSaveWaypointSignalToRadio();
    void FlybackSignalForRadio();
    void joyInputsChanged(Vec4d joyInputs);
    void sendFlyToWaypointsRadio();
    void sendStartLand();
    void sendRecordSignalToRadio();

private:
    double tolerance = 0.01;
    Vec3d homepoint;
    Vec4d joyInputs;
    StartLandButton& startLandButton;
    JoystickControl& joystickHR;
    JoystickControl& joystickN;
};
