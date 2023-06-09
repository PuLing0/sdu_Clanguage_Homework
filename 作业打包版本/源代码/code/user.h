#ifndef USER_H
#define USER_H

#include <QString>
#include "ticket.h"
#include <QList>

class user
{
public:
    QString account;//用户账号
    QString password;//用户密码
    bool gender;//用户性别，1是男性，2是女性
    QString name;//用户名
    bool Over_Power;//用户权限，1是管理员，2是普通用户
    QList<ticket> tickets;

    user();//默认构造函数
    user(QString ac , QString psd , bool gd , QString nm , bool op );//带参构造函数，根据提供的数据来生成对应用户
    void setAccount(QString ac);//将用户账号设置为ac
    void setPassword(QString ps);//将用户密码设置为ps
    void setGender(bool gd);//将用户性别设置为gd
    void setName(QString nm);//将用户名设置为nm
    void setOP(bool op); //将用户权限设置为op

    user(QString a, QString b):account(a), password(b){} //合成构造函数
    bool buy(ticket a); //购票
    bool change(ticket a, ticket b); //改签
    bool refund(ticket a); //退票
    QString getid() const; //获取用户名
    QList<ticket> getTickets() const; //获取用户已购票据
    void setTickets(QList<ticket> t); //设置用户已购票据
};

#endif // USER_H
