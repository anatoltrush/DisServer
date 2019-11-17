#ifndef IMAGE_H
#define IMAGE_H

#include "IPrimitive.h"

#define PROP_IMG_UUID       "UUID"
#define PROP_IMG_UUID_ATHR  "UUID_author"
#define PROP_IMG_UUID_POST  "UUID_post"
#define PROP_IMG_DATA       "Image_data"
#define PROP_IMG_W          "Width"
#define PROP_IMG_H          "Height"
#define PROP_IMG_FRMT       "Format"
#define PROP_IMG_TIME_CRTD  "Time_created"
#define PROP_IMG_GEO        "Geo_data"
#define PROP_IMG_LIKE       "Lice"
#define PROP_IMG_DLIKE      "Dislike"

namespace dis{

//! @addtogroup entities
//! @{
class Image : public IPrimitive
{
public:
    Image();
    ~Image() override;

    QString uuid = QUuid::createUuid().toString();
    QString uuid_author;

    //! can be DISPUTE_ID or ALBUM_ID or COMMENT_ID or USER_ID(if avatar)
    QString uuid_post;

    QByteArray img_data;
    int width = 0;
    int height = 0;
    QString format = IMG_FORMAT_JPG;

    QDateTime time_created;

    //! if has
    QString geo_data;

    int like = 0;
    int disLike = 0;

    void resize(const QSize &size);

    QString getUUID() const override {return "";} // no necessary to implement
    QString getAuthor() const override {return "";} // no necessary to implement

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) override;
    void fillByParse(const QVariantMap &params) override;

private:
    QByteArray createMessageBody(const QString &separ) override;
    QByteArray createMessageBodyHtml() override;
};
//! @} entities
}

#endif // IMAGE_H
