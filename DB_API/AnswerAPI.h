#ifndef ANSWERAPI_H
#define ANSWERAPI_H

#include "IdbAPI.h"
#include "../QDisput/Primitives/Answer.h"

namespace dis{

//! @addtogroup database_api
//! @{

/**
 * @brief The AnswerAPI class working with "Answers" table in database
 */
class AnswerAPI : public IdbAPI
{
public:
    AnswerAPI();
    ~AnswerAPI() override;

    /**
     * @brief Add answer to database
     * @param db DataBase
     * @param answer New answer
     * @return true if query executed otherwise false
     */
    bool addAnswer(const QSqlDatabase& db, const dis::Answer &answer);

    /**
     * @brief Get answers by dispute Id
     * @param db DataBase
     * @param dispUuid dispute Id
     * @param answers List of received answers
     * @return true if query executed otherwise false
     */
    bool getAnswersByDisputeUuid(const QSqlDatabase& db, const QString& dispUuid, QList<dis::Answer>& answers);

    int getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives>> &primitives, QList<QString> &uuids) override;
};

//! @} database_api

}

#endif // ANSWERAPI_H
