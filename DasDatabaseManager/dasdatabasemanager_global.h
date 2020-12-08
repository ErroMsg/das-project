#ifndef DASDATABASEMANAGER_GLOBAL_H
#define DASDATABASEMANAGER_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QByteArray>
#include <QSqlDriver>
#include <QMetaType>
#include <QDateTime>
#include <QVariant>
#include <QBuffer>
#include <QList>
#include <QDebug>
#include <QMap>

#include "tableinfo/baseinfo.h"
#include "tableinfo/userinfo.h"
#include "tableinfo/alarminfo.h"
#include "tableinfo/channelinfo.h"
#include "tableinfo/faultinfo.h"
#include "tableinfo/operateinfo.h"
#include "tableinfo/partinfo.h"
#include "tableinfo/systemparam.h"

#if defined(DASDATABASEMANAGER_LIBRARY)
#  define DASDATABASEMANAGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DASDATABASEMANAGERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DASDATABASEMANAGER_GLOBAL_H
