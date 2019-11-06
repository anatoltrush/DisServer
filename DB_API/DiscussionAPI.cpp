#include "DiscussionAPI.h"

dis::DiscussionAPI::DiscussionAPI() : IdbAPI ("Disputes", API_TYPE_DISPUTES){}

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

bool dis::DiscussionAPI::updDisputeByUuid(const QString &uuid){
    QSqlQuery query(db);
}

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

bool dis::DiscussionAPI::getDispUuidsRange(QList<QString> &uuids, int from, int batch){
    uuids.clear();
    QSqlQuery query(db);
    QString strQuery = "SELECT " + QString(PROP_DISP_UUID) + " FROM " + tableName +
            " ORDER BY Time_created DESC"
            " offset " + QString::number(from) +
            " rows fetch next " + QString::number(batch) +
            " rows only";
    if(query.exec(strQuery)){
        QSqlRecord record = query.record();
        while(query.next()) {
            QString gotUuid = query.value(record.indexOf(PROP_DISP_UUID)).toString();
            uuids.push_back(gotUuid);
        }
        return true;
    }
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

int dis::DiscussionAPI::getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive> > &entities, QList<QString> &primitives){
    entities.clear();
    primitives.clear();
    // -----
    if(parser.function == "getDisputeCount"){
        int cnt = -1;
        bool isExectd = getDisputeCount(cnt); // check error
        if(isExectd){
            primitives.push_back(QString::number(cnt));
            return HTTP_OK;
        }
        else return HTTP_INTERNAL_SERVER_ERROR;
    }
    // -----
    if(parser.function == "getDisputeByUuid"){
        QString searchUuid;
        for(int i = 0; i < parser.params.size(); i++){
            if(parser.params.keys()[i] == PROP_DISP_UUID)
                searchUuid = parser.params.values()[i].toString();
        }
        if(searchUuid.isEmpty()) return HTTP_BAD_REQUEST;

        auto disResult = std::make_unique<Discussion>();
        bool isExectd = getDisputeByUuid(searchUuid, *disResult.get());
        if(isExectd){
            entities.push_back(std::move(disResult));
            return HTTP_OK;
        }
        else return HTTP_INTERNAL_SERVER_ERROR;
    }
    // -----
    if(parser.function == "getDisputesRange"){
        QString from, package;
        for(int i = 0; i < parser.params.size(); i++){
            if(parser.params.keys()[i] == API_KW_DISP_FROM)
                from = parser.params.values()[i].toString();
            if(parser.params.keys()[i] == API_KW_DISP_PACKAGE)
                package = parser.params.values()[i].toString();
        }
        if(from.isEmpty() || package.isEmpty()) return HTTP_BAD_REQUEST;

        QList<Discussion> disps;
        bool isExectd = getDisputesRange(disps, from.toInt(), package.toInt());
        if(isExectd){
            for(const auto &dis : disps){
                auto unDis = std::make_unique<Discussion>();
                *unDis.get() = dis;
                entities.push_back(std::move(unDis));
            }
            return HTTP_OK;
        }
        else return HTTP_INTERNAL_SERVER_ERROR;
    }
    // -----
    if(parser.function == "getDispUuidsRange"){
        QString from, package;
        for(int i = 0; i < parser.params.size(); i++){
            if(parser.params.keys()[i] == API_KW_DISP_FROM)
                from = parser.params.values()[i].toString();
            if(parser.params.keys()[i] == API_KW_DISP_PACKAGE)
                package = parser.params.values()[i].toString();
        }
        if(from.isEmpty() || package.isEmpty()) return HTTP_BAD_REQUEST;

        bool isExectd = getDispUuidsRange(primitives, from.toInt(), package.toInt());
        return isExectd ? HTTP_OK : HTTP_INTERNAL_SERVER_ERROR;
    }
    else return HTTP_METHOD_NOT_ALLOWED;
}

int dis::DiscussionAPI::postFunction(const dis::HttpParser &parser){
    if(parser.function == "addDispute"){
        IPrimitive* primit = parser.object.get();
        Discussion newDisc = *static_cast<Discussion*>(primit);

        bool isExectd = addDispute(newDisc);
        return isExectd ? HTTP_OK : HTTP_INTERNAL_SERVER_ERROR;
    }
    else return HTTP_METHOD_NOT_ALLOWED;
}

int dis::DiscussionAPI::patchFunction(const dis::HttpParser &parser){}

int dis::DiscussionAPI::deleteFunction(const HttpParser &parser){
    if(parser.function == "deleteDisputeByUuid"){
        QString uuidForDel = parser.params.value(PROP_DISP_UUID).toString();
        // TODO: put check here

        CommentAPI commAPI;
        ImageAPI imageAPI;

        // 1) delete Answers
        AnswerAPI answerAPI;
        bool isAnswrsDltd = answerAPI.deleteAnswerByDisputeUuid(uuidForDel);

        // 2) Comms & Imgs

        // 2.1) Delete comments of Images
        QList<QString> imgsUuids;
        bool isImgsGot = imageAPI.getImagesUuidsByPostUuid(uuidForDel, imgsUuids);
        if(!isImgsGot) return HTTP_INTERNAL_SERVER_ERROR;
        for(const auto &imgUuid : imgsUuids){
            bool isCommsDltd = commAPI.deleteCommentByPostUuidFull(imgUuid);
            if(!isCommsDltd) return HTTP_INTERNAL_SERVER_ERROR;
        }

        // 2.2) Delete Images        
        bool isImgsDltd = imageAPI.deleteImagesByPostUuid(uuidForDel);

        // 3) Comms & Disp
        // 3.1) Delete comments of Dispute        
        bool isCommsDltd = commAPI.deleteCommentByPostUuidFull(uuidForDel);
        if(!isCommsDltd) return HTTP_INTERNAL_SERVER_ERROR;
        // 3.2) Delete Dispute
        bool isDisDltd = deleteDisputeByUuid(uuidForDel);

//        // 3) delete Comments
//        QList<QString> allCommUuids;
//        bool isCommsGot = commAPI.getCommUuidsByPostUuid(uuidForDel, allCommUuids);
//        if(isCommsGot)
//            for(const auto &commUuid : allCommUuids){
//                // 3.1)
//                bool isCommImgDltd = imageAPI.deleteImagesByPostUuid(commUuid);
//                if(!isCommImgDltd) return HTTP_INTERNAL_SERVER_ERROR;
//            }
//        else  return HTTP_INTERNAL_SERVER_ERROR;

        // -conclusion-
        return (isImgsDltd && isAnswrsDltd && isDisDltd) ? HTTP_OK : HTTP_INTERNAL_SERVER_ERROR;
    }
    else return HTTP_METHOD_NOT_ALLOWED;
}
