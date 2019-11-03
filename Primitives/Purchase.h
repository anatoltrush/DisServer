#ifndef PURCHASE_H
#define PURCHASE_H

#include "IPrimitive.h"

// TODO: #define PROP_USER_UUID"UUID + IN API" // example

namespace dis{
//! @addtogroup entities
//! @{
class Purchase : public IPrimitive
{
public:
    Purchase();
    ~Purchase() override;

    QString uuid; // USER UUID
    QString purch_name;
    QDateTime time_paid;
    QDateTime time_exp;

    QString getAuthor() const override {return "";} // no necessary to implement

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) override;
    void fillByParse(const QVariantMap &params) override;

private:
    QByteArray createMessageBody(const QString &separ) override;
    QByteArray createMessageBodyHtml() override;
};
//! @} entities
}

#endif // PURCHASE_H
