#include "User.h"

dis::User::User(){}

dis::User::~User(){}

void dis::User::fillBySQL(const QSqlQuery &query, const QSqlRecord &rec){
    this->uuid = query.value(rec.indexOf("UUID")).toString();
    this->name = query.value(rec.indexOf("Name")).toString();
    this->surname = query.value(rec.indexOf("Surname")).toString();
    this->country = query.value(rec.indexOf("Country")).toString();
    // TODO: FILL ALL FIELDS
}

void dis::User::fillByList(const QList<QString> &words, bool isFromParse){
    int startInd = (isFromParse) ? 2 : 0;
    for(int i = startInd; i < words.size(); i++){
        if(words[i] == "Name") this->name = words[i + 1];
        if(words[i] == "Surname") this->surname = words[i + 1];
        if(words[i] == "Country") this->country = words[i + 1];
    }
}

QString dis::User::getMessageBody(){

}

QByteArray dis::User::createMessageBody(const QString &separ){

}

QByteArray dis::User::createMessageBodyHtml(){

}
