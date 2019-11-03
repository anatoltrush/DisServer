#ifndef COMMENTAPI_H
#define COMMENTAPI_H

#include "IdbAPI.h"
#include "../QDisput/Primitives/Comment.h"

namespace dis{

//! @addtogroup database_api
//! @{
//!
class CommentAPI : public IdbAPI
{
public:
    CommentAPI();
    ~CommentAPI() override;

    bool addComment(const dis::Comment &comment);

    bool getCommByUuid(const QString &uuid, dis::Comment &comment);

    int getFunction(const HttpParser &parser, std::vector<std::unique_ptr<IPrimitive>> &entities, QList<QString> &primitives) override;
    int postFunction(const HttpParser &parser) override;
    int patchFunction(const HttpParser &parser) override;
    int deleteFunction(const HttpParser &parser) override;
};

//! @} database_api

}

#endif // COMMENTAPI_H
