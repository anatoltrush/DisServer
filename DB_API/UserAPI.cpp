#include "UserAPI.h"

dis::UserAPI::UserAPI(){}

bool dis::UserAPI::addUser(const QSqlDatabase &db){

}

bool dis::UserAPI::deleteUser(const QSqlDatabase& db){

}

bool dis::UserAPI::redactUser(const QSqlDatabase &db){

}

bool dis::UserAPI::getUser(const QSqlDatabase& db, dis::User &user){

}

bool dis::UserAPI::getUsers(const QSqlDatabase& db, QList<User> &users){
    users.clear();
    QSqlQuery query(db);
    QString strQuery = "SELECT * FROM Users";
    if(query.exec(strQuery)){
        QSqlRecord record = query.record();
        while(query.next()) {
            dis::User usr;
            usr.fillData(query, record);
            users.push_back(usr);
        }
        return true;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}
