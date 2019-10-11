#include "DiscussionAPI.h"

dis::DiscussionAPI::DiscussionAPI() : IdbAPI ("Disputes", "disputes"){}

dis::DiscussionAPI::~DiscussionAPI(){}

bool dis::DiscussionAPI::addDispute(const QSqlDatabase &db, const dis::Discussion &dispute){
    QSqlQuery query(db);
    query.prepare("INSERT INTO " + tableName + " (UUID, UUID_author, Section, Topic, Time_created,"
                  "Type, Step, Reward, Lang_region, Text_data, Voted, MaxVoters, Icon_data, Img_width, Img_height)"
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(dispute.uuid);
    query.addBindValue(dispute.uuid_author);
    query.addBindValue(dispute.section);
    query.addBindValue(dispute.topic);
    query.addBindValue(dispute.time_created);
    query.addBindValue(dispute.type);
    query.addBindValue(dispute.step);
    query.addBindValue(dispute.reward);
    query.addBindValue(dispute.languageRegion);
    query.addBindValue(dispute.text);
    query.addBindValue(dispute.voted);
    query.addBindValue(dispute.maxVoters);
    query.addBindValue(dispute.icon_data);
    query.addBindValue(dispute.img_w);
    query.addBindValue(dispute.img_h);

    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::DiscussionAPI::deleteDisputeByUuid(const QSqlDatabase &db, const QString &uuid){
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

bool dis::DiscussionAPI::updDisputeByUuid(const QSqlDatabase& db, const QString &uuid){}

bool dis::DiscussionAPI::getDisputeCount(const QSqlDatabase &db, int &count){
    QSqlQuery query(db);
    QString strQuery = "SELECT count(*) FROM " + tableName;
    query.prepare(strQuery);
    if(query.exec()){
        query.next();
        count = query.value(0).toInt();
        return true;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::DiscussionAPI::getDisputeByUuid(const QSqlDatabase &db, const QString &uuid, dis::Discussion &disp){
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + tableName + " WHERE UUID = ?");
    query.addBindValue(uuid);
    if(query.exec()){
        QSqlRecord record = query.record();
        disp.fillBySQL(query, record);
        return true;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::DiscussionAPI::getDisputesRange(const QSqlDatabase &db, QList<dis::Discussion> &discussions, int from, int batch){
    discussions.clear();
    QSqlQuery query(db);
    QString strQuery = "SELECT * FROM " + tableName +
            " ORDER BY Time_created DESC"
            " offset " + QString::number(from) +
            " rows fetch next " + QString::number(batch) +
            " rows only";
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

int dis::DiscussionAPI::getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives> > &primitives, QList<QString> &uuids){
    primitives.clear();
    uuids.clear();
    // -----
}
