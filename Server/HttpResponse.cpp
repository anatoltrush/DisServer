#include "HttpResponse.h"

dis::HttpResponse::HttpResponse(){}

void dis::HttpResponse::createResponse(const dis::HttpParser &parser){
    responseQSTR += "HTTP/1.1 200 OK\r\n\r\n";
    responseQSTR += "<b>DISPUTE CONNECTED!</b>";
    responseQSTR += "<hr size=8; color=FF0000>";
    responseQSTR += "<br>";
}

void dis::HttpResponse::admitResult(const QList<QString> &uuid){

}

void dis::HttpResponse::admitResult(const std::vector<std::unique_ptr<IPrimitives>> &entities){

}

const QByteArray &dis::HttpResponse::toQByteArray(){
    responseQBA.clear();
    responseQBA.append(responseQSTR);
    // TODO: impl
    return responseQBA;
}

void dis::HttpResponse::createStartLine(int status, const QString &reasonPhrase, const QString ver){
}

void dis::HttpResponse::createHeaders(){
}

void dis::HttpResponse::createMessage(){
}

void dis::HttpResponse::collectRespQstr(){

}
