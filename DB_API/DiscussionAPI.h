#ifndef DISCUSSIONAPI_H
#define DISCUSSIONAPI_H

#include <QtSql>

#include "../QDisput/Primitives/Discussion.h"

namespace dis{
class DiscussionAPI
{
public:
    DiscussionAPI();
    ~DiscussionAPI();

    bool addDiscussion(const QSqlDatabase& db, const dis::Discussion &discuss);
    bool deleteDiscussion(const QSqlDatabase& db);
    bool redactDiscussion(const QSqlDatabase& db);

    bool getDiscussions(const QSqlDatabase& db, QList<dis::Discussion>& discussions);
};
}

#endif // DISCUSSIONAPI_H
