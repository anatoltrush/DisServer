#include "UserAPI.h"

dis::UserAPI::UserAPI() : IdbAPI ("Users", API_TYPE_USERS){}

dis::UserAPI::~UserAPI(){}

bool dis::UserAPI::addUser(const dis::User &user){
    QSqlQuery query(db);
    query.prepare("INSERT INTO " + tableName + " (UUID, Name, Surname, Country) "
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

bool dis::UserAPI::deleteUser(const QString &uuid){
    QSqlQuery query(db);
    query.prepare("DELETE FROM " + tableName + " WHERE UUID = ?");
    query.addBindValue(uuid);
    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::UserAPI::updateUser(const QString& uuid, const dis::User &newData){
    QSqlQuery query(db);
    query.prepare("UPDATE " + tableName + " SET Name = ?, Surname = ?, Country = ? WHERE UUID = ?");
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

bool dis::UserAPI::getUserByUuid(const QString &uuid, dis::User &user){
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + tableName + " WHERE UUID = ?");
    query.addBindValue(uuid);
    if(query.exec()){
        if(query.first()){
            QSqlRecord record = query.record();
            user.fillBySQL(query, record);
            return true;
        }
        else return false;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::UserAPI::getUsers(QList<dis::User> &users){
    users.clear();
    QSqlQuery query(db);
    QString strQuery = "SELECT * FROM " + tableName;
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

int dis::UserAPI::getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitives> > &entities, QList<QString> &primitives){
    entities.clear();
    primitives.clear();
    // -----
    return HTTP_METHOD_NOT_ALLOWED;
}
