#include "dialogaddticket.h"
#include "ui_dialogaddticket.h"

dialogaddticket::dialogaddticket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogaddticket)
{
    ui->setupUi(this);
    connect(ui->canclebtn,&QPushButton::clicked,this,&dialogaddticket::close);
    connect(ui->addbtn,&QPushButton::clicked,this,&dialogaddticket::saveclicked);
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
    QString s=ui->BtlineEdit->text();
    return s;
}

QString dialogaddticket::getet()
{
    QString s=ui->EtlineEdit->text();
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



