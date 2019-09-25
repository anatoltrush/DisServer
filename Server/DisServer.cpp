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
    newClient.connection_time = QDateTime::currentDateTime();

    connect(newClient.socket, &QTcpSocket::readyRead, this, &DisServer::slotReadyRead);
    connect(newClient.socket, &QTcpSocket::disconnected, this, &DisServer::slotClientDisconnected);
    connect(newClient.socket, &QTcpSocket::destroyed, this, &DisServer::slotSocketDeleted);

    clients.push_back(newClient);
}

void dis::DisServer::slotReadyRead(){
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

    QString reqst(socket->readAll());
    qDebug() << reqst;
    QStringList fullWords = reqst.split("\r\n");
    QStringList infoWords = fullWords.front().split("/");

    QString resp;
    resp += "<b>DISPUTE CONNECTED!</b>";
    resp += "<hr size=5; color=FF0000>";
    resp += "<br>";

    if(infoWords[1].contains("discussion")){
        dbcntr.connect("DRIVER={SQL Server};SERVER=250PC;DATABASE=Disput_db;Trusted_Connection=yes;");
        QList<dis::Discussion>discs;
        dbcntr.discussionAPI.getDiscussions(dbcntr.dataBase, discs);
        dbcntr.disconnect();

        for(const auto &disc : discs){
            resp += "<li>";
            resp += "<b>-----";
            resp += "-----</b>";
            resp += "<br>";
            resp += "<hr>";
        }
    }
    else{
        resp += "<a href= /discussion >DISCUSSIONS</a>";
    }

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
