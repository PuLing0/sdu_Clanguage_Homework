#include "chgpddialog.h"
#include "ui_chgpddialog.h"
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
void chgpdDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
}

/**
  * @brief  默认构造函数，创建修改密码页面
  * @param  parent父级窗口
  * @retval 无
  */
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

/**
  * @brief  析构函数，用于删除修改密码窗口
  * @param  无
  * @retval 无
  */
chgpdDialog::~chgpdDialog()
{
    delete ui;
}

/**
  * @brief  返回到mainwindow
  * @param  无
  * @retval 无
  */
void chgpdDialog::on_btn_back_clicked()
{
    framelessWidget * mw = new framelessWidget();
    mw->setWindowFlags(Qt::FramelessWindowHint);//设置无边框
    mw->setAttribute(Qt::WA_TranslucentBackground);//设置半透明背景
    mw->show();
    this->hide();
}

/**
  * @brief  确认修改密码
  * @param  无
  * @retval 无
  */
void chgpdDialog::on_btn_chg_clicked()
{
    QString account = ui->L_Acount->text();
    QString oldpsd = ui->L_OldPassword->text();
    QString newpsd = ui->L_NewPassword->text();
    QString renewpsd = ui->L_ReNewPassword->text();
    user_Crl * uc = new user_Crl();
    uc->ChgUser(account , oldpsd , newpsd , renewpsd);
}

/**
  * @brief  鼠标按下事件处理函数
  * @param  event 鼠标事件
  * @retval 无
  */
void chgpdDialog::mousePressEvent(QMouseEvent *event)
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
void chgpdDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bMove) move(event->globalPos() - reltvPos);
    return QWidget::mouseMoveEvent(event);
}


/**
  * @brief  鼠标释放事件处理函数
  * @param  event 鼠标事件
  * @retval 无
  */
void chgpdDialog::mouseReleaseEvent(QMouseEvent *event)
{
    m_bMove = false; // 松开后要置为false
    return QWidget::mouseReleaseEvent(event);
}
