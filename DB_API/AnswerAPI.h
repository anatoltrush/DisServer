#ifndef ANSWERAPI_H
#define ANSWERAPI_H

#include "IdbAPI.h"
#include "../Primitives/Answer.h"

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
    ~AnswerAPI() override = default;

    bool addAnswer(const dis::Answer &answer);

    //! @brief Get answers by dispute Id
    bool getAnswersByDisputeUuid(const QString& dispUuid, QList<dis::Answer>& answers);

    bool deleteAnswersByDisputeUuid(const QString &uuid);

    bool getObjectPart(const HttpParser& parser, std::unique_ptr<IPrimitive>& object) override;

    int getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive>> &entities, QList<QString> &primitives) override;
    int postFunction(const HttpParser &parser) override;
    int patchFunction(const HttpParser &parser) override;
    int deleteFunction(const HttpParser &parser) override;
};

//! @} database_api

}

#endif // ANSWERAPI_H
