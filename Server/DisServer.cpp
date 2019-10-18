#include "DisServer.h"

dis::DisServer::DisServer(){
    tcpServer = new QTcpServer;

    connect(tcpServer, &QTcpServer::newConnection, this, &DisServer::slotNewConnection);

    dbcntr.connect("DRIVER={SQL Server};SERVER=250PC;DATABASE=Disput_db;Trusted_Connection=yes;");
}

dis::DisServer::~DisServer(){}

void dis::DisServer::slotNewConnection(){
    dis::Client newClient;
    newClient.socket = tcpServer->nextPendingConnection();
    newClient.connection_time = QDateTime::currentDateTimeUtc();

    connect(newClient.socket, &QTcpSocket::readyRead, this, &DisServer::slotReadyRead);
    connect(newClient.socket, &QTcpSocket::disconnected, this, &DisServer::slotClientDisconnected);
    connect(newClient.socket, &QTcpSocket::destroyed, this, &DisServer::slotSocketDeleted);

    clients.push_back(newClient);
}

void dis::DisServer::slotReadyRead(){
    auto begin = std::chrono::steady_clock::now();

    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

    QByteArray readAll = socket->readAll();
    QString reqst(readAll);

    HttpParser httpParser;
    httpParser.parse(readAll);

    HttpResponse httpResponse;

    HttpHandler httpHandler;
    httpHandler.handle(httpParser, dbcntr, httpResponse, Uuid_Token);

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
    for(int i = 0; i < clients.size(); i++){
        if(!clients[i].socket->isValid()){
            clients.erase(clients.begin() + i);
            i--;
        }
    }
}
