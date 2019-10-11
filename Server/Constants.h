#ifndef CONSTANTS_H
#define CONSTANTS_H

//! @group server_status
//! @{
#define OK                  200
#define ERR_CREATED         201 // (PUT || POST) CREATED GOOD
#define ERR_BAD_REQUEST     400 // (PUT || POST) BAD FORMAT OR LOST
#define ERR_UNAUTHORIZED    401
#define ERR_NOT_FOUND       404 // BAD URL
#define ERR_METHOD_NOT_ALLOWED  405 // BAD API
#define ERR_CONFLICT        409 // REPEATED RECORD
#define ERR_INTERNAL_SERVER_ERROR   500 // UNDEFINED
//! @} server_status

// //! @group entities
// //! @{
//#define Answer      answers
//#define Comment     comments
//#define Answer  answers
//#define Answer  answers
//#define Answer  answers
//#define Answer  answers
// //! @} entities

typedef enum _HTTP_VERB {
  HttpVerbUnparsed = 0,
  HttpVerbUnknown,HttpVerbInvalid,HttpVerbOPTIONS,HttpVerbGET,HttpVerbHEAD,HttpVerbPOST,HttpVerbPUT,HttpVerbDELETE,
  HttpVerbTRACE,HttpVerbCONNECT,HttpVerbTRACK,HttpVerbMOVE,HttpVerbCOPY,HttpVerbPROPFIND,HttpVerbPROPPATCH,HttpVerbMKCOL,HttpVerbLOCK,
  HttpVerbUNLOCK,HttpVerbSEARCH,HttpVerbMaximum
} HTTP_VERB;

#endif // CONSTANTS_H
