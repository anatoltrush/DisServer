#include "User.h"

dis::User::User(){  }

void dis::User::fillData(const QSqlQuery &query, const QSqlRecord &rec){
    this->name = query.value(rec.indexOf("Name")).toString();
    this->surname = query.value(rec.indexOf("Surname")).toString();
}
