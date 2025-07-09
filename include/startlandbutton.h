#pragma once
#include "QObject"

class StartLandButton: public QObject{
    Q_OBJECT
public:
    StartLandButton();
    ~StartLandButton();

public slots:
    void startLandPressed();

signals:
    void sendStartLandSignal();
};
