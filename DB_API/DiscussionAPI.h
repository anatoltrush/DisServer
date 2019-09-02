#ifndef DISCUSSIONAPI_H
#define DISCUSSIONAPI_H

#include <QtSql>

#include "../QDisput/Primitives/Discussion.h"

namespace dis{
class DiscussionAPI
{
public:
    DiscussionAPI();
    ~DiscussionAPI();

    bool addDiscussion();
    bool deleteDiscussion();
    bool redactDiscussion();
};
}

#endif // DISCUSSIONAPI_H

// TODO: add GET
