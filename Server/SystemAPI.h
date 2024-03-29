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
    SystemAPI() = default;
    ~SystemAPI() = default;

    static qint64 maxTimeLastReq;
    static int minNumberUsers;

    static float needFreeRamPerc;
    static float percRamLeft;

    static float minFreeFilePerc;
    static float minFileSizeMB;

    void sendToAll(const QList<dis::Client> &clients, const QByteArray &message);

    bool isAlreadyIn(const QList<dis::Client> &clients, const QString &userUuid);
    void logOut(QList<dis::Client> &clients, const QString &userToken);
    bool isAuthorized(QList<Client> &clients, const QString &userToken, QString &currUser);
    bool isVerified(const QString &currUser, const IPrimitive &object) {return currUser == object.getAuthor();}

    static float getFreeRamPerc();
    static QDateTime getTimeDiff(const QDateTime &lastReq);

    static void kickOld(QList<dis::Client> &clients);
    static void kickByTime(QList<dis::Client> &clients);
    static void kickByNumber(QList<dis::Client> &clients);

    // shrink functions
    static bool getFileSize(const QSqlDatabase &dataBase, float &val);
    static bool getUnAlloc(const QSqlDatabase &dataBase, float &val);
    static void shrinkDBaseFiles(const QSqlDatabase &dataBase);
};
}

#endif // SYSTEMAPI_H
