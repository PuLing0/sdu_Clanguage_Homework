#include "chgpddialog.h"
#include "ui_chgpddialog.h"
#include "mainwindow.h"
#include <string>
#include <user_crl.h>
#include <QPainter>
#include <QPaintEvent>

using std::string;

void chgpdDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
}

chgpdDialog::chgpdDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chgpdDialog)
{
    ui->setupUi(this);

    //设置背景白色
    setStyleSheet("background-color: white;");


    m_bMove = false;
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint |Qt::WindowStaysOnTopHint);
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

// 鼠标按下事件处理函数
void chgpdDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) // 左键按下
    {
        m_bMove = true; // 移动标志位
        reltvPos = event->pos(); // 按下瞬间获取相对窗口坐标
    }
    return QWidget::mousePressEvent(event);
}

// 鼠标移动事件处理函数
void chgpdDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bMove) move(event->globalPos() - reltvPos);
    return QWidget::mouseMoveEvent(event);
}

// 鼠标释放事件处理函数
void chgpdDialog::mouseReleaseEvent(QMouseEvent *event)
{
    m_bMove = false; // 松开后要置为false
    return QWidget::mouseReleaseEvent(event);
}
