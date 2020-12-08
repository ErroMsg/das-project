#include "systemparam.h"

SystemParam::SystemParam() : BaseInfo()
{

}

QStringList SystemParam::getColumns()
{
    QStringList colums;
    colums << "id" << "param_name"<< "param_type" << "value"
           << "param_comment" << "update_time";

    return colums;
}

void SystemParam::parseData()
{

}

const QVariantList SystemParam::getVariants()
{

}
