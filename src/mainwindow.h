#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);//默认构造函数
    ~MainWindow();//默认析构函数

private slots:
    void on_btn_login_clicked();//登录按钮

    void on_btn_reg_clicked();//注册按钮

    void on_btn_chg_clicked();//修改密码按钮

    void on_checkBox_clicked(bool checked);//显示密码

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
