#ifndef PURCHASEAPI_H
#define PURCHASEAPI_H

#include <QtSql>

#include "../QDisput/Primitives/Purchase.h"

namespace dis{
class PurchaseAPI
{
public:
    PurchaseAPI();
    ~PurchaseAPI();

    bool addPurchase();
    bool deletePurchase();
    bool redactPurchase();

private:
    QString tableName = "Purchases";
};
}

#endif // PURCHASEAPI_H
