#include "HttpHandler.h"

dis::HttpHandler::HttpHandler(){}

void dis::HttpHandler::handle(const dis::HttpParser &parser, const DBController &dbcntr){
    if(parser.method == "GET"){}
    if(parser.method == "POST"){}
    if(parser.method == "PATCH"){}
    if(parser.method == "DELETE"){}
    // else...
}
