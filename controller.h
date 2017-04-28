#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVariant>
#include "oscsender.h"

/**
 * @brief Controller.
 */
class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(const QString& sendHost, quint16 sendPort, quint16 receivePort, QObject* parent = 0);

signals:

public slots:
    void timeoutCb();
    void messageReceived(const QString& oscAddress, const QVariantList& value);

private:
    QTimer* m_sendTimer;
    OscSender* m_sender;
    //TODO OscReceiver* m_receiver;

    static const int TIMEOUT_INTERVAL_MS;
};

#endif // CONTROLLER_H
