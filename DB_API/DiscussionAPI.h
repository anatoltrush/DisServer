#ifndef DISCUSSIONAPI_H
#define DISCUSSIONAPI_H

#include <QtSql>

#include "../QDisput/Primitives/Discussion.h"

namespace dis{
class DiscussionAPI
{
public:
    DiscussionAPI();

    bool addDispute(const QSqlDatabase& db, const dis::Discussion &discuss);
    bool deleteDisputeByUuid(const QSqlDatabase& db, const QString &uuid);
    bool updDisputeByUuid(const QSqlDatabase& db, const QString &uuid);

    bool getDisputeCount(const QSqlDatabase& db, int& count);
    bool getDisputeByUuid(const QSqlDatabase& db, const QString &uuid, dis::Discussion &disp);

    //! will be added other type of sorting
    bool getDisputesRange(const QSqlDatabase& db, QList<dis::Discussion>& discussions, int from, int batch);

private:
    QString tableName = "Disputes";

};
}

#endif // DISCUSSIONAPI_H
