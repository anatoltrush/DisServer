#ifndef PURCHASE_H
#define PURCHASE_H

#include "IPrimitives.h"

// TODO: #define PROP_USER_UUID"UUID" // example

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
    void fillByParse(const QVariantMap &params) override;

private:
    QByteArray createMessageBody(const QString &separ) override;
    QByteArray createMessageBodyHtml() override;
};
//! @} entities
}

#endif // PURCHASE_H
