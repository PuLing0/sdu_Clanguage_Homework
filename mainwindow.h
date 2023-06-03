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
    int cornerRadius = 20;
    QPoint lastPos;
    QWidget *border = nullptr;
    QGraphicsDropShadowEffect *windowShadow;

    bool mousePressed = false;
    enum {AT_LEFT = 1, AT_TOP = 2,  AT_RIGHT = 4, AT_BOTTOM = 8,
          AT_TOP_LEFT = 3, AT_TOP_RIGHT = 6, AT_BOTTOM_LEFT = 9, AT_BOTTOM_RIGHT = 12};
    int mouseState;
    bool maximized = false;

    void Init();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event){
        mousePressed = false;
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
        if(event->globalPosition().y() < 2)
            controlWindowScale();
#else
        if(event->globalPos().y() < 2)
            controlWindowScale();
#endif
    }
    void mouseDoubleClickEvent(QMouseEvent *event)
    {
        if(event->y()<60)
            controlWindowScale();
    };
    void resizeEvent(QResizeEvent *event);

    QRect lastGeometry;
    void controlWindowScale();

private slots:
    void on_btn_login_clicked();//登录按钮

    void on_btn_reg_clicked();//注册按钮

    void on_btn_chg_clicked();//修改密码按钮

};
#endif // _MAINWINDOWH_H
