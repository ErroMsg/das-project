#include "partinfo.h"

PartInfo::PartInfo() : BaseInfo()
{

}

QStringList PartInfo::getColumns()
{
    QStringList colums;
    colums << "id" << "part_id" << "channel_id" << "part_name" << "part_start"
           << "part_end" << "alarm_algo" << "alarm_value1" << "alarm_value2"
           << "alarm_value3" << "alarm_level" << "part_enable" << "update_time";

    return colums;
}

void PartInfo::parseData()
{

}

const QVariantList PartInfo::getVariants()
{

}
