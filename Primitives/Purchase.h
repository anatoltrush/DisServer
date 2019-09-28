#ifndef PURCHASE_H
#define PURCHASE_H

#include <QDate>
#include <QUuid>

namespace dis{
class Purchase
{
public:
    Purchase();
    ~Purchase();

    QString uuid; // USER UUID
    QString purch_name;
    QDate time_paid;
    QDate time_exp;
};
}

#endif // PURCHASE_H
