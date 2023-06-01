#ifndef DIALOGADDTICKET_H
#define DIALOGADDTICKET_H

#include <QDialog>
#include<QString>
namespace Ui {
class dialogaddticket;
}

class dialogaddticket : public QDialog
{
    Q_OBJECT
friend class Widget;
public:
    explicit dialogaddticket(QWidget *parent = 0);
    ~dialogaddticket();
    QString getid();
    QString getba();
    QString getea();
    QString getbt();
    QString getet();
    QString getticket();
    QString getprice();
    int flap;
public slots:
    void saveclicked();

signals:

private:
    Ui::dialogaddticket *ui;

};

#endif // DIALOGADDTICKET_H
