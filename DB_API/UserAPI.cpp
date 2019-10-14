#include "UserAPI.h"

dis::UserAPI::UserAPI() : IdbAPI ("Users", "users"){}

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
        QSqlRecord record = query.record();
        user.fillBySQL(query, record);
        return true;
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

int dis::UserAPI::getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives> > &primitives, QList<QString> &uuids){
    primitives.clear();
    uuids.clear();
    // -----
}
