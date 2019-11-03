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

    int getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive>> &entities, QList<QString> &primitives) override;
    int postFunction(const HttpParser &parser) override;
    int patchFunction(const HttpParser &parser) override;
    int deleteFunction(const HttpParser &parser) override;
};

//! @} database_api

}

#endif // PURCHASEAPI_H
