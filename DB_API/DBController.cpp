#include "DBController.h"

dis::DBController::DBController(){
    dbAPIs.push_back(std::make_unique<AnswerAPI>());
    dbAPIs.push_back(std::make_unique<UserAPI>());
    dbAPIs.push_back(std::make_unique<DiscussionAPI>());
    dbAPIs.push_back(std::make_unique<PurchaseAPI>());
    dbAPIs.push_back(std::make_unique<CommentAPI>());
    dbAPIs.push_back(std::make_unique<ImageAPI>());
}

dis::DBController::~DBController(){
    disconnect();
}

bool dis::DBController::connect(const QString &connectString){
    dataBase = QSqlDatabase::addDatabase("QODBC3");
    dataBase.setDatabaseName(connectString);
    //    db.setUserName("250PC\\Anatol250");
    //    db.setPassword("");
    if(dataBase.open()){
        connected = true;
        connString = connectString;
        // ---
        for(const auto &api : dbAPIs)
            api->setDataBase(dataBase);
        // ---
        qDebug() << "CONNECTED: "+ connString;
        return true;
    }
    else{
        connected = false;
        qDebug() << "Not connected to DataBase";
        return false;
    }
}

void dis::DBController::disconnect(){
    dataBase.close();
    qDebug() << "DISCONNECTED FROM DATABASE";
}
