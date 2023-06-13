#include "regdialog.h"
#include "ui_regdialog.h"
#include "mainwindow.h"
#include <string>
#include <user_crl.h>
#include <QPainter>
#include <QPaintEvent>

using std::string;

/**
  * @brief  绘制一个带边框的窗口
  * @param  event 当前绘制事件
  * @retval 无
  */
void RegDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
}

/**
  * @brief  默认构造函数，创建注册用户页面
  * @param  parent父级窗口
  * @retval 无
  */
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

/**
  * @brief  析构函数，用于删除注册用户窗口
  * @param  无
  * @retval 无
  */
RegDialog::~RegDialog()
{
    delete ui;
}

/**
  * @brief  用于性别选择
  * @param  无
  * @retval 男性返回1，女性返回0，默认是男性
  */
bool RegDialog::Gender_Choose()
{
    if (ui->Rd_Female->isChecked())
        return 0;
    else if (ui->Rd_Male->isChecked())
        return 1;

    //默认返回false
    return false;
}

/**
  * @brief  返回到mainwindow
  * @param  无
  * @retval 无
  */
void RegDialog::on_Btn_Back_clicked()
{
    framelessWidget * mw = new framelessWidget();
    mw->setWindowFlags(Qt::FramelessWindowHint);//设置无边框
    mw->setAttribute(Qt::WA_TranslucentBackground);//设置半透明背景
    mw->show();
    this->hide();
}

/**
  * @brief  注册用户
  * @param  无
  * @retval 无
  */
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

/**
  * @brief  鼠标按下事件处理函数
  * @param  event 鼠标事件
  * @retval 无
  */
void RegDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) // 左键按下
    {
        m_bMove = true; // 移动标志位
        reltvPos = event->pos(); // 按下瞬间获取相对窗口坐标
    }
    return QWidget::mousePressEvent(event);
}

/**
  * @brief  鼠标移动事件处理函数
  * @param  event 鼠标事件
  * @retval 无
  */
void RegDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bMove) move(event->globalPos() - reltvPos);
    return QWidget::mouseMoveEvent(event);
}

/**
  * @brief  鼠标释放事件处理函数
  * @param  event 鼠标事件
  * @retval 无
  */
void RegDialog::mouseReleaseEvent(QMouseEvent *event)
{
    m_bMove = false; // 松开后要置为false
    return QWidget::mouseReleaseEvent(event);
}
