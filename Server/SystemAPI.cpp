#include "SystemAPI.h"

dis::SystemAPI::SystemAPI(){
}

void dis::SystemAPI::sendToAll(const QList<dis::Client> &clients, const QByteArray &message){}

void dis::SystemAPI::kickByTime(QList<dis::Client> &clients){}

void dis::SystemAPI::logOut(std::vector<QString> &allTokens, const QString &userToken){
    for(size_t i = 0; i < allTokens.size(); i++)
        if(allTokens[i] == userToken)
            allTokens.erase(allTokens.begin() + i);
}

bool dis::SystemAPI::isAuthorized(const std::vector<QString> &allTokens, const QString &userToken){
    for(const auto &tkn : allTokens)
        if(tkn == userToken)
            return true;
    return false;
}
