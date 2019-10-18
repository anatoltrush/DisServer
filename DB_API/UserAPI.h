#ifndef USERAPI_H
#define USERAPI_H

#include "IdbAPI.h"
#include "../QDisput/Primitives/User.h"

namespace dis{

//! @addtogroup database_api
//! @{

class UserAPI : public IdbAPI
{
public:
    UserAPI();
    ~UserAPI() override;

    bool addUser(const dis::User &user);
    bool deleteUser(const QString &uuid);
    bool updateUser(const QString &uuid, const dis::User &newData);
    bool getUserByUuid(const QString &uuid, dis::User &user);

    bool getUsers(QList<dis::User>& users);

    int getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives>> &entities,
                    QList<QString> &primitives, const QVariantMap &params) override;

private:
};

//! @} database_api

}

#endif // USERAPI_H
