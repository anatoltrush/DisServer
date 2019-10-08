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

private:
    QVariantMap msgBody;

    /**
     * @brief Fills msgBody from object properties
     */
    virtual void createMessageBody() = 0;
};
//! @} entities
}

#endif // IPRIMITIVES_H
