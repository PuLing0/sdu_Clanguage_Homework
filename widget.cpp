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
#include"regdialog.h"
#include"md5.h"
#include"qtmaterialautocomplete.h"
#include"qtmaterialflatbutton.h"
#include"qtmaterialradiobutton.h"
#include"qtmaterialraisedbutton.h"
#include<QColor>
#include<QDateTime>
#include<QTimer>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    //加载数据，将车票信息和用户信息读入各自list中
    loadingdata();

    ui->setupUi(this);

    //配置按钮
    ui->addticketButton->setBackgroundColor(QColor(0,188,212));//设置按钮的背景颜色
    ui->adduserButton->setBackgroundColor(QColor(0,188,212));//设置按钮的背景颜色
    ui->changeticketbtn->setBackgroundColor(QColor(0,188,212));//设置按钮的背景颜色
    ui->saveBtn->setBackgroundColor(QColor(0,188,212));//设置按钮的背景颜色
    ui->ticketList->setBackgroundColor(QColor(0,188,212));//设置按钮的背景颜色
    ui->userList->setBackgroundColor(QColor(0,188,212));//设置按钮的背景颜色
    ui->searchticketbtn->setBackgroundColor(QColor(0,188,212));//设置按钮的背景颜色
    ui->searchuserbtn->setBackgroundColor(QColor(0,188,212));//设置按钮的背景颜色

    //配置表格编辑模式
    ui->ticketWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置车票信息单元格不可被编辑
    ui->searchticketWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置查找车票单元格不可被编辑
    ui->userWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置用户信息单元格不可被编辑
    ui->searchuserwidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置查找用户信息单元格不可被编辑

    //设置表格自适应列宽
    ui->ticketWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
    ui->ticketWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    ui->searchticketWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
    ui->searchticketWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    ui->userWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
    ui->userWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    ui->searchuserwidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
    ui->searchuserwidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列

    //设置表格选择模式
    ui->ticketWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置车票信息单元格选择行为，以行为单位
    ui->ticketWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置车票信息单元格选择模式，选择单行
    ui->searchticketWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置查找车票单元格选择行为，以行为单位
    ui->searchticketWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置查找车票单元格选择模式，选择单行
    ui->userWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置用户信息单元格选择行为，以行为单位
    ui->userWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置用户信息单元格选择模式，选择单行
    ui->searchuserwidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置查找用户信息单元格选择行为，以行为单位
    ui->searchuserwidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置查找用户信息单元格选择模式，选择单行

    //配置日历
    ui->btEdit->setCalendarPopup(true);//设置能够显示日历
    ui->etEdit->setCalendarPopup(true);//设置能够显示日历
    ui->btEdit->setDisplayFormat("yyyy-MM-dd");//设置日历的显示格式
    ui->btEdit->setDateTime(QDateTime::currentDateTime());//设置日历时间为当前日期
    ui->etEdit->setDisplayFormat("yyyy-MM-dd");//设置日历的显示格式
    ui->etEdit->setDateTime(QDateTime::currentDateTime());//设置日历时间为当前日期


    //设置管理员用户头像图片
    ui->Image->setPixmap(QPixmap(":/Image/manager.png"));
    //设置窗口图标
    this->setWindowIcon(QIcon(":/Image/manager.png"));

    //设置打开页面时显示列车表和列车查询选项
    ui->stackedWidget1->setCurrentIndex(0);//将初始界面设置为列车信息的查询模式
    ui->addressButton->setChecked(true);    //设置车票默认查询方式
    ui->stackedWidget2->setCurrentIndex(0);//将初识界面设置为列车信息表格

    //将车票信息数据显示在对应表格中
    setticketdata(ticketlist);

    //时钟初始化
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::timerUpdate);
    timer->start(1000);//设置时间间隔

    //连接信号
    connect(ui->Exit,&QPushButton::clicked,this,&QWidget::close);//设置退出按钮的功能，按下关闭管理员界面

    //设置添加用户按钮功能
    ui->ticketWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    RightClick = new QMenu(ui->ticketWidget);                        //添加右键点击菜单
    deleteAction = new QAction(QString::fromLocal8Bit("delete"),this);     //添加删除事件
    RightClick->addAction(deleteAction);                                //将删除事件添加到菜单内

    //连接列车信息删除功能的信号
    connect(ui->ticketWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(RightClickSlot(QPoint)));
    connect(RightClick,SIGNAL(triggered(QAction*)),this,SLOT(RightClickDelete(QAction*)));


}

