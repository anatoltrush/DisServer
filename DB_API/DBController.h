#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include "../QDisput/Common/unique.h"

#include "UserAPI.h"
#include "DiscussionAPI.h"
#include "PurchaseAPI.h"
#include "CommentAPI.h"
#include "ImageAPI.h"
#include "AnswerAPI.h"

namespace dis{

//! @addtogroup database_api
//! @{

class DBController
{
public:
    DBController();
    ~DBController();

    QSqlDatabase dataBase;

    //! string for test "DRIVER={SQL Server};SERVER=250PC;DATABASE=Disput_db;Trusted_Connection=yes;"
    bool connect(const QString& connectString);
    void disconnect();

    std::vector<std::unique_ptr<IdbAPI>> dbAPIs;

private:
    bool connected = false;
    QString connString;
};

//! @} database_api

}

#endif // DBCONTROLLER_H
