#include "Answer.h"

dis::Answer::Answer(){}

dis::Answer::~Answer(){}

void dis::Answer::fillBySQL(const QSqlQuery &query, const QSqlRecord &rec){
    this->uuid_dispute = query.value(rec.indexOf("UUID_dispute")).toString();
    this->text = query.value(rec.indexOf("Text_data")).toString();
    this->score = query.value(rec.indexOf("Score")).toInt();
}

QString dis::Answer::getMessageBody(){

}

void dis::Answer::createMessageBody(){

}