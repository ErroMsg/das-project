#include "dasdatabasemanager.h"
#include <dbmanager/dbmanager.h>
#include "errorcode.h"
#include "tablenamedefine.h"
#include "Util/utils.h"
#include "tableinfo/userinfo.h"


DasDatabaseManager::DasDatabaseManager()
{
}

int DasDatabaseManager::initDataBase(QString host,int port, QString user,QString pwd,QString databaseName)
{
    DBManager::DBData dbdata;
    dbdata.setHostName(host);
    dbdata.setPort(port);
    dbdata.setUserName(user);
    dbdata.setPassword(pwd);
    dbdata.setDatabaseConnectionType(DBManager::MYSQL);
    dbdata.setDatabaseName(databaseName);
    dbdata.setConnectionName("DasDatabaseManager");
    DBManager::getInstance(dbdata);

    bool openStatus =   DBManager::getInstance()->getDbStatus();
    if(!openStatus){
        qDebug()<< DBManager::getInstance()->getLastError();
        return DATABASE_OPEN_ERROR;
    }

    return DAS_SUCESS;
}

QSqlError DasDatabaseManager::getDataBaseLastError()
{
    return DBManager::getInstance()->getLastError();
}

int DasDatabaseManager::getTableRowCount(QString tableName, int &count)
{
    int rowCount = DBManager::getInstance()->rowsCount(tableName);

    if(rowCount < 0){
        return DATABASE_QUERY_ERROR;
    }

    count = rowCount;
    return DAS_SUCESS;
}


int DasDatabaseManager::getUserList(QList<UserInfo> &result)
{
    UserInfo cond;
    QStringList colums = cond.getColumns();

    QList< QVariantList > dataList = DBManager::getInstance()->retrieveAll(TABLE_SYSTEM_USER,colums);

    for(auto var : dataList){
        UserInfo item;
        item.setData(var);
        result.append(item);
    }

    return DAS_SUCESS;
}

int DasDatabaseManager::insertUser(UserInfo &user)
{
    //    bool insertRow(const QString &tableName, const QStringList &columnName, const QVariantList &data);
    //remove id colum
    QStringList columns = user.getColumns();
    columns.removeFirst();

    QVariantList datas = user.getVariants();

    bool res = DBManager::getInstance()->insertRow(TABLE_SYSTEM_USER,columns,datas);

    if(!res)
        return DATABASE_INSERT_ERROR;

    return DAS_SUCESS;
}

int DasDatabaseManager::deleteUser(UserInfo &user)
{
    QStringList columns;
    columns<<"user_name";

    QVariantList values;
    values<<user.getUser_name();

    bool ret = DBManager::getInstance()->removeRow(TABLE_SYSTEM_USER,columns,values);

    if(!ret)
        return DATABASE_DELETE_ERROR;

    return DAS_SUCESS;
}

int DasDatabaseManager::updateUser(UserInfo &user)
{
    /*const QStringList &columnNameCond,
    const QVariantList &condition, const QStringList &columnName,
    const QVariantList &data, const QString &operation*/
    QStringList columnNameCond;
    columnNameCond<<""

    bool ret = DBManager::getInstance()->updateRow(TABLE_SYSTEM_USER,);
}

int DasDatabaseManager::getAlarmCount(int &count)
{
    int rowCount = DBManager::getInstance()->rowsCount(TABLE_ALARM_INFO);
    if(rowCount < 0)
    {
        return DATABASE_QUERY_ERROR;
    }

    count = rowCount;
    return DAS_SUCESS;
}

int DasDatabaseManager::getAlarmList(QList<AlarmInfo> &result)
{
    AlarmInfo cond;
    QStringList colums = cond.getColumns();

    QList<QVariantList> dataList = DBManager::getInstance()->retrieveAll(TABLE_ALARM_INFO,colums);

    for(auto var : dataList){
        AlarmInfo item;
        item.setData(var);
        result.append(item);
    }

    return DAS_SUCESS;
}

int DasDatabaseManager::insertAlarm(AlarmInfo &alarm)
{

}

int DasDatabaseManager::deleteAlarm(AlarmInfo &alarm)
{

}

int DasDatabaseManager::updateAlarm(AlarmInfo &alarm)
{

}

int DasDatabaseManager::getFaultCount(int &count)
{

}

int DasDatabaseManager::getFaultList(QList<FaultInfo> &result)
{

}

int DasDatabaseManager::getOperateCount(int &count)
{

}

int DasDatabaseManager::getOperateList(QList<OperateInfo> &result)
{

}


