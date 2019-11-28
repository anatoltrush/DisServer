#include "DiscussionAPI.h"

dis::DiscussionAPI::DiscussionAPI() : IdbAPI (TABLE_DISPUTES, API_TYPE_DISPUTES){}

bool dis::DiscussionAPI::addDispute(const dis::Discussion &dispute){
    QSqlQuery query(db);
    QString request("INSERT INTO " + tableName + " (" + PROP_DISP_UUID + ", " + PROP_DISP_UUID_AUTHOR + ", " + PROP_DISP_SECTION + ", " + PROP_DISP_TOPIC + ", "
                                                 "" + PROP_DISP_TIME_CRTD + ", " + PROP_DISP_TYPE + ", " + PROP_DISP_STEP + ", " + PROP_DISP_REWARD + ", "
                                                 "" + PROP_DISP_LANG_REG + ", " + PROP_DISP_TEXT_DATA + ", " + PROP_DISP_VOTED + ", " + PROP_DISP_MAX_VOTERS + ", "
                                                 "" + PROP_DISP_ICON + ", " + PROP_DISP_W + ", " + PROP_DISP_H + ", " + PROP_DISP_FRMT + ") "
                                                 "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    query.prepare(request);
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
    query.addBindValue(dispute.format);

    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}

bool dis::DiscussionAPI::getDisputeCount(int &count){
    QSqlQuery query(db);
    QString strQuery = "SELECT count(" + QString(PROP_DISP_UUID) + ") FROM " + tableName;
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
    query.prepare("SELECT * FROM " + tableName + " WHERE " + PROP_DISP_UUID + " = ?");
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
            " ORDER BY " + PROP_DISP_TIME_CRTD + " DESC"
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
            " ORDER BY " + PROP_DISP_TIME_CRTD + " DESC"
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

bool dis::DiscussionAPI::getObjectPart(const dis::HttpParser &parser, std::unique_ptr<dis::IPrimitive> &object){
    object = std::make_unique<Discussion>();
    QString uuidForDel = parser.params.value(PROP_DISP_UUID).toString();

    QSqlQuery query(db);
    query.prepare("SELECT " + QString(PROP_DISP_UUID_AUTHOR) + " FROM " + tableName + " WHERE " + PROP_DISP_UUID + " = ?");
    query.addBindValue(uuidForDel);
    if(query.exec()){
        if(query.first()){
            QSqlRecord record = query.record();
            object->fillBySQL(query, record);
            return true;
        }
        else return false;
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

int dis::DiscussionAPI::patchFunction(const dis::HttpParser &parser){
    // no necessary to implement (no updates)
    qDebug() << "-----> WARNING: USING UNIMPLEMENTED METHOD! <-----";
    return HTTP_METHOD_NOT_ALLOWED;
}

int dis::DiscussionAPI::deleteFunction(const HttpParser &parser){
    // del Answrs+Imgs+Comms++Dis
    if(parser.function == "deleteDisputeByUuid"){
        QString uuidForDel = parser.params.value(PROP_DISP_UUID).toString();
        if(uuidForDel.size() != uuidSize) return HTTP_BAD_REQUEST;

        // 1) Delete Answers
        AnswerAPI answerAPI;
        bool isAnswrsDltd = answerAPI.deleteAnswersByDisputeUuid(uuidForDel);
        if(!isAnswrsDltd) return HTTP_INTERNAL_SERVER_ERROR;

        // 2) Delete Images
        ImageAPI imageAPI;
        std::vector<QString> imgsUuids;
        bool isImgsGot = imageAPI.getImagesUuidsByPostUuid(uuidForDel, imgsUuids);
        if(!isImgsGot) return HTTP_INTERNAL_SERVER_ERROR;
        for(const auto &imgUuid : imgsUuids){
            bool isImgsDltd = imageAPI.deleteImageByUuid(imgUuid);
            if(!isImgsDltd) return HTTP_INTERNAL_SERVER_ERROR;
        }

        // 3) Delete Comments
        CommentAPI commAPI;
        bool isCommsDltd = commAPI.deleteCommentByPostUuidAll(uuidForDel);
        if(!isCommsDltd) return HTTP_INTERNAL_SERVER_ERROR;

        // 4) Delete Dispute
        bool isDisDltd = deleteDisputeUuid(uuidForDel);
        if(!isDisDltd) return HTTP_INTERNAL_SERVER_ERROR;

        return HTTP_OK;
    }
    else return HTTP_METHOD_NOT_ALLOWED;
}

bool dis::DiscussionAPI::deleteDisputeUuid(const QString &uuid){
    QSqlQuery query(db);
    QString strQuery = "DELETE FROM " + tableName + " WHERE " + PROP_DISP_UUID + " = ?";
    query.prepare(strQuery);
    query.addBindValue(uuid);
    if(query.exec()) return true;
    else{
        qDebug() << db.lastError().text();
        return false;
    }
}
