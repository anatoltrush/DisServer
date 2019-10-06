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
    qDebug() << "DISCONNECTED FROM DATABASE";
}

bool dis::DBController::doQuery(const QString &string){
    words = string.split(separToken); // CONFIG TOKEN

    if(parseQuery()) return true;
    else{
        qDebug() << "Query NOT done";
        return false;
    }
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
            dis::Discussion disc; // get by words
            discussionAPI.addDispute(dataBase, disc);
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
            discussionAPI.deleteDisputeByUuid(dataBase, "test");
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
