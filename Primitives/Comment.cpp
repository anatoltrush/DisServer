#include "Comment.h"

dis::Comment::Comment(){}

dis::Comment::~Comment(){}

void dis::Comment::fillBySQL(const QSqlQuery &query, const QSqlRecord &rec){
    this->uuid = query.value(rec.indexOf("UUID")).toString();
    this->uuid_post = query.value(rec.indexOf("UUID_post")).toString();
    this->uuid_author = query.value(rec.indexOf("UUID_author")).toString();
    this->uuid_receiver = query.value(rec.indexOf("UUID_receiver")).toString();
    this->time_created = query.value(rec.indexOf("Time_created")).toDateTime();
    this->text = query.value(rec.indexOf("Text_data")).toString();
}

QByteArray dis::Comment::createMessageBody(const QString &separ){

}

QByteArray dis::Comment::createMessageBodyHtml(){

}
