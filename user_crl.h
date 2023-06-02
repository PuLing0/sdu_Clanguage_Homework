#ifndef USER_CRL_H
#define USER_CRL_H

#include <user.h>
#include <QList>
#include <QString>

class user_Crl
{
    QList<user> userList;//创建一个用户链表，用于存储每一个用户的信息
public:
    user_Crl();//默认构造函数，用于用户链表的初始化，将文件中的内容导入链表
    bool AddUser(QString ac , QString psd , bool gd , QString nm , bool op);//添加一个新用户，用于注册功能
    bool ChgUser(QString ac , QString oldpd , QString newpd, QString renewpd);//修改用户信息，用于修改密码
    bool LoginUser(QString ac , QString psd );//用于用户登录
    bool checkUser_Password(QString account , QString password);//验证用户是否存在以及密码是否正确，用于登录功能和修改密码的检验功能
    bool checkUser_Reg(QString ac , QString nm);//用于检查这个用户的名字和账号是不是已经存在,用于注册功能
    bool checkUser_Name(QString name);//检查用户名是否已经存在
    bool checkUser_Account(QString account);//检查账号是否已经存在
    bool checkUser_OP(QString ac);//根据用户的账号返回该用户的权限
};

#endif // USER_CRL_H
