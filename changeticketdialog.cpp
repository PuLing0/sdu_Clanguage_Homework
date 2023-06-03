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
    ui->canclebtn->setBackgroundColor(QColor(0,188,212));
    ui->changebtn->setBackgroundColor(QColor(0,188,212));
    connect(ui->canclebtn,&QPushButton::clicked,this,&changeticketdialog::close);
}
void changeticketdialog::on_changebtn_clicked()
{
    this->hide();
    flap=1;
}

QString changeticketdialog::getiniid()
{
    return ui->initialIdlineEdit->text();
}

QString changeticketdialog::getiniba()
{
    return ui->initialBalineEdit->text();
}

QString changeticketdialog::getiniea()
{
    return ui->initialEalineEdit->text();
}

QString changeticketdialog::getinibt()
{
    return ui->initialBtlineEdit->text();
}

QString changeticketdialog::getiniet()
{
    return ui->initialEtlineEdit->text();
}

QString changeticketdialog::getfinba()
{
    return ui->finalBalineEdit->text();
}

QString changeticketdialog::getfinea()
{
    return ui->finalEalineEdit->text();
}

QString changeticketdialog::getfinbt()
{
    return ui->finalBtlineEdit->text();
}

QString changeticketdialog::getfinet()
{
    return ui->finalEtlineEdit->text();
}

QString changeticketdialog::getfinnumber()
{
    return ui->finalTicketlineEdit->text();
}

QString changeticketdialog::getfinprice()
{
    return ui->finalPrlineEdit->text();
}

changeticketdialog::~changeticketdialog()
{
    delete ui;
}
