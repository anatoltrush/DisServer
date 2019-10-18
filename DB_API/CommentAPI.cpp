#include "CommentAPI.h"

dis::CommentAPI::CommentAPI() : IdbAPI ("Comments", "comments"){}

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

bool dis::CommentAPI::getCommByUuid(const QString &uuid, dis::Comment &comment){
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

int dis::CommentAPI::getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives> > &entities,
                                 QList<QString> &primitives, const QVariantMap &params){
    entities.clear();
    primitives.clear();
    // -----
    return HTTP_METHOD_NOT_ALLOWED;
}
