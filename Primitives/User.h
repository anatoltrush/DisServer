#ifndef USER_H
#define USER_H

#include "Discussion.h"
#include "IPrimitive.h"

// TODO: #define PROP_USER_UUID"UUID + IN API" // example
#define PROP_USR_UUID   "UUID"
#define PROP_USR_PSWRD  "Password"
#define PROP_USR_EMAIL  "Email"
#define PROP_USR_NICK   "Nick_name"

namespace dis{
//! @addtogroup entities
//! @{
enum Sex{
    NA = -1,
    Male,
    Female,
    Transgender
    // other if need
};

class User : public IPrimitive
{
public:
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
    Sex sex = Sex::NA;
    Sex preference = Sex::NA;

    QString nickName;
    QString login;
    QString password;
    int role = -1;
    int status = -1; // confirmed, banned or else
    int score = 0;
    int level = 0;
    QDateTime time_registration;
    QDateTime time_last_active;
    int money = 0;

    std::vector<dis::Discussion> createdDisps;

    QString getAuthor() const override {return uuid;}

    void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) override;
    void fillByParse(const QVariantMap &params) override;

private:
    QByteArray createMessageBody(const QString &separ) override;
    QByteArray createMessageBodyHtml() override;
};
//! @} entities
}

#endif // USER_H
