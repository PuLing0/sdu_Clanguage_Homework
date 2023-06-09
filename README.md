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
    - [用户界面开发](#用户界面开发-陈硕成)
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
class Widget
{
public:
    ~Widget();

    //将信息读入列表中
    void loadingticketdata();
    void loadinguserdata();
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

···
chgdialog.cpp
void chgpdDialog::on_btn_back_clicked():// 返回到mainwindow
    framelessWidget::framelessWidget();
void chgpdDialog::on_btn_chg_clicked():// 确认修改密码
    bool user_Crl::ChgUser(QString ac , QString oldpd , QString newpd, QString renewpd); 
···

```
mainwindow.cpp
void on_btn_login_clicked();//登录按钮
    bool LoginDialog::LoginUser(QString account, QString password);
void on_btn_reg_clicked();//注册按钮
    void RegDialog::paintEvent(QPaintEvent *event);
void on_btn_chg_clicked();//修改密码按钮
    chgpdDialog::chgpdDialog(QWidget *parent);
```

```
regdialog.cpp
void on_Btn_Back_clicked();//返回mainwindow
    framelessWidget::framelessWidget();
void on_Btn_Reg_clicked();//注册用户
    bool user_Crl::AddUser(QString ac, QString psd, bool gd, QString nm, bool op);
```

### 关键算法

### 程序亮点

## 总结

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
> 收获：在完成本次大作业的过程中，我熟悉了Qt的基本框架和模块,进一步掌握了C++编程技巧，学会了如何使用Qt Creator进行开发，特别是学会了ui界面的搭建，提高了自己解决实际问题能力。<br>
> 在撰写实验报告和README文档的过程中，我第一次接触了md文档的书写方法，更加具体的了解了一个较为正规的程序所应该具有的各项细节。学习了流程图，层次图，数据流图的绘制流程，帮助我更好地理解软件层次，从而更好地设计和实现软件。<br>
> 想法：完成大作业的过程对于我来说应该是一个宝贵的财富。事实上完成大作业花费了我大量的时间和精力，同时也要克服许多困难和挑战。可以说经过了c语言和c++语言的学习，完成想要的功能并不困难。但是对于刚刚接触Qt的我来说，有太多的新知识需要去学习，去适应，去应用，经过了很长的磨合期，我才堪堪掌握Qt中各种功能的使用。但这不正是学习一项新知识该有的过程，我想这也是以后学习，工作时时常会遇到的情况，这给我打下了良好的思想基础。同时，在完成这次大作业的过程中，我也逐步的适应了团队开发的模式，学会在团队中交流，发表意见，提供想法，和队员协调各项事宜，共同完成程序的开发，测试。并且，我也学会了从不同角度审视一个软件。要考虑软件的美观性，实用性，尽可能的让软件适合更多的人使用，这给了我在程序设计方面很好的启发。总之，我十分感恩这次c语言程序设计大作业。

## 附录
### 可使用用户列表
### 可查询票据记录
### 运行示例
