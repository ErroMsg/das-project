#include "utils.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QSettings>

QString DBDRIVER_NAME = "QMYSQL";
QStringList m_ColumnUseDateList;

void initGlobalParamsInUtils()
{

}

Utils::Utils(QObject *parent) :
    QObject(parent)
{

}


void Utils::createDBConnectoin(DBConnInfor dbInfo, QString connectionName)
{
    QSqlDatabase db;
    if (connectionName.isEmpty())
    {
        db = QSqlDatabase::addDatabase(DBDRIVER_NAME);
    }
    else
    {
        db= QSqlDatabase::addDatabase(DBDRIVER_NAME, connectionName);
    }
    db.setHostName(dbInfo.host);
    db.setPort(dbInfo.port);
    db.setDatabaseName(dbInfo.dbname);
    db.setUserName(dbInfo.user);
    db.setPassword(dbInfo.password);
}

void Utils::closeDBConnection(const QString &connectionName)
{
    QSqlDatabase db;
    if (connectionName.isEmpty())       //default connection
    {
        db = QSqlDatabase::database();
    }
    else
    {
        db = QSqlDatabase::database(connectionName);
    }

    if (db.isOpen())
        db.close();
}

QString Utils::getInsertSQL(const QString tableName, const QStringList fieldList, const QStringList valueList)
{
    if (fieldList.size() != valueList.size())
    {
        qDebug() << "Utils::getInsertSQL, parameter invaled!";
        return "";
    }

    QString fieldStr = QString("(%1").arg((QString)fieldList.at(0));
    QString valueStr = QString("('%1'").arg((QString)valueList.at(0));

    if(DBDRIVER_NAME == "QMYSQL")
    {
        for (int i=1; i<fieldList.size(); i++)
        {
            fieldStr += QString(",%1").arg((QString)fieldList.at(i));
            valueStr += QString(",'%1'").arg((QString)valueList.at(i));
        }
    }
    else if(DBDRIVER_NAME == "QOCI")
    {
        for (int i=1; i<fieldList.size(); i++)
        {
            fieldStr += QString(",%1").arg((QString)fieldList.at(i));
            if(m_ColumnUseDateList.contains((QString)fieldList.at(i))) //字段类型是date
            {
                valueStr += QString(",to_date('%1','yyyy-MM-dd hh24:mi:ss')").arg((QString)valueList.at(i));
            }
            else
            {
                valueStr += QString(",'%1'").arg((QString)valueList.at(i));
            }
        }
    }

    fieldStr += ")";
    valueStr += ")";

    //qDebug() << "##########1 insert sql：" + QString("INSERT INTO %1 %2 VALUES %3").arg(tableName).arg(fieldStr).arg(valueStr);
    return QString("INSERT INTO %1 %2 VALUES %3").arg(tableName).arg(fieldStr).arg(valueStr);
}

/**
 * @brief 生成批量insert语句
 * @param tableName, 要插入的表名
 * @param fieldList，插入的字段名
 * @param valueList_vec，要插入的记录值
 * @param insertDelay，是否使用 insert delay
 * @return
 */
QString Utils::getBatchInsertSQL(const QString tableName, const QStringList fieldList, const QList<QStringList> valuesList, bool insertDelayed)
{
    int recNum = valuesList.count();
    if(recNum == 0)
    {
      qDebug() << "插入的记录数为0";
      return "";
    }

    if(DBDRIVER_NAME == "QMYSQL")
    {
      QString fieldStr = tr("%1").arg(fieldList.join(","));
      QString valueStr;
      for(int i = 0; i < recNum; i++)
      {
        QStringList valueList = valuesList.at(i);
        if(fieldList.size() != valueList.size())
        {
          qDebug() << "插入数据个数与字段数量不符";
          continue;
        }
        if(i != 0)
        {
          valueStr += ',';
        }
        valueStr += QString("('%1'").arg(valueList.at(0));
        for (int j=1; j<valueList.size(); j++)
        {
          valueStr += tr(",'%1'").arg(valueList.at(j));
        }
        valueStr += ")";
      }

      if(valueStr.isEmpty())
      {
        return "";
      }
      return QString("INSERT INTO %1(%2) VALUES %3").arg(tableName).arg(fieldStr).arg(valueStr);
    }
    else if(DBDRIVER_NAME == "QOCI")
    {
      QString fieldStr = tr("%1").arg(fieldList.join(","));
      QString valueStr;
      for(int i = 0; i < recNum; i++)
      {
        QStringList valueList = valuesList.at(i);
        if(fieldList.size() != valueList.size())
        {
          qDebug() << "插入数据个数与字段数量不符";
          continue;
        }
        valueStr.append(tr("into %1(%2) values").arg(tableName).arg(fieldStr));
        valueStr.append(tr("('%1'").arg(valueList.at(0)));
        for (int j=1; j<valueList.size(); j++)
        {
          if(m_ColumnUseDateList.contains(fieldList.at(j))) //字段类型是date
          {
              valueStr += QString(",to_date('%1','yyyy-MM-dd hh24:mi:ss')").arg(valueList.at(j));
          }
          else
          {
              valueStr += QString(",'%1'").arg(valueList.at(j));
          }
        }
        valueStr += ")";
      }

      if(valueStr.isEmpty())
      {
        return "";
      }
      return QString("INSERT all %1 select 1 from dual").arg(valueStr);
    }
    return "";
}

