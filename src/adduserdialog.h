#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H
#include"regdialog.h"
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
    ~adduserdialog();
    bool Gender_Choose();//用于性别选择，其中男性返回1，女性返回0，默认是男性
    QString account;//用户账号
    QString password;//用户密码
    bool gender;//用户性别，1是男性，2是女性
    QString name;//用户名
    bool Over_Power;//用户权限，1是管理员，2是普通用户
    int flap;
public slots:
        void btnclicked();
private:
    Ui::adduserdialog *ui;
};

#endif // ADDUSERDIALOG_H
