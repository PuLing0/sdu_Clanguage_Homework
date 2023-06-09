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
    void paintEvent(QPaintEvent *event);//边框加一条黑边以便识别

private slots:
    void on_Btn_Back_clicked();//返回mainwindow

    void on_Btn_Reg_clicked();//注册用户

//用于鼠标拖动无边框窗口移动
protected:
    void mousePressEvent(QMouseEvent *event) override;// 鼠标按下事件处理函数
    void mouseMoveEvent(QMouseEvent *event) override; // 鼠标移动事件处理函数
    void mouseReleaseEvent(QMouseEvent *event) override;// 鼠标释放事件处理函数

private:
    Ui::RegDialog *ui;
    QPoint reltvPos; // 相对坐标
    bool m_bMove; // 是否移动
};

#endif // REGDIALOG_H
