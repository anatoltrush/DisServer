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

    //! @brief (POST) Add dispute to database
    bool addDispute(const dis::Discussion &dispute);

    //! @brief (DELETE) Delete dispute knowing it Id
    bool deleteDisputeByUuid(const QString &uuid);

    /**
     * @brief (PATCH) Update dispute knowing it Id
     * @param uuid Id of dispute
     */
    bool updDisputeByUuid(const QString &uuid);

    /**
     * @brief (GET) Helps to know amount of all disputes
     * @param count Amount of records in Dispute table
     */
    bool getDisputeCount(int& count);

    /**
     * @brief (GET) Get dispute knowing it Id
     * @param uuid Id of dispute
     * @param disp Filled dispute
     */
    bool getDisputeByUuid(const QString &uuid, dis::Discussion &disp);

    /**
     * @brief (GET) Get disputes in range.
     * Now sorting by time of creation
     * @param db DataBase
     * @param discussions List of received disputes
     * @param from Start index
     * @param batch Size of package
     *  @code
     *    discussionAPI.getDisputesRange(dbcntrl.dataBase, disps, 2, 4);
     *  @endcode
     * returns 4 records from 2 index to 5 index (start index = 0)
     * @todo sorting by topic and other...
     */
    bool getDisputesRange(QList<dis::Discussion>& discussions, int from, int batch);

    int getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives>> &primitives, QList<QString> &uuids) override;
};

//! @} database_api

}

#endif // DISCUSSIONAPI_H
