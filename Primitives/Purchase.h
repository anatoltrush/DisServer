#ifndef PURCHASE_H
#define PURCHASE_H

#include <QDateTime>
#include <QUuid>

#include "IPrimitives.h"

namespace dis{
//! @addtogroup entities
//! @{
class Purchase : public IPrimitives
{
public:
    Purchase();
    ~Purchase() override;

    QString uuid; // USER UUID
    QString purch_name;
    QDateTime time_paid;
    QDateTime time_exp;

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) override;

    QString getMessageBody() override;

private:
    QByteArray createMessageBody(const QString &separ) override;
    QByteArray createMessageBodyHtml() override;
};
//! @} entities
}

#endif // PURCHASE_H
