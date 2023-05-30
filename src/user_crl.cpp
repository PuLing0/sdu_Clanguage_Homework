#include "user_crl.h"
#include <QFile>
#include <QTextStream>
#include <QVariant>
#include "user.h"
#include <QDebug>
#include <QMessageBox>
#include <string>
#include "md5.h"

using std::string;

//默认构造函数，用于用户链表的初始化，将文件中的内容导入链表
user_Crl::user_Crl()
{
    QFile file("E:\\documents\\QT\\2023\\month5\\C_homework_new\\login\\login_Vison2\\User_Data.dat");
    if (!file.open(QIODevice::ReadWrite))
    {
        // 文件打开失败处理
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine();

        // 逐行输入数据
        QString nm, ps, ac, op_s, gd_s;
        QTextStream lineStream(&line);
        lineStream >> nm >> ac >> ps >> gd_s >> op_s;

        QVariant op_v(op_s);
        QVariant gd_v(gd_s);
        bool op = op_v.toBool();
        bool gd = gd_v.toBool();

        // 将数据赋值给用户
        user u;
        u.setAccount(ac);
        u.setGender(gd);
        u.setName(nm);
        u.setPassword(ps);
        u.setOP(op);

        // 将用户添加到链表中
        userList.push_back(u);
    }

    file.close();
}

//添加一个新用户，用于注册功能
bool user_Crl::AddUser(QString ac, QString psd, bool gd, QString nm, bool op)
{
    md5 m;
    QString _psd = QString::fromStdString(m.getMD5(psd.toStdString()));
    user u;
    u.setAccount(ac);
    u.setGender(gd);
    u.setName(nm);
    u.setPassword(_psd);
    u.setOP(op);

    if (checkUser_Reg(ac ,  nm))
    {
        userList.push_back(u);

                //用于检查链表是否成功生成
                QList<user>::Iterator iter1;
                for (iter1 = userList.begin(); iter1 != userList.end(); iter1 ++)
                {
                    qDebug() << iter1->name << " " << iter1->account << " " << iter1->password << endl;
                }

        //打开文件
        QFile file("E:\\documents\\QT\\2023\\month5\\C_homework_new\\login\\login_Vison2\\User_Data.dat");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            //将用户信息输入到文件中
            QString str = nm + " " + ac + " " + _psd + " " + (gd ? "1" : "0") + " " + (op ? "1" : "0");
            out << str << endl;
            file.close();
            QMessageBox msgbx;
            //提示注册成功
            msgbx.setText("注册成功，请登录！");
            msgbx.exec();
            return true;
        }
        return false;
    }
    else if (checkUser_Account(ac) && checkUser_Name(nm))
    {
        //提示账号和用户名都存在
        QMessageBox msgbx;
        msgbx.setText("账号和用户名已存在，请重新注册");
        msgbx.exec();
        return false;
    }
    else if (checkUser_Account(ac))
    {
        //提示账号已经存在
        QMessageBox msgbx;
        msgbx.setText("账号已存在，请重新注册");
        msgbx.exec();
        return false;
    }
    else if(checkUser_Name(nm))
    {
        //提示用户名已经存在
        QMessageBox msgbx;
        msgbx.setText("用户名已存在，请重新注册");
        msgbx.exec();
        return false;
    }

    //默认返回false
    return false;
}


