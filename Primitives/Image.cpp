#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"

#include "Image.h"

void dis::Image::resize(const QSize &size){
    QImage oldImg = QImage::fromData(img_data, format.toStdString().c_str());
//    QImage oldImg(reinterpret_cast<const unsigned char*>(img_data.data()), width, height, QImage::Format_RGB32);
    QImage newImg = oldImg.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QByteArray Qba;
    QBuffer buffer(&Qba);
    buffer.open(QIODevice::WriteOnly);
    newImg.save(&buffer, format.toStdString().c_str());
    buffer.close();

    this->img_data = Qba;
    this->width = newImg.size().width();
    this->height = newImg.size().height();
}

void dis::Image::fillBySQL(const QSqlQuery &query, const QSqlRecord &rec){
    this->uuid = query.value(rec.indexOf(PROP_IMG_UUID)).toString();
    this->uuid_author = query.value(rec.indexOf(PROP_IMG_UUID_ATHR)).toString();
    this->uuid_post = query.value(rec.indexOf(PROP_IMG_UUID_ATHR)).toString();
    this->img_data = query.value(rec.indexOf(PROP_IMG_DATA)).toByteArray();
    this->width = query.value(rec.indexOf(PROP_IMG_W)).toInt();
    this->height = query.value(rec.indexOf(PROP_IMG_H)).toInt();
    this->format = query.value(rec.indexOf(PROP_IMG_FRMT)).toString();
    this->time_created = query.value(rec.indexOf(PROP_IMG_TIME_CRTD)).toDateTime();
    this->geo_data = query.value(rec.indexOf(PROP_IMG_GEO)).toString();
    this->like = query.value(rec.indexOf(PROP_IMG_LIKE)).toInt();
    this->disLike = query.value(rec.indexOf(PROP_IMG_DLIKE)).toInt();
}

void dis::Image::fillByParse(const QVariantMap &params){}

QByteArray dis::Image::createMessageBody(const QString &separ){}

QByteArray dis::Image::createMessageBodyHtml(){}

#pragma GCC diagnostic pop
