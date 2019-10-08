#include "HttpHandler.h"

dis::HttpHandler::HttpHandler(){}

void dis::HttpHandler::handle(const HttpParser &parser, const DBController &dbcntr, HttpResponse &response){
    QList<dis::IPrimitives*> entities;
    QList<QString> uuids;

    if(parser.method == "GET"){}
    if(parser.method == "POST"){}
    if(parser.method == "PATCH"){}
    if(parser.method == "DELETE"){}
    // else...
}
