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
    explicit chgpdDialog(QWidget *parent = nullptr);//构造函数
    ~chgpdDialog();//析构函数

    void paintEvent(QPaintEvent *event);//边框加一条黑边以便识别

private slots:
    void on_btn_back_clicked();// 返回到mainwindow

    void on_btn_chg_clicked();// 确认修改密码

protected:
    //用于鼠标拖动窗口移动
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::chgpdDialog *ui;
    QPoint reltvPos; // 相对坐标
    bool m_bMove; // 是否移动
};

#endif // CHGPDDIALOG_H
