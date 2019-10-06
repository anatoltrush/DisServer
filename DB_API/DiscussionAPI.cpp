#include "DiscussionAPI.h"

dis::DiscussionAPI::DiscussionAPI(){}

bool dis::DiscussionAPI::addDiscussion(const QSqlDatabase &db, const dis::Discussion &discuss){
    QSqlQuery query(db);
    query.prepare("INSERT INTO Disputes (UUID, UUID_author, Section, Topic, Time_created,"
                  "Type, Step, Reward, Lang_region, Text_data, Voted, MaxVoters, Icon_data, Img_width, Img_height)"
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(discuss.uuid);
    query.addBindValue(discuss.uuid_author);
    query.addBindValue(discuss.section);
    query.addBindValue(discuss.topic);
    query.addBindValue(discuss.time_created);
    query.addBindValue(discuss.type);
    query.addBindValue(discuss.step);
    query.addBindValue(discuss.reward);
    query.addBindValue(discuss.languageRegion);
    query.addBindValue(discuss.text);
    query.addBindValue(discuss.voted);
    query.addBindValue(discuss.maxVoters);
    query.addBindValue(discuss.icon_data);
    query.addBindValue(discuss.img_w);
    query.addBindValue(discuss.img_h);

    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::DiscussionAPI::deleteDiscussion(const QSqlDatabase &db){}

bool dis::DiscussionAPI::redactDiscussion(const QSqlDatabase& db){}

bool dis::DiscussionAPI::getDisputeByUuid(const QSqlDatabase &db, const QString &uuid, dis::Discussion &disp){
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Disputes WHERE UUID = ?");
    query.addBindValue(uuid);
    if(query.exec()){
        if(query.first()){
            QSqlRecord record = query.record();
            disp.fillBySQL(query, record);
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
