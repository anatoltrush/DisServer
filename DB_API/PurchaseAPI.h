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
    ~PurchaseAPI() override;

    bool addPurchase();
    bool deletePurchase();
    bool redactPurchase();

    int getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitives>> &entities, QList<QString> &primitives) override;
};

//! @} database_api

}

#endif // PURCHASEAPI_H
