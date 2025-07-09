#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , takeOffStep(0)
    , landStep(100)
    , indicatorHeight(0) 
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    heightScene = new QGraphicsScene(this);
    ui->heightGraphicsView->setScene(heightScene);
    initializeHeightView();

    DroneController *droneController = new DroneController(scene);
    droneFacade = new DroneFacade(droneController); // Initialisiere die Fassadenklasse
    connect(droneFacade, &DroneFacade::statusChanged_F, this, &MainWindow::updateStatusLabel_F);
    connect(droneFacade, &DroneFacade::statusChanged_L, this, &MainWindow::updateStatusLabel_L);
    connect(droneFacade, &DroneFacade::statusChanged_R, this, &MainWindow::updateStatusLabel_R);

    connect(ui->sliderVL, &QSlider::valueChanged, this, [this](int value) {
        droneFacade->setMotorRPM(1, value * 2000 / 100);
    });
    connect(ui->sliderVR, &QSlider::valueChanged, this, [this](int value) {
        droneFacade->setMotorRPM(2, value * 2000 / 100);
    });
    connect(ui->sliderHL, &QSlider::valueChanged, this, [this](int value) {
        droneFacade->setMotorRPM(3, value * 2000 / 100);
    });
    connect(ui->sliderHR, &QSlider::valueChanged, this, [this](int value) {
        droneFacade->setMotorRPM(4, value * 2000 / 100);
    });

    connect(ui->buttonTakeOff, &QPushButton::clicked, this, &MainWindow::takeOff);
    connect(ui->buttonLand, &QPushButton::clicked, this, &MainWindow::land);

    takeOffTimer = new QTimer(this);
    connect(takeOffTimer, &QTimer::timeout, this, &MainWindow::updateTakeOff);

    landTimer = new QTimer(this);
    connect(landTimer, &QTimer::timeout, this, &MainWindow::updateLand);

    droneIndicator = new DroneIndicator();
    heightScene->addItem(droneIndicator);
    droneIndicator->setHeight(indicatorHeight); 
}

MainWindow::~MainWindow()
{
    delete ui;
    delete droneFacade;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (droneIndicator->getHeight() > 0) {
        switch (event->key()) {
        case Qt::Key_R:
            droneIndicator->increaseHeight(5);
            break;
        case Qt::Key_F:
            if (droneIndicator->getHeight() <= 150) {
                land();
            } else {
                droneIndicator->decreaseHeight(5);
            }
            break;
        default:
            droneFacade->handleKeyPress(event);
            break;
        }
    } else {
        droneFacade->handleKeyPress(event);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    droneFacade->handleKeyRelease(event);
}

void MainWindow::updateStatusLabel_F(const QString &status)
{
    ui->statusLabel_F->setText(status);
}

void MainWindow::updateStatusLabel_L(const QString &status)
{
    ui->statusLabel_L->setText(status);
}

void MainWindow::updateStatusLabel_R(const QString &status)
{
    ui->statusLabel_R->setText(status);
}

void MainWindow::takeOff()
{
    takeOffStep = (ui->sliderVL->value() + ui->sliderVR->value() + ui->sliderHL->value() + ui->sliderHR->value()) / 4; // Durchschnittlicher Wert
    targetHeight = 200; 
    takeOffTimer->start(50); 
}

void MainWindow::land()
{
    landStep = (ui->sliderVL->value() + ui->sliderVR->value() + ui->sliderHL->value() + ui->sliderHR->value()) / 4; // Durchschnittlicher Wert
    targetHeight = 0; 
    landTimer->start(50); 
}

void MainWindow::updateTakeOff()
{
    if (takeOffStep >= 100) {
        takeOffTimer->stop();
        droneIndicator->setHeight(targetHeight);
    } else {
        takeOffStep += 5;
        ui->sliderVL->setValue(takeOffStep);
        ui->sliderVR->setValue(takeOffStep);
        ui->sliderHL->setValue(takeOffStep);
        ui->sliderHR->setValue(takeOffStep);
    }

    if (indicatorHeight < targetHeight) {
        indicatorHeight += (targetHeight - indicatorHeight) / 10; 
        droneIndicator->setHeight(indicatorHeight);
    } else {
        droneIndicator->setHeight(targetHeight);
    }
}

void MainWindow::updateLand()
{
    if (landStep <= 0) {
        landTimer->stop();
        droneIndicator->setHeight(targetHeight);
    } else {
        landStep -= 5;
        ui->sliderVL->setValue(landStep);
        ui->sliderVR->setValue(landStep);
        ui->sliderHL->setValue(landStep);
        ui->sliderHR->setValue(landStep);
    }

    if (indicatorHeight > targetHeight) {
        indicatorHeight -= (indicatorHeight - targetHeight) / 10; 
        droneIndicator->setHeight(indicatorHeight);
    } else {
        droneIndicator->setHeight(targetHeight);
    }
}

void MainWindow::initializeHeightView()
{
    ui->heightGraphicsView->setFixedSize(91, 711);

    QGraphicsRectItem *ground = new QGraphicsRectItem(0, 661, 91, 50); 
    ground->setBrush(QBrush(Qt::green));
    heightScene->addItem(ground);

    heightScene->setSceneRect(0, 0, 91, 711);

    ui->heightGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->heightGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
