#include "SystemAPI.h"

qint64 dis::SystemAPI::maxTimeLastReq = 82800; // 23hrs
int dis::SystemAPI::minNumberUsers = 10000; // min number of users to not delete

float dis::SystemAPI::needFreeRamPerc = 40.0f; // 40%
float dis::SystemAPI::percRamLeft = 0.9f; // left 90% of users

float dis::SystemAPI::minFreeFilePerc = 10.0f; // 10%
float dis::SystemAPI::minFileSizeMB = 10000.0f; // 10000MB/10GB

void dis::SystemAPI::sendToAll(const QList<dis::Client> &clients, const QByteArray &message){}

bool dis::SystemAPI::isAlreadyIn(const QList<dis::Client> &clients, const QString &userUuid){
    for(const auto &client : clients)
        if(client.uuid == userUuid)
            return true;
    return false;
}

void dis::SystemAPI::logOut(QList<dis::Client> &clients, const QString &userToken){
    for(int i = 0; i < clients.size(); i++)
        if(clients[i].authorToken == userToken)
            clients.erase(clients.begin() + i);
}

bool dis::SystemAPI::isAuthorized(QList<dis::Client> &clients, const QString &userToken, QString &currUser){
    for(int i = 0; i < clients.size(); i++)
        if(clients[i].authorToken == userToken){
            currUser = clients[i].uuid;
            clients[i].lastRequestTime = QDateTime::currentDateTime();
            return true;
        }
    return false;
}

float dis::SystemAPI::getFreeRamPerc(){
#ifdef linux
    // Linux code
    qDebug() << "SystemAPI::getFreeMemSize NOT IMPLEMENTED IN LINUX OS";
    return 100.0f;

#elif _WIN32
    MEMORYSTATUSEX memory_status;
    memory_status.dwLength = sizeof(MEMORYSTATUSEX);

    if(GlobalMemoryStatusEx(&memory_status)){
        unsigned long long int fullMem = memory_status.ullTotalPhys / (1024 * 1024);
        unsigned long long int busyMem = memory_status.ullAvailPhys / (1024 * 1024);

        float perc = (busyMem / static_cast<float>(fullMem)) * 100.0f;
        if(perc < 5.0f) qDebug() << "WARNING: INSUFFICIENT OF FREE MEMORY!!! " << perc << "%";
        return perc;
    }
    else{
        qDebug() << "WARNING: SystemAPI::getFreeMemSize ---> Unknown RAM";
        return 100.0f;
    }

#elif __APPLE__
    // Mac code
    qDebug() << "SystemAPI::getFreeMemSize NOT IMPLEMENTED IN MAC OS";
    return 100.0f;

#else
    //For other OS
    qDebug() << "SystemAPI::getFreeMemSize NOT IMPLEMENTED IN THIS OS";
    return 100.0f;
#endif
}

QDateTime dis::SystemAPI::getTimeDiff(const QDateTime &lastReq){
    QDateTime now = QDateTime::currentDateTime();

    qint64 seconds = lastReq.secsTo(now);
    QDateTime interval = QDateTime::fromSecsSinceEpoch(seconds);
    interval = interval.addYears(-1970);
    interval = interval.addSecs(-10800); // -3 hours (TimeZone)
    return interval;
}

void dis::SystemAPI::kickByTime(QList<dis::Client> &clients){
    while(true){
        QDateTime now = QDateTime::currentDateTime();
        qint64 seconds = clients.back().lastRequestTime.secsTo(now);
        if(seconds > dis::SystemAPI::maxTimeLastReq)
            clients.pop_back();
        else break;
    }
}

void dis::SystemAPI::kickByNumber(QList<dis::Client> &clients){
    int newSz = clients.size() * dis::SystemAPI::percRamLeft;
    while(clients.size() > newSz)
        clients.pop_back();
}

bool dis::SystemAPI::getFileSize(const QSqlDatabase &dataBase, float &val){
    QSqlQuery query(dataBase);
    QString strQuery = "SELECT CAST(size / 128.0 AS DECIMAL(17,2)) AS [SizeMB] FROM sys.database_files WHERE name = '" + QString(DB_NAME) + "'";
    query.prepare(strQuery);
    if(query.exec()){
        if(query.first()){
            val = query.value(0).toFloat();
            return true;
        }
        else return false;
    }
    else{
        qDebug() << dataBase.lastError().text();
        return false;
    }
}

bool dis::SystemAPI::getUnAlloc(const QSqlDatabase &dataBase, float &val){
    QSqlQuery query(dataBase);
    QString strQuery = "USE [" + QString(DB_NAME) + "] EXEC sp_spaceused";
    query.prepare(strQuery);
    if(query.exec()){
        if(query.first()){
            QString data = query.value(2).toString();
            data.chop(3);
            val = data.toFloat();
            return true;
        }
        else return false;
    }
    else{
        qDebug() << dataBase.lastError().text();
        return false;
    }
}

void dis::SystemAPI::shrinkDBaseFiles(const QSqlDatabase &dataBase){
    QSqlQuery query(dataBase);
    QString request = "DBCC SHRINKFILE ('" + QString(DB_NAME) + "', 0) DBCC SHRINKFILE ('" + DB_NAME_LOG + "', 0)";
    query.prepare(request);
    if(query.exec()) qDebug() << "LOG: SHRINK OF DATABASE FILES IS DONE";
    else{
        qDebug() << "LOG: ERROR WHILE SHRINKING OF DATABASE FILES!!!";
        qDebug() << dataBase.lastError().text();
    }
}
