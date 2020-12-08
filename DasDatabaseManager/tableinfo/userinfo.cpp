#include "userinfo.h"

UserInfo::UserInfo() : BaseInfo()
{

}

QStringList UserInfo::getColumns()
{
    QStringList colums;
    colums << "id" << "user_name" << "user_pwd" << "user_type";

    return colums;
}
void UserInfo::parseData()
{
    if(m_rowData.isEmpty() || m_rowData.size() < 4)
        return;

    int i = 0;
    id = m_rowData.at(i++).toInt();
    user_name = m_rowData.at(i++).toString();
    user_password = m_rowData.at(i++).toString();
    user_type = m_rowData.at(i++).toInt();
}

const QVariantList UserInfo::getVariants()
{
    QVariantList varlist;
    varlist<<user_name<<user_password<<user_type;

    return varlist;
}

int UserInfo::getId() const
{
    return id;
}

void UserInfo::setId(int value)
{
    id = value;
}

QString UserInfo::getUser_name() const
{
    return user_name;
}

void UserInfo::setUser_name(const QString &value)
{
    user_name = value;
}

QString UserInfo::getUser_password() const
{
    return user_password;
}

void UserInfo::setUser_password(const QString &value)
{
    user_password = value;
}

int UserInfo::getUser_type() const
{
    return user_type;
}

void UserInfo::setUser_type(int value)
{
    user_type = value;
}
