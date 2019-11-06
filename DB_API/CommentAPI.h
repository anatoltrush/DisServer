#ifndef COMMENTAPI_H
#define COMMENTAPI_H

#include "IdbAPI.h"
#include "../Primitives/Comment.h"
#include "../DB_API/ImageAPI.h"

namespace dis{

//! @addtogroup database_api
//! @{
//!
class CommentAPI : public IdbAPI
{
public:
    CommentAPI();
    ~CommentAPI() override;

    bool addComment(const dis::Comment &comment);

    bool getCommentByUuid(const QString &uuid, dis::Comment &comment);
    bool getCommUuidsByPostUuid(const QString &postUuid, QList<QString> &commUuids);

    bool deleteCommentByPostUuid(const QString &postUuid);
    bool deleteCommentByPostUuidFull(const QString &postUuid);

    int getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive>> &entities, QList<QString> &primitives) override;
    int postFunction(const HttpParser &parser) override;
    int patchFunction(const HttpParser &parser) override;
    int deleteFunction(const HttpParser &parser) override;
};

//! @} database_api

}

#endif // COMMENTAPI_H
