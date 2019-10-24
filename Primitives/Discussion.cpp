#include "Discussion.h"

dis::Discussion::Discussion(){}

dis::Discussion::~Discussion(){}

void dis::Discussion::fillBySQL(const QSqlQuery &query, const QSqlRecord &rec){
    this->uuid = query.value(rec.indexOf(PROP_DISP_UUID)).toString();
    this->uuid_author = query.value(rec.indexOf(PROP_DISP_UUID_AUTHOR)).toString();
    this->section = query.value(rec.indexOf(PROP_DISP_SECTION)).toString();
    this->topic = query.value(rec.indexOf(PROP_DISP_TOPIC)).toString();
    this->time_created = query.value(rec.indexOf(PROP_DISP_TIME_CRTD)).toDateTime();
    this->type = query.value(rec.indexOf(PROP_DISP_TYPE)).toInt();
    this->step = query.value(rec.indexOf(PROP_DISP_STEP)).toInt();
    this->reward = query.value(rec.indexOf(PROP_DISP_REWARD)).toInt();
    this->languageRegion = query.value(rec.indexOf(PROP_DISP_LANG_REG)).toString();
    this->text = query.value(rec.indexOf(PROP_DISP_TEXT_DATA)).toString();
    this->voted = query.value(rec.indexOf(PROP_DISP_VOTED)).toInt();
    this->maxVoters = query.value(rec.indexOf(PROP_DISP_MAX_VOTERS)).toInt();
    this->icon_data = query.value(rec.indexOf(PROP_DISP_ICON)).toByteArray();
    this->img_w = query.value(rec.indexOf(PROP_DISP_W)).toInt();
    this->img_h = query.value(rec.indexOf(PROP_DISP_H)).toInt();
}

void dis::Discussion::fillByParse(const QVariantMap &params){
    this->uuid_author = params.value(PROP_DISP_UUID_AUTHOR).toString();
    this->section = params.value(PROP_DISP_SECTION).toString();
    this->topic = params.value(PROP_DISP_TOPIC).toString();
    this->time_created = params.value(PROP_DISP_TIME_CRTD).toDateTime();
    this->type = params.value(PROP_DISP_TYPE).toInt();
    this->step = params.value(PROP_DISP_STEP).toInt();
    this->reward = params.value(PROP_DISP_REWARD).toInt();
    this->languageRegion = params.value(PROP_DISP_LANG_REG).toString();
    this->text = params.value(PROP_DISP_TEXT_DATA).toString();
    this->voted = params.value(PROP_DISP_VOTED).toInt();
    this->maxVoters = params.value(PROP_DISP_MAX_VOTERS).toInt();
    this->icon_data = params.value(PROP_DISP_ICON).toByteArray();
    this->img_w = params.value(PROP_DISP_W).toInt();
    this->img_h = params.value(PROP_DISP_H).toInt();
}

QByteArray dis::Discussion::createMessageBody(const QString &separ){
    QByteArray res;
    return res;
}

QByteArray dis::Discussion::createMessageBodyHtml(){
    QByteArray res;
    return res;
}
