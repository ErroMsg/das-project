#ifndef FAULTINFO_H
#define FAULTINFO_H
#include "baseinfo.h"

class FaultInfo : public BaseInfo
{
public:
    FaultInfo();

    // BaseInfo interface
public:
    QStringList getColumns();
    void parseData();
    const QVariantList getVariants();
};

#endif // FAULTINFO_H
