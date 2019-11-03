#include "AnswerAPI.h"

dis::AnswerAPI::AnswerAPI() : IdbAPI ("Answers", API_TYPE_ANSWERS){}

dis::AnswerAPI::~AnswerAPI(){}

bool dis::AnswerAPI::addAnswer(const dis::Answer &answer){
    QSqlQuery query(db);
    query.prepare("INSERT INTO " + tableName + " (UUID_dispute, Text_data, Score) "
                  "VALUES (?, ?, ?)");
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
    query.prepare("SELECT * FROM " + tableName + " WHERE UUID_dispute = ?");
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

int dis::AnswerAPI::getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive> > &entities, QList<QString> &primitives){
    entities.clear();
    primitives.clear();
    // -----
    return HTTP_METHOD_NOT_ALLOWED;
}

int dis::AnswerAPI::postFunction(const dis::HttpParser &parser){}

int dis::AnswerAPI::patchFunction(const dis::HttpParser &parser){}

int dis::AnswerAPI::deleteFunction(const HttpParser &parser){
    // no necessary to implement
    qDebug() << "-----> WARNING: USING UNIMPLEMENTED METHOD! <-----";
    return HTTP_METHOD_NOT_ALLOWED;
}
