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
}

Widget_User::~Widget_User()
{
    delete ui;
}


void Widget_User::on_pushButton_clicked()
{
    if(!tickets.size()){
        read();
    }
    ui->tableWidget->setRowCount(0);
    check();
}

bool Widget_User::read(){
    QFile fp("C://Users//153724521//Documents//untitled1//ticket.txt");
    if(!fp.open(QIODevice::ReadOnly)){
        return false;
    }
    else {
        ui->listWidget_2->addItem("载入文件中...");
        QTextStream in(&fp);
        QString bgT, edT, bgD, edD;
        while (!in.atEnd()){
            ticket t;
            in>>t.id;
            in>>t.beginpoint;
            in>>t.endpoint;
            in>>bgD;
            t.bgD = QDate::fromString(bgD, "yyyy-MM-dd");
            in>>bgT;
            t.bgT = QTime::fromString(bgT, "hh:mm");
            in>>edD;
            t.edD = QDate::fromString(edD, "yyyy-MM-dd");
            in>>edT;
            t.edT = QTime::fromString(edT, "hh:mm");
            in>>t.amount;
            tickets.append(t);
        }
        ui->listWidget_2->addItem("载入文件成功");
        fp.close();
        return true;
    }
}


void Widget_User::check(){
    QString b = ui->lineEdit->text();
    QString c = ui->lineEdit_2->text();
    QDate d = ui->dateEdit->date();
    if(b == "" || c == ""){
        ui->textEdit->setText("查询失败：信息不完整");
    }        
    else{
        int i = 0;
        int row = 0, column = 0;
        while(i < tickets.size() - 1){
            if(d == tickets[i].bgD && b == tickets[i].beginpoint && c == tickets[i].endpoint){
                ui->tableWidget->insertRow(0);
                column = 0;
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(tickets[i].id));
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(tickets[i].beginpoint));
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(tickets[i].endpoint));
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(tickets[i].bgT.toString("hh:mm")));
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(tickets[i].edT.toString("hh:mm")));
                QString t1;
                t1 = QString::fromStdString(std::to_string(tickets[i].bgD.daysTo(tickets[i].edD)) +"天"+ std::to_string(tickets[i].edT.hour() - tickets[i].bgT.hour()) +"时"+ std::to_string(tickets[i].edT.minute() - tickets[i].bgT.minute()) +"分");
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(t1));
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(QString::fromStdString(std::to_string(tickets[i].amount))));
                if(!mode){
                    ui->tableWidget->setItem(row, column, new QTableWidgetItem("购买"));
                }
                else{
                    ui->tableWidget->setItem(row, column, new QTableWidgetItem("改签"));
                }
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
    QFile file(QApplication::applicationDirPath() + "/" + currentUser.getid() + ".txt");
    if(file.open(QIODevice::ReadWrite|QIODevice::Text)){
        QTextStream out(&file);
        QList<ticket> t(currentUser.getTickets());
        for(auto i = t.begin(); i != t.end(); i++){
            out << i->id << " " << " " << i->beginpoint << " " << i->endpoint << " "
                << i->bgD.toString("yyyy-MM-dd") << " " << i->bgT.toString("hh:mm") << " "
                << i->edD.toString("yyyy-MM-dd") << " " << i->edT.toString("hh:mm") << endl;
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
