#include "dialog1.h"
#include "ui_dialog1.h"
#include"prompt1.h"
#include"user.h"
#include <QString>

dialog1::dialog1(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::dialog1),
    currentUser("153724521", "1245647")
{
    ui->setupUi(this);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->hide();
}

dialog1::~dialog1()
{
    delete ui;
}

void dialog1::setUser(user t){
    currentUser = t;
    tickets = t.getTickets();
    ui->textEdit_2->setText("用户名：" + currentUser.getid());
}

void dialog1::on_tableWidget_2_cellDoubleClicked(int row, int column)
{
    if(column == 6){
        ticket t;
        for (int i = 0; i < tickets.size(); i++) {
            if(tickets[i].id == ui->tableWidget_2->item(row, 0)->text()){
                bool mode = 1;
                t = tickets[i];
                emit send(mode, tickets[i]);
                this->hide();
            }
        }
    }
    else if(column == 7){
        ticket t;
        for (int i = 0; i < tickets.size(); i++) {
            if(tickets[i].id == ui->tableWidget_2->item(row, 0)->text()){
                bool mode = 0;
                t = tickets[i];
                emit send(mode, tickets[i]);
                tickets.removeOne(t);
            }
        }
    }
}

void dialog1::on_pushButton_clicked()
{
    ui->tableWidget_2->show();
    ui->tableWidget_2->clearContents();
    int i = 0, row = 0, column = 0;
    while(i < tickets.size()){
            ui->tableWidget_2->insertRow(0);
            column = 0;
            ui->tableWidget_2->setItem(row, column++, new QTableWidgetItem(tickets[i].id));
            ui->tableWidget_2->setItem(row, column++, new QTableWidgetItem(tickets[i].beginpoint));
            ui->tableWidget_2->setItem(row, column++, new QTableWidgetItem(tickets[i].endpoint));
            ui->tableWidget_2->setItem(row, column++, new QTableWidgetItem(tickets[i].bgT.toString("hh:mm")));
            ui->tableWidget_2->setItem(row, column++, new QTableWidgetItem(tickets[i].edT.toString("hh:mm")));
            QString t1;
            t1 = QString::fromStdString(std::to_string(tickets[i].bgD.daysTo(tickets[i].edD)) +"天"+ std::to_string(tickets[i].edT.hour() - tickets[i].bgT.hour()) +"时"+ std::to_string(tickets[i].edT.minute() - tickets[i].bgT.minute()) +"分");
            ui->tableWidget_2->setItem(row, column++, new QTableWidgetItem(t1));
            ui->tableWidget_2->setItem(row, column++, new QTableWidgetItem("改签"));
            ui->tableWidget_2->setItem(row, column, new QTableWidgetItem("退票"));
            i++;
    }
}

void dialog1::on_pushButton_2_clicked()
{
    this->close();
}
