#include "widget.h"
#include "ui_widget.h"
#include<QWidget>
#include<QLineEdit>
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<QList>
#include<ticket.h>
#include<QString>
#include<QStringList>
#include<QTableWidgetItem>
#include<iterator>
#include<QMessageBox>
#include<QGroupBox>
#include<QRadioButton>
#include<algorithm>
#include<QAbstractItemView>
#include<QStandardItemModel>
#include"adduserdialog.h"
#include"user.h"
#include"changeticketdialog.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    loadingdata();
    ui->setupUi(this);
    //设置单元格不可被编辑
    ui->ticketWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置自适应列宽
    ui->ticketWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
    ui->ticketWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    ui->searchticketWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
    ui->searchticketWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    ui->userWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
    ui->userWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    ui->searchuserwidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
    ui->searchuserwidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列

    ui->ticketWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->ticketWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->searchticketWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->searchticketWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->userWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->userWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->searchuserwidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->searchuserwidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行

    //载入数据
    setticketdata(ticketlist);

    //设置管理员用户头像图片
    ui->Image->setPixmap(QPixmap(":/Image/manager.png"));

    //设置打开页面时显示列车表和列车查询选项
    ui->stackedWidget1->setCurrentIndex(0);
    ui->stackedWidget2->setCurrentIndex(0);

    //连接信号
    connect(ui->Exit,&QPushButton::clicked,this,&QWidget::close);//设置退出按钮的功能


    //设置用户列表功能

    //设置添加车票按钮功能
    //设置添加用户按钮功能
    ui->ticketWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    RightClick = new QMenu(ui->ticketWidget);                        //右键点击菜单
    deleteAction = new QAction(QString::fromLocal8Bit("delete"),this);     //删除事件
    RightClick->addAction(deleteAction);                                //将action添加到菜单内


    connect(ui->ticketWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(RightClickSlot(QPoint)));
    connect(RightClick,SIGNAL(triggered(QAction*)),this,SLOT(RightClickDelete(QAction*)));
    connect(ui->userWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(RightClickSlot(QPoint)));
    connect(RightClick,SIGNAL(triggered(QAction*)),this,SLOT(RightClickDelete(QAction*)));


    //设置车票默认查询方式
    ui->addressButton->setChecked(true);

}

//将车票，用户数据读入列表中
void Widget::loadingdata()
{
    //打开文件
    QFile fticket("..\\Train\\hchsk.txt");
    if (!fticket.open(QIODevice::ReadOnly))
    {
              return;
    }
    //通过流对象读取文件信息并压入到信息列表中
    QTextStream dataticket(&fticket);
    while(!dataticket.atEnd())
    {
        ticket newt;
        auto str=dataticket.readLine().split('\t');
        newt.id=str[0];
        newt.beginpoint=str[1];
        newt.endpoint=str[2];
        newt.begintime=str[3];
        newt.endtime=str[4];
        newt.amount=str[5].toDouble();
        newt.price=str[6].toDouble();

        ticketlist.push_back(newt);
    }

    //关闭文件
    fticket.close();
    //打开文件
    QFile fuser("..\\Train\\user.txt");
    if (!fuser.open(QIODevice::ReadOnly))
    {
              return;
    }
    //通过流对象读取文件信息并压入到信息列表中
    QTextStream datauser(&fuser);
    while(!datauser.atEnd())
    {
        user news;
        auto str=datauser.readLine().split('\t');
        news.name=str[0];
        news.account=str[1];
        news.password=str[2];
        userlist.push_back(news);
    }

    //关闭文件
    fuser.close();

}

//显示车票数据
void Widget::setticketdata(const QList<ticket>&ticketlist)
{

    //清空当前列表
    for(int row = ui->ticketWidget->rowCount() - 1;row >= 0; row--)
    {
        ui->ticketWidget->removeRow(row);
    }

    //将车票信息显示到表格中
    for(QList<ticket>::const_iterator it=ticketlist.begin();it!=ticketlist.end();it++)
    {
        int rowcont=ui->ticketWidget->rowCount();
        ui->ticketWidget->insertRow(rowcont);
        ui->ticketWidget->setItem(rowcont,0,new QTableWidgetItem(it->id));
        ui->ticketWidget->setItem(rowcont,1,new QTableWidgetItem(it->beginpoint));
        ui->ticketWidget->setItem(rowcont,2,new QTableWidgetItem(it->endpoint));
        ui->ticketWidget->setItem(rowcont,3,new QTableWidgetItem(it->begintime));
        ui->ticketWidget->setItem(rowcont,4,new QTableWidgetItem(it->endtime));
        ui->ticketWidget->setItem(rowcont,5,new QTableWidgetItem(QString::number(it->amount)));
        ui->ticketWidget->setItem(rowcont,6,new QTableWidgetItem(QString::number(it->price)));
    }

}
//显示用户信息
void Widget::setuserdata(const QList<user>&)
{
    //清空当前列表
    for(int row = ui->userWidget->rowCount() - 1;row >= 0; row--)
    {
        ui->userWidget->removeRow(row);
    }

    //将车票信息显示到表格中
    for(QList<user>::const_iterator it=userlist.begin();it!=userlist.end();it++)
    {
        int rowcont=ui->userWidget->rowCount();
        ui->userWidget->insertRow(rowcont);
        ui->userWidget->setItem(rowcont,0,new QTableWidgetItem(it->name));
        ui->userWidget->setItem(rowcont,1,new QTableWidgetItem(it->account));
    }

}

