#ifndef PARTINFO_H
#define PARTINFO_H
#include "baseinfo.h"

class PartInfo : public BaseInfo
{
public:
    PartInfo();

    // BaseInfo interface
public:
    QStringList getColumns();
    void parseData();
    const QVariantList getVariants();
};

#endif // PARTINFO_H
