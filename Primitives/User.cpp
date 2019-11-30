#include "User.h"

void dis::User::fillBySQL(const QSqlQuery &query, const QSqlRecord &rec){
    this->uuid = query.value(rec.indexOf(PROP_USR_UUID)).toString();
    this->name = query.value(rec.indexOf(PROP_USR_NAME)).toString();
    this->surname = query.value(rec.indexOf(PROP_USR_SNAME)).toString();
    this->country = query.value(rec.indexOf(PROP_USR_CNTRY)).toString();
    this->city = query.value(rec.indexOf(PROP_USR_CITY)).toString();
    this->email = query.value(rec.indexOf(PROP_USR_EMAIL)).toString();
    this->sex = static_cast<Sex>(query.value(rec.indexOf(PROP_USR_SEX)).toInt());
    this->preference = static_cast<Sex>(query.value(rec.indexOf(PROP_USR_PREF)).toInt());
    this->nickName = query.value(rec.indexOf(PROP_USR_NICK)).toString();
    this->password = query.value(rec.indexOf(PROP_USR_PSWRD)).toString();
    this->money = query.value(rec.indexOf(PROP_USR_MNY)).toInt();
    this->score = query.value(rec.indexOf(PROP_USR_SCORE)).toInt();
    this->time_birth = query.value(rec.indexOf(PROP_USR_TIME_BRTH)).toDateTime();
    this->time_registration = query.value(rec.indexOf(PROP_USR_TIME_REG)).toDateTime();
    this->avtr_data = query.value(rec.indexOf(PROP_USR_AVTR)).toByteArray();
    this->avtr_w = query.value(rec.indexOf(PROP_USR_W)).toInt();
    this->avtr_h = query.value(rec.indexOf(PROP_USR_H)).toInt();
    this->format = query.value(rec.indexOf(PROP_USR_FRMT)).toString();
}

void dis::User::fillByParse(const QVariantMap &params){
    return;
}

QByteArray dis::User::createMessageBody(const QString &separ){
    QByteArray res;
    return res;
}

QByteArray dis::User::createMessageBodyHtml(){
    QByteArray res;
    return res;
}
