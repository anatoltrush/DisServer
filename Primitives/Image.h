#ifndef IMAGE_H
#define IMAGE_H

#include <QtSql>

namespace dis{
class Image
{
public:
    Image();

    //! uuid of owner
    QString uuid;

    int width;
    int height;

    QByteArray img_data;

    //! avatar OR album OR comment OR else
    QString type;

    QString time_create;

    //! if has
    QString geo_data;

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec);
};
}

#endif // IMAGE_H
