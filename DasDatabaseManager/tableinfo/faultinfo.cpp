#include "faultinfo.h"

FaultInfo::FaultInfo() : BaseInfo()
{

}

QStringList FaultInfo::getColumns()
{
    QStringList colums;
    colums << "id" << "channel" << "position" << "fault_type" << "fault_desc"
           << "fault_time" << "status" << "update_time";

    return colums;
}

void FaultInfo::parseData()
{

}

const QVariantList FaultInfo::getVariants()
{

}
