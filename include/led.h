#pragma once
#include "qobject.h"

class LED : public QObject
{
    Q_OBJECT
public:
    LED();
    ~LED();

    int getGlow();
signals:
    void changeLEDInUI(QString color);

public slots:
    void setGlow(QString color);

private:
    int glow;
};
