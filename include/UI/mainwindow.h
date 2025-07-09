#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include "drone.h"
#include "obstacle.h"
#include "DroneIndicator.h"
#include <QSlider>
#include <QCoreApplication>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QGraphicsScene *scene, QGraphicsScene *heightScene, Drone *drone, const QList<Obstacle*> &obstacles, QWidget *parent = nullptr);
    ~MainWindow();

signals:

    // Joystick
    void joystickRotation(int value);
    void joystickHeight(int value);
    void joystickLeftRight(int value);
    void joystickFrontBack(int value);

    // Infrared
    void infraredReadingsV(int value);
    void infraredReadingsL(int value);
    void infraredReadingsR(int value);
    void infraredReadingsD(int value);

    // Signal Lost
    void sendSignalLost();

    // Singal FlyBackFromController
    void flybackSingalForController();

    // Send GPS
    void sendGPStoGPSAntenna(double x, double y, double z);
    //landen starten
    void sendLandTakeOff();
    //Waypoint signale
    void setSaveWaypointSignalToHandController();
    void FlyAllWaypoints();
    //Camera signal
    void toggleRecording();
    //Stabilizations
    void setGyroscopeValues(double x, double y, double z);
    void setMagnetometerValues(double x, double y, double z);
    void setAccelerationValues(double x, double y, double z);


public slots:
    void setRotorRPMFromLogic(int rpm, int rotorIndex);
    void updateSlider(int rotorIndex, int rpm);
    void getInAirDataFromLogic(bool Data);
    void getdeleteWinUI();
    void getCurrentState(int state);
    void getSignalstrength(double strength);
    void getCurrentRecordTimer(QString currentTimer);

    void rotateDrone(int angle);
    void moveDrone(int stepX, int stepY);

    void changeLED(QString color);
    void moveClouds();


protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    Drone *drone;
    QList<Obstacle*> obstacles;
    QGraphicsScene *heightScene;
    QGraphicsScene *scene;
    DroneIndicator *droneIndicator;
    QGraphicsRectItem *groundItem;
    QPointF targetPosition;
    void setupClouds();


    QTimer *cloudTimer;
    QTimer *timer;
    QTimer *takeOffTimer;
    QTimer *landTimer;

    int calcRotationToPosition(int x, int y);
    int dx, dy, rotationDelta, targetRotation;
    int sliderVL, sliderVR, sliderHL, sliderHR;
    int takeOffStep, landStep;
    bool inAir = false;
    bool windToogle = false;

    void flyBackTimerFunktion();
    void setupGraphicsViews(QGraphicsScene *scene);
    void setupHeightIndicator();
    void setupConnections();
    void connectSliders();
    void connectButtons();
    QSlider* getSliderByRotorIndex(int rotorIndex);
    QList<QGraphicsTextItem*> W;
    QList<QGraphicsEllipseItem*> cloudItems;

    void rotateToNeutralPosition();
    void handleKeyPress(QKeyEvent *event);
    void handleKeyRelease(QKeyEvent *event);
    void updatePosition();
    void setRotorRPM(int rpm, int rotorIndex = -1);
    void startTakeOff();
    void startLand();
    bool getInAir() const;
    void setInAir(bool inAir);
    void setupTakeOffAndLandTimers();
    double getCurrentSpeed();
    void Flyto();
    void updateStatusLabels(int statusFront, int statusLeft, int statusRight);
    void updateHeightLabel(int height);
    void updateHeightIndicator(int height);
};

#endif // MAINWINDOW_H
