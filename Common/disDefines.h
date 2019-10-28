#ifndef DISDEFINES_H
#define DISDEFINES_H

//{ Entities for API by typeNames
#define API_TYPE_ANSWERS    "answers"
#define API_TYPE_COMMENTS   "comments"
#define API_TYPE_DISPUTES   "disputes"
#define API_TYPE_IMAGES     "images"
#define API_TYPE_PURCHASES  "purchases"
#define API_TYPE_USERS      "users"
//}

//! @group key_words
//! @{
// functions names
#define KW_FUNC_REGISTRATION    "registration"
#define KW_FUNC_LOGIN           "login"
#define KW_FUNC_LOGOUT          "logout"

// in headers
#define HDR_KW_AUTHORIZATION    "Authorization"
#define HDR_KW_PSWRD            "Password"
#define HDR_KW_CONTENT_TYPE     "Content-Type"
//! @} entities

#include <QMap>
using QStringMap = QMap<QString, QString>;
//    typedef QMap<QString, QString> QStringMap;

#endif // DISDEFINES_H
