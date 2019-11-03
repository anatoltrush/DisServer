#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"

#include "Image.h"

dis::Image::Image(){}

dis::Image::~Image(){}

void dis::Image::resize(const QSize &size){
    QImage oldImg = QImage::fromData(img_data, currentFormat.toStdString().c_str());
//    QImage oldImg(reinterpret_cast<const unsigned char*>(img_data.data()), width, height, QImage::Format_RGB32);
    QImage newImg = oldImg.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QByteArray Qba;
    QBuffer buffer(&Qba);
    buffer.open(QIODevice::WriteOnly);
    newImg.save(&buffer, currentFormat.toStdString().c_str());
    buffer.close();

    this->img_data = Qba;
    this->width = newImg.size().width();
    this->height = newImg.size().height();
}

void dis::Image::fillBySQL(const QSqlQuery &query, const QSqlRecord &rec){
    this->uuid = query.value(rec.indexOf("UUID")).toString();
    this->uuid_author = query.value(rec.indexOf("UUID_author")).toString();
    this->uuid_post = query.value(rec.indexOf("UUID_post")).toString();
    this->width = query.value(rec.indexOf("Width")).toInt();
    this->height = query.value(rec.indexOf("Height")).toInt();
    this->img_data = query.value(rec.indexOf("Image_data")).toByteArray();
    this->time_created = query.value(rec.indexOf("Time_created")).toDateTime();
    this->geo_data = query.value(rec.indexOf("Geo_data")).toString();
}

void dis::Image::fillByParse(const QVariantMap &params){}

QByteArray dis::Image::createMessageBody(const QString &separ){}

QByteArray dis::Image::createMessageBodyHtml(){}

#pragma GCC diagnostic pop
