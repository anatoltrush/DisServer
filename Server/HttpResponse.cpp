#include "HttpResponse.h"

dis::HttpResponse::HttpResponse(){}

void dis::HttpResponse::createResponse(const dis::HttpHandler &handler){

}

const QByteArray &dis::HttpResponse::toQByteArray(){
    // TODO: impl
    return responseQBA;
}
