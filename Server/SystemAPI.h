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

    void logOut(QStringMap &allTokens, const QString &userToken); // OPTION
    bool isAuthorized(const QStringMap &allTokens, const QString &userToken, QString &currUsr);

    bool checkPswrd(const QSqlDatabase &db, const QString &tableName, const QString &pswrd, QString &uuid);
    bool isEmailExsist(const QSqlDatabase &db, const QString &tableName, const QString &Email, bool &isExsist);
};
}

#endif // SYSTEMAPI_H

// TODO: send message to all users
// TODO: whether request is CHAT
