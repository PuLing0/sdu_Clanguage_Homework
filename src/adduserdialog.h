#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>
#include<QString>
namespace Ui {
class adduserdialog;
}

class adduserdialog : public QDialog
{
    Q_OBJECT

public:
    explicit adduserdialog(QWidget *parent = 0);
    ~adduserdialog();\
    QString getid();
    QString getname();
    QString getpw();
    bool isaddclicked();

private:
    Ui::adduserdialog *ui;
};

#endif // ADDUSERDIALOG_H
