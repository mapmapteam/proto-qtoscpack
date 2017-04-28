#ifndef OSCSENDER_H
#define OSCSENDER_H

#include <QObject>
#include <QVariant>
#include <QtNetwork>
#include <QHostAddress>

class OscSender : public QObject
{
    Q_OBJECT
public:
    explicit OscSender(const QString& hostAddress, quint16 port, QObject *parent);
    void send(const QString& oscAddress, const QVariantList& arguments);

signals:

public slots:

private:
    QUdpSocket* m_udpSocket;
    QHostAddress m_hostAddress;
    quint16 m_port;

    void variantListToByteArray(QByteArray& outputResult, const QString& oscAddress, const QVariantList& arguments);
};

#endif // OSCSENDER_H
