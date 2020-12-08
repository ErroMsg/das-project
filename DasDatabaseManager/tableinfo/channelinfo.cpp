#include "channelinfo.h"

ChannelInfo::ChannelInfo() : BaseInfo()
{

}

QStringList ChannelInfo::getColumns()
{
    QStringList colums;
    colums << "id" << "channel_id" << "channel_name" << "part_count"
           << "sample" <<"base_start"<<"base_end"<<"zero_start"<<"zero_end"
           << "algo" << "refractive" << "time_count" <<"freq_count"<<"enable"
           << "update_time";

    return colums;
}

void ChannelInfo::parseData()
{

}

const QVariantList ChannelInfo::getVariants()
{

}
