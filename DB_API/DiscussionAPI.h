#ifndef DISCUSSIONAPI_H
#define DISCUSSIONAPI_H

#include <QtSql>

#include "../QDisput/Primitives/Discussion.h"

namespace dis{
class DiscussionAPI
{
public:
    DiscussionAPI();

    bool addDiscussion(const QSqlDatabase& db, const dis::Discussion &discuss);
    bool deleteDiscussion(const QSqlDatabase& db);
    bool redactDiscussion(const QSqlDatabase& db);

    bool getDisputeByUuid(const QSqlDatabase& db, const QString &uuid, dis::Discussion &disp);
    bool getDiscussions(const QSqlDatabase& db, QList<dis::Discussion>& discussions); // FIXME: delete later ???

};
}

#endif // DISCUSSIONAPI_H
