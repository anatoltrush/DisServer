#include "Discussion.h"

dis::Discussion::Discussion(){}

dis::Discussion::~Discussion(){}

void dis::Discussion::fillBySQL(const QSqlQuery &query, const QSqlRecord &rec){
    this->uuid = query.value(rec.indexOf("UUID")).toString();
    this->section = query.value(rec.indexOf("Section")).toString();
    this->topic = query.value(rec.indexOf("Topic")).toString();
    this->author_uuid = query.value(rec.indexOf("Autor_UUID")).toString();
    this->time_create = query.value(rec.indexOf("Time_created")).toString();
    // TODO: PICTURE
    this->type = query.value(rec.indexOf("Type")).toInt();
    this->step = query.value(rec.indexOf("Step")).toInt();
    this->reward = query.value(rec.indexOf("Reward")).toInt();
    this->languageRegion = query.value(rec.indexOf("Lang_region")).toString();
}
