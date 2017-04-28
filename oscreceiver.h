#ifndef OSCRECEIVER_H
#define OSCRECEIVER_H

#include <QObject>
#include <QVariant>
#include <QtNetwork>
#include <QHostAddress>

class OscReceiver : public QObject
{
    Q_OBJECT
public:
    explicit OscReceiver(quint16 receivePort, QObject *parent = 0);

signals:
    void messageReceived(const QString& oscAddress, const QVariantList& message);

public slots:

private:
    QUdpSocket* m_udpSocket;
    void byteArrayToVariantList(QVariantList& outputVariantList, QString& outputOscAddress, const QByteArray& inputByteArray);
};

#endif // OSCRECEIVER_H
