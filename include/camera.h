#pragma once
#include <QObject>
#include <QTimer>
#include <QTime>


using namespace std;

class Camera : public QObject
{
    Q_OBJECT
public:
    Camera();
    ~Camera();

    bool getRecording();
    QTimer * getTimer();
    void setRecording(bool givenRecording);
    void setTimer(QTimer * givenTimer);

    void startRecord();
    void finishRecord();
    void timerTick();

signals:
    void updateTimer(QString currentTimer);

public slots:
    void getToggleRecordingFromRadio();

private:
    QTimer * timer;
    QTime startTime;
    QTime elapsedTime;
    bool recording;
};
