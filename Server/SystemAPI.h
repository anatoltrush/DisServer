#ifndef SYSTEMAPI_H
#define SYSTEMAPI_H

#include "../Primitives/Client.h"
#include "../Primitives/IPrimitive.h"

#ifdef linux

#elif _WIN32
#include <windows.h>
#elif __APPLE__

#else

#endif

namespace dis{
class SystemAPI
{
public:
    SystemAPI();

    static uint maxTimeSecs;
    static float maxMemPercs;
    static int maxNumUsers;

    void sendToAll(const QList<dis::Client> &clients, const QByteArray &message);

    bool isAlreadyIn(const QList<dis::Client> &clients, const QString &userUuid);
    void logOut(QList<dis::Client> &clients, const QString &userToken);
    bool isAuthorized(QList<Client> &clients, const QString &userToken, QString &currUser);
    bool isVerified(const QString &currUser, const IPrimitive &object) {return currUser == object.getAuthor();}

    static float getFreeMemSize();
    static QDateTime getTimeDiff(const QDateTime &lastReq);

    static void kickByTime(QList<dis::Client> &clients);
    static void kickByMemory(QList<dis::Client> &clients);
    static void kickByNumber(QList<dis::Client> &clients);
};
}

#endif // SYSTEMAPI_H
