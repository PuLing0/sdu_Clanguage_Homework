#include "changeticketdialog.h"
#include "ui_changeticketdialog.h"
#include"qtmaterialautocomplete.h"
#include"qtmaterialflatbutton.h"
#include"qtmaterialraisedbutton.h"
#include<QColor>
changeticketdialog::changeticketdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeticketdialog)
{
    ui->setupUi(this);

    ui->canclebtn->setBackgroundColor(QColor(0,188,212));//设置按钮的背景颜色
    ui->changebtn->setBackgroundColor(QColor(0,188,212));//设置按钮的背景颜色
    connect(ui->canclebtn,&QPushButton::clicked,this,&changeticketdialog::close);//当取消按钮按下始，该对话框关闭
    connect(ui->changebtn,&QtMaterialRaisedButton::clicked,this,&changeticketdialog::changebtnclicked);//按下保存按钮时，激活changebtnclicked函数
}

/**
  * @brief 修改按钮按下时触发修改标记
  * @param 无
  * @retval 无
  */
void changeticketdialog::changebtnclicked()
{
    this->flap=1;//记录修改按钮被按下
    this->close();//关闭窗口
}

/**
  * @brief 获取想要修改的车次的列车号
  * @param 无
  * @retval 想要修改的车次的列车号
  */
QString changeticketdialog::getiniid()
{
    return ui->initialIdlineEdit->text();
}

/**
  * @brief 获取想要修改的车次的现在的始发站
  * @param 无
  * @retval 想要修改的车次的现在的始发站
  */
QString changeticketdialog::getiniba()
{
    return ui->initialBalineEdit->text();
}

/**
  * @brief 获取想要修改的车次的现在的终点站
  * @param 无
  * @retval 想要修改的车次的现在的终点站
  */
QString changeticketdialog::getiniea()
{
    return ui->initialEalineEdit->text();
}

/**
  * @brief 获取想要修改的车次的现在的开车时间
  * @param 无
  * @retval 想要修改的车次的现在的开车时间
  */
QString changeticketdialog::getinibt()
{
    return ui->initialBtlineEdit->text();
}

/**
  * @brief 获取想要修改的车次的现在的到站时间
  * @param 无
  * @retval 想要修改的车次的现在的到站时间
  */
QString changeticketdialog::getiniet()
{
    return ui->initialEtlineEdit->text();
}

/**
  * @brief 获取想要修改的车次的改后的始发站
  * @param 无
  * @retval 想要修改的车次的改后的始发站
  */
QString changeticketdialog::getfinba()
{
    return ui->finalBalineEdit->text();
}

/**
  * @brief 获取想要修改的车次的改后的终点站
  * @param 无
  * @retval 想要修改的车次的改后的终点站
  */
QString changeticketdialog::getfinea()
{
    return ui->finalEalineEdit->text();
}

/**
  * @brief 获取想要修改的车次的改后的开车时间
  * @param 无
  * @retval 想要修改的车次的改后的开车时间
  */
QString changeticketdialog::getfinbt()
{
    return ui->finalBtlineEdit->text();
}

/**
  * @brief 获取想要修改的车次的改后的到站时间
  * @param 无
  * @retval 想要修改的车次的改后的到站时间
  */
QString changeticketdialog::getfinet()
{
    return ui->finalEtlineEdit->text();
}

/**
  * @brief 获取想要修改的车次的改后的车票数
  * @param 无
  * @retval 想要修改的车次的改后的车票数
  */
QString changeticketdialog::getfinnumber()
{
    return ui->finalTicketlineEdit->text();
}

/**
  * @brief 获取想要修改的车次的改后的票价
  * @param 无
  * @retval 想要修改的车次的改后的票价
  */
QString changeticketdialog::getfinprice()
{
    return ui->finalPrlineEdit->text();
}

changeticketdialog::~changeticketdialog()
{
    delete ui;
}
