#include "UI/mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsOpacityEffect>
#include <QRandomGenerator>//>
#include <QKeyEvent>

MainWindow::MainWindow(QGraphicsScene *scene, QGraphicsScene *heightScene, Drone *drone, const QList<Obstacle*> &obstacles, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    drone(drone),
    obstacles(obstacles),
    heightScene(heightScene),
    scene(scene),
    droneIndicator(new DroneIndicator()),
    dx(0),
    dy(0),
    rotationDelta(0),
    sliderVL(0),
    sliderVR(0),
    sliderHL(0),
    sliderHR(0),
    takeOffStep(0),
    landStep(5000),
    inAir(false)
{
    ui->setupUi(this);
    setupGraphicsViews(scene);
    setupHeightIndicator();
    setupConnections();

    QGraphicsTextItem *textItem = new QGraphicsTextItem("H");
    textItem->setPos(0, 0);
    scene->addItem(textItem);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updatePosition);
    timer->start(16);

    ui->statusLabel_D->setText(QString::number(0));


    setupClouds();
    cloudTimer = new QTimer(this);
    connect(cloudTimer, &QTimer::timeout, this, &MainWindow::moveClouds);
}


void MainWindow::setupClouds()
{
    for (int i = 0; i < 5; ++i) {
        QGraphicsEllipseItem *cloudItem = new QGraphicsEllipseItem(0, 0, 100, 50);
        cloudItem->setBrush(QColor(255, 255, 255, 128)); // semi-transparent white
        cloudItem->setPos(QRandomGenerator::global()->generate() % ui->graphicsView->width(), QRandomGenerator::global()->generate() % (ui->graphicsView->height() / 2));
        cloudItems.append(cloudItem);
        scene->addItem(cloudItem);
    }
}

void MainWindow::moveClouds()
{
    for (QGraphicsEllipseItem *cloud : cloudItems) {
        cloud->moveBy(0, -1);
        if (cloud->pos().y() > ui->graphicsView->height()) {
            cloud->setPos(cloud->pos().x(), 0);
        }
    }
}







