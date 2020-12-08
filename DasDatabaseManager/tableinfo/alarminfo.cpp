#include "alarminfo.h"

AlarmInfo::AlarmInfo() : BaseInfo()
{

}

QStringList AlarmInfo::getColumns()
{
    QStringList colums;
    colums <<"id"<<"channel"<<"part"<<"position"<<"alarm_value"<<"alarm_type"
           <<"alarm_time"<<"alarm_level"<<"status"<<"update_time";

    return colums;
}

void AlarmInfo::parseData()
{
    if(m_rowData.isEmpty() || m_rowData.size() < 10)
        return;

    int i = 0;
    id = m_rowData.at(i++).toInt();
    channel = m_rowData.at(i++).toInt();
//    user_password = m_rowData.at(i++).toString();
//    user_type = m_rowData.at(i++).toInt();

//    int i = 0;
//    id = m_rowData.at(i++).toInt();
//    user_name = m_rowData.at(i++).toString();
//    user_password = m_rowData.at(i++).toString();
//    user_type = m_rowData.at(i++).toInt();
}

const QVariantList AlarmInfo::getVariants()
{

}
