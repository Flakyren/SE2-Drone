#pragma once

#include <QObject>

class JoystickControl : public QObject
{
    Q_OBJECT

public:
    JoystickControl(QObject* parent = nullptr);
    ~JoystickControl();
    JoystickControl(int joystickID, QObject* parent = nullptr);

    double getPosX() const;
    double getPosY() const;

public slots:
    void setPosX(double reading);
    void setPosY(double reading);

signals:
    void sendXToHandController(int x);
    void sendYToHandController(int x);

private:
    int posX = 0;
    int posY = 0;
    int joystickID;
};
