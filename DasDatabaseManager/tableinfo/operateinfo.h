#ifndef OPERATEINFO_H
#define OPERATEINFO_H
#include "baseinfo.h"

class OperateInfo : public BaseInfo
{
public:
    OperateInfo();

    // BaseInfo interface
public:
    QStringList getColumns();
    void parseData();
    const QVariantList getVariants();
};

#endif // OPERATEINFO_H
