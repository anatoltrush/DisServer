#ifndef SYSTEMAPI_H
#define SYSTEMAPI_H

#include "../Common/disDefines.h"
#include "../Primitives/Client.h"

namespace dis{
class SystemAPI
{
public:
    SystemAPI();

    void sendToAll(const QList<dis::Client> &clients, const QByteArray &message);
    void kickByTime(QList<dis::Client> &clients);

    void registration(/**/);

    void logIn(/**/);
    void logOut(QStringMap &allTokens, const QString &userToken);

    bool isAuthorized(const QStringMap &allTokens, const QString &userToken);
};
}

#endif // SYSTEMAPI_H

// TODO: send message to all users
// TODO: whether request is CHAT
