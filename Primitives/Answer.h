#ifndef ANSWER_H
#define ANSWER_H

#include "IPrimitive.h"

#define PROP_ANS_UUID       "UUID"
#define PROP_ANS_UUID_DISP  "UUID_dispute"
#define PROP_ANS_TEXT       "Text_data"
#define PROP_ANS_SCORE      "Score"

namespace dis{

//! @addtogroup entities
//! @{

class Answer : public IPrimitive
{
public:
    Answer();
    ~Answer() override;

    QString uuid = QUuid::createUuid().toString();
    QString uuid_dispute;
    QString text;
    int score = 0;

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