void Widget::on_ticketList_clicked()
{
    //设置单元格不可被编辑
    ui->ticketWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //回到车票信息界面
    ui->stackedWidget2->setCurrentIndex(0);
    ui->stackedWidget1->setCurrentIndex(0);
    //清空当前列表
    for(int row = ui->ticketWidget->rowCount() - 1;row >= 0; row--)
    {
        ui->ticketWidget->removeRow(row);
    }

    //显示全部信息
    setticketdata(ticketlist);
}

void Widget::on_userList_clicked()
{
    //设置单元格不可被编辑
    ui->userWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //回到车票信息界面
    ui->stackedWidget2->setCurrentIndex(2);
    ui->stackedWidget1->setCurrentIndex(1);
    //清空当前列表
    for(int row = ui->userWidget->rowCount() - 1;row >= 0; row--)
    {
        ui->userWidget->removeRow(row);
    }
    //显示全部信息
    setuserdata(userlist);
}
//添加新的用户
void Widget::on_adduserButton_clicked()
{
    adduserdialog* au=new adduserdialog;
    au->setModal(true);
    au->show();
    au->exec();
//    if(au->isaddclicked())
//    {
        QString id=au->getid();
        QString name=au->getname();
        QString passwd=au->getpw();
        delete au;
        if(id.isEmpty()||name.isEmpty()||passwd.isEmpty())
        {
            QMessageBox::warning(this,"Warning","信息不全，无法添加！！！");
        }
        else
        {
            QList<user>::iterator it=userlist.begin();
            for(;it!=userlist.end();it++)
            {
                if(it->account==id||it->name==name)
                {

                    QMessageBox::warning(this,"Warning","信息冲突，无法添加！！！");
                    break;
                }
            }
            if(it==userlist.end())
            {
                ui->userWidget->insertRow(ui->userWidget->rowCount());
                ui->userWidget->scrollToBottom();
                ui->userWidget->setItem(ui->userWidget->rowCount()-1,0,new QTableWidgetItem(name));
                ui->userWidget->setItem(ui->userWidget->rowCount()-1,1,new QTableWidgetItem(id));
                user newu;
                newu.account=id;
                newu.name=name;
                newu.password=passwd;
                userlist.push_back(newu);
            }
        }
//    }
//    else
//        delete au;
}

//添加一行新的列车信息
void Widget::on_addticketButton_clicked()
{
    dialogaddticket* da=new dialogaddticket;
    da->setModal(true);
    da->show();
    da->exec();
//    if(da->isaddclicked())
//    {
        QString id=da->getid();
        QString ba=da->getba();
        QString ea=da->getea();
        QString bt=da->getbt();
        QString et=da->getet();
        QString t=da->getticket();
        QString pr=da->getprice();
        delete da;
        if(id.isEmpty()||ba.isEmpty()||ea.isEmpty()||bt.isEmpty()||et.isEmpty()||t.isEmpty())
        {
            QMessageBox::warning(this,"Warning","信息不全，无法添加！！！");
        }
        else
        {
            QList<ticket>::iterator it=ticketlist.begin();
            for(;it!=ticketlist.end();it++)
            {
                if(it->id==id&&it->beginpoint==ba&&it->endpoint==ea&&it->begintime==bt)
                {

                    QMessageBox::warning(this,"Warning","信息冲突，无法添加！！！");
                    break;
                }
            }
            if(it==ticketlist.end())
            {
                ui->ticketWidget->insertRow(ui->ticketWidget->rowCount());
                ui->ticketWidget->scrollToBottom();
                ui->ticketWidget->setItem(ui->ticketWidget->rowCount()-1,0,new QTableWidgetItem(id));
                ui->ticketWidget->setItem(ui->ticketWidget->rowCount()-1,1,new QTableWidgetItem(ba));
                ui->ticketWidget->setItem(ui->ticketWidget->rowCount()-1,2,new QTableWidgetItem(ea));
                ui->ticketWidget->setItem(ui->ticketWidget->rowCount()-1,3,new QTableWidgetItem(bt));
                ui->ticketWidget->setItem(ui->ticketWidget->rowCount()-1,4,new QTableWidgetItem(et));
                ui->ticketWidget->setItem(ui->ticketWidget->rowCount()-1,5,new QTableWidgetItem(t));
                ui->ticketWidget->setItem(ui->ticketWidget->rowCount()-1,6,new QTableWidgetItem(pr));
                ticket newt;
                newt.id=id;
                newt.beginpoint=ba;
                newt.endpoint=ea;
                newt.begintime=bt;
                newt.endtime=et;
                newt.amount=t.toDouble();
                newt.price=pr.toDouble();
                ticketlist.push_back(newt);
            }
        }
//    }
//    else
//        delete da;
}

