#ifndef CHANGETICKETDIALOG_H
#define CHANGETICKETDIALOG_H

#include <QDialog>
#include<QString>
namespace Ui {
class changeticketdialog;
}

class changeticketdialog : public QDialog
{
    Q_OBJECT

public:
    explicit changeticketdialog(QWidget *parent = 0);
    ~changeticketdialog();
    QString getiniid();
    QString getiniba();
    QString getiniea();
    QString getinibt();
    QString getiniet();
    QString getfinba();
    QString getfinea();
    QString getfinbt();
    QString getfinet();
    QString getfinnumber();
    QString getfinprice();
    void on_changebtn_clicked();
        int flap;

private:
    Ui::changeticketdialog *ui;

};

#endif // CHANGETICKETDIALOG_H
