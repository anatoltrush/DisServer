#ifndef PURCHASEAPI_H
#define PURCHASEAPI_H

#include "IdbAPI.h"
#include "../QDisput/Primitives/Purchase.h"

namespace dis{

//! @addtogroup database_api
//! @{

class PurchaseAPI : public IdbAPI
{
public:
    PurchaseAPI();
    ~PurchaseAPI();

    bool addPurchase();
    bool deletePurchase();
    bool redactPurchase();
};

//! @} database_api

}

#endif // PURCHASEAPI_H
