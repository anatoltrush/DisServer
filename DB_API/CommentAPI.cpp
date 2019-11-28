#include "CommentAPI.h"

dis::CommentAPI::CommentAPI() : IdbAPI (TABLE_COMMENTS, API_TYPE_COMMENTS){}

bool dis::CommentAPI::addComment(const dis::Comment &comment){
    QSqlQuery query(db);
    QString request("INSERT INTO " + tableName + " (" + PROP_COMM_UUID + ", " + PROP_COMM_UUID_POST + ", " + PROP_COMM_UUID_ATHR + ","
                                                  " " + PROP_COMM_UUID_RCVR + ", " + PROP_COMM_TIME_CRTD + ", " + PROP_COMM_TEXT + ","
                                                  " " + PROP_COMM_LIKE + ", " + PROP_COMM_DLIKE + ", " + PROP_COMM_ISDLTD + ") "
                                                                              "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.prepare(request);
    query.addBindValue(comment.uuid);
    query.addBindValue(comment.uuid_post);
    query.addBindValue(comment.uuid_author);
    query.addBindValue(comment.uuid_receiver);
    query.addBindValue(comment.time_created);
    query.addBindValue(comment.text);
    query.addBindValue(comment.like);
    query.addBindValue(comment.disLike);
    query.addBindValue(comment.isDeleted);

    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::CommentAPI::getCommentByUuid(const QString &uuid, dis::Comment &comment){
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + tableName + " WHERE " + PROP_COMM_UUID + " = ?");
    query.addBindValue(uuid);
    if(query.exec()){
        if(query.first()){
            QSqlRecord record = query.record();
            comment.fillBySQL(query, record);
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

bool dis::CommentAPI::getCommUuidsByPostUuid(const QString &postUuid, std::vector<QString> &commUuids){
    commUuids.clear();
    QSqlQuery query(db);
    query.prepare("SELECT " + QString(PROP_COMM_UUID) + " FROM " + tableName + " WHERE " + PROP_COMM_UUID_POST + " = ?");
    query.addBindValue(postUuid);
    if(query.exec()){
        QSqlRecord record = query.record();
        while(query.next()){
            QString uuid = query.value(record.indexOf(PROP_COMM_UUID)).toString();
            commUuids.push_back(uuid);
        }
        return true;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::CommentAPI::deleteCommentByUuid(const QString &uuid){
    ImageAPI imgAPI;
    std::vector<QString> imgUuids;
    bool isimgsGot = imgAPI.getImagesUuidsByPostUuid(uuid, imgUuids);
    if(!isimgsGot) return false;
    if(imgUuids.size() > 0){
        for(const auto& id : imgUuids){
            bool isImgDltd = imgAPI.deleteImageByUuid(id);
            if(!isImgDltd) return false;
        }
    }
    bool isCommDltd = deleteCommentUuid(uuid);
    return isCommDltd;
}

bool dis::CommentAPI::deleteCommentByPostUuidRecurs(const QString &postUuid){
    QSqlQuery query(db);

    std::vector<QString> parents;
    std::vector<QString> children;
    // fill parents
    bool isPrntsFilled = getCommUuidsByPostUuid(postUuid, parents);
    if(!isPrntsFilled) return false;
    while(true){
        children.clear();
        // fill children
        for(const auto &prnt : parents){
            std::vector<QString> subChldrn;
            bool isChldrnGot = getCommUuidsByPostUuid(prnt, subChldrn);
            if(!isChldrnGot) return false;
            children.insert(children.end(), subChldrn.begin(), subChldrn.end());
        }
        // delete parents
        for(const auto &prnt : parents){
            // delete image
            ImageAPI imageAPI;
            std::vector<QString> imgsUuids;
            bool isImgsGot = imageAPI.getImagesUuidsByPostUuid(prnt, imgsUuids);
            if(!isImgsGot) return false;
            for(const auto &imgUuid : imgsUuids){
                bool isImgDlt = imageAPI.deleteImageByUuid(imgUuid);
                if(!isImgDlt) return false;
            }
            // delete comment
            bool isCommDltd = deleteCommentUuid(prnt);
            if(!isCommDltd) return false;
        }

        if(children.size() == 0) break;
        parents = children;
    }
    return true;
}

bool dis::CommentAPI::deleteCommentByPostUuidAll(const QString &postUuid){
    QSqlQuery query(db);

    std::vector<QString> uuids;
    bool isCommsGot = getCommUuidsByPostUuid(postUuid, uuids);
    if(!isCommsGot) return false;
    for(const auto& id : uuids){
        bool isDltd = deleteCommentByUuid(id);
        if(!isDltd) return false;
    }
    return true;
}

bool dis::CommentAPI::getObjectPart(const dis::HttpParser &parser, std::unique_ptr<dis::IPrimitive> &object){
    object = std::make_unique<Comment>();
    QString uuidForDel = parser.params.value(PROP_COMM_UUID).toString();

    QSqlQuery query(db);
    query.prepare("SELECT " + QString(PROP_COMM_UUID_ATHR)/*params*/ + " FROM " + tableName + " WHERE " + PROP_COMM_UUID + " = ?");
    query.addBindValue(uuidForDel);
    if(query.exec()){
        if(query.first()){
            QSqlRecord record = query.record();
            object->fillBySQL(query, record);
            return true;
        }
        else return false;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

int dis::CommentAPI::getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive> > &entities, QList<QString> &primitives){
    entities.clear();
    primitives.clear();
    // -----
    return HTTP_METHOD_NOT_ALLOWED;
}

int dis::CommentAPI::postFunction(const dis::HttpParser &parser){}

int dis::CommentAPI::patchFunction(const dis::HttpParser &parser){}

int dis::CommentAPI::deleteFunction(const HttpParser &parser){
//    if(parser.function == "deleteCommentByUuid"){
//        QString uuidForDel = parser.params.value(PROP_COMM_UUID).toString();
//        bool isExctd = deleteCommentByUuid(uuidForDel);
//        return isExctd ? HTTP_OK : HTTP_INTERNAL_SERVER_ERROR;
//    }
//    else return HTTP_METHOD_NOT_ALLOWED;

    // ------
    /*
     * if (main)  -> makeCap
     * else deleteCommentByUuid
*/
}

bool dis::CommentAPI::deleteCommentUuid(const QString &uuid){
    QSqlQuery query(db);
    QString strQuery = "DELETE FROM " + tableName + " WHERE " + PROP_COMM_UUID + " = ?";
    query.prepare(strQuery);
    query.addBindValue(uuid);
    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}
