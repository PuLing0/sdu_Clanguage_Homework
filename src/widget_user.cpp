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
#include<QTimer>


Widget_User::Widget_User(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::Widget_User),
      currentUser("213454","1243421")
{
    //用户窗口初始化
    mode = 0;
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置单元格不可被编辑
    ui->tableWidget->setSortingEnabled(true); //添加按表头排序功能
    ui->label_4->setText("用户名:"+currentUser.getid()); //屏幕左上角显示用户名
    ui->label_6->hide();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列

    //时钟初始化
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget_User::timerUpdate);
    timer->start(1000);
}

Widget_User::~Widget_User()
{
    delete ui;
}

void Widget_User::setUser(user t){
    /*设置当前用户*/
    currentUser = t;
    readUsertickets(); //读取用户已购票据
    ui->label_4->setText("用户名:"+currentUser.getid()); //屏幕左上角显示用户名
}

void Widget_User::on_pushButton_clicked()
{
    /*查询按键*/
    if(!tickets.size()) //若票据链表为空
        read(); //读取票据文件
    ui->tableWidget->setRowCount(0); //清空表格
    check(); //查询票据
}

bool Widget_User::read(){
    /*读取票据文件*/
    QFile fp("..//Train//ticket.txt"); //票据文件路径
    if(!fp.open(QIODevice::ReadOnly)){
        ui->label_7->setText("载入文件失败");
        return false;
    }
    else {
        QTextStream in(&fp);
        QString bgT, edT, bgD, edD;
        while (!in.atEnd()){ //循环读取票据
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
        ui->label_7->setText("载入文件成功"); //屏显
        fp.close();
        return true;
    }
}

bool Widget_User::readUsertickets(){
    /*读取用户已购票据*/
    QFile fp("..//Train//User_Ticket//" + currentUser.getid() + ".txt");
    if(!fp.open(QIODevice::ReadOnly)){
        return false;
    }
    else {
        QList<ticket> temp; //临时链表
        QTextStream in(&fp);
        QString bgT, edT, bgD, edD;
        while (!in.atEnd()){ //循环读取票据
            ticket t;
            in>>t.id;
            in>>t.beginpoint;
            in>>t.endpoint;
            in>>t.beginDay;
            in>>t.begintime;
            in>>t.endDay;
            in>>t.endtime;
            t.amount = 1; //设置票数为1
            in>>t.price;
            if(t.endtime != "") //若该票不为空票
                temp.append(t); //尾插到temp链表
        }
        currentUser.setTickets(temp); //设置当前用户已购票据为temp
        fp.close();
        return true;
    }
}


void Widget_User::check(){
    /*查询票据实现*/
    //获取查询信息
    QString b = ui->lineEdit->text();
    QString c = ui->lineEdit_2->text();
    QString d = ui->dateEdit->date().toString("yyyy-MM-dd");

    if(b == "" || c == ""){ //若有信息为空
        ui->label_5->setText("查询失败：信息不完整"); //报错
    }        
    else{
        int i = 0;
        int row = 0, column = 0;
        while(i < tickets.size() - 1){ //循环打印票据到表格
            if(d == tickets[i].beginDay && b == tickets[i].beginpoint && c == tickets[i].endpoint){
                ui->tableWidget->insertRow(0); //插入新行
                column = 0;
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(tickets[i].id));
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(tickets[i].beginpoint));
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(tickets[i].endpoint));
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(tickets[i].begintime));
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(tickets[i].endtime));

                QString t1; //临时字符串，存储历时
                //字符串转化为QDate和QTime
                QDate b = QDate::fromString(tickets[i].beginDay, "yyyy-MM-dd");
                QDate e = QDate::fromString(tickets[i].endDay, "yyyy-MM-dd");
                QTime bt = QTime::fromString(tickets[i].begintime, "hh:mm");
                QTime et = QTime::fromString(tickets[i].endtime, "hh:mm");
                t1 = QString::fromStdString(std::to_string(b.daysTo(e)) +"天"+
                                            std::to_string(et.hour() - bt.hour()) +"时"+
                                            std::to_string(et.minute() - bt.minute()) +"分"); //历时计算
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem(t1));
                ui->tableWidget->setItem(row, column++, new QTableWidgetItem
                                         (QString::fromStdString(std::to_string(tickets[i].amount))));
                if(!mode){
                    ui->tableWidget->setItem(row, column, new QTableWidgetItem("购买"));
                }
                else{ //若为改签状态
                    ui->tableWidget->setItem(row, column, new QTableWidgetItem("改签")); //打印改签
                }
                ui->tableWidget->setItem(row, ++column, new QTableWidgetItem(QString::number(tickets[i].price, 'f', 2))); //保留两位小数显示票价
            }
            i++;
        }
        ui->label_5->setText("查询成功!");
    }
}

void Widget_User::on_tableWidget_cellDoubleClicked(int row, int column)
{
    /*购买、改签实现*/
    if(column == 7){ //若双击单元格在第8列
        if(!mode){ //且不为改签状态
            for (int i = 0; i < tickets.size(); i++) {
                if(tickets[i].id == ui->tableWidget->item(row, 0)->text() && tickets[i].amount){ //匹配票据
                    prompt1* t = new prompt1;
                    t->show(); //弹出提示框
                    if(currentUser.buy(tickets[i])){
                        t->setText("购票成功");
                        tickets[i].amount--; //所购票据数量减少1
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
                    if(currentUser.change(changingTicket, tickets[i])){ //若不为同一张票
                        t->setText("改签成功");
                        tickets[i].amount--;
                        tickets[tickets.indexOf(changingTicket)].amount++; //已改签票据数量加1
                        mode = 0; //转换状态
                        ui->label_6->clear();
                        ui->label_6->hide();
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
    /*个人中心按钮*/
    dialog1 *t = new dialog1;
    t->setUser(currentUser); //传递当前用户到子窗口
    connect(t, SIGNAL(send(bool, ticket)), this, SLOT(get(bool, ticket))); //窗口间传ticket
    if(!mode){
        t->show();
    }
    else{
        t->hide();
    }
}

void Widget_User::on_pushButton_4_clicked()
{
    /*退出登录按钮*/
    save();
    close();
}

bool Widget_User::save(){
    /*保存用户购买票据*/
    QFile file("..//Train//User_Ticket//" + currentUser.getid() + ".txt");
    if(file.open(QIODevice::ReadWrite|QIODevice::Text)){ //读写打开文本文件，若不存在则新建
        QTextStream out(&file);
        QList<ticket> t(currentUser.getTickets());
        for(auto i = t.begin(); i != t.end(); i++){ //写入票据
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
    /*窗口间传ticket实现*/
    mode = m;
    if(mode){ //若为改签状态
        changingTicket = a; //设置当前正在操作的票据
        ui->label_6->setText(a.id+" 正在改签中...");
        ui->label_6->show();
    }
    else { //若不为改签状态
       changingTicket = a;
       refund(changingTicket); //退票
    }
}

bool Widget_User::refund(ticket a){
    /*退票实现*/
    if(currentUser.refund(a)){ //若退票成功
        tickets[tickets.indexOf(a)].amount++; //所退票据数量增加1
        prompt1 *t = new prompt1 ();
        t->setText("退票成功");
        t->show(); //显示提示框
    }
    else{ //若退票失败
        prompt1 *t = new prompt1 ();
        t->setText("退票失败");
        t->show();
    }
}

void Widget_User::timerUpdate(){
    /*时钟实现*/
    QDateTime t = QDateTime::currentDateTime(); //获取当前时间
    QString s = t.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->label_8->setText(s); //屏显
}
