#ifndef PURCHASE_H
#define PURCHASE_H

#include <QDateTime>
#include <QUuid>

namespace dis{
class Purchase
{
public:
    Purchase();
    ~Purchase();

    QString uuid; // USER UUID
    QString purch_name;
    QDateTime time_paid;
    QDateTime time_exp;
};
}

#endif // PURCHASE_H
