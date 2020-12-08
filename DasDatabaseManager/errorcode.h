#ifndef ERRORCODE_H
#define ERRORCODE_H

//成功
#define DAS_SUCESS 0

#define NULLPTR_ERROR                               50
#define INDEX_OUTOF_RANGE                           51

/********************数据库相关错误码********************************/
#define DATABASE_ERROR_CODE                         1000
#define DATABASE_OPEN_ERROR                         DATABASE_ERROR_CODE+1
#define DATABASE_QUERY_ERROR                        DATABASE_ERROR_CODE+2
#define DATABASE_TABLE_EMPTY                        DATABASE_ERROR_CODE+3
#define DATABASE_INSERT_ERROR                       DATABASE_ERROR_CODE+4
#define DATABASE_DELETE_ERROR                       DATABASE_ERROR_CODE+5


/********************用户登陆相关错误码******************************/
#define DAS_USER_MODULE                             2000

#define DAS_USER_LOGIN_ERR                          DAS_USER_MODULE+1
#define DAS_USER_LOGIN_PWD_ERR                      DAS_USER_MODULE+2
#define DAS_USER_LOGIN_USERNAME_ERR                 DAS_USER_MODULE+3

const char* getErrorDetail(int errorCode);

#endif // ERRORCODE_H
