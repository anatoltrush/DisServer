#include <iostream>

#include <QtSql>

#include <QTcpServer>
#include <QTcpSocket>

#include "Primitives/User.h"
#include "Primitives/Discussion.h"
#include "Primitives/Purchase.h"

#include "Server/DisServer.h"

int main(){
    QTcpServer server;

//    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");
//    db.setDatabaseName("DRIVER={SQL Server};SERVER=250PC;DATABASE=Disput_db;Trusted_Connection=yes;");

//    db.setUserName("250PC\\Anatol250");
//    db.setPassword("");

//    if(!db.open())  qDebug()<<"ERROR: "<<QSqlError(db.lastError()).text();
//    else qDebug()<<"Ok";

//    QSqlQuery query(db);
//    query.prepare("INSERT INTO Users (Name, Surname) " "VALUES (?, ?)");
//    query.addBindValue("Anatol");
//    query.addBindValue("Trush");

//    if(!query.exec())
//        qDebug() << db.lastError().text();
//    db.close();

    dis::User user;
    dis::Discussion disc;
    dis::Purchase purch;

    dis::DisServer serv;

    std::cout << "Hello SQL!" << std::endl;

    system("pause");
    return 0;
}
