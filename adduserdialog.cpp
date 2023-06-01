#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include<QString>
#include"user.h"
adduserdialog::adduserdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adduserdialog)
{
    ui->setupUi(this);
    connect(ui->BtnReg,&QPushButton::clicked,this,&adduserdialog::btnclicked);
    connect(ui->BtnBack,&QPushButton::clicked,this,&adduserdialog::hide);
}
adduserdialog::~adduserdialog()
{
    delete ui;
}
void adduserdialog::btnclicked()
{
    this->name=ui->L_Name->text();
    this->account=ui->L_Account->text();
    this->password=ui->L_pswd->text();
    this->gender=this->Gender_Choose();
    this->Over_Power=false;
    flap=1;
    this->hide();
}

//用于性别选择，其中男性返回1，女性返回0，默认是男性
bool adduserdialog::Gender_Choose()
{
    if (ui->Rd_Female->isChecked())
        return 0;
    else if (ui->Rd_Male->isChecked())
        return 1;

    //默认返回false
    return false;
}
