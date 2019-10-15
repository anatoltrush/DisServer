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

    /**
     * @brief Transforms QVariantMap in single string
     * @return string filled by properties of object
     */
    virtual QString getMessageBody() = 0;

    static QString nextLn;
    static QByteArray createMessageBody(const QList<QString> &uuids, const QString &separ);
    static QByteArray createMessageBodyHtml(const QList<QString> &uuids);

    //! @brief Fills msgBody from object properties
    virtual QByteArray createMessageBody(const std::vector<std::unique_ptr<IPrimitives>> &entities, const QString &separ) = 0;

    //! @brief Fills msgBody from object properties for HTML
    virtual QByteArray createMessageBodyHtml() = 0;
};
//! @} entities
}

#endif // IPRIMITIVES_H
