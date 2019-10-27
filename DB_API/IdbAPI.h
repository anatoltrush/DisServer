#ifndef IDBAPI_H
#define IDBAPI_H

#include <QString>

#include "../Common/unique.h"
#include "../Primitives/IPrimitives.h"
#include "../Server/Constants.h"
#include "../Server/HttpParser.h"

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

    QSqlDatabase db;

    //! name of the table in database
    QString tableName;

    //! name of the current API
    QString typeApi;

    void setDataBase(const QSqlDatabase &dataBase){db = dataBase;}

    virtual int getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitives>> &entities, QList<QString> &primitives) = 0;

    virtual int postFunction(const HttpParser &parser) = 0;

//    virtual int patchFunction() = 0;

//    virtual int deleteFunction() = 0;
};

//! @} database_api
//!
}
#endif // IDBAPI_H
