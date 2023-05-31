#ifndef CHGPDDIALOG_H
#define CHGPDDIALOG_H

#include <QWidget>

namespace Ui {
class chgpdDialog;
}

class chgpdDialog : public QWidget
{
    Q_OBJECT

public:
    explicit chgpdDialog(QWidget *parent = nullptr);
    ~chgpdDialog();

private slots:
    void on_btn_back_clicked();// 返回到mainwindow

    void on_btn_chg_clicked();// 确认修改密码

private:
    Ui::chgpdDialog *ui;
};

#endif // CHGPDDIALOG_H
