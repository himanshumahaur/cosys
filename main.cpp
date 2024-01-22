#include "cosys.h"
#include "main.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server udpServer;
    cosys w;

    QObject::connect(&udpServer, &Server::recvCmd, &w, &cosys::onCmd);
    QObject::connect(&w, &cosys::recvRes, &udpServer, &Server::OnRes);

    w.show();
    return a.exec();
}
