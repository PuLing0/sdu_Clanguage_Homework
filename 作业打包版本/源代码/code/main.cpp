#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    framelessWidget w;
    w.setWindowFlags(Qt::FramelessWindowHint);//设置无边框
    w.setAttribute(Qt::WA_TranslucentBackground);//设置半透明背景
    w.setWindowTitle("登录");
    w.show();
    return a.exec();
}
