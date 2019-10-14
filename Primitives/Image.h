#ifndef IMAGE_H
#define IMAGE_H

#include <QtSql>
#include <QDateTime>
#include <QDate>

#include "IPrimitives.h"

namespace dis{

//! @addtogroup entities
//! @{

class Image : IPrimitives
{
public:
    Image();

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

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) override;

    QString getMessageBody() override;

private:
    QByteArray createMessageBody(const QString &separ) override;
    QByteArray createMessageBodyHtml() override;
};

//! @} entities

}

#endif // IMAGE_H