//将车票，用户数据读入列表中
void Widget::loadingdata()
{
    //打开存储车票信息的文件
    QFile fticket("..//Train//ticket.txt");
    //判断是否成功打开
    if (!fticket.open(QIODevice::ReadOnly))
    {
              return;
    }
    //连接流
    QTextStream dataticket(&fticket);
    //通过流对象读取文件信息并压入到信息列表中
    while(!dataticket.atEnd())
    {
        ticket newt;//创建一个新的车票对象
        QString bgT, edT, bgD, edD;//创建字符串用于存储发车时间和到站时间
        dataticket>>newt.id;//读入列车号
        dataticket>>newt.beginpoint;//读入始发站
        dataticket>>newt.endpoint;//读入终点站
        dataticket>>bgD;//读入发车日期
        dataticket>>bgT;//读入发车具体时间
        dataticket>>edD;//读入到站时间
        dataticket>>edT;//读入到站具体时间
        newt.begintime=bgD+" "+bgT;//拼接字符串为完整的发车时间
        newt.endtime=edD+" "+edT;//拼接字符串为完整的到站时间
        dataticket>>newt.amount;//读入车票数量
        dataticket>>newt.price;//读入车票的价格
        QDateTime bt=QDateTime::fromString(newt.begintime,"yyyy-MM-dd hh:mm");//将车票的发车时间转换为QDateTime便于比较
        QDateTime curtime=QDateTime::currentDateTime();//创建当前时间的QDateTime对象
        int days=bt.daysTo(curtime);//计算发车日期和当前日期相差的天数

        //若车票发车日期比当前的日期早，则不存入列车信息列表。反之，则存入
        if(days<=0)
        ticketlist.push_back(newt);
    }

    //判断列车信息列表是否为空（如果不检查，当列表为空时，程序会崩溃）
    if(ticketlist.isEmpty())
        ;
    else
        ticketlist.pop_back();//如果list不为空，弹出最后一个数据（该数据是无用的数据）
    //关闭文件
    fticket.close();

    //打开文件
    QFile fuser("..\\Train\\User_Data.dat");
    if (!fuser.open(QIODevice::ReadOnly))
    {
              return;
    }
    //通过流对象读取文件信息并压入到信息列表中
    QTextStream datauser(&fuser);
    while(!datauser.atEnd())
    {
        // 逐行输入数据
        QString nm, ps, ac, op_s, gd_s;//创建字符串分别存储用户名，密码，账号，性别，权限
        datauser>> nm >> ac >> ps >> gd_s >> op_s;//读入用户名，密码，账号，性别，权限

        //将性别和权限转换为布尔型数据
        QVariant op_v(op_s);
        QVariant gd_v(gd_s);
        bool op = op_v.toBool();
        bool gd = gd_v.toBool();

        // 将数据赋值给用户
        user u;//创建一个新的用户对象
        u.setAccount(ac);//设置账号
        u.setGender(gd);//设置性别
        u.setName(nm);//设置用户名
        u.setPassword(ps);//设置密码
        u.setOP(op);//设置权限

        // 将用户添加到链表中
        userlist.push_back(u);
    }

    //弹出最后一个无用数据
    userlist.pop_back();
    //关闭文件
    fuser.close();

}

//显示车票数据
void Widget::setticketdata(const QList<ticket>&ticketlist)
{

    //清空车票信息列表
    for(int row = ui->ticketWidget->rowCount() - 1;row >= 0; row--)
    {
        ui->ticketWidget->removeRow(row);
    }

    //将车票信息显示到表格中
    for(QList<ticket>::const_iterator it=ticketlist.begin();it!=ticketlist.end();it++)
    {
        int rowcont=ui->ticketWidget->rowCount();//记录当前的行数
        ui->ticketWidget->insertRow(rowcont);//插入新的一行
        ui->ticketWidget->setItem(rowcont,0,new QTableWidgetItem(it->id));//显示列车号
        ui->ticketWidget->setItem(rowcont,1,new QTableWidgetItem(it->beginpoint));//显示始发站
        ui->ticketWidget->setItem(rowcont,2,new QTableWidgetItem(it->endpoint));//显示终点站
        ui->ticketWidget->setItem(rowcont,3,new QTableWidgetItem(it->begintime));//显示发车时间
        ui->ticketWidget->setItem(rowcont,4,new QTableWidgetItem(it->endtime));//显示到站时间
        ui->ticketWidget->setItem(rowcont,5,new QTableWidgetItem(QString::number(it->amount)));//显示车票数量
        ui->ticketWidget->setItem(rowcont,6,new QTableWidgetItem(QString::number(it->price)));//显示车票价格
    }

}

