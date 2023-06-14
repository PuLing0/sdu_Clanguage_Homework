#include "prompt1.h"
#include "ui_prompt1.h"

prompt1::prompt1(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::prompt1)
{
    //提示框初始化
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true); //设置文字不可被编辑
    setWindowFlags(this->windowFlags() |Qt::Dialog);
    setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体
}

prompt1::~prompt1()
{
    delete ui;
}

/**
  * @brief 确定按钮
  * @param 无
  * @retval 无
  */
void prompt1::on_pushButton_clicked()
{
    /*确定按钮*/
    this->close();
}

/**
  * @brief 设置提示框文本
  * @param 所设置文本
  * @retval 无
  */
void prompt1::setText(QString a){
    /*设置提示框文本*/
    ui->textEdit->setText(a);
}
