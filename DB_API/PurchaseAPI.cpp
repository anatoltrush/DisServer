#include "PurchaseAPI.h"

dis::PurchaseAPI::PurchaseAPI() : IdbAPI ("Purchases", API_TYPE_PURCHASES){}

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

int dis::PurchaseAPI::getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitives> > &entities, QList<QString> &primitives){
    entities.clear();
    primitives.clear();
    // -----
    return HTTP_METHOD_NOT_ALLOWED;
}

int dis::PurchaseAPI::postFunction(const dis::HttpParser &parser){}
