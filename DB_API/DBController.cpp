#include "DBController.h"

dis::DBController::DBController(){}

bool dis::DBController::connect(const QString &connectString){
    dataBase = QSqlDatabase::addDatabase("QODBC3");
    dataBase.setDatabaseName(connectString);
    //    db.setUserName("250PC\\Anatol250");
    //    db.setPassword("");
    if(dataBase.open()){
        connected = true;
        connString = connectString;
        qDebug() << "CONNECTED: "+ connString;
        return true;
    }
    else{
        connected = false;
        qDebug() << "Not connected to DataBase";
        return false;
    }
}

dis::DBController::~DBController(){
    disconnect();
}

void dis::DBController::disconnect(){
    dataBase.close();
}

bool dis::DBController::doQuery(const QByteArray &array){
    if(parseByteArray(array)){
        if(parseQuery()) return true;
        else{
            qDebug() << "Query NOT done";
            return false;
        }
    }
    else{
        qDebug() << "QByteArray NOT parsed";
        return false;
    }
}

bool dis::DBController::doQuery(){

}

bool dis::DBController::parseByteArray(const QByteArray &array){
    QString strArray = QString(array);
    if(strArray.size() <= 0) return false;

    words.clear();
    words = strArray.split('_'); // CONFIG TOKEN
    if(words.size() <= 0) return false;

    return true;
}

dis::User dis::DBController::getUserFromWords(){
    dis::User usr;
    usr.fillByList(words);
    return usr;
}

bool dis::DBController::parseQuery(){
    if(!connected){
        qDebug() << "Base NOT connected";
        return false;
    }

    if(words.at(0) == "POST"){
        if(words.at(1) == "User"){
            dis::User usr = getUserFromWords();
            if(userAPI.addUser(dataBase, usr)) return true;
            else{
                qDebug() << "User NOT added";
                return false;
            }
        }
        if(words.at(1) == "Discussion"){
            discussionAPI.addDiscussion();
        }
        if(words.at(1) == "Purchase"){
            purchaseAPI.addPurchase();
        }
    }
    if(words.at(0) == "GET"){
        if(words.at(1) == "User"){
        }
        if(words.at(1) == "Discussion"){
        }
        if(words.at(1) == "Purchase"){
        }
    }
    if(words.at(0) == "PUT"){ // update all fields in record
        if(words.at(1) == "User"){
        }
        if(words.at(1) == "Discussion"){
        }
        if(words.at(1) == "Purchase"){
        }
    }
    if(words.at(0) == "DELETE"){
        if(words.at(1) == "User"){
            QString usUUID = words.at(2);
            userAPI.deleteUser(dataBase, usUUID);
        }
        if(words.at(1) == "Discussion"){
            discussionAPI.deleteDiscussion();
        }
        if(words.at(1) == "Purchase"){
            purchaseAPI.deletePurchase();
        }
    }
    if(words.at(0) == "PATCH"){ // update several fields in record
        if(words.at(1) == "User"){
        }
        if(words.at(1) == "Discussion"){
        }
        if(words.at(1) == "Purchase"){
        }
    }
    if(words.at(0) == "OPTION"){
        if(words.at(1) == "Test"){
        }
    }
    else{
        // TODO: default parseQuery
    }
}
