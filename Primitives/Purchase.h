#ifndef PURCHASE_H
#define PURCHASE_H

#include <QDate>
#include <QUuid>

namespace dis{
class Purchase
{
public:
    Purchase();

    QUuid uuid = QUuid::createUuid();
    int cost = 0;
    QString purch_name;
    QDate time_paid;
    QDate time_exp;
};
}

#endif // PURCHASE_H
