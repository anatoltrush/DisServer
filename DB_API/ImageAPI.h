#ifndef IMAGEAPI_H
#define IMAGEAPI_H

#include "../QDisput/Primitives/Image.h"

namespace dis{
class ImageAPI
{
public:
    ImageAPI();

    bool addImage(const QSqlDatabase& db, const dis::Image &img);

    bool getImageByUuid(const QSqlDatabase& db, const QString &uuid, dis::Image &img);

    //! UUID of dispute OR album OR comment OR userID(if avatar)
    bool getImagesByPostUuid(const QSqlDatabase& db, const QString &postUuid, QList<dis::Image>& images);

private:
    QString tableName = "Images";
};
}

#endif // IMAGEAPI_H
