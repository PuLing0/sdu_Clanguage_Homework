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
    ui->addbtn->setBackgroundColor(QColor(0,188,212));
    ui->canclebtn->setBackgroundColor(QColor(0,188,212));
    // 设置按钮的样式表
    //QString styleSheet = "background-color: rgb(0, 188, 212);";  // 设置背景颜色为 RGB(0, 188, 212)
//    ui->addbtn->setStyleSheet(styleSheet);
//    ui->canclebtn->setStyleSheet(styleSheet);

    connect(ui->canclebtn,&QPushButton::clicked,this,&dialogaddticket::close);
    connect(ui->addbtn,&QPushButton::clicked,this,&dialogaddticket::saveclicked);
    ui->BtdateTimeEdit->setTime(QTime::currentTime());
    ui->EtdateTimeEdit->setTime(QTime::currentTime());
}

dialogaddticket::~dialogaddticket()
{
    delete ui;
}
void dialogaddticket::saveclicked()
{
    this->flap=1;
    this->hide();
}

QString dialogaddticket::getid()
{
    QString s=ui->IdlineEdit->text();
    return s;
}
QString dialogaddticket::getba()
{
    QString s=ui->BalineEdit->text();
    return s;
}

QString dialogaddticket::getea()
{
    QString s=ui->EalineEdit->text();
    return s;
}

QString dialogaddticket::getbt()
{
    QDateTime time=ui->BtdateTimeEdit->dateTime();
    QString s=time.toString("yyyy-MM-dd hh:mm");
    return s;
}

QString dialogaddticket::getet()
{
    QDateTime time=ui->EtdateTimeEdit->dateTime();
    QString s=time.toString("yyyy-MM-dd hh:mm");
    return s;
}

QString dialogaddticket::getticket()
{
    QString s=ui->TicketlineEdit->text();
    return s;
}
QString dialogaddticket::getprice()
{
    QString s=ui->PrlineEdit->text();
    return s;
}



