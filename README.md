# 火车票务管理系统/火车票购票系统 ver1.1

> ### 开发环境：
> 
> Qt 5.9.0 <br>
> Qt Creator 4.3.0 

## 目录
- ### [1. 系统介绍](#1)<br>
    - [系统功能](#1-系统功能)
    - [系统用户](#2-系统用户)
    - [使用场景](#3-使用场景)
- ### [2. 概要设计](#2)<br>
    - [软件层次结构图](#软件层次结构图)
    - [设计数据类型](#涉及数据类型)
    - [数据流图](#数据流图)
    - [流程图](#流程图)
- ### [3. 详细设计](#3)<br>
    - [函数接口](#函数接口)
    - [调用关系](#调用关系)
    - [关键算法](#关键算法)
    - [程序亮点](#程序亮点)
- ### [4. 总结](#4)<br>
    - [登录界面开发](#登录主界面开发-司居正)
    - [用户界面开发](#用户界面开发-陈硕成)
    - [管理员界面开发](#管理员界面开发-袁恩晗)
- ### [5. 附录](#5-附录)
    - [可使用用户列表](#可使用用户列表)
    - [可查询票据记录](#可查询票据记录)
    - [运行示例](#运行示例)

<p id="1"></p>

## 系统介绍

### 1. 系统功能 
- 登录界面：用户登录、管理员登录、注册用户、修改用户密码
- 用户界面：
- 1. 购票查询界面：票据查询（按各标签排序）、购票、改签
- 2. 个人中心界面：已购买票据查询、改签、退票
- 管理员界面：
- 1. 车票列表、用户列表界面：按车站、日期查询车票，按用户名查询车票
- 2. 增加车次、更改车次、添加用户窗口

### 2. 系统用户
管理员、旅客

### 3. 使用场景
用于火车站购票、后台管理票据

<p id="2"></p>

## 概要设计

### 软件层次结构图
<img src="https://raw.githubusercontent.com/PuLing0/sdu_Clanguage_Homework/master/Image/%E8%BD%AF%E4%BB%B6%E5%B1%82%E6%AC%A1%E5%9B%BE.png" alt="图片alt" title="软件层次结构图">

### 涉及数据类型
```
class ticket
{
public:
    ticket();
    QString id;//列车号
    QString beginpoint;//始发地
    QString endpoint;//终点站
    QString beginDay; //发车日期
    QString endDay; //到站日期
    QString begintime;//发车时间
    QString endtime;//到站时间
    int amount;//车票数
    double price;//车票价格
};
class user
{
public:
    QString account;//用户账号
    QString password;//用户密码
    bool gender;//用户性别，1是男性，2是女性
    QString name;//用户名
    bool Over_Power;//用户权限，1是管理员，2是普通用户
    QList<ticket> tickets;
};

```

### 数据流图
#### 0层数据流图
<img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/0%E5%B1%82%E6%95%B0%E6%8D%AE%E6%B5%81%E5%9B%BE.png" alt="sd" title="0层数据流图">

#### 1层数据流图
<img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/1%E5%B1%82%E6%95%B0%E6%8D%AE%E6%B5%81%E5%9B%BE-%E7%94%A8%E6%88%B7.png" alt="sd" title="1层数据流图-用户"><br>
<img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E7%AE%A1%E7%90%86%E5%91%981%E5%B1%82%E6%95%B0%E6%8D%AE%E6%B5%81%E5%9B%BE.jpg" alt="sd" title="1层数据流图-管理员">
![Image text](https://raw.githubusercontent.com/PuLing0/sdu_Clanguage_Homework/master/Image/%E7%94%A8%E6%88%B7%E5%AD%98%E5%82%A8%E6%96%87%E4%BB%B6%E6%95%B0%E6%8D%AE%E6%B5%81%E5%9B%BE.png)

### 流程图
#### 登陆界面流程图
![Image text](https://raw.githubusercontent.com/PuLing0/sdu_Clanguage_Homework/master/Image/%E7%99%BB%E9%99%86%E7%B3%BB%E7%BB%9F%E6%B5%81%E7%A8%8B%E5%9B%BE.png)

#### 用户界面流程图
<img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E7%94%A8%E6%88%B7%E7%95%8C%E9%9D%A2%E6%B5%81%E7%A8%8B%E5%9B%BE.png" alt="sd" title="用户界面流程图">

#### 管理员界面流程图
<img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E6%B5%81%E7%A8%8B%E5%9B%BE.jpg" alt="sd" title="管理员界面流程图">

<p id="3"></p>

## 详细设计

### 函数接口

```
class widget_user
{
public:
    Widget_User(QWidget *parent = nullptr);
    ~Widget_User();
    void setUser(user t); //设置当前用户

private slots:
    void on_pushButton_clicked(); //查询按键
    void check(); //查询
    bool read(); //读取票据文件
    void on_tableWidget_cellDoubleClicked(int row, int column); //双击购买/改签单元格事件
    bool refund(ticket a); //退票
    void on_pushButton_3_clicked(); //个人中心按钮
    bool readUsertickets(); //读取用户已购票据
    void on_pushButton_4_clicked(); //退出登录按钮
    bool save(); //保存
    void get(bool m, ticket a); //窗口间传递changingTicket
    void timerUpdate(); //时钟
    void updateTicketData(); //更新票据文件
    void tableUpdate(); //更新列表
protected:
    void closeEvent(QCloseEvent *event); //关闭窗口动作
};

class user{
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
class ticket
{
public:
    ticket();//构造函数
    bool operator ==(const ticket l)
    {
        /*判断两票相同与否*/
        if(id == l.id) return true;
        return false;
    }
};
class dialog1
{
    public:
    explicit dialog1(QWidget *parent = nullptr);
    void setUser(user t); //设置当前用户
    ~dialog1();

signals:
    void send(bool mode, ticket a); //窗口间传递changingTicket

private slots:
    void on_tableWidget_2_cellDoubleClicked(int row, int column); //双击改签/退票单元格事件
    void on_pushButton_clicked(); //已购票据查询按钮
    void on_pushButton_2_clicked(); //退出按钮
}
```
```
class adduserdialog
{
public:
    ~adduserdialog();

    bool Gender_Choose();//用于性别选择，其中男性返回1，女性返回0，默认是男性
    bool gender;//用户性别，1是男性，2是女性
    bool Over_Power;//用户权限，1是管理员，2是普通用户

public slots:
    void btnclicked();//记录注册按钮的点击
};
class changeticketdialog
{
public:
    ~changeticketdialog();
    
    QString getiniid();//获取想要修改的车次的列车号
    QString getiniba();//获取想要修改的列车的现在的始发站
    QString getiniea();//获取想要修改的列车的现在的终点站
    QString getinibt();//获取想要修改的列车的现在的开车时间
    QString getiniet();//获取想要修改的列车的现在的到站时间
    QString getfinba();//获取想要修改的列车的改后的始发站
    QString getfinea();//获取想要修改的列车的改后的终点站
    QString getfinbt();//获取想要修改的列车的改后的开车时间
    QString getfinet();//获取想要修改的列车的改后的到站时间
    QString getfinnumber();//获取想要修改的列车的改后的票数
    QString getfinprice();//获取想要修改的列车的改后的车价
    
    void changebtnclicked();//修改按钮按下时触发
    int flap;//记录是否为修改按钮按下
};
```
```
class dialogaddticket
{
public:
    ~dialogaddticket();

    QString getid();//获取想要添加的列车的列车号
    QString getba();//获取想要添加的列车的始发站
    QString getea();//获取想要添加的列车的终点站
    QString getbt();//获取想要添加的列车的发车时间
    QString getet();//获取想要添加的列车的到站时间
    QString getticket();//获取想要添加的列车的车票数
    QString getprice();//获取想要添加的列车的票价
public slots:
    
    void saveclicked();//保存按钮按下式触发
};
```
```
class Widget
{
public:
    ~Widget();

    //将信息读入列表中
    void loadingticketdata();
    void loadinguserdata();
    //在列车表格显示一个车票数据
    void setticketWidgetsingleticket(const ticket& );
    //在列车查询表格显示一个车票数据
    void setsearchticketWidgetsingleticket(const ticket& );
    //将列车信息显示在表格中
    void setticketdata(const QList<ticket>&);
    //将用户信息显示在表格中
    void setuserdata(const QList<user>&);
    //保存车票修改按钮
    void saveticket();
    //保存用户修改按钮
    void saveuser();

public slots:

    //添加用户信息按钮
    void on_adduserButton_clicked();
    //添加车次信息按钮
    void on_addticketButton_clicked();
    //列车信息菜单点击，获取当前位置
    void RightClickSlot(QPoint pos);
    //列车信息得知菜单当前的位置并删除
    void RightClickDelete(QAction *act);
    //点击查询车票按钮
    void on_searchticketbtn_clicked();
    //点击查询用户按钮
    void on_searchuserbtn_clicked();
    //点击车票信息列表按钮
    void on_ticketList_clicked();
    //点击用户信息列表按钮
    void on_userList_clicked();
    //点击退出按钮
    void on_Exit_clicked();
    //点击修改列车信息是触发
    void on_changeticketbtn_clicked();
    //计时器
    void timerUpdate();
};

```

```
chgdialog.h
#ifndef CHGPDDIALOG_H
#define CHGPDDIALOG_H

#include <QWidget>

namespace Ui {
class chgpdDialog;
}

class chgpdDialog : public QWidget
{
    Q_OBJECT

public:
    explicit chgpdDialog(QWidget *parent = nullptr);//构造函数
    ~chgpdDialog();//析构函数

    void paintEvent(QPaintEvent *event);//边框加一条黑边以便识别

private slots:
    void on_btn_back_clicked();// 返回到mainwindow

    void on_btn_chg_clicked();// 确认修改密码

protected:
    //用于鼠标拖动窗口移动
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::chgpdDialog *ui;
    QPoint reltvPos; // 相对坐标
    bool m_bMove; // 是否移动
};

#endif // CHGPDDIALOG_H
```

```
logindialog.h
#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QString>


class LoginDialog
{
public:
    bool LoginUser(QString account , QString password);//用于进行登录的操作
public:
    LoginDialog();//默认构造函数
};

#endif // LOGINDIALOG_H

```

```
md5.h
#ifndef MD5_H
#define MD5_H

#include <string>
using std::string;

class md5
{
public:
    //构造函数，用于初始化类的成员变量
    md5();

    /*MD5主循环函数，用于处理每个512位的分组。
    根据索引 i 的不同值，选择不同的运算方式，并更新临时变量。*/
    void mainLoop(unsigned int M[]);

    unsigned int* add(string str);//填充函数，将输入的字符串填充为64字节的整数倍，并添加长度信息。

    string changeHex(int a);//将整数转换为16进制字符串表示。

    /*计算给定字符串的MD5哈希值。初始化临时变量并调用 add 函数对输入字符串进行填充，
    然后通过 mainLoop 处理每个512位分组，最后将结果转换为16进制字符串形式并返回。*/
    string getMD5(string source);
};

#endif // MD5_H

```

```
regdialog.h
#ifndef REGDIALOG_H
#define REGDIALOG_H

#include <QWidget>

namespace Ui {
class RegDialog;
}

class RegDialog : public QWidget
{
    Q_OBJECT

public:
    explicit RegDialog(QWidget *parent = nullptr);//默认构造函数
    ~RegDialog();//默认析构函数
    bool Gender_Choose();//用于性别选择，其中男性返回1，女性返回0，默认是男性
    void paintEvent(QPaintEvent *event);//边框加一条黑边以便识别

private slots:
    void on_Btn_Back_clicked();//返回mainwindow

    void on_Btn_Reg_clicked();//注册用户

//用于鼠标拖动无边框窗口移动
protected:
    void mousePressEvent(QMouseEvent *event) override;// 鼠标按下事件处理函数
    void mouseMoveEvent(QMouseEvent *event) override; // 鼠标移动事件处理函数
    void mouseReleaseEvent(QMouseEvent *event) override;// 鼠标释放事件处理函数

private:
    Ui::RegDialog *ui;
    QPoint reltvPos; // 相对坐标
    bool m_bMove; // 是否移动
};

#endif // REGDIALOG_H

```

```
user_crl.h
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

```

```
mainwindow.h
#ifndef _MAINWINDOWH_H
#define _MAINWINDOWH_H

#include <QMainWindow>
#include <QTimer>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class framelessWidget; }
QT_END_NAMESPACE

class framelessWidget : public QWidget
{
    Q_OBJECT

public:
    framelessWidget(QWidget *parent = nullptr);
    ~framelessWidget();

private:
    Ui::framelessWidget *ui;
    int cornerRadius = 20;// 窗口圆角半径
    QPoint lastPos; // 上次鼠标位置
    QWidget *border = nullptr;// 窗口边框
    QGraphicsDropShadowEffect *windowShadow; // 窗口阴影效果

    bool mousePressed = false;// 鼠标按下标志位
    //鼠标状态
    enum {AT_LEFT = 1, AT_TOP = 2,  AT_RIGHT = 4, AT_BOTTOM = 8,
          AT_TOP_LEFT = 3, AT_TOP_RIGHT = 6, AT_BOTTOM_LEFT = 9, AT_BOTTOM_RIGHT = 12};
    int mouseState;// 当前鼠标状态
    bool maximized = false;// 窗口最大化标志位

    void Init();// 给centralwidget添加一个mainwidget，设置遮罩及遮挡锯齿边缘的board
    void mousePressEvent(QMouseEvent *event);// 鼠标按下事件(记录拉伸窗口或移动窗口时的起始坐标（左上角）)
    void mouseMoveEvent(QMouseEvent *event);// 鼠标移动事件处理函数
    void mouseReleaseEvent(QMouseEvent *event);// 鼠标释放事件处理函数

    void mouseDoubleClickEvent(QMouseEvent *event);// 鼠标双击事件处理函数

    void resizeEvent(QResizeEvent *event);// 窗口大小改变事件处理函数

    QRect lastGeometry;// 上次窗口位置信息
    void controlWindowScale();// 控制窗口缩放函数

private slots:
    void on_btn_login_clicked();//登录按钮

    void on_btn_reg_clicked();//注册按钮

    void on_btn_chg_clicked();//修改密码按钮

};
#endif // _MAINWINDOWH_H

```

### 调用关系
<p id="4"></p>

```
widget_user.cpp
Widget_User::Widget_User(QWidget *parent):
    Widget_User::tableUpdate()
void Widget_User::setUser(user t):
    Widget_User::readUsertickets()
    currentUser.getid()
void Widget_User::closeEvent(QCloseEvent *event):
    void Widget_User::updateTicketData()
    bool Widget_User::save()
bool Widget_User::readUsertickets():
    currentUser.getid()
    currentUser.setTickets()
void Widget_User::tableUpdate():
    void Widget_User::check()
void Widget_User::on_tableWidget_cellDoubleClicked(int row, int column):
    currentUser.buy()
    void Widget_User::tableUpdate()
    currentUser.change()
void Widget_User::on_pushButton_3_clicked():
    void dialog1::setUser(user t)
void Widget_User::on_pushButton_4_clicked():
    bool Widget_User::save()
    void Widget_User::updateTicketData()
bool Widget_User::save():
    currentUser.getid()
    currentUser.getTickets()
void Widget_User::get(bool m, ticket a):
    bool Widget_User::refund(ticket a)
bool Widget_User::refund(ticket a):
    currentUser.refund(a)
    void Widget_User::tableUpdate()
```
```
dialog1.cpp
void dialog1::setUser(user t):
    t.getTickets()
void dialog1::on_tableWidget_2_cellDoubleClicked(int row, int column):
    void dialog1::send(bool mode, ticket a)
    void dialog1::on_pushButton_clicked()
```
```
adduserdialog.cpp
adduserdialog::adduserdialog(QWidget *parent):
    void adduserdialog::btnclicked()
void adduserdialog::btnclicked():
    bool adduserdialog::Gender_Choose()
```
```
changeticketdialog.cpp
changeticketdialog::changeticketdialog(QWidget *parent):
    void changeticketdialog::changebtnclicked()
```
```
dialogaddticket.cpp
dialogaddticket::dialogaddticket(QWidget *parent):
    void dialogaddticket::saveclicked()
```
```
Widget::Widget(QWidget *parent):
    void Widget::loadingticketdata()
    void Widget::loadinguserdata()
    void Widget::on_ticketList_clicked()
    void Widget::on_userList_clicked()
    void Widget::on_adduserButton_clicked()
    void Widget::on_addticketButton_clicked()
    void Widget::RightClickSlot(QPoint pos)
    void Widget::RightClickDelete(QAction *act)
    void Widget::on_searchticketbtn_clicked()
    void Widget::on_searchuserbtn_clicked()
    void Widget::on_changeticketbtn_clicked()
    void Widget::timerUpdate()
void Widget::loadinguserdata():
    void user::setAccount(QString ac)
    void user::setPassword(QString ps)
    void user::setGender(bool gd)
    void user::setName(QString nm)
    void user::setOP(bool op)
    void user::setTickets(QList<ticket> t)
void Widget::on_ticketList_clicked():
    void Widget::setticketdata(const QList<ticket>&ticketlist)
void Widget::on_userList_clicked():
    void Widget::setuserdata(const QList<user>&)
void Widget::setticketdata(const QList<ticket>&ticketlist)
    void Widget::setticketWidgetsingleticket(const ticket& it)
void Widget::on_searchticketbtn_clicked()
    void Widget::setsearchticketWidgetsingleticket(const ticket& it)
void Widget::on_adduserButton_clicked():
    string md5::getMD5(string source)
    void Widget::saveuser()
void Widget::on_addticketButton_clicked():
    QString dialogaddticket::getid()
    QString dialogaddticket::getba()
    QString dialogaddticket::getea()
    QString dialogaddticket::getbt()
    QString dialogaddticket::getet()
    QString dialogaddticket::getticket()
    QString dialogaddticket::getprice()
    void Widget::saveticket()
void Widget::RightClickDelete(QAction *act):
    void Widget::saveticket()
    void Widget::saveuser()
void Widget::on_changeticketbtn_clicked():
    void Widget::saveticket()
    void Widget::saveuser()
    void Widget::setticketdata(const QList<ticket>&ticketlist)
    void Widget::setuserdata(const QList<user>&)
    QString changeticketdialog::getiniid()
    QString changeticketdialog::getiniba()
    QString changeticketdialog::getiniea()
    QString changeticketdialog::getinibt()
    QString changeticketdialog::getiniet()
    QString changeticketdialog::getfinba()
    QString changeticketdialog::getfinea()
    QString changeticketdialog::getfinbt()
    QString changeticketdialog::getfinet()
    QString changeticketdialog::getfinnumber()
    QString changeticketdialog::getfinprice()
void Widget::on_Exit_clicked():
    void Widget::saveticket()
    void Widget::saveuser()
```

```
chgpddialog.cpp
void chgpdDialog::on_btn_back_clicked():// 返回到mainwindow
    framelessWidget::framelessWidget();
    void framelessWidget::setWindowFlags(Qt::WindowFlags type);
    void framelessWidget::setAttribute(Qt::WidgetAttribute, bool on = true);
void chgpdDialog::on_btn_chg_clicked():// 确认修改密码
    user_Crl::user_Crl();
    bool user_Crl::ChgUser(QString ac , QString oldpd , QString newpd, QString renewpd); 
```

```
mainwindow.cpp
void on_btn_login_clicked()://登录按钮
    LoginDialog::LoginDialog();
    bool LoginDialog::LoginUser(QString account, QString password);
void on_btn_reg_clicked()://注册按钮
    explicit RegDialog::RegDialog(QWidget *parent = nullptr);
void on_btn_chg_clicked()://修改密码按钮
    explicit chgpdDialog::chgpdDialog(QWidget *parent = nullptr);
```

```
regdialog.cpp
void on_Btn_Back_clicked();//返回mainwindow
    framelessWidget::framelessWidget();
    void framelessWidget::setWindowFlags(Qt::WindowFlags type);
void on_Btn_Reg_clicked();//注册用户
    user_Crl::user_Crl();
    bool user_Crl::AddUser(QString ac, QString psd, bool gd, QString nm, bool op);
```

### 关键算法
#### 登陆系统
- 排序：在排序方面使用的是快速排序，本函数基于用户的名字进行了排序，能够极大提高文件的使用性，也可以让管理员看到用户信息有序的排列，提高可观性
    详见函数：`void user_Crl::userlist_sort(int l , int r)`
- 查找：使用的二分查找进行查找，由于对用户的名字进行了排序，因此在用户登录时对用户信息的搜索使用了二分查找，能够提高登录查找数据的效率
    详见函数:`bool user_Crl::checkUser_Name(QString name)`
    
#### 管理员系统
#### 用户系统

### 程序亮点

```
string md5::getMD5(string source)；//使用md5加密算法对密码进行加密
```

## 总结

### 登录主界面开发-司居正
1. 所做工作：
    - 实现了登录主界面
    - 实现了注册界面
    - 实现了修改密码界面
    - 实现了用户数据的读取、存入、修改
    - 用md5加密算法实现了用户密码的加密
    - 在文件中加入了qt-material-widgets-master静态库，使ui界面更简洁人性化
2. 开发中遇到的问题
    - 已解决
        - 窗口无边框
        - 点击窗口空白区域可以拖动窗口
        - 登录注册修改密码遇到的多种情况进行分情况讨论
        - 在注册时User_Data.dat文件内的数据自动更新
        - 密码在User_Data.dat中的密码加密，避免直接被人盗取
    - 未解决
        - 密码加密不可逆，如果使用非对称可逆加密SRA加密算法更具有科学性
        - 用户列表的查找方式时间复杂度太大，如果将用户列表排序后用二分查找会减少查找时间
3. 收获和想法
> 我的收获：通过本次开发，我学会了QT软件的基本使用，学会了静态库基本使用，熟悉了一个软件从设计，开发到测试和报告的整个流程，进一步掌握了C/C++语言基础语法的使用，同时也明白了一些前端设计的基础，对C/C++语言语法的掌握更进了一步。<br>
> 在撰写实验报告的过程中，我了解了软件工程的一些基础知识，例如软件流程图，软件层次图，数据流图等概念，学会了从整体布局，局部分析完成的思维逻辑，受益匪浅。同时我也学会了markdown的基础语法，能够使文本的编      写更加规矩整洁，提高可读性。<br>
> 在团队合作过程中，由于大家初次团队合作，对彼此的了解不算太深，一开始时问题百出，分工的不明确，功能漏洞百出。在不断的磨合中，我们对彼此的了解更加深刻，同时团队的合作也更加紧密。我与两位组员之间沟通到位，    遇到问题及时沟通解决，彼此主动承担任务，对自身的任务压力毫无推脱，大家一心为了好好完成和打磨大作业，给老师，队员和自己一个完美的答复。同时我们这次开发借助了github，对于初次接触github的我们来说，各种操作对大家来说都是从未接触的，导致前四五天操作github的时候总是操作失误，导致文件总是需要进行`git reset --hard ...`，导致现在看见这个代码就已经有反应了。但是经过几天的磨合后，我们团队就已经体会到在github合作的好处了。我认为github不仅为团队提高了效率，在点开主页看到一条一条的commit之后，内心的自豪感也是油然而生，这是我们一点一点从无到有搭建起来的一座小木屋，是我们近三个周共同努力的结果。<br>
> 我的想法：非常感谢老师能够提供这次难得的机会，用一段比较长的时间来提高我自己的代码能力，让我提高自己的代码能力。在这次开发过程中，我对C/C++语言的熟练程度得到了提高，同时参与了整个管理系统的制作过程。同    时我也要感谢我的各位组员，在最开始我邀请两位一起成组的时候，大家在合作上还是很不熟悉彼    此，但是在几周的合作下，我们已经成功熟悉了彼此，遇到问题一起集思广益去解决问题，用集体的力量去解决问题。同时这次大作业也让我对自己认知有了更深的了解，一个人对于自己的能力应该有自信，要有面对困难，解决困难的勇气，如果不是经历过整个大作业的过程，过去的我也不会相信自己会在短短三周时间里学会qt、github、markdown、密码加密等基础知识，并有机会将这些知识转化为在大作业里面的应用。在经历了这次的大作业后，我会更加有勇气的去面对未来的困难，并且用乐观积极的态度解决问题，因为我相信我可以，我有能力去面对。最后，再次感谢老师和两位和我一起努力的队友。

### 用户界面开发-陈硕成
1. 所做工作：
- 实现了用户界面
- 实现了个人中心界面
- 实现了用户购买车票文件的读取和存入
- 实现了现有票据文件的读取和存入
2. 开发中遇到的问题：
- 已解决
    - 窗口间传值
    - 文本文件编码
    - 同步更新用户信息
    - 表头排序功能
    - 关闭窗口事件触发自动保存
- 未解决
    - 经停站显示
    - 票务转让
3. 收获和想法
> 我的收获：通过本次开发，我在步步摸索中学会了Qt5(C++)的开发模式，掌握了基本的ui设计，在应用中巩固了面向对象技术的要点，扎实了文件输入/输出、数据类型、函数调用等程序设计的基本功<br>
> 在撰写报告的过程中，我了解了软件工程中层次图、流程图、数据流图的画法与作用，体会到软件设计框架对于整体设计思路的益处<br>
> 我的想法：对于程序设计大作业来说，管理系统可谓是老生常谈，实现其功能并不难，关键在于对于功能的封装，以及呈现在使用者面前的效果即对于使用者的友好性，以及操作的直观性、便捷性，这就需要一个良好的ui设计。另一方面，“金玉其外，败絮其中”的现象经常会发生在过于注重ui的程序，其经常会出现一些运行时错误，对于极端情况下的操作缺乏对策，因此需要全面考虑各种情况，分别给出提示信息。总的来说，这次的大作业开发周期不短，实现了良好的功能，同时我也学到了各方面的许多知识，对于我个人来说，是一次提升的过程。

### 管理员界面开发-袁恩晗
1.所做工作
- 实现了管理员界面
- 实现了添加车票界面
- 实现了删除车票功能
- 实现了修改车票界面
- 实现了添加用户界面
- 实现了车票数据文件和用户数据文件的读取、修改和存入
2. 开发中遇到的问题
- 已解决的问题
    - QTableView排序功能
    - 用户、车票信息的及时更新功能实现
    - 不同窗口间的值传递问题、以及不同窗口间的调用问题
    - 对于用户不同行为的判断问题
    - 退出时保存所有修改
- 暂未解决的问题
    - 在QTableView中操作数据问题
    - 更为完善的车票信息冲突判断
    - ui界面控件的简化
3. 收获与想法
> 收获：在完成本次大作业的过程中，我熟悉了Qt的基本框架和模块,进一步掌握了C++编程技巧，学会了如何使用Qt Creator进行开发，特别是学会了ui界面的搭建，提高了自己解决实际问题能力。同时，我也了解了Qt中静态库的调用方法，并运用到了实际的开发过程中。<br>
> 在开发的过程中，我们采用了github共同开发的方法，在此过程中解决了一系列在共同开发中遇到的上传，冲突，回退等问题。现在已能够较为熟练地使用github完成项目。同时，我学会了通过网络，参考书籍，帮助文档等方法解决在实际开发中遇到的各种问题。<br>
> 在撰写实验报告和README文档的过程中，我第一次接触了md文档的书写方法，掌握了一门新的技能。更加具体的了解了一个较为正规的程序所应该具有的各项组成部分以及细节。学习了流程图，层次图，数据流图的绘制流程，帮助我更好地理解软件层次，从而更好地设计和实现软件。<br>
> 想法：完成大作业的过程对于我来说应该是一个宝贵的财富。事实上完成大作业花费了我大量的时间和精力，同时也要克服许多困难和挑战。可以说经过了c语言和c++语言的学习，完成想要的功能并不困难。但是对于刚刚接触Qt的我来说，有太多的新知识需要去学习，去适应，去应用，经过了很长的磨合期，我才堪堪掌握Qt中各种功能的使用。但这不正是学习一项新知识该有的过程，我想这也是以后学习，工作时时常会遇到的情况，这给我打下了良好的思想基础。同时，在完成这次大作业的过程中，我也逐步的适应了团队开发的模式，学会在团队中交流，发表意见，提供想法，和队员协调各项事宜，共同完成程序的开发，测试。并且，我也学会了从不同角度审视一个软件。要考虑软件的美观性，实用性，尽可能的让软件适合更多的人使用，这给了我在程序设计方面很好的启发。总之，我十分感恩这次c语言程序设计大作业。

## 附录
### 可使用用户列表
|用户名|账号|密码|性别|权限|
|-----|----|----|---|----|
|admin|admin|admin|男|管理员|
|admin0|admin0|admin0|男|管理员|
|admin1|admin1|admin1|男|管理员|
|admin2|admin2|admin2|男|管理员|
|sijuzheng|sijuzheng|sijuzheng|男|普通用户|
|yuanenhan|yuanenhan|yuanenhan|男|普通用户|
|chenshuocheng|chenshuocheng|chenshuocheng|男|普通用户|

### 可查询票据记录
#### 查询实例1：2023-07-11 北京-上海
|车次|发站|到站|出发日期|出发时间|到达日期|到达时间|车票剩余数量|票价|
|-----|----|----|-----------|-----|-----------|-----|----|----|
|D2023|北京|上海|2023-07-11|07:37|2023-07-11|09:32|2|250.00|
|D2231|北京|上海|2023-07-11|07:43|2023-07-11|09:23|2|251.00|
|G213|北京|上海|2023-07-11|15:55|2023-07-11|20:33|2|252.00|
|L21|北京|上海|2023-07-11|05:19|2023-07-11|08:43|2|253.00|
|T21|北京|上海|2023-07-11|11:40|2023-07-11|16:02|2|254.00|
|A380|北京|上海|2023-07-11|20:15|2023-07-11|22:14|2|255.00|
|M231|北京|上海|2023-07-11|21:01|2023-07-11|23:09|2|256.00|
|G9094|北京|上海|2023-07-11|10:49|2023-07-11|13:11|2|257.00|
|N1023|北京|上海|2023-07-11|13:47|2023-07-11|14:21|2|258.00|
|D2139|北京|上海|2023-07-11|01:39|2023-07-11|03:26|2|259.00|
|D1413|北京|上海|2023-07-11|16:43|2023-07-11|18:10|2|290.00|
|K1493|北京|上海|2023-07-11|10:35|2023-07-11|12:01|2|221.00|
|K1432|北京|上海|2023-07-11|13:17|2023-07-11|16:21|2|243.00|
|K879|北京|上海|2023-07-11|20:30|2023-07-11|21:44|2|254.00|
|Z2391|北京|上海|2023-07-11|21:14|2023-07-11|22:10|2|267.00|
|UFO|北京|上海|2023-07-11|00:00|2023-07-11|00:01|0|2686.00|

#### 查询实例2：2023-07-11 hn hb
|车次|发站|到站|出发日期|出发时间|到达日期|到达时间|车票剩余数量|票价|
|-----|----|----|-----------|-----|-----------|-----|----|----|
|k123|hn|hb|2023-07-11|15:00|2023-07-11|16:00|32|200.00|
|g20|hn|hb|2023-07-11|10:00|2023-07-11|15:00|32|200.00|
|g099|hn|hb|2023-07-11|13:00|2023-07-11|14:00|32|200.00|
|k011|hn|hb|2023-07-11|01:00|2023-07-11|09:00|32|200.00|
|g9000|hn|hb|2023-07-11|12:00|2023-07-11|15:00|32|200.00|
|g2999|hn|hb|2023-07-11|19:00|2023-07-11|23:00|32|200.00|
|g16|hn|hb|2023-07-11|16:00|2023-07-11|20:00|32|200.00|
|g800|hn|hb|2023-07-11|12:00|2023-07-11|19:00|32|200.00|
|g009|hn|hb|2023-07-11|08:00|2023-07-11|10:00|32|200.00|
|y9000|hn|hb|2023-07-11|03:00|2023-07-11|23:00|32|200.00|
|g15|hn|hb|2023-07-11|11:00|2023-07-11|17:00|32|200.00|
|g231|hn|hb|2023-07-11|12:00|2023-07-11|15:00|32|200.00|
|d1345|hn|hb|2023-07-11|22:14|2023-07-11|22:14|2|233.00|

#### 票据总览
|车次|发站|到站|出发日期|出发时间|到达日期|到达时间|车票剩余数量|票价|
|-----|----|----|-----------|-----|-----------|-----|----|----|
|D2023|北京|上海|2023-07-11|07:37|2023-07-11|09:32|2|250.00|
|D2231|北京|上海|2023-07-11|07:43|2023-07-11|09:23|2|251.00|
|G213|北京|上海|2023-07-11|15:55|2023-07-11|20:33|2|252.00|
|L21|北京|上海|2023-07-11|05:19|2023-07-11|08:43|2|253.00|
|T21|北京|上海|2023-07-11|11:40|2023-07-11|16:02|2|254.00|
|A380|北京|上海|2023-07-11|20:15|2023-07-11|22:14|2|255.00|
|M231|北京|上海|2023-07-11|21:01|2023-07-11|23:09|2|256.00|
|G9094|北京|上海|2023-07-11|10:49|2023-07-11|13:11|2|257.00|
|N1023|北京|上海|2023-07-11|13:47|2023-07-11|14:21|2|258.00|
|D2139|北京|上海|2023-07-11|01:39|2023-07-11|03:26|2|259.00|
|D1413|北京|上海|2023-07-11|16:43|2023-07-11|18:10|2|290.00|
|K1493|北京|上海|2023-07-11|10:35|2023-07-11|12:01|2|221.00|
|K1432|北京|上海|2023-07-11|13:17|2023-07-11|16:21|2|243.00|
|K879|北京|上海|2023-07-11|20:30|2023-07-11|21:44|2|254.00|
|Z2391|北京|上海|2023-07-11|21:14|2023-07-11|22:10|2|267.00|
|UFO|北京|上海|2023-07-11|00:00|2023-07-11|00:01|0|2686.00|
|T951|成都|北京|2023-07-27|12:10|2023-07-27|20:25|1|9.00|
|K114|长沙|上海|2023-07-31|07:40|2023-07-31|14:15|4|6.00|
|G831|北京|广州|2023-08-03|19:25|2023-08-04|05:40|3|5.00|
|T222|上海|成都|2023-08-07|13:00|2023-08-07|20:35|2|8.00|
|K489|广州|长沙|2023-08-11|08:20|2023-08-11|15:55|5|7.00|
|G726|成都|北京|2023-08-15|17:50|2023-08-16|03:05|1|9.00|
|T623|北京|上海|2023-08-19|12:30|2023-08-19|18:45|4|6.00|
|K875|上海|广州|2023-08-23|07:05|2023-08-23|14:40|3|5.00|
|G512|广州|成都|2023-08-27|16:40|2023-08-27|23:55|2|8.00|
|T759|长沙|北京|2023-08-31|11:20|2023-08-31|19:35|5|7.00|
|K987|北京|成都|2023-09-04|14:50|2023-09-04|23:15|4|8.00|
|G654|上海|长沙|2023-09-08|09:15|2023-09-08|16:45|2|6.00|
|T321|广州|北京|2023-09-12|18:30|2023-09-13|05:05|5|9.00|
|T763|北京|上海|2023-10-30|15:45|2023-10-30|22:55|1|5.00|
|K982|上海|广州|2023-11-03|12:15|2023-11-03|19:40|4|8.00|
|G543|广州|成都|2023-11-07|17:30|2023-11-08|01:05|2|6.00|
|T321|长沙|北京|2023-11-11|10:50|2023-11-11|18:25|5|9.00|
|K876|北京|上海|2023-11-15|08:05|2023-11-15|15:35|3|7.00|
|G654|上海|长沙|2023-11-19|12:40|2023-11-19|20:10|1|5.00|
|K987|北京|成都|2023-11-23|14:50|2023-11-23|23:15|4|8.00|
|G654|上海|长沙|2023-11-27|09:15|2023-11-27|16:45|2|6.00|
|T321|广州|北京|2023-12-01|18:30|2023-12-02|05:05|5|9.00|
|K876|成都|上海|2023-12-05|12:40|2023-12-05|19:55|3|7.00|
|G543|长沙|广州|2023-12-09|07:55|2023-12-09|15:25|1|5.00|
|T210|北京|上海|2023-12-13|16:10|2023-12-13|22:30|4|8.00|
|K763|上海|成都|2023-12-17|13:45|2023-12-17|21:15|2|6.00|
|G982|广州|北京|2023-12-21|18:20|2023-12-22|03:05|5|9.00|
|T543|成都|长沙|2023-12-25|10:35|2023-12-25|18:10|3|7.00|
|K321|长沙|上海|2023-12-29|06:50|2023-12-29|14:25|1|5.00|
|G654|北京|广州|2024-01-02|19:10|2024-01-03|04:45|4|8.00|
|T876|上海|成都|2024-01-06|15:25|2024-01-06|22:55|2|6.00|
|K543|广州|长沙|2024-01-10|11:35|2024-01-10|19:05|5|9.00|
|G210|成都|北京|2024-01-14|21:00|2024-01-15|05:35|3|7.00|
|T763|北京|上海|2024-01-18|15:45|2024-01-18|22:55|1|5.00|
|K982|上海|广州|2024-01-22|12:15|2024-01-22|19:40|4|8.00|
|G543|广州|成都|2024-01-26|17:30|2024-01-27|01:05|2|6.00|
|T321|长沙|北京|2024-01-30|10:50|2024-01-30|18:25|5|9.00|
|K210|北京|上海|2024-02-03|09:15|2024-02-03|15:40|3|7.00|
|T654|广州|长沙|2024-02-11|08:05|2024-02-11|15:30|4|8.00|
|K543|长沙|上海|2024-02-15|16:30|2024-02-15|23:55|2|6.00|
|G321|北京|广州|2024-02-19|19:50|2024-02-20|03:15|5|9.00|
|T982|上海|成都|2024-02-23|12:55|2024-02-23|20:20|3|7.00|
|K763|成都|长沙|2024-02-27|07:30|2024-02-27|14:55|1|5.00|
|G210|长沙|广州|2024-03-02|10:45|2024-03-02|18:10|4|8.00|
|T876|广州|北京|2024-03-06|16:20|2024-03-07|01:45|2|6.00|
|K543|北京|上海|2024-03-10|19:35|2024-03-11|02:50|5|9.00|
|G654|上海|成都|2024-03-14|13:20|2024-03-14|20:45|3|7.00|
|T321|广州|长沙|2024-03-18|08:45|2024-03-18|16:10|1|5.00|
|K876|长沙|上海|2024-03-22|17:00|2024-03-22|00:25|4|8.00|
|G543|北京|广州|2024-03-26|09:35|2024-03-26|17:00|2|6.00|
|T210|上海|成都|2024-03-30|14:00|2024-03-30|21:25|5|9.00|
|K763|成都|长沙|2024-04-03|11:25|2024-04-03|18:50|3|7.00|
|G982|长沙|北京|2024-04-07|10:40|2024-04-07|18:05|1|5.00|
|T543|广州|上海|2024-04-11|17:05|2024-04-12|00:20|4|8.00|
|K321|上海|成都|2024-04-15|14:30|2024-04-15|21:55|2|6.00|
|G654|北京|广州|2024-04-19|12:15|2024-04-19|19:40|5|9.00|
|T876|上海|长沙|2024-04-23|08:50|2024-04-23|16:15|3|7.00|
|K543|广州|北京|2024-04-27|19:05|2024-04-28|02:30|1|5.00|
|G210|成都|上海|2024-05-01|09:20|2024-05-01|16:45|4|8.00|
|T763|北京|长沙|2024-05-05|16:35|2024-05-06|00:00|2|6.00|
|K982|上海|广州|2024-05-09|12:40|2024-05-09|20:05|5|9.00|
|G543|广州|成都|2024-05-13|17:55|2024-05-14|01:20|3|7.00|
|T321|长沙|北京|2024-05-17|11:10|2024-05-17|18:35|1|5.00|
|K876|北京|上海|2024-05-21|19:35|2024-05-22|02:50|4|8.00|
|G654|上海|成都|2024-05-25|12:20|2024-05-25|19:45|2|6.00|
|T543|广州|长沙|2024-05-29|08:35|2024-05-29|16:00|5|9.00|
|K210|成都|上海|2024-06-02|14:00|2024-06-02|21:25|3|7.00|
|G876|长沙|广州|2024-06-06|10:15|2024-06-06|17:40|1|5.00|
|T654|北京|成都|2024-06-10|18:30|2024-06-11|01:55|4|8.00|
|K543|上海|长沙|2024-06-14|14:50|2024-06-14|22:15|2|6.00|
|G321|广州|北京|2024-06-18|20:15|2024-06-19|03:40|5|9.00|
|T982|成都|上海|2024-06-22|13:40|2024-06-22|21:05|3|7.00|
|K763|北京|广州|2024-06-26|10:55|2024-06-26|18:20|1|5.00|
|G210|上海|长沙|2024-06-30|09:10|2024-06-30|16:35|4|8.00|
|T876|广州|成都|2024-07-04|15:35|2024-07-04|22:55|2|6.00|
|K543|长沙|北京|2024-07-08|07:50|2024-07-08|15:10|5|9.00|
|G654|北京|上海|2024-07-12|19:10|2024-07-13|02:30|3|7.00|
|T321|上海|成都|2024-07-16|14:35|2024-07-16|21:55|1|5.00|
|K876|广州|长沙|2024-07-20|09:45|2024-07-20|17:05|4|8.00|
|G543|成都|北京|2024-07-24|19:00|2024-07-25|02:20|2|6.00|
|T210|长沙|上海|2024-07-28|14:25|2024-07-28|21:45|5|9.00|
|K763|上海|广州|2024-08-01|11:40|2024-08-01|19:00|3|7.00|
|G982|广州|成都|2024-08-05|17:55|2024-08-06|01:15|1|5.00|
|T543|北京|长沙|2024-08-09|09:10|2024-08-09|16:30|4|8.00|
|K321|上海|北京|2024-08-13|19:35|2024-08-14|02:55|2|6.00|
|G654|成都|上海|2024-08-17|12:50|2024-08-17|20:10|5|9.00|
|T876|长沙|广州|2024-08-21|08:55|2024-08-21|16:15|3|7.00|
|K543|广州|北京|2024-08-25|19:10|2024-08-26|02:30|1|5.00|
|G210|上海|成都|2024-08-29|13:35|2024-08-29|20:55|4|8.00|
|T763|北京|长沙|2024-09-02|18:00|2024-09-03|01:20|2|6.00|
|K982|上海|广州|2024-09-06|15:15|2024-09-06|22:35|5|9.00|
|G543|广州|成都|2024-09-10|17:20|2024-09-11|00:40|3|7.00|
|T321|长沙|北京|2024-09-14|10:35|2024-09-14|17:55|1|5.00|
|K876|北京|上海|2024-09-18|19:00|2024-09-19|02:20|4|8.00|
|G654|上海|成都|2024-09-22|12:15|2024-09-22|19:35|2|6.00|
|T543|广州|长沙|2024-09-26|08:30|2024-09-26|15:50|5|9.00|
|K210|成都|上海|2024-09-30|13:45|2024-09-30|21:05|3|7.00|
|G876|长沙|广州|2024-10-04|09:00|2024-10-04|16:20|1|5.00|
|T654|北京|成都|2024-10-08|18:15|2024-10-09|01:35|4|8.00|
|K543|上海|长沙|2024-10-12|14:30|2024-10-12|21:50|2|6.00|
|G321|广州|北京|2024-10-16|19:45|2024-10-17|03:05|5|9.00|
|T982|成都|上海|2024-10-20|13:00|2024-10-20|20:20|3|7.00|
|K763|北京|广州|2024-10-24|10:15|2024-10-24|17:35|1|5.00|
|G210|上海|长沙|2024-10-28|15:30|2024-10-28|22:50|4|8.00|
|T876|长沙|成都|2024-11-01|08:45|2024-11-01|16:05|2|6.00|
|K543|广州|北京|2024-11-05|19:00|2024-11-06|02:20|5|9.00|
|G654|成都|上海|2024-11-09|12:15|2024-11-09|19:35|3|7.00|
|T321|北京|长沙|2024-11-13|17:30|2024-11-13|00:50|1|5.00|
|K876|上海|广州|2024-11-17|09:45|2024-11-17|17:05|4|8.00|
|G543|长沙|成都|2024-11-21|18:00|2024-11-22|01:20|2|6.00|
|T210|广州|上海|2024-11-25|12:15|2024-11-25|19:35|5|9.00|
|K763|成都|长沙|2024-11-29|09:30|2024-11-29|16:50|3|7.00|
|G982|长沙|北京|2024-12-03|16:45|2024-12-04|00:05|1|5.00|
|T543|上海|长沙|2024-12-07|08:00|2024-12-07|15:20|4|8.00|
|K321|广州|北京|2024-12-11|17:15|2024-12-11|00:35|2|6.00|
|G654|上海|成都|2024-12-15|10:30|2024-12-15|17:50|5|9.00|
|T876|长沙|广州|2024-12-19|07:45|2024-12-19|15:05|3|7.00|
|K543|北京|上海|2024-12-23|19:00|2024-12-24|02:20|1|5.00|
|G210|上海|成都|2024-12-27|13:15|2024-12-27|20:35|4|8.00|
|T763|广州|长沙|2024-12-31|09:30|2024-12-31|16:50|2|6.00|
|T543|成都|长沙|2025-01-04|08:00|2025-01-04|15:20|5|9.00|
|G654|北京|上海|2025-01-12|10:30|2025-01-12|17:50|1|5.00|
|T876|上海|成都|2025-01-16|07:45|2025-01-16|15:05|4|8.00|
|K543|长沙|北京|2025-01-20|19:00|2025-01-21|02:20|2|6.00|
|G210|广州|上海|2025-01-24|13:15|2025-01-24|20:35|5|9.00|
|T763|成都|长沙|2025-01-28|09:30|2025-01-28|16:50|3|7.00|
|K876|上海|广州|2025-02-01|08:45|2025-02-01|16:05|1|5.00|
|G543|长沙|成都|2025-02-05|18:00|2025-02-06|01:20|4|8.00|
|T210|北京|上海|2025-02-09|12:15|2025-02-09|19:35|2|6.00|
|K763|上海|长沙|2025-02-13|09:30|2025-02-13|16:50|5|9.00|
|G982|长沙|北京|2025-02-17|16:45|2025-02-18|00:05|3|7.00|
|T543|成都|长沙|2025-02-21|08:00|2025-02-21|15:20|1|5.00|
|K321|长沙|广州|2025-02-25|17:15|2025-02-25|00:35|4|8.00|
|G654|北京|上海|2025-03-01|10:30|2025-03-01|17:50|2|6.00|
|T876|上海|成都|2025-03-05|07:45|2025-03-05|15:05|5|9.00|
|G210|广州|上海|2025-03-13|13:15|2025-03-13|20:35|1|5.00|
|T763|成都|长沙|2025-03-17|09:30|2025-03-17|16:50|4|8.00|
|K876|上海|广州|2025-03-21|08:45|2025-03-21|16:05|2|6.00|
|G543|长沙|成都|2025-03-25|18:00|2025-03-26|01:20|5|9.00|
|T210|北京|上海|2025-03-29|12:15|2025-03-29|19:35|3|7.00|
|K763|上海|长沙|2025-04-02|09:30|2025-04-02|16:50|1|5.00|
|G982|长沙|北京|2025-04-06|16:45|2025-04-07|00:05|4|8.00|
|T543|成都|长沙|2025-04-10|08:00|2025-04-10|15:20|2|6.00|
|K321|长沙|广州|2025-04-14|17:15|2025-04-14|00:35|5|9.00|
|G654|北京|上海|2025-04-18|10:30|2025-04-18|17:50|3|7.00|
|T876|上海|成都|2025-04-22|07:45|2025-04-22|15:05|1|5.00|
|K543|长沙|北京|2025-04-26|19:00|2025-04-27|02:20|4|8.00|
|G210|广州|上海|2025-04-30|13:15|2025-04-30|20:35|2|6.00|
|T763|成都|长沙|2025-05-04|09:30|2025-05-04|16:50|5|9.00|
|K876|上海|广州|2025-05-08|08:45|2025-05-08|16:05|3|7.00|
|G543|长沙|成都|2025-05-12|18:00|2025-05-13|01:20|1|5.00|
|T210|北京|上海|2025-05-16|12:15|2025-05-16|19:35|4|8.00|
|K763|上海|长沙|2025-05-20|09:30|2025-05-20|16:50|2|6.00|
|G982|长沙|北京|2025-05-24|16:45|2025-05-25|00:05|5|9.00|
|T543|成都|长沙|2025-05-28|08:00|2025-05-28|15:20|3|7.00|
|K321|长沙|广州|2025-06-01|17:15|2025-06-01|00:35|1|5.00|
|G654|北京|上海|2025-06-05|10:30|2025-06-05|17:50|4|8.00|
|T876|上海|成都|2025-06-09|07:45|2025-06-09|15:05|2|6.00|
|K543|长沙|北京|2025-06-13|19:00|2025-06-14|02:20|5|9.00|
|G210|广州|上海|2025-06-17|13:15|2025-06-17|20:35|3|7.00|
|T763|成都|长沙|2025-06-21|09:30|2025-06-21|16:50|1|5.00|
|K876|上海|广州|2025-06-25|08:45|2025-06-25|16:05|4|8.00|
|G543|长沙|成都|2025-06-29|18:00|2025-06-30|01:20|2|6.00|
|T210|北京|上海|2025-07-03|12:15|2025-07-03|19:35|5|9.00|
|K763|上海|长沙|2025-07-07|09:30|2025-07-07|16:50|3|7.00|
|G982|长沙|北京|2025-07-11|16:45|2025-07-12|00:05|1|5.00|
|T543|成都|长沙|2025-07-15|08:00|2025-07-15|15:20|4|8.00|
|K321|长沙|广州|2025-07-19|17:15|2025-07-19|00:35|2|6.00|
|G654|北京|上海|2025-07-23|10:30|2025-07-23|17:50|5|9.00|
|T876|上海|成都|2025-07-27|07:45|2025-07-27|15:05|3|7.00|
|K543|长沙|北京|2025-07-31|19:00|2025-08-01|02:20|1|5.00|
|G210|广州|上海|2025-08-04|13:15|2025-08-04|20:35|4|8.00|
|T763|成都|长沙|2025-08-08|09:30|2025-08-08|16:50|2|6.00|
|K876|上海|广州|2025-08-12|08:45|2025-08-12|16:05|5|9.00|
|G543|长沙|成都|2025-08-16|18:00|2025-08-17|01:20|3|7.00|
|T210|北京|上海|2025-08-20|12:15|2025-08-20|19:35|1|5.00|
|K763|上海|长沙|2025-08-24|09:30|2025-08-24|16:50|4|8.00|
|G982|长沙|北京|2025-08-28|16:45|2025-08-29|00:05|2|6.00|
|T543|成都|长沙|2025-09-01|08:00|2025-09-01|15:20|5|9.00|
|K321|长沙|广州|2025-09-05|17:15|2025-09-05|00:35|3|7.00|
|G654|北京|上海|2025-09-09|10:30|2025-09-09|17:50|1|5.00|
|T876|上海|成都|2025-09-13|07:45|2025-09-13|15:05|4|8.00|
|K543|长沙|北京|2025-09-17|19:00|2025-09-18|02:20|2|6.00|
|G210|广州|上海|2025-09-21|13:15|2025-09-21|20:35|5|9.00|
|T763|成都|长沙|2025-09-25|09:30|2025-09-25|16:50|3|7.00|
|K876|上海|广州|2025-09-29|08:45|2025-09-29|16:05|1|5.00|
|G543|长沙|成都|2025-10-03|18:00|2025-10-04|01:20|4|8.00|
|T210|北京|上海|2025-10-07|12:15|2025-10-07|19:35|2|6.00|
|K763|上海|长沙|2025-10-11|09:30|2025-10-11|16:50|5|9.00|
|G982|长沙|北京|2025-10-15|16:45|2025-10-16|00:05|3|7.00|
|T543|成都|长沙|2025-10-19|08:00|2025-10-19|15:20|1|5.00|
|K321|长沙|广州|2025-10-23|17:15|2025-10-23|00:35|4|8.00|
|G654|北京|上海|2025-10-27|10:30|2025-10-27|17:50|2|6.00|
|T876|上海|成都|2025-10-31|07:45|2025-10-31|15:05|5|9.00|
|K543|长沙|北京|2025-11-04|19:00|2025-11-05|02:20|3|7.00|
|G210|广州|上海|2025-11-08|13:15|2025-11-08|20:35|1|5.00|
|T763|成都|长沙|2025-11-12|09:30|2025-11-12|16:50|4|8.00|
|K876|上海|广州|2025-11-16|08:45|2025-11-16|16:05|2|6.00|
|G543|长沙|成都|2025-11-20|18:00|2025-11-21|01:20|5|9.00|
|T210|北京|上海|2025-11-24|12:15|2025-11-24|19:35|3|7.00|
|K763|上海|长沙|2025-11-28|09:30|2025-11-28|16:50|1|5.00|
|G982|长沙|北京|2025-12-02|16:45|2025-12-02|00:05|4|8.00|
|T543|成都|长沙|2025-12-06|08:00|2025-12-06|15:20|2|6.00|
|G654|北京|上海|2025-12-14|10:30|2025-12-14|17:50|3|7.00|
|T876|上海|成都|2025-12-18|07:45|2025-12-18|15:05|1|5.00|
|K543|长沙|北京|2025-12-22|19:00|2025-12-23|02:20|4|8.00|
|G210|广州|上海|2025-12-26|13:15|2025-12-26|20:35|2|6.00|
|T763|成都|长沙|2025-12-30|09:30|2025-12-30|16:50|5|9.00|
|K876|上海|广州|2026-01-03|08:45|2026-01-03|16:05|3|7.00|
|G543|长沙|成都|2026-01-07|18:00|2026-01-08|01:20|1|5.00|
|k123|hn|hb|2023-07-11|15:00|2023-07-11|16:00|32|200.00|
|g20|hn|hb|2023-07-11|10:00|2023-07-11|15:00|32|200.00|
|g099|hn|hb|2023-07-11|13:00|2023-07-11|14:00|32|200.00|
|k011|hn|hb|2023-07-11|01:00|2023-07-11|09:00|32|200.00|
|g9000|hn|hb|2023-07-11|12:00|2023-07-11|15:00|32|200.00|
|g2999|hn|hb|2023-07-11|19:00|2023-07-11|23:00|32|200.00|
|g16|hn|hb|2023-07-11|16:00|2023-07-11|20:00|32|200.00|
|g800|hn|hb|2023-07-11|12:00|2023-07-11|19:00|32|200.00|
|g009|hn|hb|2023-07-11|08:00|2023-07-11|10:00|32|200.00|
|y9000|hn|hb|2023-07-11|03:00|2023-07-11|23:00|32|200.00|
|g15|hn|hb|2023-07-11|11:00|2023-07-11|17:00|32|200.00|
|g231|hn|hb|2023-07-11|12:00|2023-07-11|15:00|32|200.00|
|d1345|hn|hb|2023-07-11|22:14|2023-07-11|22:14|2|233.00|

### 运行示例
1. 首先运行程序进入登录界面
   <img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B1.png"><br>
2. 点击注册用户并输入注册用户信息
   <img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B1.1.png"><br>
3. 输入刚才注册的用户信息并点击登录
   <img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B1.2.png">
4. 进入用户界面
   <img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B2.png">
5. 双击购买g800
   <img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B2.1.png">
6. 点击进入个人中心界面
   <img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B3.png">
7. 查询已购买票据
   <img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B4.png">
8. 双击改签返回购买界面
   <img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B5.png">
9. 双击改签选择要改的票据y9000
   <img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B6.png">
10. 再次进入个人中心界面查询
   <img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B7.png">
11. 双击退票
   <img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B8.png">
12. 返回购票界面查询
   <img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B9.png">
13. 关闭程序，再次打开时使用管理员账户
   <img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B/%E8%BF%90%E8%A1%8C%E7%A4%BA%E4%BE%8B10.png">
