#ifndef COMMENT_H
#define COMMENT_H

#include "IPrimitives.h"

// TODO: #define PROP_USER_UUID"UUID + IN API" // example

namespace dis{
//! @addtogroup entities
//! @{
class Comment : public IPrimitives
{
public:
    Comment();
    ~Comment() override;

    QString uuid = QUuid::createUuid().toString();

    //! dispute OR foto OR other comment
    QString uuid_post;

    QString uuid_author;

    //! can be empty if first comment at all
    QString uuid_receiver;

    QDateTime time_created;

    QString text;

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) override;
    void fillByParse(const QVariantMap &params) override;

private:
    QByteArray createMessageBody(const QString &separ) override;
    QByteArray createMessageBodyHtml() override;
};
//! @} entities
}

#endif // COMMENT_H
