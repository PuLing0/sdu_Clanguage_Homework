#ifndef PROMPT1_H
#define PROMPT1_H

#include <QGroupBox>

namespace Ui {
class prompt1;
}

class prompt1 : public QGroupBox
{
    Q_OBJECT

public:
    explicit prompt1(QWidget *parent = nullptr);
    ~prompt1();
    void setText(QString a); //设置提示框文本

private slots:
    void on_pushButton_clicked(); //确定按钮

private:
    Ui::prompt1 *ui;
};

#endif // PROMPT1_H
