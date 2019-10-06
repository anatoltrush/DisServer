#include "Discussion.h"

dis::Discussion::Discussion(){}

dis::Discussion::~Discussion(){}

void dis::Discussion::fillBySQL(const QSqlQuery &query, const QSqlRecord &rec){
    this->uuid = query.value(rec.indexOf("UUID")).toString();
    this->uuid_author = query.value(rec.indexOf("UUID_author")).toString();
    this->section = query.value(rec.indexOf("Section")).toString();
    this->topic = query.value(rec.indexOf("Topic")).toString();    
    this->time_created = query.value(rec.indexOf("Time_created")).toDateTime();
    this->type = query.value(rec.indexOf("Type")).toInt();
    this->step = query.value(rec.indexOf("Step")).toInt();
    this->reward = query.value(rec.indexOf("Reward")).toInt();
    this->languageRegion = query.value(rec.indexOf("Lang_region")).toString();
    this->text = query.value(rec.indexOf("Text_data")).toString();
    this->voted = query.value(rec.indexOf("Voted")).toInt();
    this->maxVoters = query.value(rec.indexOf("MaxVoters")).toInt();
    this->icon_data = query.value(rec.indexOf("Icon_data")).toByteArray();
    this->img_w = query.value(rec.indexOf("Img_width")).toInt();
    this->img_h = query.value(rec.indexOf("Img_height")).toInt();
}
