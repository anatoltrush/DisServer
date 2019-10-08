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

    bool addComment(const QSqlDatabase& db, const dis::Comment &comment);

    bool getCommByUuid(const QSqlDatabase& db, const QString &uuid, dis::Comment &comment);
};

//! @} database_api

}

#endif // COMMENTAPI_H
