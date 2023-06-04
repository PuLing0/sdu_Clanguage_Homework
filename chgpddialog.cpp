#include "chgpddialog.h"
#include "ui_chgpddialog.h"
#include "mainwindow.h"
#include <string>
#include <user_crl.h>

using std::string;

chgpdDialog::chgpdDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chgpdDialog)
{
    ui->setupUi(this);

    //设置背景白色
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}

chgpdDialog::~chgpdDialog()
{
    delete ui;
}

// 返回到mainwindow
void chgpdDialog::on_btn_back_clicked()
{
    framelessWidget * mw = new framelessWidget();
    mw->setWindowFlags(Qt::FramelessWindowHint);//设置无边框
    mw->setAttribute(Qt::WA_TranslucentBackground);//设置半透明背景
    mw->show();
    this->hide();
}

// 确认修改密码
void chgpdDialog::on_btn_chg_clicked()
{
    QString account = ui->L_Acount->text();
    QString oldpsd = ui->L_OldPassword->text();
    QString newpsd = ui->L_NewPassword->text();
    QString renewpsd = ui->L_ReNewPassword->text();
    user_Crl * uc = new user_Crl();
    uc->ChgUser(account , oldpsd , newpsd , renewpsd);
}

