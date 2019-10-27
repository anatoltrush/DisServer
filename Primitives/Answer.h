#ifndef ANSWER_H
#define ANSWER_H

#include "IPrimitives.h"

// TODO: #define PROP_USER_UUID"UUID" // example

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

    void fillByParse(const QVariantMap &params) override;

private:
    QByteArray createMessageBody(const QString &separ) override;
    QByteArray createMessageBodyHtml() override;
};

//! @} entities

}

#endif // ANSWER_H
