#ifndef DASDATABASEMANAGER_H
#define DASDATABASEMANAGER_H

#include "dasdatabasemanager_global.h"

class DASDATABASEMANAGERSHARED_EXPORT DasDatabaseManager
{

public:
    DasDatabaseManager();

    int initDataBase(QString host, int port, QString user, QString pwd, QString databaseName);
    QSqlError getDataBaseLastError();

    int getTableRowCount(QString tableName,int &count);

    //das_user_info

    int getUserList(QList<UserInfo> &result);
    int insertUser(UserInfo &user);
    int deleteUser(UserInfo &user);
    int updateUser(UserInfo &user);

    int getAlarmCount(int &count);
    int getAlarmList(QList<AlarmInfo> &result);
    int insertAlarm(AlarmInfo &alarm);
    int deleteAlarm(AlarmInfo &alarm);
    int updateAlarm(AlarmInfo &alarm);


    int getFaultCount(int &count);
    int getFaultList(QList<FaultInfo> &result);

    int getOperateCount(int &count);
    int getOperateList(QList<OperateInfo> &result);


private:

};

#endif // DASDATABASEMANAGER_H
