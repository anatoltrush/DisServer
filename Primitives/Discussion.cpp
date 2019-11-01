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
    this->time_created = QDateTime::fromString(params.value(PROP_DISP_TIME_CRTD).toString(), Qt::SystemLocaleShortDate);
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
    res.append(IPrimitives::toQBA(separ, PROP_DISP_UUID, this->uuid));
    res.append(IPrimitives::toQBA(separ, PROP_DISP_UUID_AUTHOR, this->uuid_author));
    res.append(IPrimitives::toQBA(separ, PROP_DISP_SECTION, this->section));
    res.append(IPrimitives::toQBA(separ, PROP_DISP_TOPIC, this->topic));
    res.append(IPrimitives::toQBA(separ, PROP_DISP_TIME_CRTD, this->time_created.toString(Qt::SystemLocaleShortDate)));
    res.append(IPrimitives::toQBA(separ, PROP_DISP_TYPE, QString::number(this->type)));
    res.append(IPrimitives::toQBA(separ, PROP_DISP_STEP, QString::number(this->step)));
    res.append(IPrimitives::toQBA(separ, PROP_DISP_REWARD, QString::number(this->reward)));
    res.append(IPrimitives::toQBA(separ, PROP_DISP_LANG_REG, this->languageRegion));
    res.append(IPrimitives::toQBA(separ, PROP_DISP_TEXT_DATA, this->text));
    res.append(IPrimitives::toQBA(separ, PROP_DISP_VOTED, QString::number(this->voted)));
    res.append(IPrimitives::toQBA(separ, PROP_DISP_MAX_VOTERS, QString::number(this->maxVoters)));
    res.append(IPrimitives::toQBA(separ, PROP_DISP_ICON, this->icon_data));
    res.append(IPrimitives::toQBA(separ, PROP_DISP_W, QString::number(this->img_w)));
    res.append(IPrimitives::toQBA(separ, PROP_DISP_H, QString::number(this->img_h)));
    res.append("--" + separ + "--");
    return res;
}

QByteArray dis::Discussion::createMessageBodyHtml(){
    QByteArray res;
    return res;
}
