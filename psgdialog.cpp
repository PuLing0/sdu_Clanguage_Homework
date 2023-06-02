#include "psgdialog.h"
#include "ui_psgdialog.h"

PsgDialog::PsgDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PsgDialog)
{
    ui->setupUi(this);
}

PsgDialog::~PsgDialog()
{
    delete ui;
}
