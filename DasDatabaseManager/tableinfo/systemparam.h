#ifndef SYSTEMPARAM_H
#define SYSTEMPARAM_H
#include "baseinfo.h"

class SystemParam : public BaseInfo
{
public:
    SystemParam();

    // BaseInfo interface
public:
    QStringList getColumns();
    void parseData();
    const QVariantList getVariants();
};

#endif // SYSTEMPARAM_H
