#include "HttpResponse.h"

QString dis::HttpResponse::serverName = "DisServer";

QString dis::HttpResponse::httpVersion = "HTTP/1.1";

dis::HttpResponse::HttpResponse(){}

void dis::HttpResponse::createResponse(const dis::HttpParser &parser, int code){
    starting_line.clear();
    headers.clear();
    message_body.clear();
    // -----
    createStartLine(code);
    if(code >= 100 && code < 400){
        createHeaders(parser);
        createMessage();
    }
}

void dis::HttpResponse::admitResult(const QList<QString> &uuid){
    this->uuid = uuid;
}

void dis::HttpResponse::admitResult(const std::vector<std::unique_ptr<IPrimitives>> &&ents){
//    this->entities = entities;
//    entities = (std::move(ents));
    //TODO: important
}

const QByteArray &dis::HttpResponse::toQByteArray(){
    responseQBA.clear();
    responseQBA.append(responseQSTR);
    // TODO: impl
    return responseQBA;
}

void dis::HttpResponse::createStartLine(int status){
    starting_line.append(httpVersion);
    starting_line.append(" ");
    starting_line.append(QString::number(status));
    starting_line.append(" ");
    starting_line.append(getReasonPhrase(status));
}

void dis::HttpResponse::createHeaders(const dis::HttpParser &parser){
    // use parser
}

void dis::HttpResponse::createMessage(){
    // use uuids
    // use entities

    responseQSTR += "<b>DISPUTE CONNECTED!</b>";
    responseQSTR += "<hr size=8; color=FF0000>";
    responseQSTR += "<br>";
}

void dis::HttpResponse::collectRespQstr(){

}
