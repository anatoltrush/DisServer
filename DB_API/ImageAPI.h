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

    /**
     * @brief Add image to database
     * @param db DataBase
     * @param img New image
     * @return true if query executed otherwise false
     */
    bool addImage(const QSqlDatabase& db, const dis::Image &img);

    /**
     * @brief Get only one image by it Id
     * @param db DataBase
     * @param uuid Image Id
     * @param img Received imge
     * @return true if query executed otherwise false
     */
    bool getImageByUuid(const QSqlDatabase& db, const QString &uuid, dis::Image &img);

    //! UUID of dispute OR album OR comment OR userID(if avatar)
    /**
     * @brief Get images by post Id
     * @param db DataBase
     * @param postUuid It can be disputeId OR albumId OR commentId OR smthn else
     * @param images List of received images
     * @return true if query executed otherwise false
     */
    bool getImagesByPostUuid(const QSqlDatabase& db, const QString &postUuid, QList<dis::Image>& images);

    int getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives>> &primitives, QList<QString> &uuids) override;
};

//! @} database_api

}

#endif // IMAGEAPI_H
