#include "DBController.h"

dis::DBController::DBController(){}

bool dis::DBController::connect(const QString &connectString){
    dataBase = QSqlDatabase::addDatabase("QODBC3");
    dataBase.setDatabaseName(connectString);
    //    db.setUserName("250PC\\Anatol250");
    //    db.setPassword("");
    return  dataBase.open();
}

void dis::DBController::disconnect(){
    dataBase.close();
}

bool dis::DBController::parseByteArray(const QByteArray &array){
// make list of words
}

bool dis::DBController::parseQuery(){
    if(words.at(0) == "POST"){
        if(words.at(1) == "User"){
            userAPI.addUser(dataBase); // TODO: implement
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
            userAPI.deleteUser(dataBase);
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
        // TODO:
    }
}

dis::DBController::~DBController(){
    disconnect();
}
