#include "user_crl.h"
#include <QFile>
#include <QTextStream>
#include <QVariant>
#include "user.h"
#include <QDebug>
#include <QMessageBox>
#include <string>
#include "md5.h"
#include <QTextCodec>

using std::string;

/**
  * @brief  默认构造函数，用于用户链表的初始化，将文件中的内容导入链表
  * @param  无
  * @retval 无
  */
user_Crl::user_Crl()
{
    QFile file("..\\Train\\User_Data.dat");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        // 文件打开失败处理
        return;
    }
    QTextStream in(&file);
    QTextCodec* codec = QTextCodec::codecForName("GBK");
    in.setCodec(codec);

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

    userlist_sort(0 , userList.size() - 1);

//    for (auto u = userList.begin(); u != userList.end(); u ++)
//    {
//        qDebug() << u->name << endl;
//    }
}

/**
  * @brief  添加一个新用户，用于注册功能
  * @param  ac 用户账号
  * @param  psd 用户密码
  * @param  gd 用户性别
  * @param  nm 用户姓名
  * @param  op 用户权限
  * @retval 注册成功返回1，注册失败返回0
  */
//添加一个新用户，用于注册功能
bool user_Crl::AddUser(QString ac, QString psd, bool gd, QString nm, bool op)
{
    //当账号，密码，姓名有一项为空时
    if(ac == "" || psd == "" || nm == "")
    {
        QMessageBox msgbx;
        msgbx.setText("禁止输入为空！");
        msgbx.setWindowFlags(msgbx.windowFlags() | Qt::WindowStaysOnTopHint);
        msgbx.exec();
        return false;
    }

    //将用户信息写入u
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
        //若u不存在则将u push进入链表
        userList.push_back(u);
        userlist_sort(0 , userList.size() - 1);
    //该代码用于检查链表是否生成成功
//                QList<user>::Iterator iter1;
//                for (iter1 = userList.begin(); iter1 != userList.end(); iter1 ++)
//                {
//                    qDebug() << iter1->name << " " << iter1->account << " " << iter1->password << endl;
//                }

        //打开文件
        QFile file("..\\Train\\User_Data.dat");
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            QTextStream out(&file);
            //将编码改为gbk方便输入中文
            QTextCodec* codec = QTextCodec::codecForName("GBK");
            out.setCodec(codec);
            //将用户信息输入到文件中
            for (auto iter = userList.begin(); iter != userList.end(); iter ++)
            {
                QString str = iter->name + " " + iter->account + " " + iter->password + " " + (iter->gender ? "1" : "0") + " " + (iter->Over_Power ? "1" : "0");
                out << str << endl;
            }
                for (auto u = userList.begin(); u != userList.end(); u ++)
                {
                qDebug() << u->name << u->Over_Power << endl;
                }
//            QString str = nm + " " + ac + " " + _psd + " " + (gd ? "1" : "0") + " " + (op ? "1" : "0");
//            out << str << endl;
            file.close();

            //在User_Ticket文件加中生成一个以user.name命名的txt文件，用于存储车票信息
            QFile file_name("..\\Train\\User_Ticket\\" + nm + ".txt");
            if (!file_name.open(QIODevice::WriteOnly | QIODevice::Text))
                return -1;
            file_name.close();

            //提示注册成功
            QMessageBox msgbx;
            msgbx.setText("注册成功，请登录！");
            msgbx.setWindowFlags(msgbx.windowFlags() | Qt::WindowStaysOnTopHint);
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
        msgbx.setWindowFlags(msgbx.windowFlags() | Qt::WindowStaysOnTopHint);
        msgbx.exec();
        return false;
    }
    else if (checkUser_Account(ac))
    {
        //提示账号已经存在
        QMessageBox msgbx;
        msgbx.setText("账号已存在，请重新注册");
        msgbx.setWindowFlags(msgbx.windowFlags() | Qt::WindowStaysOnTopHint);
        msgbx.exec();
        return false;
    }
    else if(checkUser_Name(nm))
    {
        //提示用户名已经存在
        QMessageBox msgbx;
        msgbx.setText("用户名已存在，请重新注册");
        msgbx.setWindowFlags(msgbx.windowFlags() | Qt::WindowStaysOnTopHint);
        msgbx.exec();
        return false;
    }

    //默认返回false
    return false;
}

