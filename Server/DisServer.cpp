#include "DisServer.h"

dis::DisServer::DisServer(){
    tcpServer = new QTcpServer;

    connect(tcpServer, &QTcpServer::newConnection, this, &DisServer::slotNewConnection);

    dbcntr.connect("DRIVER={SQL Server};SERVER=250PC;DATABASE=Disput_db;Trusted_Connection=yes;");
}

dis::DisServer::~DisServer(){}

void dis::DisServer::slotNewConnection(){
    QTcpSocket* tcpSock = tcpServer->nextPendingConnection();
    connect(tcpSock, &QTcpSocket::readyRead, this, &DisServer::slotReadyRead);
    connect(tcpSock, &QTcpSocket::disconnected, this, &DisServer::slotClientDisconnected);
    connect(tcpSock, &QTcpSocket::destroyed, this, &DisServer::slotSocketDeleted);
    sockets.push_back(tcpSock);
}

void dis::DisServer::slotReadyRead(){
    auto begin = std::chrono::steady_clock::now();

    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    qDebug() << socket->socketDescriptor();

    QByteArray readAll = socket->readAll();
    QString reqst(readAll);

    HttpParser httpParser;
    httpParser.parse(readAll);

    HttpResponse httpResponse;

    HttpHandler httpHandler;
    httpHandler.handle(httpParser, dbcntr, httpResponse, clients);

    httpResponse.createResponse(httpParser, httpHandler.status /*, userToken*/);

    qDebug() << reqst;
    qDebug() << httpResponse.responseQBA;

    socket->write(httpResponse.responseQBA);
    socket->disconnectFromHost();

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    qDebug() << "-----> Time: " << elapsed_ms.count() << " ms\n";
}

void dis::DisServer::slotClientDisconnected(){
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    socket->close();
    socket->deleteLater();
}

void dis::DisServer::slotSocketDeleted(){
    for(int i = 0; i < sockets.size(); i++)
        if(!sockets[i]->isValid())
            sockets.erase(sockets.begin() + i);
}
