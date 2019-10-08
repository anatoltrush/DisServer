#ifndef IDBAPI_H
#define IDBAPI_H

#include <QString>

namespace dis{

//! @addtogroup database_api
//! @{

/**
 * @brief The IdbAPI is an interface for all inherited classes
 */
class IdbAPI
{
public:
    IdbAPI(const QString &tabName = "\tERROR\t");

    //! name of the table in database
    QString tableName;
};

//! @} database_api
//!
}
#endif // IDBAPI_H
