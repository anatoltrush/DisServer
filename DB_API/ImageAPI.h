#ifndef IMAGEAPI_H
#define IMAGEAPI_H

#include "../QDisput/Primitives/Image.h"

namespace dis{
class ImageAPI
{
public:
    ImageAPI();

    bool addImage(const QSqlDatabase& db, const dis::Image &img);

    bool getImageByUuid(const QSqlDatabase& db, const QString &uuid, dis::Image &img, const QString &geo = "na");  // FIXME: no need, delete later
};
}

#endif // IMAGEAPI_H
