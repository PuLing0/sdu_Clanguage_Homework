#include "prompt1.h"
#include "ui_prompt1.h"

prompt1::prompt1(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::prompt1)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
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
    ui->textEdit->setText(a);
}
