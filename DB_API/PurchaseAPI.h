#ifndef PURCHASEAPI_H
#define PURCHASEAPI_H

#include <QtSql>

#include "../QDisput/Primitives/Purchase.h"

namespace dis{
class PurchaseAPI
{
public:
    PurchaseAPI();

    bool addPurchase();
    bool deletePurchase();
    bool redactPurchase();
};
}

#endif // PURCHASEAPI_H

// TODO: add GET
