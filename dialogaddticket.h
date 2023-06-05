#ifndef DIALOGADDTICKET_H
#define DIALOGADDTICKET_H

#include <QDialog>
#include<QString>
namespace Ui {
class dialogaddticket;
}

class dialogaddticket : public QDialog
{
    Q_OBJECT
friend class Widget;
public:
    explicit dialogaddticket(QWidget *parent = 0);
    ~dialogaddticket();

    QString getid();//获取想要添加的列车的列车号
    QString getba();//获取想要添加的列车的始发站
    QString getea();//获取想要添加的列车的终点站
    QString getbt();//获取想要添加的列车的发车时间
    QString getet();//获取想要添加的列车的到站时间
    QString getticket();//获取想要添加的列车的车票数
    QString getprice();//获取想要添加的列车的票价
    
    int flap;//判断保存按钮是否被按下
public slots:
    
    void saveclicked();//保存按钮按下式触发

signals:

private:
    Ui::dialogaddticket *ui;

};

#endif // DIALOGADDTICKET_H
