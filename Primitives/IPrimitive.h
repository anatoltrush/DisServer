#ifndef IPRIMITIVE_H
#define IPRIMITIVE_H

#include <QtSql>

#include "../Common/disDefines.h"

namespace dis{
//! @addtogroup entities
//! @{

/**
 * @brief The IPrimitive is an interface for all inherited classes
 */
class IPrimitive
{
public:
    IPrimitive() = default;
    virtual ~IPrimitive() = default;

    virtual QString getUUID() const = 0;
    virtual QString getAuthor() const = 0;

    //! @brief fillBySQL Fills properties of object by SQL query
    virtual void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) = 0;
    //! @brief fillBySQL Fills properties of object by input params
    virtual void fillByParse(const QVariantMap &params) = 0;

    static QString nextLn;
    //! use for primitive types (int, QString)
    static QByteArray createMessageBody(const QList<QString> &uuids, const QString &separ);
    //! use for primitive types (int, QString)
    static QByteArray createMessageBodyHtml(const QList<QString> &uuids);

    static QByteArray toQBA(const QString &bound, const QString &propName, const QString &data);
    static QByteArray toQBA(const QString &bound, const QString &propName, const QByteArray &data);

    //! @brief Fills msgBody from object properties
    virtual QByteArray createMessageBody(const QString &separ) = 0;
    //! @brief Fills msgBody from object properties for HTML
    virtual QByteArray createMessageBodyHtml() = 0;
};
//! @} entities
}

#endif // IPRIMITIVE_H
