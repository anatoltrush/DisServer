#include "HttpResponse.h"

QString dis::HttpResponse::serverName = "DisServer/1.0";
QString dis::HttpResponse::httpVersion = "HTTP/1.1";
QString dis::HttpResponse::nextLn = "\r\n";

dis::HttpResponse::HttpResponse(){}

void dis::HttpResponse::createResponse(const HttpParser &parser, int code){
#ifdef IS_HTML
    if(parser.entity.isEmpty() && parser.function.isEmpty()){
        Deploy_HTML html(true);
        responseQBA = html.startQBA;
        return;
    }
#endif
    responseQBA.clear();
    // -----
    if(code >= 100 && code < 400){
        createStartLine(code);
        createHeaders();
        createMessage(parser);
    }
    else{
        createStartLine(code);
        createHeaders();
#ifdef IS_HTML
        responseQBA.append(Deploy_HTML::errorHtml(code, serverName));
#endif
    }
}

void dis::HttpResponse::admitResult(const QList<QString> &uuids){
    this->uuids = uuids;
}

void dis::HttpResponse::admitResult(std::vector<std::unique_ptr<IPrimitives> > &ents){
    entities.clear();
    for(auto &ent : ents)
        entities.push_back(std::move(ent));
}

void dis::HttpResponse::createStartLine(int status){
    QString starting_line;
    starting_line.append(httpVersion);
    starting_line.append(" ");
    starting_line.append(QString::number(status));
    starting_line.append(" ");
    starting_line.append(getReasonPhrase(status));
    starting_line.append(nextLn);
    // to QBA
    responseQBA.append(starting_line);
}

void dis::HttpResponse::createHeaders(){
    // if(method == )... several cases

    QList<QString> headers;
    headers.push_back("Server: " + serverName);
    headers.push_back("Date: " + QDateTime::currentDateTimeUtc().toString());

#ifdef IS_HTML
    if(uuids.size() > 0) headers.push_back("Content-Type: text/html; boundary=\"" + bound + "\"");
#else
    if(uuids.size() > 0) headers.push_back("Content-Type: text/plain; boundary=\"" + bound + "\"");
#endif

#ifdef IS_HTML
    if(entities.size() > 0) headers.push_back("Content-Type: multipart/form-data; boundary=\"" + bound + "\"");
#else
    if(entities.size() > 0) headers.push_back("Content-Type: multipart/mixed; boundary=\"" + bound + "\"");
#endif

#ifdef IS_HTML
    if(uuids.size() == 0 && entities.size() == 0)
        headers.push_back("Content-Type: text/html; boundary=\"" + bound + "\"");
#endif


    // to QBA
    for(const auto &hdr : headers){
        QString newHdr = hdr + nextLn;
        responseQBA.append(newHdr);
    }
    responseQBA.append(nextLn);
}

void dis::HttpResponse::createMessage(const HttpParser &parser){
    // if(method == )... several cases
    if(uuids.size() > 0){
#ifdef IS_HTML
        QByteArray messQBA = IPrimitives::createMessageBodyHtml(uuids);
        responseQBA.append(messQBA);
#else
        QByteArray messQBA = IPrimitives::createMessageBody(uuids, bound);
        responseQBA.append(messQBA);
#endif
    }
    if(entities.size() > 0){
#ifdef IS_HTML
        if(parser.method == QString(VERB_GET)){
            entities.front()->createMessageBodyHtml();
        }
#else
        if(parser.method == QString(VERB_GET)){
            entities.front()->createMessageBody(parser.bound);
        }
#endif
    }
}

