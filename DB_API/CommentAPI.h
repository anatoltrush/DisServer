#ifndef COMMENTAPI_H
#define COMMENTAPI_H

#include "IdbAPI.h"
#include "../QDisput/Primitives/Comment.h"

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

    bool getCommByUuid(const QString &uuid, dis::Comment &comment);

    int getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives>> &primitives,
                    QList<QString> &uuids, const QList<QVariantMap> &params) override;
};

//! @} database_api

}

#endif // COMMENTAPI_H
