#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include<QString>
adduserdialog::adduserdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adduserdialog)
{
    ui->setupUi(this);
    connect(ui->canclebtn,&QPushButton::clicked,this,&adduserdialog::close);
    connect(ui->savebtn,&QPushButton::clicked,this,&adduserdialog::close);
}

adduserdialog::~adduserdialog()
{
    delete ui;
}
QString adduserdialog::getid()
{
    return ui->IdlineEdit->text();
}
QString adduserdialog::getname()
{
    return ui->NamelineEdit->text();
}

QString adduserdialog::getpw()
{
    return ui->PwlineEdit->text();
}

bool adduserdialog::isaddclicked()
{
    return ui->savebtn->isDown();
}
