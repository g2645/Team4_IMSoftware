#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QPushButton>
#include "register.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void mySignal();
private slots:
    void registorclicked();

    //void returnClicked();

    void loginclicked();

private:
    Ui::Login *ui;
};
#endif // LOGIN_H
