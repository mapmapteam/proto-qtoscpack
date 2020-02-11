#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVariant>
#include "oscsender.h"
#include "oscreceiver.h"

/**
 * @brief Controller.
 */
class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(const QString& sendHost, quint16 sendPort, quint16 receivePort, QObject* parent = 0);

signals:
    void messageReceived(const QString& oscAddress, const QVariantList& value);

public:
    Q_INVOKABLE void sendSomething(const QString& oscAddress, const QVariantList& arguments);

public slots:
    void timeoutCb();
    void messageReceivedCb(const QString& oscAddress, const QVariantList& value);

private:
    QTimer* m_sendTimer;
    OscSender* m_sender;
    OscReceiver* m_receiver;
    static const int TIMEOUT_INTERVAL_MS;
};

#endif // CONTROLLER_H
