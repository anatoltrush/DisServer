#include "PurchaseAPI.h"

dis::PurchaseAPI::PurchaseAPI() : IdbAPI ("Purchases", "purchases"){}

dis::PurchaseAPI::~PurchaseAPI(){}

bool dis::PurchaseAPI::addPurchase(){}

bool dis::PurchaseAPI::deletePurchase(){}

bool dis::PurchaseAPI::redactPurchase(){}

int dis::PurchaseAPI::getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives> > &primitives, QList<QString> &uuids){
    primitives.clear();
    uuids.clear();
    // -----
}
