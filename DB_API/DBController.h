#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include "UserAPI.h"
#include "DiscussionAPI.h"
#include "CommentAPI.h"
#include "ImageAPI.h"

namespace dis{

//! @addtogroup database_api
//! @{

class DBController
{
public:
    DBController();
    ~DBController();

    QSqlDatabase dataBase;

    //! string for test "DRIVER={SQL Server};SERVER=250PC;DATABASE=" + QString(DB_NAME) + ";Trusted_Connection=yes;"
    bool connect(const QString& connectString);
    void disconnect();

    std::vector<std::unique_ptr<IdbAPI>> dbAPIs;    

private:
    bool connected = false;
};

//! @} database_api

}

#endif // DBCONTROLLER_H
