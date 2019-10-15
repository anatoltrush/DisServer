#include "Constants.h"

QString dis::getReasonPhrase(int code){
    QString result;

    switch (code) {
    case HTTP_OK: // 200
        result = "OK";
        break;
    case HTTP_CREATED: // 201
        result = "Created";
        break;

    case HTTP_BAD_REQUEST: // 400
        result = "Bad Request";
        break;
    case HTTP_UNAUTHORIZED: // 401
        result = "Unauthorized";
        break;
    case HTTP_NOT_FOUND: // 404
        result = "Not Found";
        break;
    case HTTP_METHOD_NOT_ALLOWED: // 405
        result = "Method Not Allowed";
        break;
    case HTTP_CONFLICT: // 409
        result = "Conflict";
        break;
    case HTTP_UNPROCESSABLE_ENTITY: // 422
        result = "Unprocessable Entity";
        break;

    case HTTP_INTERNAL_SERVER_ERROR: // 500
        result = "Internal Server Error";
        break;
    case HTTP_NOT_IMPLEMENTED: // 501
        result = "Not Implemented";
        break;
    case HTTP_WEB_SERVER_IS_DOWN: // 521
        result = "Web Server Is Down";
        break;
    default:
        result = "Internal Server Error";
        break;
    }

    return result;
}
