#ifndef IMAGEAPI_H
#define IMAGEAPI_H

#include "IdbAPI.h"
#include "../QDisput/Primitives/Image.h"

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

    /**
     * @brief Get only one image by it Id
     * @param uuid Image Id
     * @param img Received imge
     */
    bool getImageByUuid(const QString &uuid, dis::Image &img);

    //! UUID of dispute OR album OR comment OR userID(if avatar)
    /**
     * @brief Get images by post Id
     * @param postUuid It can be disputeId OR albumId OR commentId OR smthn else
     * @param images List of received images
     */
    bool getImagesByPostUuid(const QString &postUuid, QList<dis::Image>& images);

    int getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives>> &primitives,
                    QList<QString> &uuids, const QList<QVariantMap> &params) override;
};

//! @} database_api

}

#endif // IMAGEAPI_H