void MainWindow::updateSlider(int rotorIndex, int rpm) {
    QSlider *slider = getSliderByRotorIndex(rotorIndex);
    if (slider) {
        int sliderValue = rpm * 100 / 10000; // Umrechnung von RPM in Sliderwert (0-100)
        slider->blockSignals(true); // Verhindert rekursive Signalauslösung
        slider->setValue(sliderValue);
        slider->blockSignals(false);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    handleKeyPress(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    handleKeyRelease(event);
}

void MainWindow::handleKeyPress(QKeyEvent *event)
{
    if (inAir) {
        switch (event->key()) {
        case Qt::Key_W: dy = -5; emit joystickFrontBack(1); break;
        case Qt::Key_A: dx = -5; emit joystickLeftRight(-1); break;
        case Qt::Key_S: dy = 5;  emit joystickFrontBack(-1); break;
        case Qt::Key_D: dx = 5;  emit joystickLeftRight(1);break;
        case Qt::Key_Q: rotationDelta = -5; emit joystickRotation(-1); break;
        case Qt::Key_E: rotationDelta = 5; emit joystickRotation(1); break;
        case Qt::Key_R: emit joystickHeight(1); break;
        case Qt::Key_F: emit joystickHeight(-1); break;
        default: break;
        }
    }
}

void MainWindow::handleKeyRelease(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W: dy = 0; emit joystickFrontBack(0); break;
    case Qt::Key_S: dy = 0; emit joystickFrontBack(0); break;
    case Qt::Key_A: dx = 0; emit joystickLeftRight(0); break;
    case Qt::Key_D: dx = 0; emit joystickLeftRight(0); break;
    case Qt::Key_Q: rotationDelta = 0; emit joystickRotation(0); break;
    case Qt::Key_E: rotationDelta = 0; emit joystickRotation(0); break;
    case Qt::Key_R: emit joystickHeight(0); break;
    case Qt::Key_F: emit joystickHeight(0); break;
    default: break;
    }
}

void MainWindow::updatePosition()
{
    auto updateStatus = [this](int status, int &delta, int blockValue) {
        if (status == 1 && delta == blockValue) delta = 0;
    };

    QList<QGraphicsItem *> obstacleItems;
    for (Obstacle *obstacle : obstacles) {
        obstacleItems.append(obstacle);
    }

    int statusFront = drone->checkForObstacleFront(obstacleItems);
    int statusLeft = drone->checkForObstacleLeft(obstacleItems);
    int statusRight = drone->checkForObstacleRight(obstacleItems);

    emit infraredReadingsV(statusFront);
    emit infraredReadingsL(statusLeft);
    emit infraredReadingsR(statusRight);


    updateStatus(statusFront, dy, -5);
    updateStatus(statusLeft, dx, -5);
    updateStatus(statusRight, dx, 5);

    QPointF currentPosition = drone->pos();
    emit sendGPStoGPSAntenna(double(currentPosition.x()), double(currentPosition.y()), double(drone->getHeight()));
    drone->rotateDrone(rotationDelta);
    drone->moveDrone(dx, dy);
    updateStatusLabels(statusFront, statusLeft, statusRight);
}

void MainWindow::updateStatusLabels(int statusFront, int statusLeft, int statusRight)
{
    ui->statusLabel_F->setText(QString::number(statusFront));
    ui->statusLabel_L->setText(QString::number(statusLeft));
    ui->statusLabel_R->setText(QString::number(statusRight));
}

void MainWindow::updateHeightLabel(int height)
{
    ui->statusLabel_Height->setText(QString::number(height));
}

void MainWindow::updateHeightIndicator(int height)
{
    int statusDown;
    statusDown = droneIndicator->checkForObstacle(*groundItem);
    emit infraredReadingsD(statusDown);
    ui->statusLabel_D->setText(QString::number(statusDown));
    qreal maxHeight = ui->heightGraphicsView->height() - droneIndicator->boundingRect().height();
    qreal yPos = maxHeight - (maxHeight * height / 5000.0);
    droneIndicator->setY(yPos);
}

void MainWindow::setupGraphicsViews(QGraphicsScene *scene)
{
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    ui->heightGraphicsView->setScene(heightScene);
    ui->heightGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->heightGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::setupHeightIndicator()
{
    // Add a ground item at the bottom
    groundItem = new QGraphicsRectItem(0, 701, ui->heightGraphicsView->width(), 20);
    groundItem->setBrush(Qt::blue);
    heightScene->addItem(groundItem);

    QGraphicsRectItem *groundItem2 = new QGraphicsRectItem(0, 671, ui->heightGraphicsView->width(), 40);
    groundItem2->setBrush(Qt::green);
    heightScene->addItem(groundItem2);


    // Add a cloud item at the top
    QGraphicsEllipseItem *cloudItem = new QGraphicsEllipseItem(0, 0, 50, 20);
    cloudItem->setBrush(Qt::white);
    cloudItem->setPos(ui->heightGraphicsView->width() / 2 - 25, 0); // Centered at the top
    heightScene->addItem(cloudItem);

    heightScene->addItem(droneIndicator);
    droneIndicator->setPos(25,676);
}

void MainWindow::setupConnections()
{
    ui->statusLabel_Height->setText(QString::number(0));
    ui->statusLabel_State->setText(QString::fromStdString("X"));
    ui->statusLabel_Signalst->setText(QString::fromStdString("X"));
    connect(drone, &Drone::heightChanged, this, &MainWindow::updateHeightLabel);
    connect(drone, &Drone::heightChanged, this, &MainWindow::updateHeightIndicator);

    connectSliders();
    connectButtons();
}

void MainWindow::connectSliders()
{
    auto connectSlider = [this](QSlider *slider, int rotorIndex) {
        connect(slider, &QSlider::valueChanged, this, [this, rotorIndex](int value) {
            setRotorRPM(value * 10000 / 100, rotorIndex);
        });
    };

    connectSlider(ui->sliderVL, 1);
    connectSlider(ui->sliderVR, 2);
    connectSlider(ui->sliderHL, 3);
    connectSlider(ui->sliderHR, 4);
}

void MainWindow::connectButtons()
{
    connect(ui->buttonFlyBack, &QPushButton::clicked, this, [this]() {
        emit flybackSingalForController();
    });
    connect(ui->buttonWaypointSet, &QPushButton::clicked, this, [this]() {
        if(inAir){
            if(W.length() < 5){
                emit setSaveWaypointSignalToHandController();
                QGraphicsTextItem *textItem = new QGraphicsTextItem("W");
                textItem->setPos(drone->pos().x(), drone->pos().y());
                scene->addItem(textItem);
                W.append(textItem);
            }
        }
    });

    connect(ui->buttonWaypointFly, &QPushButton::clicked, this, [this]() {
        if(inAir)
            emit FlyAllWaypoints();
    });
    connect(ui->buttonTakeOff, &QPushButton::clicked, this, [this]() {
        emit sendLandTakeOff();
    });
    connect(ui->buttonDisconnect, &QPushButton::clicked, this, &MainWindow::sendSignalLost);
    connect(ui->buttonRecord, &QPushButton::clicked, this, [this](){
        emit toggleRecording();
    });
    connect(ui->buttonWind, &QPushButton::clicked, this, [this](){
        if(windToogle == false){
            emit setGyroscopeValues(0, 1, 0);
            emit setMagnetometerValues(0, 1, 0);
            emit setAccelerationValues(0, 1, 0);
            cloudTimer->start(50); // Start moving clouds
            windToogle = !windToogle;
        } else {
            emit setGyroscopeValues(0, 0, 0);
            emit setMagnetometerValues(0, 0, 0);
            emit setAccelerationValues(0, 0, 0);
            cloudTimer->stop(); // Stop moving clouds
            windToogle = !windToogle;
        }

    });

}

QSlider* MainWindow::getSliderByRotorIndex(int rotorIndex)
{
    switch (rotorIndex) {
    case 1: return ui->sliderVL;
    case 2: return ui->sliderVR;
    case 3: return ui->sliderHL;
    case 4: return ui->sliderHR;
    default: return nullptr;
    }
}

void MainWindow::setRotorRPM(int rpm, int rotorIndex)
{
    if (rotorIndex == -1) {
        for (int i = 1; i <= 4; ++i) drone->setRotorRPM(i, rpm);
    } else {
        drone->setRotorRPM(rotorIndex, rpm);
    }
}

void MainWindow::setRotorRPMFromLogic(int rpm, int rotorIndex)
{
    if (rotorIndex == -1) {
        for (int i = 1; i <= 4; ++i) drone->setRotorRPM(i, rpm);
    } else {
        drone->setRotorRPM(rotorIndex, rpm);
    }
}

void MainWindow::startTakeOff()
{
    if (drone->getHeight() <= 0) {
        takeOffStep = 0;
        takeOffTimer->start(50);
    }
}

void MainWindow::startLand()
{
    if (drone->getHeight() > 1) {
        landStep = drone->getHeight() * 2;
        landTimer->start(50);
    }
}

double MainWindow::getCurrentSpeed()
{
    return qSqrt(dx * dx + dy * dy);
}

void MainWindow::rotateDrone(int angle){
    drone->rotateDrone(-drone->rotation()-angle);
}

void MainWindow::moveDrone(int stepX, int stepY){
    drone->moveDrone(stepX, stepY);
}

void MainWindow::getInAirDataFromLogic(bool Data){
    inAir = Data;
}

void MainWindow::getdeleteWinUI(){
    if(W.empty())
        return;
    scene->removeItem(W.last());
    W.removeLast();
}

void MainWindow::getCurrentState(int state){
    ui->statusLabel_State->setText(QString::number(state));
}

void MainWindow::getSignalstrength(double strength){
    ui->statusLabel_Signalst->setText(QString::number(strength));
}

void MainWindow::getCurrentRecordTimer(QString currentTimer) {
    ui->currentRecordTime->setText(currentTimer);
}

void MainWindow::changeLED(QString color){
    drone->changeLED(color);
}
