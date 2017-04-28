#include "oscreceiver.h"
#include "osc/OscTypes.h"
#include "osc/OscReceivedElements.h"

OscReceiver::OscReceiver(quint16 receivePort, QObject *parent) :
        QObject(parent)
{
    m_udpSocket = new QUdpSocket(this);
    m_udpSocket->bind(QHostAddress::LocalHost, receivePort);

    connect(m_udpSocket, &QUdpSocket::readyRead, this, [this]() {
        while (this->m_udpSocket->hasPendingDatagrams()) {
            QNetworkDatagram datagram = this->m_udpSocket->receiveDatagram();
            // XXX: we could also retrieve the sender host and port
            QByteArray data = datagram.data();
            QVariantList arguments;
            QString oscAddress;
            this->byteArrayToVariantList(arguments, oscAddress, data);
            emit messageReceived(oscAddress, arguments);
        }
    });
}

void OscReceiver::byteArrayToVariantList(QVariantList& outputVariantList, QString& outputOscAddress, const QByteArray& inputByteArray) {
    osc::ReceivedPacket packet(inputByteArray.data(), inputByteArray.size());
    // TODO: catch parsing exceptions
    if (packet.IsMessage()) {
        osc::ReceivedMessage message(packet);
        // Get address pattern
        QString address(message.AddressPattern());
        outputOscAddress.replace(0, address.size(), address);

        for (auto iter = message.ArgumentsBegin(); iter != message.ArgumentsEnd(); ++ iter) {
            osc::ReceivedMessageArgument argument = (*iter);
            if (argument.IsBool()) {
                outputVariantList.append(QVariant(argument.AsBool()));
            } else if (argument.IsString()) {
                outputVariantList.append(QVariant(argument.AsString()));
            } else if (argument.IsInt32()) {
                outputVariantList.append(QVariant(argument.AsInt32()));
            } else if (argument.IsFloat()) {
                outputVariantList.append(QVariant(argument.AsFloat()));
            } else if (argument.IsChar()) {
                outputVariantList.append(QVariant(argument.AsChar()));
            //} else if (argument.IsInt64()) {
            //    outputVariantList.append(QVariant(argument.AsInt64()));
            } else if (argument.IsDouble()) {
                outputVariantList.append(QVariant(argument.AsDouble()));
            }
            // TODO: support Array, Midi, Blob, Symbol, TimeTag, RGBA, Nil
        }
    } // TODO: also parse bundles
}
