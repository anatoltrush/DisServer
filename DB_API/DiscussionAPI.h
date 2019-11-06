#ifndef DISCUSSIONAPI_H
#define DISCUSSIONAPI_H

#include "IdbAPI.h"
#include "ImageAPI.h"
#include "AnswerAPI.h"
#include "CommentAPI.h"
#include "../Primitives/Discussion.h"

#define API_KW_DISP_FROM    "from"
#define API_KW_DISP_PACKAGE "package"

namespace dis{

//! @addtogroup database_api
//! @{
//! @brief The DiscussionAPI class working with "Disputes" table in database
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

    //! @brief (GET) Helps to know amount of all disputes
    bool getDisputeCount(int& count);

    //! @brief (GET) Get dispute knowing it Id
    bool getDisputeByUuid(const QString &uuid, dis::Discussion &disp);

    /**
     * @brief (GET) Get disputes in range.
     * Now sorting by time of creation
     * @param discussions List of received disputes
     * @param from Start index
     * @param batch Size of package
     *  @code
     *    discussionAPI.getDisputesRange(dbcntrl.dataBase, disps, 2, 4);
     *  @endcode
     * returns 4 records from 2 index to 5 index (start index = 0)
     * @todo sorting by topic and other params...
     */
    bool getDisputesRange(QList<dis::Discussion>& discussions, int from, int batch);
    bool getDispUuidsRange(QList<QString>& uuids, int from, int batch);

    int getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive>> &entities, QList<QString> &primitives) override;
    int postFunction(const HttpParser &parser) override;
    int patchFunction(const HttpParser &parser) override;
    int deleteFunction(const HttpParser &parser) override;

private:
    bool deleteDisputeUuid(const QString &uuid);
};
//! @} database_api
}

#endif // DISCUSSIONAPI_H
