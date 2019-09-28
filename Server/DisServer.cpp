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
    resp += "HTTP/1.1 200 OK\r\n\r\n";
    resp += "<b>DISPUTE CONNECTED!</b>";
    resp += "<hr size=8; color=FF0000>";
    resp += "<br>";

    if(infoWords[1].contains("discussion")){        
        QList<dis::Discussion>discs;
        dbcntr.discussionAPI.getDiscussions(dbcntr.dataBase, discs);
        dbcntr.disconnect();

        resp += "<b>&emsp;&emsp;ID&emsp; &brvbar;Section&emsp; &brvbar;Topic&emsp; &brvbar;Reward&emsp; &brvbar;Created&emsp; &brvbar;Lang</b><br><hr>";
        for(const auto &disc : discs){
            resp += "<li>";
            resp += "<b>";

            resp += disc.uuid + "&nbsp; &brvbar;";
            resp += "&nbsp" + disc.section + "&nbsp; &brvbar;";
            resp += "&nbsp" + disc.topic + "&nbsp; &brvbar;";
            resp += "&nbsp" + QString::number(disc.reward) + "&nbsp; &brvbar;";
            resp += "&nbsp" + disc.time_create + "&nbsp; &brvbar;";
            resp += "&nbsp" + disc.languageRegion;

            resp += "</b>";
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
