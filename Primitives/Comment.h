#ifndef COMMENT_H
#define COMMENT_H

#include "IPrimitive.h"

#define PROP_COMM_UUID          "UUID"
#define PROP_COMM_UUID_POST     "UUID_post"
#define PROP_COMM_UUID_ATHR     "UUID_author"
#define PROP_COMM_UUID_RCVR     "UUID_receiver"
#define PROP_COMM_TIME_CRTD     "Time_created"
#define PROP_COMM_TEXT          "Text_data"
#define PROP_COMM_LIKE          "Lice"
#define PROP_COMM_DLIKE         "Dislike"
#define PROP_COMM_ISDLTD        "Is_deleted"

namespace dis{
//! @addtogroup entities
//! @{
class Comment : public IPrimitive
{
public:
    Comment() = default;
    ~Comment() override = default;

    QString uuid = QUuid::createUuid().toString();

    //! can be DISPUTE_ID or COMMENT_ID or USER_ID(if his foto)
    QString uuid_post;
    QString uuid_author;
    //! can be empty if first comment at all
    QString uuid_receiver;
    QDateTime time_created;
    QString text;
    int like = 0;
    int disLike = 0;
    bool isDeleted = false;

    QString getUUID() const override {return uuid;}
    QString getAuthor() const override {return uuid_author;}

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) override;
    void fillByParse(const QVariantMap &params) override;

private:
    QByteArray createMessageBody(const QString &separ) override;
    QByteArray createMessageBodyHtml() override;
};
//! @} entities
}

#endif // COMMENT_H
