#include "User.h"

dis::User::User(){}

void dis::User::fillBySQL(const QSqlQuery &query, const QSqlRecord &rec){
    this->uuid = query.value(rec.indexOf("UUID")).toString();
    this->name = query.value(rec.indexOf("Name")).toString();
    this->surname = query.value(rec.indexOf("Surname")).toString();
    this->country = query.value(rec.indexOf("Country")).toString();
    // FILL ALL FIELDS
}

void dis::User::fillByList(const QList<QString> &words){

}
