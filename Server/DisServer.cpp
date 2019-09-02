#include "DisServer.h"

dis::DisServer::DisServer(){
    tcpServer = new QTcpServer;

    connect(tcpServer, &QTcpServer::newConnection, this, &DisServer::slotNewConnection);
}

dis::DisServer::~DisServer(){
    for(const auto &client : clients)
        client.socket->close();
    delete tcpServer;
}

void dis::DisServer::slotNewConnection(){
    dis::Client newClient;
    newClient.socket = tcpServer->nextPendingConnection();
    clients.push_back(newClient);
}
