#include "messagebox1.h"
#include "ui_messagebox1.h"

messagebox::messagebox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::messagebox)
{
    ui->setupUi(this);
}

messagebox::~messagebox()
{
    delete ui;
}
