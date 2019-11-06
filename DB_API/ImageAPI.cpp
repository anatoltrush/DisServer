#include "ImageAPI.h"

dis::ImageAPI::ImageAPI() : IdbAPI ("Images", API_TYPE_IMAGES){}

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
        else return false;
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
        while(query.next()){
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

bool dis::ImageAPI::getImagesByPostUuidLight(const QString &postUuid, QList<dis::Image> &images, const QSize &size){
    images.clear();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + tableName + " WHERE UUID_post = ?");
    query.addBindValue(postUuid);
    if(query.exec()){
        QSqlRecord record = query.record();
        while(query.next()) {
            dis::Image img;
            img.fillBySQL(query, record);
            img.resize(size);
            images.push_back(img);
        }
        return true;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::ImageAPI::getImagesUuidsByPostUuid(const QString &postUuid, QList<QString> &imgsUuids){
    imgsUuids.clear();
    QSqlQuery query(db);
    query.prepare("SELECT UUID FROM " + tableName + " WHERE UUID_post = ?");
    query.addBindValue(postUuid);
    if(query.exec()){
        QSqlRecord record = query.record();
        while(query.next()){
            QString uuid = query.value(record.indexOf("UUID")).toString();
            imgsUuids.push_back(uuid);
        }
        return true;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::ImageAPI::deleteImageByUuid(const QString &uuid){
    CommentAPI commAPI;
    bool isCommsDltd = commAPI.deleteCommentByPostUuidFull(uuid);
    bool isImgDltd = deleteImageUuid(uuid);
    return (isCommsDltd && isImgDltd);
}

int dis::ImageAPI::getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive> > &entities, QList<QString> &primitivess){
    entities.clear();
    primitivess.clear();
    // -----
    return HTTP_METHOD_NOT_ALLOWED;
}

int dis::ImageAPI::postFunction(const dis::HttpParser &parser){}

int dis::ImageAPI::patchFunction(const dis::HttpParser &parser){}

int dis::ImageAPI::deleteFunction(const HttpParser &parser){
    // TODO: impl ImageAPI::deleteFunction(const HttpParser &parser)
    // 1) USE deleteCommentByPostUuidFull (send this->uuid)
    // 2) then kill itself

//    // no necessary to implement
//    qDebug() << "-----> WARNING: USING UNIMPLEMENTED METHOD! <-----";
    //    return HTTP_METHOD_NOT_ALLOWED;
}

bool dis::ImageAPI::deleteImageUuid(const QString &uuid){
    QSqlQuery query(db);
    QString strQuery = "DELETE FROM " + tableName + " WHERE UUID = ?";
    query.prepare(strQuery);
    query.addBindValue(uuid);
    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}
