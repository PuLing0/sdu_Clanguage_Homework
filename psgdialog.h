#ifndef PSGDIALOG_H
#define PSGDIALOG_H

#include <QWidget>

namespace Ui {
class PsgDialog;
}

class PsgDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PsgDialog(QWidget *parent = nullptr);
    ~PsgDialog();

private:
    Ui::PsgDialog *ui;
};

#endif // PSGDIALOG_H
