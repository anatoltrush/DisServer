#include "DiscussionAPI.h"

dis::DiscussionAPI::DiscussionAPI() : IdbAPI ("Disputes", "disputes"){}

dis::DiscussionAPI::~DiscussionAPI(){}

bool dis::DiscussionAPI::addDispute(const dis::Discussion &dispute){
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

bool dis::DiscussionAPI::deleteDisputeByUuid(const QString &uuid){
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

bool dis::DiscussionAPI::updDisputeByUuid(const QString &uuid){}

bool dis::DiscussionAPI::getDisputeCount(int &count){
    QSqlQuery query(db);
    QString strQuery = "SELECT count(*) FROM " + tableName;
    query.prepare(strQuery);
    if(query.exec()){
        if(query.first()){
            count = query.value(0).toInt();
            return true;
        }
        else return false;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::DiscussionAPI::getDisputeByUuid(const QString &uuid, dis::Discussion &disp){
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + tableName + " WHERE UUID = ?");
    query.addBindValue(uuid);
    if(query.exec()){
        if(query.first()){
            QSqlRecord record = query.record();
            disp.fillBySQL(query, record);
            return true;
        }
        else return false;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::DiscussionAPI::getDisputesRange(QList<dis::Discussion> &discussions, int from, int batch){
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

int dis::DiscussionAPI::getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives> > &entities,
                                    QList<QString> &primitives, const QVariantMap &params){
    entities.clear();
    primitives.clear();
    // -----
    if(method == "getDisputeCount"){
        int cnt = -1;
        bool isExec = getDisputeCount(cnt); // check error
        if(isExec){
            primitives.push_back(QString::number(cnt));
            return HTTP_OK;
        }
        else return HTTP_INTERNAL_SERVER_ERROR;
    }
    // -----
    if(method == "getDisputeByUuid"){        
        QString searchUuid;
        for(int i = 0; i < params.size(); i++){
            if(params.keys()[i] == KW_UUID_DISPUTE)
                searchUuid = params.values()[i].toString();
        }
        if(searchUuid.isEmpty()) return HTTP_BAD_REQUEST;
        std::unique_ptr<Discussion> disResult = std::make_unique<Discussion>();
        bool isExec = getDisputeByUuid(searchUuid, *disResult.get());
        if(isExec){
            entities.push_back(std::move(disResult));
            return HTTP_OK;
        }
        else return HTTP_INTERNAL_SERVER_ERROR;
    }
    // -----
    if(method == "getDisputesRange"){
        return HTTP_METHOD_NOT_ALLOWED;
    }
    // -----
    else
        return HTTP_METHOD_NOT_ALLOWED;
}
