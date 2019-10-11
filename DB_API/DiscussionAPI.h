#ifndef DISCUSSIONAPI_H
#define DISCUSSIONAPI_H

#include "IdbAPI.h"
#include "../QDisput/Primitives/Discussion.h"

namespace dis{

//! @addtogroup database_api
//! @{

/**
 * @brief The DiscussionAPI class working with "Disputes" table in database
 */
class DiscussionAPI : public IdbAPI
{
public:
    DiscussionAPI();
    ~DiscussionAPI() override;

    /**
     * @brief Add dispute to database
     * @param db DataBase
     * @param dispute New dispute
     * @return true if query executed otherwise false
     */
    bool addDispute(const QSqlDatabase& db, const dis::Discussion &dispute);

    /**
     * @brief Delete dispute knowing it Id
     * @param db DataBase
     * @param uuid Id of dispute
     * @return true if query executed otherwise false
     */
    bool deleteDisputeByUuid(const QSqlDatabase& db, const QString &uuid);

    /**
     * @brief Update dispute knowing it Id
     * @param db DataBase
     * @param uuid Id of dispute
     * @return true if query executed otherwise false
     */
    bool updDisputeByUuid(const QSqlDatabase& db, const QString &uuid);

    /**
     * @brief Helps to know amount of all disputes
     * @param db DataBase
     * @param count Amount of records in Dispute table
     * @return true if query executed otherwise false
     */
    bool getDisputeCount(const QSqlDatabase& db, int& count);

    /**
     * @brief Get dispute knowing it Id
     * @param db DataBase
     * @param uuid Id of dispute
     * @param disp Filled dispute
     * @return true if query executed otherwise false
     */
    bool getDisputeByUuid(const QSqlDatabase& db, const QString &uuid, dis::Discussion &disp);

    /**
     * @brief Get disputes in range.
     * Now sorting by time of creation
     * @param db DataBase
     * @param discussions List of received disputes
     * @param from Start index
     * @param batch Size of package
     * @return true if query executed otherwise false
     *  @code
     *    discussionAPI.getDisputesRange(dbcntrl.dataBase, disps, 2, 4);
     *  @endcode
     * returns 4 records from 2 index to 5 index (start index = 0)
     * @todo sorting by topic and other...
     */
    bool getDisputesRange(const QSqlDatabase& db, QList<dis::Discussion>& discussions, int from, int batch);

    int getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives>> &primitives, QList<QString> &uuids) override;
};

//! @} database_api

}

#endif // DISCUSSIONAPI_H
