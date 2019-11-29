#include "DisServer.h"

dis::DisServer::DisServer(){
    tcpServer = new QTcpServer;

    timerKick = new QTimer(this);
    timerKick->setInterval(60000); // config tick time in msec
    timerKick->start();

    timerShrink = new QTimer(this);
    timerShrink->setInterval(1000); // config tick time in msec
    timerShrink->start();

    connect(tcpServer, &QTcpServer::newConnection, this, &DisServer::slotNewConnection);

    connect(timerKick, &QTimer::timeout, this, &DisServer::slotTickKick);
    connect(timerShrink, &QTimer::timeout, this, &DisServer::slotTickShrink);

    dbcntr.connect("DRIVER={SQL Server};SERVER=250PC;DATABASE=Disput_db;Trusted_Connection=yes;");

//    clients.push_back(Client("1", "11", QDateTime::fromString("21.11.2019 16:52", Qt::SystemLocaleShortDate)));
}

dis::DisServer::~DisServer(){
    delete tcpServer;
    delete timerKick;
    delete timerShrink;
}

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

bool byLastReq(const dis::Client& clFrst, const dis::Client& clSec){return clFrst.lastRequestTime > clSec.lastRequestTime;}

void dis::DisServer::slotTickKick(){
    if(tcpServer->isListening()){
        while(true){
            if(clients.size() < dis::SystemAPI::minNumberUsers) break;
            // -----
            if(dis::SystemAPI::getFreeRamPerc() >= dis::SystemAPI::needFreeRamPerc) break;
            // free by time
            std::sort(clients.begin(), clients.end(), byLastReq);
            dis::SystemAPI::kickByTime(clients);
            // -----
            if(dis::SystemAPI::getFreeRamPerc() >= dis::SystemAPI::needFreeRamPerc) break;
            // free by num
            dis::SystemAPI::kickByNumber(clients);
            // -----
            if(dis::SystemAPI::getFreeRamPerc() >= dis::SystemAPI::needFreeRamPerc) break;
        }
    }
}

void dis::DisServer::slotTickShrink(){
    if(tcpServer->isListening()){
        float fileSz = 0.0f;
        bool isGotFileSz = dis::SystemAPI::getFileSize(dbcntr.dataBase, fileSz);
        if(!isGotFileSz || fileSz < dis::SystemAPI::minFileSizeMB) return;

        float unallocSz = 0.0f;
        bool isGotUnalloc = dis::SystemAPI::getUnAlloc(dbcntr.dataBase, unallocSz);
        if(!isGotUnalloc) return;

        float currFreePerc = unallocSz / fileSz * 100.0f;
        if(currFreePerc > dis::SystemAPI::minFreeFilePerc)
            dis::SystemAPI::shrinkDBaseFiles(dbcntr.dataBase);
    }
}
