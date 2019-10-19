#include "SystemAPI.h"

dis::SystemAPI::SystemAPI(){
}

void dis::SystemAPI::sendToAll(const QList<dis::Client> &clients, const QByteArray &message){}

void dis::SystemAPI::kickByTime(QList<dis::Client> &clients){}

void dis::SystemAPI::logOut(QStringMap &allTokens, const QString &userToken){
    for(int i = 0; i < allTokens.size(); i++)
        if(allTokens.values()[i] == userToken)
            allTokens.erase(allTokens.begin() + i);
}

bool dis::SystemAPI::isAuthorized(const QStringMap &allTokens, const QString &userToken, QString &currUsr){
    for(int i = 0; i < allTokens.size(); i++)
        if(allTokens.values()[i] == userToken){
            currUsr = allTokens.keys()[i];
            return true;
        }
    return false;
}

bool dis::SystemAPI::checkPswrd(const QSqlDatabase &db, const QString &tableName, const QString &pswrd, QString &uuid){
    QSqlQuery query(db);
    query.prepare("SELECT UUID, Password FROM " + tableName + " WHERE Password = ?");
    query.addBindValue(pswrd);
    if(query.exec()){
        if(query.first()){
            QSqlRecord record = query.record();
            uuid = query.value(record.indexOf("UUID")).toString();
            return true;
        }
        else return false;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::SystemAPI::isEmailExsist(const QSqlDatabase &db, const QString &tableName, const QString &Email, bool &isExsist){
    QSqlQuery query(db);
    query.prepare("SELECT UUID FROM " + tableName + " WHERE Email = ?");
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
