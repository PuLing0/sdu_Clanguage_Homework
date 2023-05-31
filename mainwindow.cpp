#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regdialog.h"
#include <QLineEdit>
#include "chgpddialog.h"
#include "user_crl.h"
#include "logindialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//登录按钮
void MainWindow::on_btn_login_clicked()
{
    LoginDialog *Log = new LoginDialog();
    QString account = ui->L_Ac->text();
    QString password = ui->L_Psd->text();
    if (Log->LoginUser(account , password))
    {
        //如果登录成功，将主页面隐藏
        this->hide();
    }
    //登录不成功重新输入,将输入栏清空
    else
    {
        ui->L_Ac->clear();
        ui->L_Psd->clear();
    }
}

//注册按钮
void MainWindow::on_btn_reg_clicked()
{
    RegDialog *reg = new RegDialog();
    reg->show();
    this->hide();
}

//修改密码按钮
void MainWindow::on_btn_chg_clicked()
{
    chgpdDialog *chg = new chgpdDialog();
    chg->show();
    this->hide();
}

//显示密码
void MainWindow::on_checkBox_clicked(bool checked)
{
    if (checked)//判断显示密码按钮是否打开（默认打开）
    {
        ui->L_Psd->setEchoMode(QLineEdit::Normal);//显示密码
    }
    else
    {
        ui->L_Psd->setEchoMode(QLineEdit::Password);//隐藏密码
    }
}

