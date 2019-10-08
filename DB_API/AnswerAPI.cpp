#include "AnswerAPI.h"

dis::AnswerAPI::AnswerAPI() : IdbAPI ("Answers"){}

bool dis::AnswerAPI::addAnswer(const QSqlDatabase &db, const dis::Answer &answer){
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

bool dis::AnswerAPI::getAnswersByDisputeUuid(const QSqlDatabase &db, const QString &dispUuid, QList<dis::Answer> &answers){
    answers.clear();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + tableName + " WHERE UUID_dispute = ?");
    query.addBindValue(dispUuid);
    if(query.exec()){
        QSqlRecord record = query.record();
        while(query.next()) {
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
