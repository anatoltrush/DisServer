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

int dis::PurchaseAPI::getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive> > &entities, QList<QString> &primitives){
    entities.clear();
    primitives.clear();
    // -----
    return HTTP_METHOD_NOT_ALLOWED;
}

int dis::PurchaseAPI::postFunction(const dis::HttpParser &parser){}

int dis::PurchaseAPI::patchFunction(const dis::HttpParser &parser){}

int dis::PurchaseAPI::deleteFunction(const HttpParser &parser){
    // no necessary to implement
    qDebug() << "-----> WARNING: USING UNIMPLEMENTED METHOD! <-----";
    return HTTP_METHOD_NOT_ALLOWED;
}
