#include "DiscussionAPI.h"

dis::DiscussionAPI::DiscussionAPI(){}

dis::DiscussionAPI::~DiscussionAPI(){}

bool dis::DiscussionAPI::addDiscussion(const QSqlDatabase &db, const dis::Discussion &discuss){
    QSqlQuery query(db);
    query.prepare("INSERT INTO Discussions (UUID, Section, Topic, UUID_author, Time_created,"
                  "Type, Step, Reward, Lang_region, Text_data)"
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(discuss.uuid);
    query.addBindValue(discuss.section);
    query.addBindValue(discuss.topic);
    query.addBindValue(discuss.uuid_author);
    query.addBindValue(discuss.time_created);
    // IMAGE
    query.addBindValue(discuss.type);
    query.addBindValue(discuss.step);
    query.addBindValue(discuss.reward);
    query.addBindValue(discuss.languageRegion);
    query.addBindValue(discuss.text);

    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
    // TODO: FILL IMAGE
}

bool dis::DiscussionAPI::deleteDiscussion(const QSqlDatabase &db){}

bool dis::DiscussionAPI::redactDiscussion(const QSqlDatabase& db){}

bool dis::DiscussionAPI::getDiscussions(const QSqlDatabase &db, QList<dis::Discussion> &discussions){
    discussions.clear();
    QSqlQuery query(db);
    QString strQuery = "SELECT * FROM Discussions";
    if(query.exec(strQuery)){
        QSqlRecord record = query.record();
        while(query.next()) {
            dis::Discussion discuss;
            discuss.fillBySQL(query, record);
            discussions.push_back(discuss);
        }
        return true;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}
