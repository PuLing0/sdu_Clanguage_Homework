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
    //个人中心窗口初始化
    ui->setupUi(this);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置单元格不可被修改
    ui->tableWidget_2->hide();
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    ui->tableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget_2->setAlternatingRowColors(true);
    ui->tableWidget_2->horizontalHeader()->setMinimumHeight(30);

}

dialog1::~dialog1()
{
    delete ui;
}

void dialog1::setUser(user t)
{
    /*设置当前用户*/
    currentUser = t;
    tickets = t.getTickets(); //获取用户已购票据
    ui->label->setText("用户名：" + currentUser.getid()); //窗口左上角显示用户名
}

void dialog1::on_tableWidget_2_cellDoubleClicked(int row, int column)
{
    /*改签退票信号*/
    if(column == 6)
    { //若双击改签单元格
        ticket t;
        for (int i = 0; i < tickets.size(); i++)
        {
            if(tickets[i].id == ui->tableWidget_2->item(row, 0)->text())
            { //匹配票据
                bool mode = 1; //设置改签状态
                t = tickets[i];
                emit send(mode, tickets[i]); //发送至主窗口
                this->hide(); //当前窗口隐藏
            }
        }
    }
    else if(column == 7)
    { //若双击退票单元格
        ticket t;
        for (int i = 0; i < tickets.size(); i++)
        {
            if(tickets[i].id == ui->tableWidget_2->item(row, 0)->text())
            { //匹配票据
                bool mode = 0;
                t = tickets[i];
                emit send(mode, tickets[i]); //发送至主窗口
                tickets.removeOne(t); //从已购买票据中移除
            }
        }
    }
}

void dialog1::on_pushButton_clicked()
{
    /*已购买票据查询按钮*/
    ui->label_2->setText("查询成功");
    ui->tableWidget_2->show();
    ui->tableWidget_2->setRowCount(0); //清空表格
    int i = 0, row = 0, column = 0;
    while(i < tickets.size())
    { //循环打印票据
            ui->tableWidget_2->insertRow(0);
            column = 0;
            ui->tableWidget_2->setItem(row, column++, new QTableWidgetItem(tickets[i].id));
            ui->tableWidget_2->setItem(row, column++, new QTableWidgetItem(tickets[i].beginpoint));
            ui->tableWidget_2->setItem(row, column++, new QTableWidgetItem(tickets[i].endpoint));
            ui->tableWidget_2->setItem(row, column++, new QTableWidgetItem(tickets[i].begintime));
            ui->tableWidget_2->setItem(row, column++, new QTableWidgetItem(tickets[i].endtime));

            QString t1; //临时容器，存储历时
            //将字符串转换为QDate和QTime
            QDate b = QDate::fromString(tickets[i].beginDay, "yyyy-MM-dd");
            QDate e = QDate::fromString(tickets[i].endDay, "yyyy-MM-dd");
            QTime bt = QTime::fromString(tickets[i].begintime, "hh:mm");
            QTime et = QTime::fromString(tickets[i].endtime, "hh:mm");

            t1 = QString::fromStdString(std::to_string(b.daysTo(e)) +"天"+
                                        std::to_string(et.hour() - bt.hour()) +"时"+
                                        std::to_string(et.minute() - bt.minute()) +"分"); //历时计算
            ui->tableWidget_2->setItem(row, column++, new QTableWidgetItem(t1));
            ui->tableWidget_2->setItem(row, column++, new QTableWidgetItem("改签"));
            ui->tableWidget_2->setItem(row, column, new QTableWidgetItem("退票"));
            i++;
    }
}

void dialog1::on_pushButton_2_clicked()
{
    /*退出按钮*/
    this->close();
}
