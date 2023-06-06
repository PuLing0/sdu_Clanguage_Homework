#ifndef WIDGET_USER_H
#define WIDGET_USER_H

#include <QWidget>
#include "ticket.h"
#include"user.h"
#include<QCloseEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget_User; }
QT_END_NAMESPACE

class Widget_User : public QWidget
{
    Q_OBJECT

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
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::Widget_User *ui;
    QList<ticket> tickets; //所有票据
    user currentUser; //当前用户
    bool mode; //当前状态
    ticket changingTicket; //正在操作的票据
};
#endif // WIDGET_USER_H
