#include <iostream>

#include <QImage>
#include <QLabel>
#include <QApplication>

#include "DB_API/DBController.h"
#include "Server/DisServer.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    dis::DisServer disServ;

    dis::DBController dbcntrl;
//    dbcntrl.connect("DRIVER={SQL Server};SERVER=250PC;DATABASE=Disput_db;Trusted_Connection=yes;");
//    QByteArray arrQuery("POST_User_Name_Vitya one_Surname_Dude_Country_Country for life");
//    if(dbcntrl.doQuery(arrQuery)) qDebug() << "User added!";

//    QImage img("D://ФОТО//DIP.jpg");

//    QByteArray arr = QByteArray::fromRawData((const char*)img.bits(), img.byteCount());

    // test 1
//    dis::Image sImg;
//    sImg.uuid = "asdasdasd";
//    sImg.img_data = arr;
//    sImg.type = 1;
//    sImg.time_create = "09.2019";
//    sImg.geo_data = "Minsk";
//    dbcntrl.imageAPI.addImage(dbcntrl.dataBase, sImg);

    // test 2
    dis::Image oImg;
    dbcntrl.imageAPI.getImageByOwnerUuid(dbcntrl.dataBase, "asdasdasd", oImg);
    //

    QImage iimmgg(reinterpret_cast<const unsigned char *>(oImg.img_data.data()), 400, 453, QImage::Format_RGB32);

    QLabel myLabel;
    myLabel.setPixmap(QPixmap::fromImage(iimmgg));
    myLabel.show();

//    std::cout << "SIZE U: " << sizeof(dis::User) << std::endl;
//    std::cout << "SIZE D: " << sizeof(dis::Discussion) << std::endl;

//    system("pause");
//    return 0;

    return a.exec();
}
