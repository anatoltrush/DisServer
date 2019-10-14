#include "HttpResponse.h"

QString dis::HttpResponse::serverName = "DisServer";
QString dis::HttpResponse::httpVersion = "HTTP/1.1";
QString dis::HttpResponse::nextLn = "\r\n";

dis::HttpResponse::HttpResponse(){}

void dis::HttpResponse::createResponse(int code){
    responseQBA.clear();
    // -----
    if(code >= 100 && code < 400){
        createStartLine(code);
        createHeaders();
        createMessage();
    }
    else{
        createStartLine(code);
    }
}

void dis::HttpResponse::admitResult(const QList<QString> &uuids){
    this->uuids = uuids;
}

void dis::HttpResponse::admitResult(const std::vector<std::unique_ptr<IPrimitives>> &&ents){
//    this->entities = entities;
//    entities = (std::move(ents));
    // TODO: important
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
    QList<QString> headers;
    headers.push_back("Date: " + QDateTime::currentDateTimeUtc().toString());
    headers.push_back("Server: " + serverName);
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
    // to QBA
    for(const auto &hdr : headers){
        QString newHdr = hdr + nextLn;
        responseQBA.append(newHdr);
    }
    responseQBA.append(nextLn);
}

void dis::HttpResponse::createMessage(){
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
#else
#endif
// HTML ???
    }
    // use uuids
    // use entities

//    responseQSTR += "<b>DISPUTE CONNECTED!</b>";
//    responseQSTR += "<hr size=8; color=FF0000>";
//    responseQSTR += "<br>";
}