//显示用户信息
void Widget::setuserdata(const QList<user>&)
{
    //清空用户信息列表
    for(int row = ui->userWidget->rowCount() - 1;row >= 0; row--)
    {
        ui->userWidget->removeRow(row);
    }

    //将用户信息显示到表格中
    for(QList<user>::const_iterator it=userlist.begin();it!=userlist.end();it++)
    {
        //判断是否为用户，如果是则显示；否则，则不显示
        if(it->Over_Power==false)
        {
            int rowcont=ui->userWidget->rowCount();//记录当前行数
            ui->userWidget->insertRow(rowcont);//插入新的一行
            ui->userWidget->setItem(rowcont,0,new QTableWidgetItem(it->name));//显示用户名
            ui->userWidget->setItem(rowcont,1,new QTableWidgetItem(it->account));//显示账号

            //打开存储用户购票信息的文件
            QFile userticket("..//Train//User_Ticket//"+it->name+".txt");
            //判断是否成功打开
            if (!userticket.open(QIODevice::ReadOnly))
            {
                return;
            }
            QTextStream datauserticket(&userticket);//创建流对象
            QString userticketinformation;//创建存储已购车票信息的字符串
            //逐行读入
            while (!datauserticket.atEnd())
            {
                QString line = datauserticket.readLine();
                userticketinformation+="\n"+line;
            }
            //关闭文件
            userticket.close();
            //显示用户已购车票信息
            ui->userWidget->setItem(rowcont,2,new QTableWidgetItem(userticketinformation));
        }
    }

}

//列车信息列表按钮功能的实现
void Widget::on_ticketList_clicked()
{
    //设置单元格不可被编辑
    ui->ticketWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //回到车票信息界面，查询车票信息界面
    ui->stackedWidget2->setCurrentIndex(0);
    ui->stackedWidget1->setCurrentIndex(0);
    //清空列车信息当前表格
    for(int row = ui->ticketWidget->rowCount() - 1;row >= 0; row--)
    {
        ui->ticketWidget->removeRow(row);
    }

    //显示全部信息
    setticketdata(ticketlist);
}

//用户信息列表
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

//添加用户按钮
void Widget::on_adduserButton_clicked()
{

    adduserdialog* au=new adduserdialog;//创建一个新的添加用户对话框
    au->setModal(true);
    au->show();//显示对话框
    au->exec();//设置为模态对话框

    QString name = au->name;//获取添加用户的用户名
    QString account = au->account;//获取添加用户的账号
    bool gender = au->gender;//获取添加用户的性别
    md5 m;//创建一个md5对象
    QString password = QString::fromStdString(m.getMD5(au->password.toStdString()));//对密码进行加密

    //如果按下了添加按钮
    if( au->flap==1)
    {
        //释放空间
        delete au;
        //判断信息是否完整
        if(name.isEmpty()||account.isEmpty()||password.isEmpty())
        {
            QMessageBox::warning(this,"Warning","信息不全，无法添加！！！");//信息不完整则警告，不予添加
        }
        else
        {
            //判断用户的信息是否存在冲突
            QList<user>::iterator it=userlist.begin();
            for(;it!=userlist.end();it++)
            {
                //如果用户名和账号已存在则报告
                if(it->account==account||it->name==name)
                {
                    QMessageBox::warning(this,"Warning","信息冲突，无法添加！！！");//信息冲突警告，不予添加
                    break;
                }
            }
            //如果信息完全，没有冲突信息，则添加该用户
            if(it==userlist.end())
            {
                ui->userWidget->insertRow(ui->userWidget->rowCount());//在用户信息表格添加一行
                ui->userWidget->scrollToBottom();//将用户信息表格置于最底端
                ui->userWidget->setItem(ui->userWidget->rowCount()-1,0,new QTableWidgetItem(name));//显示新用户的用户名
                ui->userWidget->setItem(ui->userWidget->rowCount()-1,1,new QTableWidgetItem(account));//显示新用户的账号
                user newu;//创建一个用户对象
                newu.account=account;//设置账号
                newu.name=name;//设置用户名
                newu.password=password;//设置密码
                newu.gender=gender;//设置性别
                newu.Over_Power=0;//设置权限
                userlist.push_back(newu);//压入用户列表中
            }
        }
     }
     else
        delete au;//释放空间


}

