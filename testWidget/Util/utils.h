#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QStringList>
#include <QVector>

#ifdef ACTIVE_HIK
#if _MSC_VER >= 1600
    #pragma execution_character_set("utf-8")
#endif
#endif

// 多线程判断 by huyingjian
#define ASSERT_IN_SUB_THREAD Q_ASSERT(QThread::currentThread() != QApplication::instance()->thread());
#define ASSERT_IN_MAIN_THREAD Q_ASSERT(QThread::currentThread() == QApplication::instance()->thread());

/*************************
 *说明：公共的工具类，包含一些公用的静态函数及静态变量
 *作者：jt
 *时间：2012-8-1
 *************************/

extern QString DBDRIVER_NAME;           //数据库驱动类型
extern QStringList m_ColumnUseDateList; //目前数据库中字段类型为date的字段名称

void initGlobalParamsInUtils();

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = 0);
    enum Log_level {
        Information = 0,
        Warning = 1,
        Error = 2
    };

    //数据库连接信息
    struct DBConnInfor
    {
        QString host;
        QString dbname;
        QString user;
        QString password;
        int     port;
    };

    static void createDBConnectoin(DBConnInfor dbInfo, QString connectionName="");
    static void closeDBConnection(const QString &connectionName = "");
    static QString getInsertSQL(const QString tableName, const QStringList fieldList, const QStringList valueList);
    static QString getBatchInsertSQL(const QString tableName, const QStringList fieldList, const QList<QStringList> valuesList, bool insertDelayed = false);
    static QString getBatchIgnoreInsertSQL(const QString tableName, const QStringList fieldList, const QList<QStringList> valuesList);
    static QString getSelectSQL(const QString tableName, const QStringList fieldList, const QString condition);
    static QString getUpdateSQL(const QString tableName, const QStringList fieldList, const QStringList valueList, const QString condition);
    static QString getDeleteSQL(const QString tableName, const QString condition);
    static QString getCreateTableSql(const QString copyTableName, const QString createTableName, const QString processName="");


signals:

public slots:

};
#endif // UTILS_H
