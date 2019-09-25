#include "UserAPI.h"

dis::UserAPI::UserAPI(){}

dis::UserAPI::~UserAPI(){}

bool dis::UserAPI::addUser(const QSqlDatabase &db, const dis::User &user){
    QSqlQuery query(db);
    query.prepare("INSERT INTO Users (UUID, Name, Surname, Country) "
                  "VALUES (?, ?, ?, ?)");
    query.addBindValue(user.uuid);
    query.addBindValue(user.name);
    query.addBindValue(user.surname);
    query.addBindValue(user.country);

    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::UserAPI::deleteUser(const QSqlDatabase& db, const QString &uuid){
    QSqlQuery query(db);
    query.prepare("DELETE FROM Users WHERE UUID = ?");
    query.addBindValue(uuid);
    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::UserAPI::updateUser(const QSqlDatabase &db, const QString& uuid, const dis::User &newData){
    QSqlQuery query(db);
    query.prepare("UPDATE Users SET Name = ?, Surname = ?, Country = ? WHERE UUID = ?");
    query.addBindValue(newData.name);
    query.addBindValue(newData.surname);
    query.addBindValue(newData.country);
    query.addBindValue(uuid);

    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::UserAPI::getUserByUuid(const QSqlDatabase& db, const QString &uuid, dis::User &user){
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Users WHERE UUID = ?");
    query.addBindValue(uuid);
    if(query.exec()){
        if(query.first()){
            QSqlRecord record = query.record();
            user.fillBySQL(query, record);
            return true;
        }
        else{
            qDebug() << db.lastError().text();
            return false;
        }
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::UserAPI::getUsers(const QSqlDatabase& db, QList<dis::User> &users){
    users.clear();
    QSqlQuery query(db);
    QString strQuery = "SELECT * FROM Users";
    if(query.exec(strQuery)){
        QSqlRecord record = query.record();
        while(query.next()) {
            dis::User usr;
            usr.fillBySQL(query, record);
            users.push_back(usr);
        }
        return true;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}
