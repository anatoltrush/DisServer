#include "ImageAPI.h"

dis::ImageAPI::ImageAPI(){}

bool dis::ImageAPI::addImage(const QSqlDatabase &db, const Image &img){
    QSqlQuery query(db);
    query.prepare("INSERT INTO Images (UUID_owner, Width, Height, Image_data, Entity_type, Time_created, Geo_data) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(img.uuid);
    query.addBindValue(img.width);
    query.addBindValue(img.height);
    query.addBindValue(img.img_data);
    query.addBindValue(img.type);
    query.addBindValue(img.time_create);
    query.addBindValue(img.geo_data);

    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::ImageAPI::getImageByOwnerUuid(const QSqlDatabase &db, const QString &uuid, dis::Image &img, int type, const QString &geo){
    // TODO: GEO & TYPE
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Images WHERE UUID_owner = ?");
    query.addBindValue(uuid);
    if(query.exec()){
        if(query.first()){
            QSqlRecord record = query.record();
            img.fillBySQL(query, record);
            return true;
        }
        else{
            qDebug() << db.lastError().text();
            return false;
        }
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}
