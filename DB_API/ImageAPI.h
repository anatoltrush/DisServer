#ifndef IMAGEAPI_H
#define IMAGEAPI_H

#include "IdbAPI.h"
#include "../Primitives/Image.h"

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
     * @param images List of received images
     */
    bool getImagesByPostUuid(const QString &postUuid, QList<dis::Image>& images);
    bool getImagesByPostUuidLight(const QString &postUuid, QList<dis::Image>& images, const QSize &size);

    bool deleteImagesByPostUuid(const QString &postUuid);

    int getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive>> &entities, QList<QString> &primitivess) override;
    int postFunction(const HttpParser &parser) override;
    int patchFunction(const HttpParser &parser) override;
    int deleteFunction(const HttpParser &parser) override;
};

//! @} database_api

}

#endif // IMAGEAPI_H
