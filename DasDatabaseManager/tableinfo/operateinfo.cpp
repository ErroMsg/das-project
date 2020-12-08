#include "operateinfo.h"

OperateInfo::OperateInfo() : BaseInfo()
{

}

QStringList OperateInfo::getColumns()
{
    QStringList colums;
    colums << "id" << "operate_time" << "user_id" << "operate_type" << "update_time";
    return colums;
}

void OperateInfo::parseData()
{

}

const QVariantList OperateInfo::getVariants()
{

}

