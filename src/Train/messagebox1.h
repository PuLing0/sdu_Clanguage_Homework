#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QWidget>

namespace Ui {
class messagebox;
}

class messagebox : public QWidget
{
    Q_OBJECT

public:
    explicit messagebox(QWidget *parent = nullptr);
    ~messagebox();

private:
    Ui::messagebox *ui;
};

#endif // MESSAGEBOX_H
