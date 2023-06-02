#ifndef DIALOG1_H
#define DIALOG1_H

#include <QGroupBox>
#include <user.h>
namespace Ui {
class dialog1;
}

class dialog1 : public QGroupBox
{
    Q_OBJECT

public:
    explicit dialog1(QWidget *parent = nullptr);
    void setUser(user t); //设置当前用户
    ~dialog1();

signals:
    void send(bool mode, ticket a); //窗口间传递changingTicket

private slots:
    void on_tableWidget_2_cellDoubleClicked(int row, int column); //双击改签/退票单元格事件

    void on_pushButton_clicked(); //已购票据查询按钮

    void on_pushButton_2_clicked(); //退出按钮

private:
    Ui::dialog1 *ui;
    user currentUser; //当前用户
    QList<ticket> tickets; //用户已购票据
};

#endif // DIALOG1_H