//修改用户信息，用于修改密码
bool user_Crl::ChgUser(QString ac , QString oldpd , QString newpd, QString renewpd)
{
    md5 m;
    QString _oldpd = QString::fromStdString(m.getMD5(oldpd.toStdString()));
    //先检查账号和旧密码是否对应
    if (checkUser_Password(ac , _oldpd))
    {
        //检查两次新密码是否输入一致
        if (newpd == renewpd)
        {
            QString _newpd = QString::fromStdString(m.getMD5(newpd.toStdString()));            //若两次新密码输入一致，将链表中的用户信息修改，同时将文件中的用户信息修改
            //链表用户信息修改
            int num_line = 0;
            user u;
            QList<user>::Iterator iter1;
            for (iter1 = userList.begin(); iter1 != userList.end(); iter1 ++ , num_line ++)
            {
                if (iter1->account == ac)
                {
                    u.setAccount(iter1->account);
                    u.setGender(iter1->gender);
                    u.setName(iter1->name);
                    u.setOP(iter1->Over_Power);
                    u.setPassword(_newpd);//将用户密码设置为新密码
                    userList.removeAt(num_line);
                    userList.push_back(u);
                    break;
                }
            }

            //文件用户信息修改
            QString newline = u.name + " " + u.account + " " + u.password + " " + (u.gender ? "1" : "0") + " " + (u.Over_Power ? "1" : "0");
            QFile file("E:\\documents\\QT\\2023\\month5\\C_homework_new\\login\\login_Vison2\\User_Data.dat");
            if (file.open(QIODevice::ReadWrite))
            {
                QTextStream in(&file);
                QStringList fileContent;
                int currentLineIndex = 0;
                //将文件中除需改动的地方复制，需改动的地方替换
                while (!in.atEnd())
                {
                    QString line = in.readLine();

                    if (currentLineIndex == num_line)
                    {
                        // 修改数据
                        line = newline;
                    }

                    fileContent.append(line);
                    currentLineIndex++;
                }
                file.close();

                // 打开文件并写入修改后的内容
                if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                {
                    QTextStream out(&file);
                    for (const QString& line : fileContent)
                    {
                        // 写入修改后的内容
                        out << line << "\n";
                    }

                    // 关闭文件
                    file.close();
                }
            }

            //提示修改密码成功
            QMessageBox msgbx;
            msgbx.setText("修改密码成功，请重新登录！");
            msgbx.exec();
            return true;
        }
        else
        {
            //提示两次新密码不一样
            QMessageBox msgbx;
            msgbx.setText("两次密码不一致！");
            msgbx.exec();
            return false;
        }
    }
    else
    {
        //提示账号不存在或这密码错误，这里将两者混淆是因为防止其他人居心叵测以测试他人的密码
        QMessageBox msgbx;
        msgbx.setText("账号不存在或密码错误");
        msgbx.exec();
        return false;
    }
}

//用于用户登录
bool user_Crl::LoginUser(QString ac, QString psd)
{
//    qDebug() << "你的密码是："  << psd << Qt::endl << "这个密码加密之后是: " << _psd << Qt::endl;
//    qDebug() << checkUser_Account(ac) << checkUser_Password(ac , _psd);
    if (checkUser_Account(ac) && checkUser_Password(ac , psd))
    {
        //如果用户账号存在，并且该账号对应的密码正确，则返回true
        return true;
    }
    else
    {
        return false;
    }
}


//检查用户名是否已经存在，若存在返回true
bool user_Crl::checkUser_Name(QString name)
{
    QList<user>::Iterator iter1;
    for (iter1 = userList.begin(); iter1 != userList.end(); iter1 ++)
    {
        if (iter1->name == name)
        {
            return true;
        }
    }

    return false;
}

//检查账号是否已经存在，若存在返回true
bool user_Crl::checkUser_Account(QString account)
{
    bool flag = false;
    QList<user>::Iterator iter1;
    for (iter1 = userList.begin(); iter1 != userList.end(); iter1 ++)
    {
        if (iter1->account == account)
        {
            flag = true;
        }
    }

    return flag;
}

//根据用户的账号返回该用户的权限，若是管理员返回1，普通用户返回0
bool user_Crl::checkUser_OP(QString ac)
{
    QList<user>::Iterator iter1;
    for (iter1 = userList.begin(); iter1 != userList.end(); iter1 ++)
    {
        if (iter1->account == ac)
        {
            return iter1->Over_Power;
        }
    }

    //如果查询不到用户默认返回错误,并进行提示
    QMessageBox msgbx;
    msgbx.setText("该用户不存在，请重试");
    msgbx.exec();
    return false;
}

//验证用户是否存在以及密码是否正确，用于登录功能和修改密码的检验功能，正确返回1，错误返回0
bool user_Crl::checkUser_Password(QString account, QString password)
{
    bool flag = false;//默认返回密码不正确

    md5 m;
    QString _password = QString::fromStdString(m.getMD5(password.toStdString()));
    QList<user>::Iterator iter1;
    for (iter1 = userList.begin(); iter1 != userList.end(); iter1 ++)
    {
        if (iter1->account == account && iter1->password == _password)
        {
//            qDebug() << "account: " << iter1->account << "password: " << _password << Qt::endl;
//            qDebug() << (iter1->account == account && iter1->password == _password) << Qt::endl;
            flag = true;
            break;
        }
    }

//    qDebug() << "checkuser_password" << flag << Qt::endl;
    return flag;
}

//用于检查这个用户的名字和账号是不是已经存在,用于注册功能，若不存在返回1，若存在返回0
bool user_Crl::checkUser_Reg(QString ac, QString nm)
{
    bool flag = false;//默认返回不存在

    QList<user>::Iterator iter1;
    for (iter1 = userList.begin(); iter1 != userList.end(); iter1 ++)
    {
        if (!checkUser_Account(ac) && !checkUser_Name(nm))
        {
            flag = true;;
        }
    }

    return flag;
}
