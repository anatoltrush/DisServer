#include "Image.h"

dis::Image::Image(){}

void dis::Image::fillBySQL(const QSqlQuery &query, const QSqlRecord &rec){
    this->uuid = query.value(rec.indexOf("UUID_owner")).toString();
    this->width = query.value(rec.indexOf("Width")).toInt();
    this->height = query.value(rec.indexOf("Height")).toInt();
    this->img_data = query.value(rec.indexOf("Image_data")).toByteArray();
    this->type = query.value(rec.indexOf("Entity_type")).toString();
    this->time_create = query.value(rec.indexOf("Time_created")).toString();
    this->geo_data = query.value(rec.indexOf("Geo_data")).toString();
}
