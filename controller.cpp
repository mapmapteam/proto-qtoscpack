#include <QDebug>
#include "controller.h"

const int Controller::TIMEOUT_INTERVAL_MS = 5000;
//static const bool VERY_VERBOSE = true;
//static const bool VERY_VERBOSE = false;

Controller::Controller(const QString& sendHost, quint16 sendPort, quint16 receivePort, QObject *parent) :
    QObject(parent)
{
    Q_UNUSED(receivePort);
    qDebug() << "create OSC sender to " << sendHost << " " << sendPort;
    m_sender = new OscSender(sendHost, sendPort, this);
    m_sendTimer = new QTimer(this);

    //connect(m_sendTimer, SIGNAL(timeout()), this, [this]() {
    connect(m_sendTimer, &QTimer::timeout, this, [this]() {
        QList<QVariant> arguments;
        arguments.append(QVariant("abcdef"));
        arguments.append(QVariant(1));
        arguments.append(QVariant(2));
        arguments.append(QVariant(3.1415f));
        this->m_sender->send("/hello", arguments);
    });

    m_sendTimer->setSingleShot(true);
    m_sendTimer->start(10); // ms
    //connect(&m_timeoutTimer, &QTimer::timeout, this, &Controller::timeoutCb);
    //m_timeoutTimer.start(TIMEOUT_INTERVAL_MS);

    m_receiver = new OscReceiver(receivePort, this);
    connect(m_receiver, &OscReceiver::messageReceived, this, [this](const QString& oscAddress, const QVariantList& arguments) {
        qDebug() << "Received " << oscAddress;
        qDebug() << arguments;
    });
}

void Controller::timeoutCb() {
    qDebug() << "timeoutCb";
}

void Controller::messageReceived(const QString& oscAddress, const QVariantList& value) {
    Q_UNUSED(oscAddress);
    Q_UNUSED(value);
    // TODO
}
