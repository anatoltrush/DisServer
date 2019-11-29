#include "Discussion.h"

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
    this->format = query.value(rec.indexOf(PROP_DISP_FRMT)).toString();
    this->isAdvert = query.value(rec.indexOf(PROP_DISP_ISADV)).toBool();
    this->isArch = query.value(rec.indexOf(PROP_DISP_ISARCH)).toBool();
    this->secsLive = query.value(rec.indexOf(PROP_DISP_SECONDS)).toInt();
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
    this->format = params.value(PROP_DISP_FRMT).toString();    
    this->isAdvert = params.value(PROP_DISP_ISADV).toBool();
    this->isArch = params.value(PROP_DISP_ISARCH).toBool();
    this->secsLive = params.value(PROP_DISP_SECONDS).toInt();
}

QByteArray dis::Discussion::createMessageBody(const QString &separ){
    QByteArray res;
    res.append(IPrimitive::toQBA(separ, PROP_DISP_UUID, this->uuid));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_UUID_AUTHOR, this->uuid_author));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_SECTION, this->section));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_TOPIC, this->topic));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_TIME_CRTD, this->time_created.toString(Qt::SystemLocaleShortDate)));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_TYPE, QString::number(this->type)));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_STEP, QString::number(this->step)));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_REWARD, QString::number(this->reward)));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_LANG_REG, this->languageRegion));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_TEXT_DATA, this->text));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_VOTED, QString::number(this->voted)));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_MAX_VOTERS, QString::number(this->maxVoters)));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_ICON, this->icon_data));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_W, QString::number(this->img_w)));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_H, QString::number(this->img_h)));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_FRMT, this->format));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_ISADV, QString::number(this->isAdvert)));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_ISARCH, QString::number(this->isArch)));
    res.append(IPrimitive::toQBA(separ, PROP_DISP_SECONDS, QString::number(this->secsLive)));
    res.append("--" + separ + "--");
    return res;
}

QByteArray dis::Discussion::createMessageBodyHtml(){
    QByteArray res;
    return res;
}
