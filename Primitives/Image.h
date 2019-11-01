#ifndef IMAGE_H
#define IMAGE_H

#include "IPrimitives.h"

// TODO: #define PROP_USER_UUID"UUID + IN API" // example

namespace dis{

//! @addtogroup entities
//! @{

class Image : public IPrimitives
{
public:
    Image();
    ~Image() override;

    QString uuid = QUuid::createUuid().toString();
    QString uuid_author;

    //! can be dispute OR album OR comment OR userID(if avatar)
    QString uuid_post;

    int width;
    int height;
    QByteArray img_data;

    QDateTime time_created;

    //! if has
    QString geo_data;

    void resize(const QSize &size);

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) override;
    void fillByParse(const QVariantMap &params) override;

private:    
    QByteArray createMessageBody(const QString &separ) override;
    QByteArray createMessageBodyHtml() override;
};

//! @} entities

}

#endif // IMAGE_H
