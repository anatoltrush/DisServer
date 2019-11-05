#include "CommentAPI.h"

dis::CommentAPI::CommentAPI() : IdbAPI ("Comments", API_TYPE_COMMENTS){}

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

bool dis::CommentAPI::getCommUuidsByPostUuid(const QString &postUuid, QList<QString> &commUuids){
    commUuids.clear();
    // TODO: impl
}

bool dis::CommentAPI::deleteCommentByPostUuid(const QString &postUuid){
    QSqlQuery query(db);
    QString strQuery = "DELETE FROM " + tableName + " WHERE UUID_post = ?";
    query.prepare(strQuery);
    query.addBindValue(postUuid);
    if(query.exec()) return true;
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

int dis::CommentAPI::deleteFunction(const HttpParser &parser){}
