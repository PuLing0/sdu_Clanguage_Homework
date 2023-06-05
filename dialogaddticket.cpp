#include "dialogaddticket.h"
#include "ui_dialogaddticket.h"
#include"qtmaterialautocomplete.h"
#include"qtmaterialflatbutton.h"
#include"qtmaterialraisedbutton.h"
#include<QColor>
#include<QDateTime>
#include<QTime>
dialogaddticket::dialogaddticket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogaddticket)
{
    ui->setupUi(this);


    ui->addbtn->setBackgroundColor(QColor(0,188,212));//设置按钮颜色
    ui->canclebtn->setBackgroundColor(QColor(0,188,212));//设置按钮颜色
    connect(ui->canclebtn,&QPushButton::clicked,this,&dialogaddticket::close);//按下取消按钮关闭对话框
    connect(ui->addbtn,&QPushButton::clicked,this,&dialogaddticket::saveclicked);//按下添加按钮触发Saveclicked
    ui->BtdateTimeEdit->setTime(QTime::currentTime());//设置时间选择空间显示当前时间
    ui->EtdateTimeEdit->setTime(QTime::currentTime());//设置时间选择空间显示当前时间
}


dialogaddticket::~dialogaddticket()
{
    delete ui;
}

//按下添加按钮时触发，记录添加按钮被按下，关闭对话框
void dialogaddticket::saveclicked()
{
    this->flap=1;
    this->hide();
}

//获取添加的列车的列车号
QString dialogaddticket::getid()
{
    QString s=ui->IdlineEdit->text();
    return s;
}

//获取添加列车的始发站
QString dialogaddticket::getba()
{
    QString s=ui->BalineEdit->text();
    return s;
}

//获取添加列车的终点站
QString dialogaddticket::getea()
{
    QString s=ui->EalineEdit->text();
    return s;
}

//获取添加列车的发车时间
QString dialogaddticket::getbt()
{
    QDateTime time=ui->BtdateTimeEdit->dateTime();//获取时间
    QString s=time.toString("yyyy-MM-dd hh:mm");//设置字符串格式
    return s;
}

//获取添加列车的到站时间
QString dialogaddticket::getet()
{
    QDateTime time=ui->EtdateTimeEdit->dateTime();//获取时间
    QString s=time.toString("yyyy-MM-dd hh:mm");//设置字符串格式
    return s;
}

//获取添加列车的车票数
QString dialogaddticket::getticket()
{
    QString s=ui->TicketlineEdit->text();
    return s;
}

//获取添加列车的票价
QString dialogaddticket::getprice()
{
    QString s=ui->PrlineEdit->text();
    return s;
}



