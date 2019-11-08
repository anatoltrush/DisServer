#include "CommentAPI.h"

dis::CommentAPI::CommentAPI() : IdbAPI (TABLE_COMMENTS, API_TYPE_COMMENTS){}

dis::CommentAPI::~CommentAPI(){}

bool dis::CommentAPI::addComment(const dis::Comment &comment){
    QSqlQuery query(db);
    query.prepare("INSERT INTO " + tableName + " (UUID, UUID_post, UUID_author, UUID_receiver, Time_created, Text_data) "
                  "VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(comment.uuid);
    query.addBindValue(comment.uuid_post);
    query.addBindValue(comment.uuid_author);
    query.addBindValue(comment.uuid_receiver);
    query.addBindValue(comment.time_created);
    query.addBindValue(comment.text);

    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::CommentAPI::getCommentByUuid(const QString &uuid, dis::Comment &comment){
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + tableName + " WHERE UUID = ?");
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
    query.prepare("SELECT UUID FROM " + tableName + " WHERE UUID_post = ?");
    query.addBindValue(postUuid);
    if(query.exec()){
        QSqlRecord record = query.record();
        while(query.next()){
            QString uuid = query.value(record.indexOf("UUID")).toString();
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
    bool isCommsDltd = deleteCommentByPostUuidFull(uuid);
    bool isCommDltd = deleteCommentUuid(uuid);
    return (isCommsDltd && isCommDltd);
}

bool dis::CommentAPI::deleteCommentByPostUuidFull(const QString &postUuid){
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
            QList<QString> imgsUuids;
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

int dis::CommentAPI::getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive> > &entities, QList<QString> &primitives){
    entities.clear();
    primitives.clear();
    // -----
    return HTTP_METHOD_NOT_ALLOWED;
}

int dis::CommentAPI::postFunction(const dis::HttpParser &parser){}

int dis::CommentAPI::patchFunction(const dis::HttpParser &parser){}

int dis::CommentAPI::deleteFunction(const HttpParser &parser){
    // TODO: impl CommentAPI::deleteFunction(const HttpParser &parser)
    // USE deleteCommentByUuid
}

bool dis::CommentAPI::deleteCommentUuid(const QString &uuid){
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
