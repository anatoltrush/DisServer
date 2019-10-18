#ifndef USER_H
#define USER_H

#include <QDateTime>
#include <QUuid>
#include <QtSql>

#include "Discussion.h"
#include "Purchase.h"
#include "IPrimitives.h"

namespace dis{
//! @addtogroup entities
//! @{
class User : public IPrimitives
{
public:
    //! short constructor
    User();
    ~User() override;

    // COMMON PROPERTY
    QString uuid = QUuid::createUuid().toString();
    QString name;
    QString surname;

    QString country;
    QString city;

    QString email;
    QList<QString> IPs;

    QDateTime time_birth;
    int sex = 0;    

    // SPECIAL PROPERTY
    QString nickName;
    QString login;
    QString password;
    int role = -1;
    int status = -1; // confirmed, banned or else
    int score = 0;
    int level = 0;
    QDateTime time_registration;
    QDateTime time_last_active;

    std::vector<dis::Discussion> discsGood;
    std::vector<dis::Discussion> discsBad;
    std::vector<dis::Purchase> purchases;

    bool isAuthorized = false;

    int money = 0;

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) override;
    void fillByList(const QList<QString> &words, bool isFromParse = false);

private:
    QByteArray createMessageBody(const QString &separ) override;
    QByteArray createMessageBodyHtml() override;
};
//! @} entities
}

#endif // USER_H
