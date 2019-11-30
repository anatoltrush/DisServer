#include "Comment.h"

void dis::Comment::fillBySQL(const QSqlQuery &query, const QSqlRecord &rec){
    this->uuid = query.value(rec.indexOf(PROP_COMM_UUID)).toString();
    this->uuid_post = query.value(rec.indexOf(PROP_COMM_UUID_POST)).toString();
    this->uuid_author = query.value(rec.indexOf(PROP_COMM_UUID_ATHR)).toString();
    this->uuid_receiver = query.value(rec.indexOf(PROP_COMM_UUID_RCVR)).toString();
    this->time_created = query.value(rec.indexOf(PROP_COMM_TIME_CRTD)).toDateTime();
    this->text = query.value(rec.indexOf(PROP_COMM_TEXT)).toString();
    this->like = query.value(rec.indexOf(PROP_COMM_LIKE)).toInt();
    this->disLike = query.value(rec.indexOf(PROP_COMM_DLIKE)).toInt();
    this->isDeleted = query.value(rec.indexOf(PROP_COMM_ISDLTD)).toBool();
}

void dis::Comment::fillByParse(const QVariantMap &params){
    return;
}

QByteArray dis::Comment::createMessageBody(const QString &separ){
    QByteArray res;
    return res;
}

QByteArray dis::Comment::createMessageBodyHtml(){
    QByteArray res;
    return res;
}
