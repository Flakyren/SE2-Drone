#include "camera.h"

Camera::Camera() {
    recording = false; // Initialize recording state
    // Initialize and Connect the timer timeout signal to the timerTick slot to count the Time of Recording
    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, this, &Camera::timerTick);
}

Camera::~Camera(){}

bool Camera::getRecording() {
    return recording;
}

QTimer* Camera::getTimer() {
    return timer;
}

void Camera::setRecording(bool givenRecording) {
    recording = givenRecording;
}

void Camera::setTimer(QTimer* givenTimer) {
    timer = givenTimer;
}

void Camera::startRecord() {
    recording = true;
    startTime = QTime::currentTime(); // Store the current time as the start time
    timer->start(1000); // Start the timer with a 1-second interval
}

void Camera::finishRecord() {
    recording = false;
    timer->stop(); // Stop the timer
    QTime recordedTime(0, 0);
    elapsedTime = recordedTime.addSecs(startTime.secsTo(QTime::currentTime())); // Calculate the elapsed time
    emit updateTimer(elapsedTime.toString("hh:mm:ss")); // Emit the elapsed time in hh:mm:ss format
}

void Camera::timerTick() {
    QTime recordedTime(0, 0);
    QTime elapsed = recordedTime.addSecs(startTime.secsTo(QTime::currentTime())); // Calculate the elapsed time
    emit updateTimer(elapsed.toString("hh:mm:ss")); // Emit the elapsed time in hh:mm:ss format
}

void Camera::getToggleRecordingFromRadio() {
    recording ? finishRecord() : startRecord(); // Toggle recording state
}
