#include "Constants.h"

QString dis::getReasonPhrase(int code){
    QString result;

    switch (code) {
    case HTTP_OK:
        result = "OK";
        break;
    case HTTP_NOT_IMPLEMENTED:
        result = "Not Implemented";
        break;
    default:
        result = "Internal Server Error";
        break;
    }

    return result;
}
