#ifndef DASEXPORT_H
#define DASEXPORT_H
#include "paramstruct.h"

int initDatabaseConnection(const char* host,int port,const char* user,const char* pwd,const char* dbname);
char *getDataBaseLastError();

/*用户权限模块*/
int getUserCount(int *length);
int getUser(USER *pUser,int index);
int userLogin(const USER *pUser,int *userType);
int userPasswordModify(const USER *pUser,const char* newPwd);
int insertUser(const USER *pUser);
int deleteUser(const USER *pUser);

/*报警*/
int getHisAlarmCount(int *length);
int getHisAlarm(ALARM_LOG *pAlarm,int index);
int insertHisAlarm(const ALARM_LOG *pAlarm);
int deleteHisAlarm(const ALARM_LOG *pAlarm);

/*故障*/
int getHisFaultCount();
int getHisFault(ERR_LOG *pFault,int index);
int insertHisFault(const ERR_LOG *pFault);
int deleteHisFault(const ERR_LOG *pFault);

//操作日志
int getOperateLogCount();
int getOperate(OP_LOG *pOperate,int index);
int insertOperate(const OP_LOG *pOperate);
int deleteOperate(const OP_LOG *pOperate);

//系统参数
int getSystemConfigParam(SYS_CFG *pParam);
int setSystemConfigParam(const SYS_CFG *param);

//Meta
int getUserTypeMetaCount(int *length);
int getUserTypeMetaInfo(META_TYPE *pMeta,int index);

int getAlarmTypeMetaCount(int *length);
int getALarmTypeMetaInfo(META_TYPE *pMeta,int index);

int getFaultTypeMetaCount(int *length);
int getFaultTypeMetaInfo(META_TYPE *pMeta,int index);

int getOperateTypeMetaCount(int *length);
int getOperateTypeMetaInfo(META_TYPE *pMeta,int index);

#endif // DASEXPORT_H
