#ifndef TICKET_H
#define TICKET_H
#include<QString>
#include<QDateTime>
#include <QTime>

class ticket
{
public:
    ticket();
    QString id;//列车号
    QString beginpoint;//始发地
    QString endpoint;//终点站
    QString beginDay; //发车日期
    QString endDay; //到站日期
    QString begintime;//发车时间
    QString endtime;//到站时间
    int amount;//车票数
    double price;//车票价格

    bool operator ==(const ticket l){
        /*判断两票相同与否*/
        if(id == l.id) return true;
        return false;
    }
};

#endif // TICKET_H