QString Utils::getBatchIgnoreInsertSQL(const QString tableName, const QStringList fieldList, const QList<QStringList> valuesList)
{
    int recNum = valuesList.count();
    if(recNum == 0)
    {
      qDebug() << "插入的记录数为0";
      return "";
    }

    QString fieldStr = QString("(%1").arg((QString)fieldList.at(0));
    for (int i=1; i<fieldList.size(); i++)
    {
        fieldStr += QString(",%1").arg((QString)fieldList.at(i));
    }
    fieldStr += ")";

    QString valueStr;
    for(int i = 0; i < recNum; i++)
    {
      QStringList valueList = valuesList.at(i);
      if(fieldList.size() != valueList.size())
      {
        qDebug() << "插入数据个数与字段数量不符";
        continue;
      }
      if(i != 0)
      {
        valueStr += ',';
      }
      valueStr += QString("('%1'").arg((QString)valueList.at(0));

      if(DBDRIVER_NAME == "QMYSQL")
      {
          for (int j=1; j<valueList.size(); j++)
          {
            valueStr += QString(",'%1'").arg((QString)valueList.at(j));
          }
      }
      else if(DBDRIVER_NAME == "QOCI")
      {
          for (int j=1; j<valueList.size(); j++)
          {
            if(m_ColumnUseDateList.contains((QString)fieldList.at(j))) //字段类型是date
            {
                valueStr += QString(",to_date('%1','yyyy-MM-dd hh24:mi:ss')").arg((QString)valueList.at(j));
            }
            else
            {
                valueStr += QString(",'%1'").arg((QString)valueList.at(j));
            }
          }
      }
      valueStr += ")";
    }

    if(valueStr.isEmpty())
    {
      return "";
    }

     return QString("INSERT IGNORE INTO %1 %2 VALUES %3").arg(tableName).arg(fieldStr).arg(valueStr);
}

QString Utils::getSelectSQL(const QString tableName, const QStringList fieldList, const QString condition)
{
    QString sql = "SELECT ";
    for (int i=0; i<fieldList.size(); i++)
    {
        sql += (QString)fieldList.at(i);
        if (i+1 < fieldList.size())
            sql += ",";
    }
    sql += " FROM " + tableName;

    if (!condition.isEmpty())
    {
        sql += " WHERE " + condition;
    }

    return sql;
}

QString Utils::getUpdateSQL(const QString tableName, const QStringList fieldList, const QStringList valueList, const QString condition)
{
    if (fieldList.size() != valueList.size())
    {
        qDebug() << "Utils::getUpdateSQL, parameter invaled!";
        return "";
    }

    QString sql = QString("UPDATE %1 SET ").arg(tableName);

    if(DBDRIVER_NAME == "QMYSQL")
    {
        for (int i=0; i<fieldList.size(); i++)
        {
            sql += QString("%1='%2'").arg((QString)fieldList.at(i)).arg((QString)valueList.at(i));
            if (i+1 < fieldList.size())
                sql += ",";
        }
    }
    else if(DBDRIVER_NAME == "QOCI")
    {
        for (int i=0; i<fieldList.size(); i++)
        {
            if(m_ColumnUseDateList.contains((QString)fieldList.at(i))) //字段类型是date
            {
                sql += QString("%1=to_date('%2','yyyy-MM-dd hh24:mi:ss')").arg((QString)fieldList.at(i)).arg((QString)valueList.at(i));
            }
            else
            {
                sql += QString("%1='%2'").arg((QString)fieldList.at(i)).arg((QString)valueList.at(i));
            }

            if (i+1 < fieldList.size())
                sql += ",";
        }
    }

    sql += QString(" WHERE %1").arg(condition);

    return sql;
}

QString Utils::getDeleteSQL(const QString tableName, const QString condition)
{
    QString sql = QString("DELETE FROM %1 WHERE %2").arg(tableName).arg(condition);
    return sql;
}

/**
 * @brief Utils::getCreateTableSql
 * @param copyTableName：需要拷贝的表的名称
 * @param createTableName：新建表的名称
 * @param processName：存储过程名
 * @return
 */
QString Utils::getCreateTableSql(const QString copyTableName, const QString createTableName, const QString processName)
{
  QString sql="";
  if (DBDRIVER_NAME == "QMYSQL")
  {
    sql = tr("CREATE TABLE IF NOT EXISTS %1 LIKE %2").arg(createTableName).arg(copyTableName);
  }
  else if (DBDRIVER_NAME == "QOCI" && !processName.isEmpty())
  {
    sql = tr("DECLARE tableName varchar(40);BEGIN tableName:='%1';%2(tableName); END;").arg(createTableName).arg(processName);
  }
  return sql;
}
