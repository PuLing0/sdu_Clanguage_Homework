#ifndef OPDIALOG_H
#define OPDIALOG_H

#include <QWidget>

namespace Ui {
class OPDialog;
}

class OPDialog : public QWidget
{
    Q_OBJECT

public:
    explicit OPDialog(QWidget *parent = nullptr); //默认构造函数
    ~OPDialog(); //默认析构函数

private:
    Ui::OPDialog *ui;
};

#endif // OPDIALOG_H