//在列车信息列表右键单击时触发
void Widget::RightClickSlot(QPoint pos)
{

        QModelIndex index = ui->ticketWidget->indexAt(pos);    //找到tableview当前位置信息
        iDeletcRow = index.row();    //获取到了当前右键所选的行数

        if(index.isValid())        //如果行数有效，则显示菜单
        {
            RightClick->exec(QCursor::pos());
        }

}

//在列车信息列表右键单击时判断是否删除
void Widget::RightClickDelete(QAction *act)
{

    //弹出提示框，看是否删除数据
    QMessageBox message(QMessageBox::NoIcon, QString::fromLocal8Bit("warning"),
                                QString::fromLocal8Bit("Whether to delete the data of this bank"),
    QMessageBox::Yes | QMessageBox::No, NULL);

    //如确认删除

        if(message.exec() == QMessageBox::Yes)
        {

            if(act->text() == QString::fromLocal8Bit("delete"))   //看选中了删除这个菜单
            {
                QString id=ui->ticketWidget->model()->index(iDeletcRow,0).data().toString();
                QString ba=ui->ticketWidget->model()->index(iDeletcRow,1).data().toString();
                QString ea=ui->ticketWidget->model()->index(iDeletcRow,2).data().toString();
                QString bt=ui->ticketWidget->model()->index(iDeletcRow,3).data().toString();
                QString et=ui->ticketWidget->model()->index(iDeletcRow,4).data().toString();
                for(QList<ticket>::iterator it=ticketlist.begin();it!=ticketlist.end();it++)
                {
                    if(it->id==id&&it->beginpoint==ba&&it->endpoint==ea&&it->begintime==bt&&it->endtime==et)
                    {
                        ticketlist.erase(it);
                        break;
                    }
                }
                ui->ticketWidget->removeRow(iDeletcRow);  //删除掉了表格信息
            }

        }
}

//查询车票
void Widget::on_searchticketbtn_clicked()
{
    //清空当前列表数据
    for(int row = ui->searchticketWidget->rowCount() - 1;row >= 0; row--)
    {
        ui->searchticketWidget->removeRow(row);
    }
    ui->stackedWidget2->setCurrentIndex(1);


    //判断查询方式

    if(ui->addressButton->isChecked())
    {
        QString ba;
        QString ea;
        ba=ui->baEdit->text();
        ea=ui->eaEdit->text();

        for(QList<ticket>::iterator it=ticketlist.begin();it!=ticketlist.end();it++)
        {
            if(it->beginpoint==ba&&it->endpoint==ea)
            {
                int rowcont=ui->searchticketWidget->rowCount();
                ui->searchticketWidget->insertRow(rowcont);
                ui->searchticketWidget->setItem(rowcont,0,new QTableWidgetItem(it->id));
                ui->searchticketWidget->setItem(rowcont,1,new QTableWidgetItem(it->beginpoint));
                ui->searchticketWidget->setItem(rowcont,2,new QTableWidgetItem(it->endpoint));
                ui->searchticketWidget->setItem(rowcont,3,new QTableWidgetItem(it->begintime));
                ui->searchticketWidget->setItem(rowcont,4,new QTableWidgetItem(it->endtime));
                ui->searchticketWidget->setItem(rowcont,5,new QTableWidgetItem(QString::number(it->amount)));
                ui->searchticketWidget->setItem(rowcont,5,new QTableWidgetItem(QString::number(it->price)));
            }
        }
        //qDebug()<<"按地址查询"<<endl;
    }
    if(ui->timeButton->isChecked())
    {
        QString strbt=ui->btEdit->dateTime().toString("yyyy-MM-dd");
        QString stret=ui->etEdit->dateTime().toString("yyyy-MM-dd");
        for(QList<ticket>::iterator it=ticketlist.begin();it!=ticketlist.end();it++)
        {
            QString rbt=it->begintime.mid(0,10);
            QString ret=it->endtime.mid(0,10);
            if(rbt==strbt&&ret==stret)
            {
                int rowcont=ui->searchticketWidget->rowCount();
                ui->searchticketWidget->insertRow(rowcont);
                ui->searchticketWidget->setItem(rowcont,0,new QTableWidgetItem(it->id));
                ui->searchticketWidget->setItem(rowcont,1,new QTableWidgetItem(it->beginpoint));
                ui->searchticketWidget->setItem(rowcont,2,new QTableWidgetItem(it->endpoint));
                ui->searchticketWidget->setItem(rowcont,3,new QTableWidgetItem(it->begintime));
                ui->searchticketWidget->setItem(rowcont,4,new QTableWidgetItem(it->endtime));
                ui->searchticketWidget->setItem(rowcont,5,new QTableWidgetItem(QString::number(it->amount)));
                ui->searchticketWidget->setItem(rowcont,5,new QTableWidgetItem(QString::number(it->price)));
            }
         }
        }
        //qDebug()<<"按时间查询"<<endl;
}

