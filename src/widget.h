#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QString>
#include<QList>
#include<ticket.h>
#include<user.h>
#include<QMenu>
#include"dialogaddticket.h"
#include"changeticketdialog.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
friend class dialogaddticket;
friend class changeticketdialog;
public:
    explicit Widget(QWidget *parent = 0);
    //将信息读入列表中
    void loadingdata();
    //将列车信息显示在表格中
    void setticketdata(const QList<ticket>&);
    //将用户信息显示在表格中
    void setuserdata(const QList<user>&);
    ~Widget();
public slots:
    //添加用户信息
    void on_adduserButton_clicked();
    //添加车次信息
    void on_addticketButton_clicked();
    //保存修改
    void on_saveBtn_clicked();
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
    //点击用户信息列表
    void on_userList_clicked();
    //点击修改列车信息是触发
    void on_changeticketbtn_clicked();
private:
    Ui::Widget *ui;
    QList<ticket> ticketlist;//车票信息列表
    QList<user> userlist;//用户信息列表
    //删除信息时用到的事件
    QMenu *RightClick;        //右键点击
    QAction *deleteAction;    //删除事件
    int iDeletcRow;

    //

};

#endif // WIDGET_H