/**
  * @brief  修改用户信息，用于修改密码
  * @param  ac 用户账号
  * @param  oldpsd 用户旧密码
  * @param  newpd 用户新密码
  * @param  renewpd 用户重复输入的新密码
  * @retval 修改密码成功返回1，注册失败返回0
  */
bool user_Crl::ChgUser(QString ac , QString oldpd , QString newpd, QString renewpd)
{
    md5 m;
    //先检查账号和旧密码是否对应
    if (checkUser_Password(ac , oldpd))
    {
        //检查两次新密码是否输入一致
        if (newpd == renewpd)
        {
            //如果新旧密码一致
            if (oldpd == newpd)
            {
                //提示新旧密码一致
                QMessageBox msgbx;
                msgbx.setText("旧密码和新密码一致!");
                msgbx.setWindowFlags(msgbx.windowFlags() | Qt::WindowStaysOnTopHint);
                msgbx.exec();
                return false;
            }
            else //新旧密码不一致
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
                QFile file("..\\Train\\User_Data.dat");
                QTextCodec* codec = QTextCodec::codecForName("GBK");
                QTextStream in(&file);
                in.setCodec(codec);
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
                msgbx.setWindowFlags(msgbx.windowFlags() | Qt::WindowStaysOnTopHint);
                msgbx.exec();
                return true;
            }
        }
        else
        {
            //提示两次新密码不一样
            QMessageBox msgbx;
            msgbx.setText("两次密码不一致！");
            msgbx.setWindowFlags(msgbx.windowFlags() | Qt::WindowStaysOnTopHint);
            msgbx.exec();
            return false;
        }
    }
    else
    {
        //提示账号不存在或这密码错误，这里将两者混淆是因为防止其他人居心叵测以测试他人的密码
        QMessageBox msgbx;
        msgbx.setText("账号不存在或密码错误");
        msgbx.setWindowFlags(msgbx.windowFlags() | Qt::WindowStaysOnTopHint);
        msgbx.exec();
        return false;
    }
}

/**
  * @brief  用于用户登录
  * @param  ac 用户账号
  * @param  psd 用户密码
  * @retval 用户登录成功返回1，注册失败返回0
  */
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

/**
  * @brief  检查用户名是否已经存在
  * @param  name 用户姓名
  * @retval 若用户名存在返回true，不存在返回false
  */
bool user_Crl::checkUser_Name(QString name)
{
    int l = 0 , r = userList.size() - 1;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (userList[mid].name >= name) r = mid;
        else
            l = mid + 1;
    }

    return (userList[l].name == name);
}

/**
  * @brief  检查账号是否已经存在
  * @param  account 用户账号
  * @retval 若用户账号存在返回true，不存在返回false
  */
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

/**
  * @brief  根据用户的账号返回该用户的权限
  * @param  ac 用户账号
  * @retval 若是管理员返回1，普通用户返回0
  */
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

    return false;//默认返回false
}

/**
  * @brief  快排，用于用户链表排序
  * @param  l 当前排序中链表的最左端
  * @param  r 当前排序中链表的最右端
  * @retval 无
  */
void user_Crl::userlist_sort(int l , int r)
{
    if (l >= r) return;

    int i = l - 1, j = r + 1;
    user u = userList[i + j >> 1];

    while (i < j)
    {
        do i ++; while(userList[i].name < u.name);
        do j --; while(userList[j].name > u.name);
        if (i < j)
            qSwap(userList[i] , userList[j]);
    }

    userlist_sort(l , j);
    userlist_sort(j + 1 , r);
}

/**
  * @brief  验证用户是否存在以及密码是否正确，用于登录功能和修改密码的检验功能
  * @param  account 用户账号
  * @param  password 用户密码
  * @retval 若账号及对应密码匹配返回1，不匹配返回0
  */
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

/**
  * @brief  用于检查这个用户的名字和账号是不是已经存在,用于注册功能
  * @param  ac 用户账号
  * @param  nm 用户名
  * @retval 若二者都不存在返回1，否则返回0
  */
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
