#include "opdialog.h"
#include "ui_opdialog.h"

OPDialog::OPDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OPDialog)
{
    ui->setupUi(this);
}

OPDialog::~OPDialog()
{
    delete ui;
}
