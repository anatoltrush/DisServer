#include "SystemAPI.h"

qint64 dis::SystemAPI::maxTime = 82800; // 23hrs
float dis::SystemAPI::needFreeMemPercs = 40.0f; // 40%
float dis::SystemAPI::percLeft = 0.9f; // left 90% of users

dis::SystemAPI::SystemAPI(){}

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

float dis::SystemAPI::getFreeMemSize(){
#ifdef linux
    // Linux code
    qDebug() << "SystemAPI::getFreeMemSize NOT IMPLEMENTED IN LINUX OS";

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

#else
    //For other OS
    qDebug() << "SystemAPI::getFreeMemSize NOT IMPLEMENTED IN THIS OS";
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
        if(seconds > dis::SystemAPI::maxTime)
            clients.pop_back();
        else break;
    }
}

void dis::SystemAPI::kickByNumber(QList<dis::Client> &clients){
    int newSz = clients.size() * dis::SystemAPI::percLeft;
    while(clients.size() > newSz)
        clients.pop_back();
}
