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

    bool addComment(const QSqlDatabase& db, const dis::Comment &comment);

    bool getCommByUuid(const QSqlDatabase& db, const QString &uuid, dis::Comment &comment);

    int getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives>> &primitives, QList<QString> &uuids) override;
};

//! @} database_api

}

#endif // COMMENTAPI_H
