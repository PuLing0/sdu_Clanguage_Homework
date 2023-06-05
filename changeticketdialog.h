#ifndef CHANGETICKETDIALOG_H
#define CHANGETICKETDIALOG_H

#include <QDialog>
#include<QString>
namespace Ui {
class changeticketdialog;
}

class changeticketdialog : public QDialog
{
    Q_OBJECT

public:
    explicit changeticketdialog(QWidget *parent = 0);
    ~changeticketdialog();

    QString getiniid();//获取想要修改的列车号
    QString getiniba();//获取想要修改的列车的现在的始发站
    QString getiniea();//获取想要修改的列车的现在的终点站
    QString getinibt();//获取想要修改的列车的现在的开车时间
    QString getiniet();//获取想要修改的列车的现在的到站时间
    QString getfinba();//获取想要修改的列车的改后的始发站
    QString getfinea();//获取想要修改的列车的改后的终点站
    QString getfinbt();//获取想要修改的列车的改后的开车时间
    QString getfinet();//获取想要修改的列车的改后的到站时间
    QString getfinnumber();//获取想要修改的列车的改后的票数
    QString getfinprice();//获取想要修改的列车的改后的车价

    void on_changebtn_clicked();//修改按钮按下时触发
    int flap;//记录是否为修改按钮按下

private:

    Ui::changeticketdialog *ui;

};

#endif // CHANGETICKETDIALOG_H
