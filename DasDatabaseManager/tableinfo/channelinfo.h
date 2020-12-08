#ifndef CHANNELINFO_H
#define CHANNELINFO_H
#include "baseinfo.h"

class ChannelInfo : public BaseInfo
{
public:
    ChannelInfo();

    // BaseInfo interface
public:
    QStringList getColumns();
    void parseData();
    const QVariantList getVariants();
};

#endif // CHANNELINFO_H
