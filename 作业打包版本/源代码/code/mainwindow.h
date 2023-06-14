#ifndef _MAINWINDOWH_H
#define _MAINWINDOWH_H

#include <QMainWindow>
#include <QTimer>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class framelessWidget; }
QT_END_NAMESPACE

class framelessWidget : public QWidget
{
    Q_OBJECT

public:
    framelessWidget(QWidget *parent = nullptr);
    ~framelessWidget();

private:
    Ui::framelessWidget *ui;
    int cornerRadius = 20;// 窗口圆角半径
    QPoint lastPos; // 上次鼠标位置
    QWidget *border = nullptr;// 窗口边框
    QGraphicsDropShadowEffect *windowShadow; // 窗口阴影效果

    bool mousePressed = false;// 鼠标按下标志位
    //鼠标状态
    enum {AT_LEFT = 1, AT_TOP = 2,  AT_RIGHT = 4, AT_BOTTOM = 8,
          AT_TOP_LEFT = 3, AT_TOP_RIGHT = 6, AT_BOTTOM_LEFT = 9, AT_BOTTOM_RIGHT = 12};
    int mouseState;// 当前鼠标状态
    bool maximized = false;// 窗口最大化标志位

    void Init();// 给centralwidget添加一个mainwidget，设置遮罩及遮挡锯齿边缘的board
    void mousePressEvent(QMouseEvent *event);// 鼠标按下事件(记录拉伸窗口或移动窗口时的起始坐标（左上角）)
    void mouseMoveEvent(QMouseEvent *event);// 鼠标移动事件处理函数
    void mouseReleaseEvent(QMouseEvent *event);// 鼠标释放事件处理函数

    void mouseDoubleClickEvent(QMouseEvent *event);// 鼠标双击事件处理函数

    void resizeEvent(QResizeEvent *event);// 窗口大小改变事件处理函数

    QRect lastGeometry;// 上次窗口位置信息
    void controlWindowScale();// 控制窗口缩放函数

private slots:
    void on_btn_login_clicked();//登录按钮

    void on_btn_reg_clicked();//注册按钮

    void on_btn_chg_clicked();//修改密码按钮

};
#endif // _MAINWINDOWH_H
