#include "UserAPI.h"

dis::UserAPI::UserAPI() : IdbAPI (TABLE_USERS, API_TYPE_USERS){}

bool dis::UserAPI::addUser(const dis::User &user){
    QSqlQuery query(db);
    QString request("INSERT INTO " + tableName + " (" + PROP_USR_UUID + ", " + PROP_USR_NAME + ", " + PROP_USR_SNAME + ", " + PROP_USR_CNTRY + ","
                                                  " " + PROP_USR_CITY + ", " + PROP_USR_EMAIL + ", " + PROP_USR_SEX + ", " + PROP_USR_PREF + ","
                                                  " " + PROP_USR_NICK + ", " + PROP_USR_PSWRD + ", " + PROP_USR_MNY + ", " + PROP_USR_SCORE + ","
                                                  " " + PROP_USR_TIME_BRTH + ", " + PROP_USR_TIME_REG + ", " + PROP_USR_AVTR + ", " + PROP_USR_W + ","
                                                  " " + PROP_USR_H + ", " + PROP_USR_FRMT + ") "
                                                 "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.prepare(request);
    query.addBindValue(user.uuid);
    query.addBindValue(user.name);
    query.addBindValue(user.surname);
    query.addBindValue(user.country);
    query.addBindValue(user.city);
    query.addBindValue(user.email);
    query.addBindValue(user.sex);
    query.addBindValue(user.preference);
    query.addBindValue(user.nickName);
    query.addBindValue(user.password);
    query.addBindValue(user.money);
    query.addBindValue(user.score);
    query.addBindValue(user.time_birth);
    query.addBindValue(user.time_registration);
    query.addBindValue(user.avtr_data);
    query.addBindValue(user.avtr_w);
    query.addBindValue(user.avtr_h);
    query.addBindValue(user.format);

    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::UserAPI::deleteUser(const QString &uuid){
    QSqlQuery query(db);
    query.prepare("DELETE FROM " + tableName + " WHERE " + PROP_USR_UUID + " = ?");
    query.addBindValue(uuid);
    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::UserAPI::updateUser(const QString& uuid, const dis::User &newData){ // TODO: fill all fields in "UserAPI::updateUser"
    QSqlQuery query(db);
    query.prepare("UPDATE " + tableName + " SET " + PROP_USR_NAME + " = ?,"
                                          " " + PROP_USR_SNAME + " = ?, " + PROP_USR_CNTRY + " = ? WHERE " + PROP_USR_UUID + " = ?");
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
    query.prepare("SELECT * FROM " + tableName + " WHERE " + PROP_USR_UUID + " = ?");
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

bool dis::UserAPI::checkPswrd(const QString &pswrd, QString &uuid){
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

bool dis::UserAPI::isExsistEmail(const QString &Email, bool &isExsist){
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

bool dis::UserAPI::isExsistNick(const QString &Nick, bool &isExsist){
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

bool dis::UserAPI::getObjectPart(const dis::HttpParser &parser, std::unique_ptr<dis::IPrimitive> &object){
    object = std::make_unique<User>();
    QString uuidForDel = parser.params.value(PROP_USR_UUID).toString();

    QSqlQuery query(db);
    query.prepare("SELECT " + QString(PROP_USR_UUID) + " FROM " + tableName + " WHERE " + PROP_USR_UUID + " = ?");
    query.addBindValue(uuidForDel);
    if(query.exec()){
        if(query.first()){
            QSqlRecord record = query.record();
            object->fillBySQL(query, record);
            return true;
        }
        else return false;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

int dis::UserAPI::getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive> > &entities, QList<QString> &primitives){
    entities.clear();
    primitives.clear();
    // -----
    return HTTP_METHOD_NOT_ALLOWED;
}

int dis::UserAPI::postFunction(const dis::HttpParser &parser){/*LEAVE EMPTY*/}

int dis::UserAPI::patchFunction(const dis::HttpParser &parser){}

int dis::UserAPI::deleteFunction(const HttpParser &parser){
    // del Usr+Imgs+Flwers+Flwings+ListOfVoted
    // Диспуты юзера не удаляются
}
