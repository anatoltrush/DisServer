//#ifndef COMMENTAPI_H
//#define COMMENTAPI_H

#pragma once

#include "IdbAPI.h"
#include "../Primitives/Comment.h"
#include "../DB_API/ImageAPI.h"

namespace dis{

//! @addtogroup database_api
//! @{
class CommentAPI : public IdbAPI
{
public:
    CommentAPI();
    ~CommentAPI() override = default;

    bool addComment(const dis::Comment &comment);

    bool updateComment(const QString &uuid, const dis::Comment &newComm);

    bool getCommentByUuid(const QString &uuid, dis::Comment &comment);
    bool getCommUuidsByPostUuid(const QString &postUuid, std::vector<QString> &commUuids);
    bool isHasReceiver(const QString &uuid, QString &receiverUuid);

    bool deleteCommByUuidPseudo(const QString &uuid);
    bool deleteCommentByUuid(const QString &uuid);
    [[deprecated("Old version. Use <deleteCommentByPostUuidAll> instead")]]
    bool deleteCommentByPostUuidRecurs(const QString &postUuid);
    bool deleteCommentByPostUuidAll(const QString &postUuid);

    bool getObjectPart(const HttpParser& parser, std::unique_ptr<IPrimitive>& object) override;

    int getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive>> &entities, QList<QString> &primitives) override;
    int postFunction(const HttpParser &parser) override;
    int patchFunction(const HttpParser &parser) override;
    int deleteFunction(const HttpParser &parser) override;

private:
    bool deleteCommentUuid(const QString &uuid);
};
//! @} database_api
}

//#endif // COMMENTAPI_H
