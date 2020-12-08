#include <QDebug>
#include <QSqlDatabase>
#include "dasexport.h"
#include "errorcode.h"
#include "dbmanager/dbmanager.h"
#include "dasdatabasemanager.h"
#include "tablenamedefine.h"


static DasDatabaseManager manager;

int initDatabaseConnection(const char *host, int port, const char *user, const char *pwd, const char *dbname)
{
    return manager.initDataBase(host,port,user,pwd,dbname);
}

int getUserCount(int *length)
{
    if(!length){
        return NULLPTR_ERROR;
    }

    return manager.getTableRowCount(TABLE_SYSTEM_USER,*length);
}

int getUser(USER *pUser, int index)
{
    if(!pUser)
        return NULLPTR_ERROR;

    QList<UserInfo> result;

    manager.getUserList(result);

    if(result.size() == 0){
        QString error = manager.getDataBaseLastError().text();

        if(error.isEmpty())
            return DATABASE_TABLE_EMPTY;
        else
            return DATABASE_QUERY_ERROR;
    }

    if(index > result.count())
        return INDEX_OUTOF_RANGE;

    UserInfo info = result.at(index);

    strcpy(pUser->username,info.getUser_name().toStdString().c_str());
    strcpy(pUser->password,info.getUser_password().toStdString().c_str());
    pUser->userType = (uint8_t)info.getUser_type();

    return DAS_SUCESS;
}

int userLogin(const USER *pUser, int *userType)
{
    if(!pUser){
        return NULLPTR_ERROR;
    }

    QList<UserInfo> result;
    manager.getUserList(result);

    for(auto var : result)
    {
        QString username = QString(QLatin1String(pUser->username));
        QString password = QString(QLatin1String(pUser->password));

        if(var.getUser_name() == username && var.getUser_password() == password)
        {
            *userType = var.getUser_type();
            return DAS_SUCESS;
        }
    }

    return DAS_USER_LOGIN_ERR;
}

int userPasswordModify(const USER *pUser, const char *newPwd)
{



    return DAS_SUCESS;
}

int insertUser(const USER *pUser)
{
    UserInfo userinfo;
    userinfo.setUser_name(QString(QLatin1String(pUser->username)));
    userinfo.setUser_password(QString(QLatin1String(pUser->password)));
    userinfo.setUser_type(pUser->userType);

    return manager.insertUser(userinfo);
}

int deleteUser(const USER *pUser)
{
    UserInfo userinfo;
    userinfo.setUser_name(QString(QLatin1String(pUser->username)));

    return manager.deleteUser(userinfo);
}

int getHisAlarmCount(int *length)
{
    if(!length){
        return NULLPTR_ERROR;
    }


    return DAS_SUCESS;
}

int getHisAlarm(ALARM_LOG *pAlarm, int index)
{
    return DAS_SUCESS;
}

int insertHisAlarm(const ALARM_LOG *pAlarm)
{
    return DAS_SUCESS;
}

int deleteHisAlarm(const ALARM_LOG *pAlarm)
{
    return DAS_SUCESS;
}

int getHisFaultCount()
{
    return DAS_SUCESS;
}

int getHisFault(ERR_LOG *pFault, int index)
{
    return DAS_SUCESS;
}

int insertHisFault(const ERR_LOG *pFault)
{
    return DAS_SUCESS;
}

int deleteHisFault(const ERR_LOG *pFault)
{
    return DAS_SUCESS;
}

int getOperateLogCount()
{
    return DAS_SUCESS;
}

int getOperate(OP_LOG *pOperate, int index)
{
    return DAS_SUCESS;
}

int insertOperate(const OP_LOG *pOperate)
{
    return DAS_SUCESS;
}

int deleteOperate(const OP_LOG *pOperate)
{
    return DAS_SUCESS;
}

int getSystemConfigParam(SYS_CFG *pParam)
{
    return DAS_SUCESS;
}

int setSystemConfigParam(const SYS_CFG *param)
{
    return DAS_SUCESS;
}

int getUserTypeMetaInfo(META_TYPE *pMeta, int index)
{
    return DAS_SUCESS;
}

int getUserTypeMetaCount(int *length)
{
    return DAS_SUCESS;
}

int getAlarmTypeMetaCount(int *length)
{
    return DAS_SUCESS;
}

int getALarmTypeMetaInfo(META_TYPE *pMeta, int index)
{
    return DAS_SUCESS;
}

int getFaultTypeMetaInfo(META_TYPE *pMeta, int index)
{
    return DAS_SUCESS;
}

int getFaultTypeMetaCount(int *length)
{
    return DAS_SUCESS;
}

int getOperateTypeMetaCount(int *length)
{
    return DAS_SUCESS;
}

int getOperateTypeMetaInfo(META_TYPE *pMeta, int index)
{
    return DAS_SUCESS;
}
