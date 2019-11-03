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

    //! WARNING: use only for registration, not use in "postFunction"
    bool addUser(const dis::User &user);
    bool deleteUser(const QString &uuid);
    bool updateUser(const QString &uuid, const dis::User &newData);
    bool getUserByUuid(const QString &uuid, dis::User &user);

    bool getUsers(QList<dis::User>& users);

    int getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive>> &entities, QList<QString> &primitives) override;
    int postFunction(const HttpParser &parser) override;
    int patchFunction(const HttpParser &parser) override;
    int deleteFunction(const HttpParser &parser) override;

private:
};

//! @} database_api

}

#endif // USERAPI_H
