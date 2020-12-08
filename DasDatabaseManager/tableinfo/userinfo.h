#ifndef SYSTEMUSERINFO_H
#define SYSTEMUSERINFO_H
#include "baseinfo.h"

class UserInfo : public BaseInfo
{
public:
    UserInfo();
    // BaseInfo interface
public:
    QStringList getColumns();
    void parseData();
    const QVariantList getVariants();

    int getId() const;
    void setId(int value);

    QString getUser_name() const;
    void setUser_name(const QString &value);

    QString getUser_password() const;
    void setUser_password(const QString &value);

    int getUser_type() const;
    void setUser_type(int value);

private:
    int id;
    QString user_name;
    QString user_password;
    int user_type;


};

#endif // SYSTEMUSERINFO_H
