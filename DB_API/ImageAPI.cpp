#include "ImageAPI.h"

dis::ImageAPI::ImageAPI() : IdbAPI ("Images", "images"){}

dis::ImageAPI::~ImageAPI(){}

bool dis::ImageAPI::addImage(const Image &img){
    QSqlQuery query(db);
    query.prepare("INSERT INTO " + tableName + " (UUID, UUID_author, UUID_post, Width, Height, Image_data, Time_created, Geo_data) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(img.uuid);
    query.addBindValue(img.uuid_author);
    query.addBindValue(img.uuid_post);
    query.addBindValue(img.width);
    query.addBindValue(img.height);
    query.addBindValue(img.img_data);
    query.addBindValue(img.time_created);
    query.addBindValue(img.geo_data);

    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::ImageAPI::getImageByUuid(const QString &uuid, dis::Image &img){
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + tableName + " WHERE UUID = ?");
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

bool dis::ImageAPI::getImagesByPostUuid(const QString &postUuid, QList<Image> &images){
    images.clear();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + tableName + " WHERE UUID_post = ?");
    query.addBindValue(postUuid);
    if(query.exec()){
        QSqlRecord record = query.record();
        while(query.next()) {
            dis::Image img;
            img.fillBySQL(query, record);
            images.push_back(img);
        }
        return true;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

int dis::ImageAPI::getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives> > &primitives,
                               QList<QString> &uuids, const QList<QVariant> &params){
    primitives.clear();
    uuids.clear();
    // -----
    return HTTP_METHOD_NOT_ALLOWED;
}
