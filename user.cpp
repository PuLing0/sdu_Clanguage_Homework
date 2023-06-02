#include "user.h"
#include <QDebug>
#include "ticket.h"

user::user()
{

}

//带参构造函数，根据提供的数据来生成对应用户
user::user(QString ac, QString psd, bool gd, QString nm, bool op)
    : account(ac) , password(psd) , gender(gd) , name(nm) , Over_Power(op)
{

}

//将用户账号设置为ac
void user::setAccount(QString ac)
{
    account = ac;
}

//将用户密码设置为ps
void user::setPassword(QString ps)
{
    password = ps;
}

//将用户性别设置为gd
void user::setGender(bool gd)
{
    gender = gd;
}

//将用户名设置为nm
void user::setName(QString nm)
{
    name = nm;
}

//将用户权限设置为op
void user::setOP(bool op)
{
    Over_Power = op;
}

bool user::buy(ticket a){
    if(!tickets.contains(a)){
        a.amount = 1;
        tickets.push_back(a);
        return true;
    }
    else{
        return false;
    }
}

QList<ticket> user::getTickets() const{
    return tickets;
}

void user::setTickets(QList<ticket> t){
    tickets = t;
}

bool user::change(ticket a, ticket b){
    if(!tickets.contains(b)){
        tickets.removeOne(a);
        b.amount = 1;
        tickets.push_back(b);
        return true;
    }
    else{
        return false;
    }
}

bool user::refund(ticket a){
    if(tickets.contains(a)){
        tickets.removeOne(a);
        return true;
    }
    else{
        return false;
    }
}

QString user::getid() const{
    return account;
}
