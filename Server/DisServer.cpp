#include "DisServer.h"

dis::DisServer::DisServer(){
    tcpServer = new QTcpServer;

    connect(tcpServer, &QTcpServer::newConnection, this, &DisServer::slotNewConnection);
//    connect(this, SIGNAL(socketDeleted()), this, SLOT(slotSocketDeleted()));
}

dis::DisServer::~DisServer(){}

void dis::DisServer::slotNewConnection(){
    dis::Client newClient;
    newClient.socket = tcpServer->nextPendingConnection();

    connect(newClient.socket, &QTcpSocket::readyRead, this, &DisServer::slotReadyRead);
    connect(newClient.socket, &QTcpSocket::disconnected, this, &DisServer::slotClientDisconnected);
    connect(newClient.socket, &QTcpSocket::destroyed, this, &DisServer::slotSocketDeleted);

    clients.push_back(newClient);
}

void dis::DisServer::slotReadyRead(){
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

    qDebug() << socket->readAll();

    QString resp = "HTTP/1.1 200 OK\r\n\r\n";

    resp += "<b>DISPUTE CONNECTED!</b>";
    resp += "<hr noshade>";
    resp += "<br>";
    resp += "<a href= /users HTTP/1.1>USERS</a>";
    resp += "<br>";
    resp += "<a href= /discussions >DISCUSSIONS</a>";

    QByteArray arr;
    arr.append(resp);
    socket->write(arr);

    socket->disconnectFromHost();
}

void dis::DisServer::slotClientDisconnected(){
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    socket->close();
    socket->deleteLater();
}

void dis::DisServer::slotSocketDeleted(){
    for(int i = 0; i < clients.size(); i++){
        if(!clients[i].socket->isValid()){
            clients.erase(clients.begin() + i);
            i--;
        }
    }
}
