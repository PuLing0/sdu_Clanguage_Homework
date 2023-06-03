#include "regdialog.h"
#include "ui_regdialog.h"
#include "mainwindow.h"
#include <string>
#include <user_crl.h>

using std::string;

//默认构造函数
RegDialog::RegDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegDialog)
{
    ui->setupUi(this);
}

//默认析构函数
RegDialog::~RegDialog()
{
    delete ui;
}

//用于性别选择，其中男性返回1，女性返回0，默认是男性
bool RegDialog::Gender_Choose()
{
    if (ui->Rd_Female->isChecked())
        return 0;
    else if (ui->Rd_Male->isChecked())
        return 1;

    //默认返回false
    return false;
}

//返回mainwindow
void RegDialog::on_Btn_Back_clicked()
{
    framelessWidget * mw = new framelessWidget();
    mw->setWindowFlags(Qt::FramelessWindowHint);//设置无边框
    mw->setAttribute(Qt::WA_TranslucentBackground);//设置半透明背景
    mw->show();
    this->hide();
}

//注册用户
void RegDialog::on_Btn_Reg_clicked()
{
    QString name = ui->L_Name->text();
    QString account = ui->L_Account->text();
    bool gender = Gender_Choose();
    QString password = ui->L_pswd->text();
    user_Crl* uc = new user_Crl();
    uc->AddUser(account , password , gender , name , 0 );
    ui->L_Name->clear();
    ui->L_Account->clear();
    ui->L_pswd->clear();
}
