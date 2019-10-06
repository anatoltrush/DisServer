#ifndef ANSWERAPI_H
#define ANSWERAPI_H

#include "../QDisput/Primitives/Answer.h"

namespace dis{
class AnswerAPI
{
public:
    AnswerAPI();

    bool addAnswer(const QSqlDatabase& db, const dis::Answer &answer);

    bool getAnswersByDisputeUuid(const QSqlDatabase& db, const QString& dispUuid, QList<dis::Answer>& answers);

private:
    QString tableName = "Answers";
};
}

#endif // ANSWERAPI_H
