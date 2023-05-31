#include "widget_user.h"
#include "ui_widget_user.h"
#include<user.h>
#include<QString>
#include<algorithm>
#include<QDate>
#include<string>
#include<QFile>
#include<QTextStream>
#include<prompt1.h>
#include<dialog1.h>

Widget_User::Widget_User(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::Widget_User),
      currentUser("213454","1243421")
{
    mode = 0;
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->textEdit_2->setText("用户名:"+currentUser.getid());
    ui->textEdit_2->setReadOnly(true);
    ui->tableWidget->setSortingEnabled(true);
    ui->listWidget->hide();
}

Widget_User::~Widget_User()
{
    delete ui;
}

void Widget_User::setUser(user t){
    currentUser = t;
    readUsertickets();
    ui->textEdit_2->setText("用户名:"+currentUser.getid());
}

void Widget_User::on_pushButton_clicked()
{
    if(!tickets.size())
        read();
    ui->tableWidget->setRowCount(0);
    check();
}

bool Widget_User::read(){
    QFile fp("..//Train//ticket.txt");
    if(!fp.open(QIODevice::ReadOnly)){
        return false;
    }
    else {
        QTextStream in(&fp);
        QString bgT, edT, bgD, edD;
        while (!in.atEnd()){
            ticket t;
            in>>t.id;
            in>>t.beginpoint;
            in>>t.endpoint;
            in>>t.beginDay;
            in>>t.begintime;
            in>>t.endDay;
            in>>t.endtime;
            in>>t.amount;
            in>>t.price;
            tickets.append(t);
        }
        ui->listWidget_2->addItem("载入文件成功");
        fp.close();
        return true;
    }
}

bool Widget_User::readUsertickets(){
    QFile fp("..//Train//" + currentUser.getid() + ".txt");
    if(!fp.open(QIODevice::ReadOnly)){
        return false;
    }
    else {
        QList<ticket> temp;
        QTextStream in(&fp);
        QString bgT, edT, bgD, edD;
        while (!in.atEnd()){
            ticket t;
            in>>t.id;
            in>>t.beginpoint;
            in>>t.endpoint;
            in>>t.beginDay;
            in>>t.begintime;
            in>>t.endDay;
            in>>t.endtime;
            t.amount = 1;
            in>>t.price;
            temp.append(t);
        }
        currentUser.setTickets(temp);
        fp.close();
        return true;
    }
}


void Widget_User::check(){
    QString b = ui->lineEdit->text();
    QString c = ui->lineEdit_2->text();
    QString d = ui->dateEdit->date().toString("yyyy-MM-dd");
    if(b == "" || c == ""){
        ui->textEdit->setText("查询失败：信息不完整");
    }        
    else{
        int i = 0;
        int row = 0, column = 0;
        while(i < tickets.size() - 1){
            if(d == tickets[i].beginDay && b == tickets[i].beginpoint && c == tickets[i].endpoint){
                ui->tableWidget->insertRow(0);
                column = 0;
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(tickets[i].id));
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(tickets[i].beginpoint));
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(tickets[i].endpoint));
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(tickets[i].begintime));
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(tickets[i].endtime));
                QString t1;
                QDate b = QDate::fromString(tickets[i].beginDay, "yyyy-MM-dd");
                QDate e = QDate::fromString(tickets[i].endDay, "yyyy-MM-dd");
                QTime bt = QTime::fromString(tickets[i].begintime, "hh:mm");
                QTime et = QTime::fromString(tickets[i].endtime, "hh:mm");
                t1 = QString::fromStdString(std::to_string(b.daysTo(e)) +"天"+ std::to_string(et.hour() - bt.hour()) +"时"+ std::to_string(et.minute() - bt.minute()) +"分");
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(t1));
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(QString::fromStdString(std::to_string(tickets[i].amount))));
                if(!mode){
                    ui->tableWidget->setItem(row, column, new QTableWidgetItem("购买"));
                }
                else{
                    ui->tableWidget->setItem(row, column, new QTableWidgetItem("改签"));
                }
                ui->tableWidget->setItem(row, ++column, new QTableWidgetItem(QString::number(tickets[i].price, 'f', 2)));
            }
            i++;
        }
        ui->textEdit->setText("查询成功");

    }
}

void Widget_User::on_tableWidget_cellDoubleClicked(int row, int column)
{
    if(column == 7){
        if(!mode){
            for (int i = 0; i < tickets.size(); i++) {
                if(tickets[i].id == ui->tableWidget->item(row, 0)->text() && tickets[i].amount){
                    prompt1* t = new prompt1;
                    t->show();
                    if(currentUser.buy(tickets[i])){
                        t->setText("购票成功");
                        tickets[i].amount--;
                    }
                    else{
                        t->setText("已购买过该票");
                    }
                }
            }
        }
        else {
            for (int i = 0; i < tickets.size(); i++) {
                if(tickets[i].id == ui->tableWidget->item(row, 0)->text() && tickets[i].amount){
                    prompt1 *t = new prompt1();
                    t->show();
                    if(currentUser.change(changingTicket, tickets[i])){
                        t->setText("改签成功");
                        tickets[i].amount--;
                        tickets[tickets.indexOf(changingTicket)].amount++;
                        mode = 0;
                        ui->listWidget->clear();
                        ui->listWidget->hide();
                    }
                    else{
                        t->setText("改了个寂寞");
                    }
                }
            }
        }
    }
}

void Widget_User::on_pushButton_3_clicked()
{
    dialog1 *t = new dialog1;
    t->setUser(currentUser);
    connect(t, SIGNAL(send(bool, ticket)), this, SLOT(get(bool, ticket)));
    if(!mode){
        t->show();
    }
    else{
        t->hide();
    }
}

void Widget_User::on_pushButton_4_clicked()
{
    save();
    close();
}

bool Widget_User::save(){
    QFile file("..//Train//" + currentUser.getid() + ".txt");
    if(file.open(QIODevice::ReadWrite|QIODevice::Text)){
        QTextStream out(&file);
        QList<ticket> t(currentUser.getTickets());
        for(auto i = t.begin(); i != t.end(); i++){
            out << i->id << " " << " " << i->beginpoint << " " << i->endpoint << " "
                << i->beginDay << " " << i->begintime << " "
                << i->endDay << " " << i->endtime << " " << QString::number(i->price, 'f', 2) << endl;
        }
        return true;
    }
    else{
        return false;
    }
}

void Widget_User::get(bool m, ticket a){
    mode = m;
    if(mode){
        changingTicket = a;
        ui->listWidget->addItem(a.id+" 正在改签中...");
        ui->listWidget->show();
    }
    else {
       changingTicket = a;
       refund(changingTicket);
    }
}

bool Widget_User::refund(ticket a){
    if(currentUser.refund(a)){
        tickets[tickets.indexOf(a)].amount++;
        prompt1 *t = new prompt1 ();
        t->setText("退票成功");
        t->show();
    }
    else{
        prompt1 *t = new prompt1 ();
        t->setText("退票失败");
        t->show();
    }
}
