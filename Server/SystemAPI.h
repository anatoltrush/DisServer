#ifndef SYSTEMAPI_H
#define SYSTEMAPI_H

#include "../QDisput/Primitives/Client.h"

namespace dis{
class SystemAPI
{
public:
    SystemAPI();

    void sendToAll(const QList<dis::Client> &clients, const QByteArray &message);
    void kickByTime(QList<dis::Client> &clients);

    void registration(/**/);

    void logIn(/**/);
    void logOut(std::vector<QString> &allTokens, const QString &userToken);

    bool isAuthorized(const std::vector<QString> &allTokens, const QString &userToken);
};
}

#endif // SYSTEMAPI_H

// TODO: send message to all users
// TODO: whether request is CHAT
