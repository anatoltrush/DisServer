#ifndef IPRIMITIVES_H
#define IPRIMITIVES_H

#include <QtSql>

namespace dis{
//! @addtogroup entities
//! @{

/**
 * @brief The IPrimitives is an interface for all inherited classes
 */
class IPrimitives
{
public:
    IPrimitives();
    virtual ~IPrimitives();

    /**
     * @brief fillBySQL Fills properties of object by SQL query
     * @param query SQL query
     * @param rec SQL record
     */
    virtual void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) = 0;
    virtual void fillByParse(const QVariantMap &params) = 0;

    static QString nextLn;
    //! use for primitive types (int, QString)
    static QByteArray createMessageBody(const QList<QString> &uuids, const QString &separ);
    //! use for primitive types (int, QString)
    static QByteArray createMessageBodyHtml(const QList<QString> &uuids);

    //! @brief Fills msgBody from object properties
    virtual QByteArray createMessageBody(const QString &separ) = 0;
    //! @brief Fills msgBody from object properties for HTML
    virtual QByteArray createMessageBodyHtml() = 0;
};
//! @} entities
}

#endif // IPRIMITIVES_H
