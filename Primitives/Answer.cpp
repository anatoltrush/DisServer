#include "Answer.h"

void dis::Answer::fillBySQL(const QSqlQuery &query, const QSqlRecord &rec){
    this->uuid = query.value(rec.indexOf(PROP_ANS_UUID)).toString();
    this->uuid_dispute = query.value(rec.indexOf(PROP_ANS_UUID_DISP)).toString();
    this->text = query.value(rec.indexOf(PROP_ANS_TEXT)).toString();
    this->score = query.value(rec.indexOf(PROP_ANS_SCORE)).toInt();
}

void dis::Answer::fillByParse(const QVariantMap &params){}

QByteArray dis::Answer::createMessageBody(const QString &separ){}

QByteArray dis::Answer::createMessageBodyHtml(){}