//添加列车信息按钮功能的实现
void Widget::on_addticketButton_clicked()
{

    dialogaddticket* da=new dialogaddticket;//创建一个新的添加列车对话框
    da->setModal(true);
    da->show();//显示对话框
    da->exec();//设置为模态
    //判断添加按钮是否被按下
    if(da->flap==1)
    {

        QString id=da->getid();//获取新车次的列车号
        QString ba=da->getba();//获取新车次的始发站
        QString ea=da->getea();//获取新车次的终点站
        QString bt=da->getbt();//获取新车次的发车时间
        QString et=da->getet();//获取新车次的到站时间
        QString t=da->getticket();//获取新车次的车票数
        QString pr=da->getprice();//获取新车次的票价
        delete da;//释放
        //判断是否有信息不全
        if(id.isEmpty()||ba.isEmpty()||ea.isEmpty()||bt.isEmpty()||et.isEmpty()||t.isEmpty())
        {
            QMessageBox::warning(this,"Warning","信息不全，无法添加！！！");//如果信息不全则警告，不予添加
        }
        else
        {
            //如果信息完全则尝试添加

            //判断有信息冲突
            QList<ticket>::iterator it=ticketlist.begin();
            for(;it!=ticketlist.end();it++)
            {
                if(it->id==id&&it->beginpoint==ba&&it->endpoint==ea&&it->begintime==bt)//这里仅判断是否有同一列车相同始发站和终点站同时开车的情况
                {

                    QMessageBox::warning(this,"Warning","信息冲突，无法添加！！！");//如果信息有冲突，则警告，不予添加
                    break;
                }
            }
            //如果信息完全无冲突，则添加该车次
            if(it==ticketlist.end())
            {
                ui->ticketWidget->insertRow(ui->ticketWidget->rowCount());//获取列车当前表格的行数
                ui->ticketWidget->scrollToBottom();//将表格置于底端
                ui->ticketWidget->setItem(ui->ticketWidget->rowCount()-1,0,new QTableWidgetItem(id));//显示列车号
                ui->ticketWidget->setItem(ui->ticketWidget->rowCount()-1,1,new QTableWidgetItem(ba));//显示始发站
                ui->ticketWidget->setItem(ui->ticketWidget->rowCount()-1,2,new QTableWidgetItem(ea));//显示终点站
                ui->ticketWidget->setItem(ui->ticketWidget->rowCount()-1,3,new QTableWidgetItem(bt));//显示开车时间
                ui->ticketWidget->setItem(ui->ticketWidget->rowCount()-1,4,new QTableWidgetItem(et));//显示到站时间
                ui->ticketWidget->setItem(ui->ticketWidget->rowCount()-1,5,new QTableWidgetItem(t));//显示车票数
                ui->ticketWidget->setItem(ui->ticketWidget->rowCount()-1,6,new QTableWidgetItem(pr));//显示票价
                ticket newt;//创建新的车票对象
                newt.id=id;//设置列车号
                newt.beginpoint=ba;//设置始发站
                newt.endpoint=ea;//设置终点站
                newt.begintime=bt;//设置开车时间
                newt.endtime=et;//设置到站时间
                newt.amount=t.toInt();//设置车票数
                newt.price=pr.toDouble();//设置票价
                ticketlist.push_back(newt);//加入车次列表中
            }
        }
    }
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
                                QString::fromLocal8Bit("Whether to delete the data of this ticket"),
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
    QFile fticket("..//Train//ticket.txt");
    if (!fticket.open(QIODevice::WriteOnly))
    {
         return;
    }

    //通过流对象写入文件信息
    QTextStream dataticket(&fticket);
    for(QList<ticket>::const_iterator it=ticketlist.begin();it!=ticketlist.end();it++)
    {
         dataticket<<it->id<<" "<<it->beginpoint<<" "<<it->endpoint<<" "<<it->begintime<<" "<<it->endtime<<" "<<it->amount<<" "<<it->price<<endl;
    }

    //关闭文件
    fticket.close();

    //打开文件
    QFile fuser("..//Train//User_Data.dat");
    if (!fuser.open(QIODevice::WriteOnly))
    {
              return;
    }

    //通过流对象读取文件信息并压入到信息列表中
    QTextStream datauser(&fuser);
    for(QList<user>::const_iterator it=userlist.begin();it!=userlist.end();it++)
    {
         datauser<<it->name<<' '<<it->account<<' '<<it->password<<" "<<it->gender<<" "<<it->Over_Power<<endl;
         QFile file_name("..\\Train\\User_Ticket\\" + it->name + ".txt");
         if (!file_name.open(QIODevice::WriteOnly | QIODevice::Text))
                return ;
         file_name.close();
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
    if(ct->flap==1)
    {
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

}
void Widget::timerUpdate(){
    /*时钟实现*/
    QDateTime t = QDateTime::currentDateTime(); //获取当前时间
    QString s = t.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->TimeLabel->setText(s); //屏显
}


Widget::~Widget()
{

    delete ui;
}
