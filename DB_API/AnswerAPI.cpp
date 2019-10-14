#include "AnswerAPI.h"

dis::AnswerAPI::AnswerAPI() : IdbAPI ("Answers", "answers"){}

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

int dis::AnswerAPI::getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives> > &primitives, QList<QString> &uuids){
    primitives.clear();
    uuids.clear();
    // -----
}
