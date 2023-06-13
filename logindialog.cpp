#include "logindialog.h"
#include "qdebug.h"
#include "user_crl.h"
#include <QMessageBox>
#include "md5.h"
#include "widget.h"
#include "widget_user.h"

/**
  * @brief  用于进行登录的操作
  * @param  account 用户的账号
  * @param password 用户的密码
  * @retval 登陆成功返回1，登陆失败返回0
  */
bool LoginDialog::LoginUser(QString account, QString password)
{
    bool flag = false;
    user_Crl *uc = new user_Crl();
    if (uc->LoginUser(account , password))
    {
        //登录成功，检查用户的权限并选择性的进入对应的界面
        if (uc->checkUser_OP(account) == 1)
        {
            //权限为1，进入管理员界面
            Widget* w = new Widget();
            w->show();
            flag = true;
        }
        else
        {
            //权限为0，进入用户界面
            Widget_User *wu = new Widget_User();
            user t(account, password);
            wu->setUser(t);
            wu->show();
            flag = true;
        }
    }
    else
    {
        //登陆失败，说明原因
        //(1) 用户账号不存在
        if(! uc->checkUser_Account(account))
        {
            QMessageBox msgbx;
            msgbx.setText("用户不存在！请重试。");
            msgbx.exec();
        }
        //(2)用户存在，但是账号与密码不匹配
        else if(! uc->checkUser_Password(account , password))
        {
            QMessageBox msgbx;
            msgbx.setText("密码错误！请重试。");
            msgbx.exec();
        }
    }

//    qDebug() << "end" << Qt::endl;
    //默认返回flase
    return flag;
}

/**
  * @brief  默认构造函数，用于登录功能
  * @param  无
  * @retval 无
  */
LoginDialog::LoginDialog()
{

}
