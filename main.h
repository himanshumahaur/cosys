#ifndef MAIN_H
#define MAIN_H

#include <QObject>
#include <QUdpSocket>
#include <QTextStream>

class Server : public QObject
{
    Q_OBJECT

public:
    QHostAddress sender;
    quint16 senderPort;

    Server(QObject *parent = nullptr) : QObject(parent)
    {
        udpSocket = new QUdpSocket(this);

        connect(udpSocket, &QUdpSocket::readyRead, this, &Server::readCmd);

        if (!udpSocket->bind(QHostAddress::Any, 23456))
        {
            QTextStream(stderr) << "Failed to bind UDP socket" << Qt::endl;
        }
        else
        {
            QTextStream(stdout) << "UDP Server listening on port 23456..." << Qt::endl;
        }
    }

    virtual ~Server() {};

signals:
    void recvCmd(QString cmd);

private slots:
    void readCmd()
    {
        QString cmd;

        while (udpSocket->hasPendingDatagrams())
        {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());

            udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

            cmd += datagram.constData();
        }

        QTextStream(stdout) << "Received: " << cmd << Qt::endl;

        emit recvCmd(cmd);
    }

public slots:
    void OnRes(QString res)
    {
        QByteArray responseData = res.toUtf8();
        udpSocket->writeDatagram(responseData, sender, senderPort);
        QTextStream(stdout) << "Sending: " << res << Qt::endl;
    }

private:
    QUdpSocket *udpSocket;
};

#endif // MAIN_H
