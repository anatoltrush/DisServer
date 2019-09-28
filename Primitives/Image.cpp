#include "Image.h"

dis::Image::Image(){}

void dis::Image::fillBySQL(const QSqlQuery &query, const QSqlRecord &rec){
    this->uuid = query.value(rec.indexOf("UUID_owner")).toString();
    this->img_data = query.value(rec.indexOf("Image_data")).toByteArray();
    this->type = query.value(rec.indexOf("Entity_type")).toInt();
    this->time_create = query.value(rec.indexOf("Time_created")).toString();
    this->geo_data = query.value(rec.indexOf("Geo_data")).toString();
}
