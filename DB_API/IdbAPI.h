#ifndef IDBAPI_H
#define IDBAPI_H

#include <QString>

#include "../QDisput/Primitives/IPrimitives.h"

namespace dis{

//! @addtogroup database_api
//! @{

/**
 * @brief The IdbAPI is an interface for all inherited classes
 */
class IdbAPI
{
public:
    IdbAPI(const QString &tabName = "\tDEFAULT_TABLE_NAME\t", const QString &typeName = "\tDEFAULT_IdbAPI\t");
    virtual ~IdbAPI();

    //! name of the table in database
    QString tableName;

    //! name of the current API
    QString typeApi;

    virtual int getFunction(const QString &method, std::vector<std::unique_ptr<IPrimitives>> &primitives, QList<QString> &uuids) = 0;

//    virtual void postFunction() = 0;

//    virtual void patchFunction() = 0;

//    virtual void deleteFunction() = 0;
};

//! @} database_api
//!
}
#endif // IDBAPI_H
