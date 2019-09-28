#ifndef IMAGEAPI_H
#define IMAGEAPI_H

#include "../QDisput/Primitives/Image.h"

namespace dis{
class ImageAPI
{
public:
    ImageAPI();

    bool addImage(const QSqlDatabase& db, const dis::Image &img);

    bool getImageByOwnerUuid(const QSqlDatabase& db, const QString &uuid, dis::Image &img, int type = -1, const QString &geo = "na");
};
}

#endif // IMAGEAPI_H
