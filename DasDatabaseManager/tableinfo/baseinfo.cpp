#include "baseinfo.h"

BaseInfo::BaseInfo()
{

}

BaseInfo::BaseInfo(QVariantList data)
    : m_rowData(data)
{

}

BaseInfo::~BaseInfo()
{

}

void BaseInfo::setData(QVariantList data)
{
    m_rowData = data;
    parseData();
}
