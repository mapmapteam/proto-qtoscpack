#include "oscsender.h"
#include "osc/OscOutboundPacketStream.h"
#include "osc/OscTypes.h"
#include <iostream>

// FIXME: we should also allow addresses such as "localhost", or "example.com"

OscSender::OscSender(const QString& hostAddress, quint16 port, QObject *parent) :
        QObject(parent),
        m_udpSocket(new QUdpSocket(this)),
        m_hostAddress(hostAddress),
        m_port(port)
{
    m_udpSocket->connectToHost(QHostAddress(m_hostAddress) , m_port);
}

void OscSender::send(const QString& oscAddress, const QVariantList& arguments) {
    QByteArray datagram;
    this->variantListToByteArray(datagram, oscAddress, arguments);

    qint64 written = m_udpSocket->write(datagram);

    qDebug() << "Send " << datagram.size() << " bytes: " << datagram.toHex();
    qDebug() << "...to " << m_hostAddress << " " << m_port;

    if (written == -1) {
        qCritical() << "Failed to send OSC";
    }
    m_udpSocket->flush();
    m_udpSocket->waitForBytesWritten();
}


void OscSender::variantListToByteArray(QByteArray& outputResult, const QString& oscAddress, const QVariantList& arguments) {
    char buffer[1024];
    osc::OutboundPacketStream packet(buffer, 1024);
    // FIXME: Sending datagrams larger than 512 bytes is in general disadvised, as even if they are sent successfully,
    // they are likely to be fragmented by the IP layer before arriving at their final destination.
    packet << osc::BeginBundleImmediate << osc::BeginMessage(oscAddress.toStdString().c_str());

    for (int i = 0; i < arguments.count(); ++ i) {
        QVariant argument = arguments[i];
        QVariant::Type type = argument.type();

        if (type == QVariant::Type::Int) {
            packet << argument.toInt();
        } else if (type == QMetaType::Float) {
            packet << argument.toFloat();
        } else if (type == QMetaType::QString) {
            packet << argument.toString().toStdString().c_str();
        //} else if (type == QMetaType::QByteArray) {
        //    osc::Blob b(argument.toByteArray().constData());
        //    packet << b;
        } else if (type == QMetaType::Bool) {
            packet << argument.toBool();
        }
        // TODO: implement other OSC types
    }

    packet << osc::EndMessage << osc::EndBundle;
    outputResult.append(packet.Data(), packet.Size());
}
