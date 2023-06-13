#include "user.h"
#include <QDebug>
#include "ticket.h"

/**
  * @brief  默认构造函数，新建一个用户
  * @param  parent父级窗口
  * @retval 无
  */
user::user()
{

}

/**
  * @brief  带参构造函数，根据提供的数据来生成对应用户
  * @param  ac 用户账号
  * @param  psd 用户密码
  * @param  gd 用户性别
  * @param  nm 用户姓名
  * @param  op 用户权限
  * @retval 无
  */
user::user(QString ac, QString psd, bool gd, QString nm, bool op)
    : account(ac) , password(psd) , gender(gd) , name(nm) , Over_Power(op)
{

}

/**
  * @brief  将用户账号设置为ac
  * @param  ac 用户账号
  * @retval 无
  */
void user::setAccount(QString ac)
{
    account = ac;
}

/**
  * @brief  将用户密码设置为ps
  * @param  ps 用户密码
  * @retval 无
  */
void user::setPassword(QString ps)
{
    password = ps;
}

/**
  * @brief  将用户性别设置为gd
  * @param  gd 用户性别
  * @retval 无
  */
void user::setGender(bool gd)
{
    gender = gd;
}

/**
  * @brief  将用户名设置为nm
  * @param  nm 用户姓名
  * @retval 无
  */
void user::setName(QString nm)
{
    name = nm;
}

/**
  * @brief  将用户权限设置为op
  * @param  op 用户权限
  * @retval 无
  */
void user::setOP(bool op)
{
    Over_Power = op;
}

bool user::buy(ticket a)
{
    /*用户购票*/
    if(!tickets.contains(a))
    { //若未购买过该票
        a.amount = 1;
        tickets.push_back(a); //加入链表
        return true;
    }
    else
    {
        return false;
    }
}

QList<ticket> user::getTickets() const
{
    /*获取用户已购票据*/
    return tickets;
}

void user::setTickets(QList<ticket> t)
{
    /*设置用户已购票据*/
    tickets = t;
}

bool user::change(ticket a, ticket b)
{
    /*用户改签*/
    if(!tickets.contains(b))
    { //若改签前后不为同一张票
        tickets.removeOne(a); //移除当前票据
        b.amount = 1;
        tickets.push_back(b); //插入所改票据到链表
        return true;
    }
    else
    {
        return false;
    }
}

bool user::refund(ticket a)
{
    /*用户退票*/
    if(tickets.contains(a))
    { //若包含该票
        tickets.removeOne(a); //则移除
        return true;
    }
    else
    {
        return false;
    }
}

QString user::getid() const
{
    /*获取用户名*/
    return account;
}
