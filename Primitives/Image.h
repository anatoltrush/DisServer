#ifndef IMAGE_H
#define IMAGE_H

#include "IPrimitive.h"

#define IMG_FORMAT_JPG  "JPG"

// TODO: #define PROP_USER_UUID"UUID + IN API" // example

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

    int width = 0;
    int height = 0;
    QByteArray img_data;

    QDateTime time_created;

    //! if has
    QString geo_data;

    void resize(const QSize &size);

    QString getAuthor() const override {return "";} // no necessary to implement

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) override;
    void fillByParse(const QVariantMap &params) override;

private:
    QString currentFormat = IMG_FORMAT_JPG;

    QByteArray createMessageBody(const QString &separ) override;
    QByteArray createMessageBodyHtml() override;
};

//! @} entities

}

#endif // IMAGE_H
