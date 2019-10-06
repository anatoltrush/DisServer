#ifndef IPRIMITIVES_H
#define IPRIMITIVES_H

#include <QtSql>

namespace dis{
class IPrimitives
{
public:
    IPrimitives();
    virtual ~IPrimitives();

    virtual void fillBySQL(const QSqlQuery& query, const QSqlRecord& rec) = 0;
};
}

#endif // IPRIMITIVES_H
