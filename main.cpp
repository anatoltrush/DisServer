#include <iostream>

#include <QTcpServer>
#include <QTcpSocket>

#include "DB_API/DBController.h"
#include "Server/DisServer.h"

int main(){
    dis::DisServer disServ;

    dis::DBController dbcntrl;
    dbcntrl.connect("DRIVER={SQL Server};SERVER=250PC;DATABASE=Disput_db;Trusted_Connection=yes;");
    QByteArray arrQuery("POST_User_Name_Vitya one_Surname_Dude_Country_Country for life");
    if(dbcntrl.doQuery(arrQuery)) qDebug() << "User added!";

//    std::cout << "Hello SERV!" << std::endl;

    system("pause");
    return 0;
}
