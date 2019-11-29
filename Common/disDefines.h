#ifndef DISDEFINES_H
#define DISDEFINES_H

constexpr int uuidSize = 38; // size of UUID string

#define DB_NAME         "Disput_db"
#define DB_NAME_LOG     "Disput_db_log"

#define IMG_FORMAT_JPG  "JPG"

//{ Names of tables
#define TABLE_ANSWERS       "Answers"
#define TABLE_COMMENTS      "Comments"
#define TABLE_DISPUTES      "Disputes"
#define TABLE_IMAGES        "Images"
#define TABLE_USERS         "Users"
//}

// Entities for API by typeNames
#define API_TYPE_ANSWERS    "answers"
#define API_TYPE_COMMENTS   "comments"
#define API_TYPE_DISPUTES   "disputes"
#define API_TYPE_IMAGES     "images"
#define API_TYPE_USERS      "users"

// Functions names
#define KW_FUNC_REGISTRATION    "registration"
#define KW_FUNC_LOGIN           "login"
#define KW_FUNC_LOGOUT          "logout"

// In headers
#define HDR_KW_AUTHORIZATION    "Authorization"
#define HDR_KW_PSWRD            "Password"
#define HDR_KW_CONTENT_TYPE     "Content-Type"

#include <QMap>
using QStringMap = QMap<QString, QString>;

#endif // DISDEFINES_H
