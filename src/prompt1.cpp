#include "prompt1.h"
#include "ui_prompt1.h"

prompt1::prompt1(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::prompt1)
{
    //提示框初始化
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true); //设置文字不可被编辑
}

prompt1::~prompt1()
{
    delete ui;
}

void prompt1::on_pushButton_clicked()
{
    this->close();
}

void prompt1::setText(QString a){
    /*设置提示框文本*/
    ui->textEdit->setText(a);
}
