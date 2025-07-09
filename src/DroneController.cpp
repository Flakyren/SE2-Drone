#include "DroneController.h"

DroneController::DroneController(QGraphicsScene *scene)
    : dx(0), dy(0), rotationDelta(0)
{
    drone = new Drone();
    scene->addItem(drone);

    obstacles.append(new Obstacle(100, 100, 30));
    obstacles.append(new Obstacle(200, 150, 30));
    obstacles.append(new Obstacle(300, 200, 30));
    obstacles.append(new Obstacle(400, 250, 30));
    obstacles.append(new Obstacle(500, 300, 30));

    for (Obstacle *obstacle : obstacles) {
        scene->addItem(obstacle);
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DroneController::updatePosition);
    timer->start(16); 
}

void DroneController::handleKeyPress(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
        dy = -5; 
        break;
    case Qt::Key_A:
        dx = -5;
        break;
    case Qt::Key_S:
        dy = 5;
        break;
    case Qt::Key_D:
        dx = 5;
        break;
    case Qt::Key_Q:
        rotationDelta = -5;
        break;
    case Qt::Key_E:
        rotationDelta = 5;
        break;
    default:
        break;
    }
}

void DroneController::handleKeyRelease(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
    case Qt::Key_S:
        dy = 0; 
        break;
    case Qt::Key_A:
    case Qt::Key_D:
        dx = 0;
        break;
    case Qt::Key_Q:
    case Qt::Key_E:
        rotationDelta = 0;
        break;
    default:
        break;
    }
}

void DroneController::updatePosition()
{
    QList<QGraphicsItem *> obstacleItems;
    for (Obstacle *obstacle : obstacles) {
        obstacleItems.append(obstacle);
    }

    int statusFront = drone->checkForObstacleFront(obstacleItems);
    int statusLeft = drone->checkForObstacleLeft(obstacleItems);
    int statusRight = drone->checkForObstacleRight(obstacleItems);

    QString statusText_F = QString::number(statusFront);
    QString statusText_L = QString::number(statusLeft);
    QString statusText_R = QString::number(statusRight);

    if (statusFront == 1 && dy < 0) {
        dy = 0; 
    }
    if (statusLeft == 1 && dx < 0) {
        dx = 0;
    }
    if (statusRight == 1 && dx > 0) {
        dx = 0;
    }

    emit statusChanged_F(statusText_F);
    emit statusChanged_L(statusText_L);
    emit statusChanged_R(statusText_R);

    drone->rotateDrone(rotationDelta);
    drone->moveDrone(dx, dy);
}

void DroneController::setRotorRPM(int rotorIndex, int rpm)
{
    drone->setRotorRPM(rotorIndex, rpm);
}

int DroneController::getSensorDataFront()
{
    QList<QGraphicsItem *> obstacleItems;
    for (Obstacle *obstacle : obstacles) {
        obstacleItems.append(obstacle);
    }
    return drone->checkForObstacleFront(obstacleItems);
}

int DroneController::getSensorDataLeft()
{
    QList<QGraphicsItem *> obstacleItems;
    for (Obstacle *obstacle : obstacles) {
        obstacleItems.append(obstacle);
    }
    return drone->checkForObstacleLeft(obstacleItems);
}

int DroneController::getSensorDataRight()
{
    QList<QGraphicsItem *> obstacleItems;
    for (Obstacle *obstacle : obstacles) {
        obstacleItems.append(obstacle);
    }
    return drone->checkForObstacleRight(obstacleItems);
}

double DroneController::getCurrentSpeed()
{
    return qSqrt(dx * dx + dy * dy);
}
