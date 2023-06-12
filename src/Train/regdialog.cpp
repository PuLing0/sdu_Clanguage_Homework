#include "regdialog.h"
#include "ui_regdialog.h"
#include "mainwindow.h"
#include <string>
#include <user_crl.h>
#include <QPainter>
#include <QPaintEvent>

using std::string;


void RegDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
}

//默认构造函数
RegDialog::RegDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegDialog)
{
    ui->setupUi(this);

    //设置背景白色
    setStyleSheet("background-color: white;");

    m_bMove = false;
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint |Qt::WindowStaysOnTopHint);

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

//鼠标按下事件处理函数
void RegDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) // 左键按下
    {
        m_bMove = true; // 移动标志位
        reltvPos = event->pos(); // 按下瞬间获取相对窗口坐标
    }
    return QWidget::mousePressEvent(event);
}

//鼠标移动事件处理函数
void RegDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bMove) move(event->globalPos() - reltvPos);
    return QWidget::mouseMoveEvent(event);
}

//鼠标释放事件处理函数
void RegDialog::mouseReleaseEvent(QMouseEvent *event)
{
    m_bMove = false; // 松开后要置为false
    return QWidget::mouseReleaseEvent(event);
}
