#ifndef ANSWER_H
#define ANSWER_H

#include "IPrimitives.h"

namespace dis{

//! @addtogroup entities
//! @{

class Answer : public IPrimitives
{
public:
    Answer();
    ~Answer() override;

    QString uuid_dispute;
    QString text;
    int score;

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) override;

    QString getMessageBody() override;

private:
    void createMessageBody() override;
};

//! @} entities

}

#endif // ANSWER_H