//查询用户
void Widget::on_searchuserbtn_clicked()
{
    for(int row = ui->searchuserwidget->rowCount() - 1;row >= 0; row--)
    {
        ui->searchuserwidget->removeRow(row);
    }
    ui->stackedWidget2->setCurrentIndex(3);

    QString name=ui->nameEdit->text();
        for(QList<user>::iterator it=userlist.begin();it!=userlist.end();it++)
        {
            if(name==it->name)
            {
                int rowcont=ui->searchuserwidget->rowCount();
                ui->searchuserwidget->insertRow(rowcont);
                ui->searchuserwidget->setItem(rowcont,0,new QTableWidgetItem(it->name));
                ui->searchuserwidget->setItem(rowcont,1,new QTableWidgetItem(it->account));
            }
        }
}
//保存修改
void Widget::on_saveBtn_clicked()
{

    //打开文件
    QFile fticket("..\\Train\\hchsk.txt");
    if (!fticket.open(QIODevice::WriteOnly))
    {
         return;
    }
    //通过流对象写入文件信息
    QTextStream dataticket(&fticket);
    for(QList<ticket>::const_iterator it=ticketlist.begin();it!=ticketlist.end();it++)
    {
         dataticket<<it->id<<'\t'<<it->beginpoint<<'\t'<<it->endpoint<<'\t'<<it->begintime<<'\t'<<it->endtime<<'\t'<<it->amount<<'\t'<<it->price<<endl;
    }
    //关闭文件
    fticket.close();

    //打开文件
    QFile fuser("..\\Train\\user.txt");
    if (!fuser.open(QIODevice::WriteOnly))
    {
              return;
    }
    //通过流对象读取文件信息并压入到信息列表中
    QTextStream datauser(&fuser);
    for(QList<user>::const_iterator it=userlist.begin();it!=userlist.end();it++)
    {
         datauser<<it->name<<'\t'<<it->account<<'\t'<<it->password<<endl;
    }




    //关闭文件
    fuser.close();



}

//修改列车信息
void Widget::on_changeticketbtn_clicked()
{
    changeticketdialog* ct=new changeticketdialog;
    ct->setModal(true);
    ct->show();
    ct->exec();
    QString iniid=ct->getiniid();
    QString iniba=ct->getiniba();
    QString iniea=ct->getiniea();
    QString inibt=ct->getinibt();
    QString iniet=ct->getiniet();
    QString finba=ct->getfinba();
    QString finea=ct->getfinea();
    QString finbt=ct->getfinbt();
    QString finet=ct->getfinet();
    QString finnumber=ct->getfinnumber();
    QString finprice=ct->getfinprice();
    for(QList<ticket>::iterator it=ticketlist.begin();it!=ticketlist.end();it++)
    {
        //找到要修改的车票信息
        if(it->id==iniid&&it->beginpoint==iniba&&it->endpoint==iniea&&it->begintime==inibt&&it->endtime==iniet)
        {
            int flap=0;
            //检查信息是否有冲突
            for(QList<ticket>::iterator it1=ticketlist.begin();it1!=ticketlist.end();it1++)
            {
                if(it1->id==iniid&&it1->beginpoint==finba&&it1->endpoint==finea&&it1->begintime==finbt&&it1->endpoint==finet&&QString::number(it1->amount)==finnumber&&QString::number(it1->price)==finprice)
                {
                        QMessageBox::warning(this,"Warning","信息冲突，无法修改！！！");
                        flap=1;
                        break;
                }
            }

            if(flap)
            {
                break;
            }
            else
            {
                it->beginpoint=finba;
                it->endpoint=finea;
                it->begintime=finbt;
                it->endtime=finet;
                it->amount=finnumber.toDouble();
                it->price=finprice.toDouble();
                QMessageBox::information(this,"提示","修改成功");
                setticketdata(ticketlist);
            }
        }
        else
        {
            QMessageBox::warning(this,"Warning","查询不到想要修改的列车，无法修改！！！");
            break;
        }

    }



}



Widget::~Widget()
{

    delete ui;
}
