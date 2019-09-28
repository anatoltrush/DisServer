#ifndef COMMENTAPI_H
#define COMMENTAPI_H

#include "../QDisput/Primitives/Comment.h"

namespace dis{
class CommentAPI
{
public:
    CommentAPI();

    bool addComment(const QSqlDatabase& db, const dis::Comment &comment);
};
}

#endif // COMMENTAPI_H
