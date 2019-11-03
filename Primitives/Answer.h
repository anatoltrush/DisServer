#ifndef ANSWER_H
#define ANSWER_H

#include "IPrimitive.h"

// TODO: #define PROP_USER_UUID"UUID + IN API" // example

namespace dis{

//! @addtogroup entities
//! @{

class Answer : public IPrimitive
{
public:
    Answer();
    ~Answer() override;

    QString uuid_dispute;
    QString text;
    int score;

    QString getAuthor() const override {return "";} // no necessary to implement

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) override;
    void fillByParse(const QVariantMap &params) override;

private:
    QByteArray createMessageBody(const QString &separ) override;
    QByteArray createMessageBodyHtml() override;
};

//! @} entities

}

#endif // ANSWER_H
