#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include<QString>
#include"user.h"
#include"qtmaterialautocomplete.h"
#include"qtmaterialflatbutton.h"
#include"qtmaterialraisedbutton.h"
#include<QColor>
adduserdialog::adduserdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adduserdialog)
{
    ui->setupUi(this);

    ui->BtnReg->setBackgroundColor(QColor(0,188,212));//设置注册按钮的背景颜色
    ui->BtnBack->setBackgroundColor(QColor(0,188,212));//设置取消按钮的背景颜色

    connect(ui->BtnReg,&QPushButton::clicked,this,&adduserdialog::btnclicked);//按下注册按钮触发btnclicked函数
    connect(ui->BtnBack,&QPushButton::clicked,this,&adduserdialog::hide);//按下取消按钮该对话框关闭
}

//析构函数
adduserdialog::~adduserdialog()
{
    delete ui;
}

/**
  * @brief 当注册按钮被按下时触发，用于获取注册账户的信息
  * @param 无
  * @retval 无
  */
void adduserdialog::btnclicked()
{

    this->name=ui->L_Name->text();//获取用户名
    this->account=ui->L_Account->text();//获取账号
    this->password=ui->L_pswd->text();//获取密码
    this->gender=this->Gender_Choose();//获取性别
    this->Over_Power=false;//获取权限，默认为用户权限
    flap=1;//记录注册按钮被按下了
    this->hide();//关闭对话框
}

/**
  * @brief 用于性别选择，其中男性返回1，女性返回0，默认是男性
  * @param 无
  * @retval 用户性别
  */
bool adduserdialog::Gender_Choose()
{
    if (ui->Rd_Female->isChecked())
        return 0;
    else if (ui->Rd_Male->isChecked())
        return 1;

    //默认返回false
    return false;
}
