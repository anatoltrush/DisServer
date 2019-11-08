#include "SystemAPI.h"

dis::SystemAPI::SystemAPI(){
}

void dis::SystemAPI::sendToAll(const QList<dis::Client> &clients, const QByteArray &message){}

void dis::SystemAPI::kickByTime(QList<dis::Client> &clients){}

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

bool dis::SystemAPI::checkPswrd(const QSqlDatabase &db, const QString &tableName, const QString &pswrd, QString &uuid){
    if(pswrd.isEmpty()) return false;
    QSqlQuery query(db);
    query.prepare("SELECT " + QString(PROP_USR_UUID) + " FROM " + tableName + " WHERE " + PROP_USR_PSWRD + " = ?");
    query.addBindValue(pswrd);
    if(query.exec()){
        if(query.first()){
            QSqlRecord record = query.record();
            uuid = query.value(record.indexOf(PROP_USR_UUID)).toString();
            return true;
        }
        else return false;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::SystemAPI::isExsistEmail(const QSqlDatabase &db, const QString &tableName, const QString &Email, bool &isExsist){
    QSqlQuery query(db);
    query.prepare("SELECT " + QString(PROP_USR_UUID) + " FROM " + tableName + " WHERE " + PROP_USR_EMAIL + " = ?");
    query.addBindValue(Email);
    if(query.exec()){
        if(query.first()) isExsist = true;
        else isExsist = false;
        return true;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::SystemAPI::isExsistNick(const QSqlDatabase &db, const QString &tableName, const QString &Nick, bool &isExsist){
    QSqlQuery query(db);
    query.prepare("SELECT " + QString(PROP_USR_UUID) + " FROM " + tableName + " WHERE " + PROP_USR_NICK + " = ?");
    query.addBindValue(Nick);
    if(query.exec()){
        if(query.first()) isExsist = true;
        else isExsist = false;
        return true;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}
