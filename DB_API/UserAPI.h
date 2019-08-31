#ifndef USERAPI_H
#define USERAPI_H

#include "../QDisput/Primitives/User.h"

namespace dis{
class UserAPI
{
public:
    UserAPI();

    bool addUser(const QSqlDatabase& db);
    bool deleteUser(const QSqlDatabase& db);
    bool redactUser(const QSqlDatabase& db);
    bool getUser(const QSqlDatabase& db, dis::User& user);

    bool getUsers(const QSqlDatabase& db, QList<dis::User>& users);
};
}

#endif // USERAPI_H

// TODO: add GET
