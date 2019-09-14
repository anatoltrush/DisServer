#include "DisServer.h"

dis::DisServer::DisServer(){
    webServer = new QWebSocketServer("DisServer", QWebSocketServer::NonSecureMode);

    connect(webServer, &QWebSocketServer::newConnection, this, &DisServer::slotNewConnection);
}

dis::DisServer::~DisServer(){
    webServer->close();
    for(const auto& cl : clients)
        delete cl.websocket;
}

void dis::DisServer::slotNewConnection(){
    dis::Client newClient;
    newClient.websocket = webServer->nextPendingConnection();

    connect(newClient.websocket, &QWebSocket::textMessageReceived, this, &DisServer::slotTextMessage);
    connect(newClient.websocket, &QWebSocket::binaryMessageReceived, this, &DisServer::slotBinaryMessage);
    connect(newClient.websocket, &QWebSocket::disconnected, this, &DisServer::slotClientDisconnected);

    clients.push_back(newClient);
}

void dis::DisServer::slotTextMessage(QString message){
    std::cout << message.toStdString() << std::endl;
}

void dis::DisServer::slotBinaryMessage(QByteArray message){}

void dis::DisServer::slotClientDisconnected(){}
