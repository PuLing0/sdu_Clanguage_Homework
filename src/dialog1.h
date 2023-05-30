#ifndef DIALOG1_H
#define DIALOG1_H

#include <QGroupBox>
#include <user.h>
namespace Ui {
class dialog1;
}

class dialog1 : public QGroupBox
{
    Q_OBJECT

public:
    explicit dialog1(QWidget *parent = nullptr);
    void setUser(user t);
    ~dialog1();

signals:
    void send(bool mode, ticket a);

private slots:
    void on_tableWidget_2_cellDoubleClicked(int row, int column);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::dialog1 *ui;
    user currentUser;
    QList<ticket> tickets;
};

#endif // DIALOG1_H
