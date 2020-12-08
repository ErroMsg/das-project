#ifndef BASEINFO_H
#define BASEINFO_H

#include <QObject>
#include <QVariant>
#include <QStringList>

class BaseInfo
{
public:
    BaseInfo();
    BaseInfo(QVariantList data);
    ~BaseInfo();

    virtual QStringList getColumns() = 0;
    virtual void parseData() = 0;
    virtual void setData(QVariantList data);
    virtual const QVariantList getVariants() = 0;

protected:
    QVariantList m_rowData;
};

#endif // BASEINFO_H
