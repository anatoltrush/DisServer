#include "AnswerAPI.h"

dis::AnswerAPI::AnswerAPI() : IdbAPI (TABLE_ANSWERS, API_TYPE_ANSWERS){}

bool dis::AnswerAPI::addAnswer(const dis::Answer &answer){
    QSqlQuery query(db);
    QString request("INSERT INTO " + tableName + " (" + PROP_ANS_UUID + ", " + PROP_ANS_UUID_DISP + ", "
                                                    "" + PROP_ANS_TEXT + ", " + PROP_ANS_SCORE + ") "
                                                    "VALUES (?, ?, ?, ?)");
    query.prepare(request);
    query.addBindValue(answer.uuid);
    query.addBindValue(answer.uuid_dispute);
    query.addBindValue(answer.text);
    query.addBindValue(answer.score);

    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::AnswerAPI::getAnswersByDisputeUuid(const QString &dispUuid, QList<dis::Answer> &answers){
    answers.clear();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + tableName + " WHERE " + PROP_ANS_UUID_DISP + " = ?");
    query.addBindValue(dispUuid);
    if(query.exec()){
        QSqlRecord record = query.record();
        while(query.next()){
            dis::Answer answer;
            answer.fillBySQL(query, record);
            answers.push_back(answer);
        }
        return true;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::AnswerAPI::deleteAnswerByDisputeUuid(const QString &uuid){
    QSqlQuery query(db);
    QString strQuery = "DELETE FROM " + tableName + " WHERE " + PROP_ANS_UUID_DISP + " = ?";
    query.prepare(strQuery);
    query.addBindValue(uuid);
    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::AnswerAPI::getObjectPart(const dis::HttpParser &parser, std::unique_ptr<dis::IPrimitive> &object){
    object = std::make_unique<Answer>();
    return false;
}

int dis::AnswerAPI::getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive> > &entities, QList<QString> &primitives){
    entities.clear();
    primitives.clear();
    // -----
    return HTTP_METHOD_NOT_ALLOWED;
}

int dis::AnswerAPI::postFunction(const dis::HttpParser &parser){}

int dis::AnswerAPI::patchFunction(const dis::HttpParser &parser){}

int dis::AnswerAPI::deleteFunction(const HttpParser &parser){
    // no necessary to implement (deletes by Dispute deletion)
    qDebug() << "-----> WARNING: USING UNIMPLEMENTED METHOD! <-----";
    return HTTP_METHOD_NOT_ALLOWED;
}
