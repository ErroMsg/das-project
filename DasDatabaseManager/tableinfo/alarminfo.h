#ifndef ALARMINFO_H
#define ALARMINFO_H
#include "baseinfo.h"
#include <QTime>

class AlarmInfo : public BaseInfo
{
public:
    AlarmInfo();

    // BaseInfo interface
public:
    QStringList getColumns();
    void parseData();
    const QVariantList getVariants();

private:
    int id;
    int channel;
    int part;
    int position;
    int alarm_value;
    int alarm_type;
    QDateTime alarm_time;
    int alarm_level;
    int status;
    QDateTime update_time;
};

#endif // ALARMINFO_H
