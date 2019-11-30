#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include "../Common/Constants.h"
#include "../Common/unique.h"
#include "../Primitives/Discussion.h"
#include "../Primitives/Answer.h"
#include "../Primitives/Comment.h"
#include "../Primitives/Image.h"
#include "../Primitives/User.h"

namespace dis{
//! @addtogroup server_part
//! @{
class HttpParser
{
public:
    HttpParser() = default;
    ~HttpParser() = default;

    int status = HTTP_BAD_REQUEST;
    const QString& lastError() const {return statMsg;}

//{ input raw data
    QString method, address, httpVers;
    QString entity, function, bound/*if post*/;

    QString starting_line;

    using QStringMap = QMap<QString, QString>;
    QStringMap headers;
//}

//{ output data
    QString authorToken; // for authorization
    QString pswrd; // for logIn
    QVariantMap params; // contains pairs (for GET or DELETE requests)
    QList<QString> blocks; // everywhere
    std::unique_ptr<IPrimitive> object; // contains whole object (for POST or PATCH or PUT requests)
//}

    void parse(const QByteArray &data);

private:
    // inner
    QString statMsg = "NA";
    void setStatus(int stat, const QString& msg);
    // ---
    void basicParse(const QByteArray &data);

    void getParse();
    void postParse();
    void patchParse();
    void deleteParse();
    void optionParse();
    void putParse();
    void headParse();

    void validateParams();

    QPair<QString, QVariant> parseBlock(const QString &block);

    static void getPrimitive(std::unique_ptr<IPrimitive> &object, const QString &entity);
};
//! @} server_part
}

#endif // HTTPPARSER_H
