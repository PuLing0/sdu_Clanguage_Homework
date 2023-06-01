#ifndef WIDGET_USER_H
#define WIDGET_USER_H

#include <QWidget>
#include "ticket.h"
#include"user.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget_User; }
QT_END_NAMESPACE

class Widget_User : public QWidget
{
    Q_OBJECT

public:
    Widget_User(QWidget *parent = nullptr);
    ~Widget_User();
    void setUser(user t);

private slots:
    void on_pushButton_clicked();
    void check();
    bool read();
    void on_tableWidget_cellDoubleClicked(int row, int column);
    bool refund(ticket a);
    void on_pushButton_3_clicked();
    bool readUsertickets();
    void on_pushButton_4_clicked();
    bool save();
    void get(bool m, ticket a);
private:
    Ui::Widget_User *ui;
    QList<ticket> tickets;
    user currentUser;
    bool mode;
    ticket changingTicket;
};
#endif // WIDGET_USER_H
