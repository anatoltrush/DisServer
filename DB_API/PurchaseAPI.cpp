#include "PurchaseAPI.h"

dis::PurchaseAPI::PurchaseAPI() : IdbAPI ("Purchases", "purchases"){}

dis::PurchaseAPI::~PurchaseAPI(){}

bool dis::PurchaseAPI::addPurchase(){
    return 1;
}

bool dis::PurchaseAPI::deletePurchase(){
    return 1;
}

bool dis::PurchaseAPI::redactPurchase(){
    return 1;
}

int dis::PurchaseAPI::getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives> > &primitives, QList<QString> &uuids){
    primitives.clear();
    uuids.clear();
    // -----
    return 1;
}
