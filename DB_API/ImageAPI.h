//#ifndef IMAGEAPI_H
//#define IMAGEAPI_H

#pragma once

#include "IdbAPI.h"
#include "../Primitives/Image.h"
#include "../DB_API/CommentAPI.h"

namespace dis{

//! @addtogroup database_api
//! @{

/**
 * @brief The ImageAPI class working with "Images" table in database
 */
class ImageAPI : public IdbAPI
{
public:
    ImageAPI();
    ~ImageAPI() override;

    //! @brief Add image to database
    bool addImage(const dis::Image &img);

    //! @brief Get only one image by it Id
    bool getImageByUuid(const QString &uuid, dis::Image &img);

    //! UUID of dispute OR album OR comment OR userID(if avatar)
    /**
     * @brief Get images by post Id
     * @param postUuid It can be disputeId OR albumId OR commentId OR smthn else
     */
    bool getImagesByPostUuid(const QString &postUuid, QList<dis::Image>& images);
    bool getImagesByPostUuidLight(const QString &postUuid, QList<dis::Image>& images, const QSize &size);
    bool getImagesUuidsByPostUuid(const QString &postUuid, QList<QString> &imgsUuids);

    bool deleteImageByUuid(const QString &uuid);

    bool getObjectPart(const HttpParser& parser, std::unique_ptr<IPrimitive>& object) override;

    int getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive>> &entities, QList<QString> &primitivess) override;
    int postFunction(const HttpParser &parser) override;
    int patchFunction(const HttpParser &parser) override;
    int deleteFunction(const HttpParser &parser) override;

private:
    bool deleteImageUuid(const QString &uuid);
};

//! @} database_api

}

//#endif // IMAGEAPI_H
