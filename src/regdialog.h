#ifndef REGDIALOG_H
#define REGDIALOG_H

#include <QWidget>

namespace Ui {
class RegDialog;
}

class RegDialog : public QWidget
{
    Q_OBJECT

public:
    explicit RegDialog(QWidget *parent = nullptr);//默认构造函数
    ~RegDialog();//默认析构函数
    bool Gender_Choose();//用于性别选择，其中男性返回1，女性返回0，默认是男性

private slots:
    void on_Btn_Back_clicked();//返回mainwindow

    void on_Btn_Reg_clicked();//注册用户

private:
    Ui::RegDialog *ui;
};

#endif // REGDIALOG_H
