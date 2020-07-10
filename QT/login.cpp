#include "login.h"
#include "ui_login.h"
#include "friendlist.h"
#include "register.h"
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QPushButton>
#include <QObject>
#include "Client.cpp"
#include "baohan.h"
//#include ""
Client cli;

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->lineEdituser->setAlignment(Qt::AlignHCenter);
    ui->lineEdituser->setPlaceholderText("username");
    ui->lineEditpwd->setAlignment(Qt::AlignHCenter);
    ui->lineEditpwd->setEchoMode(QLineEdit::Password);
    ui->lineEditpwd->setPlaceholderText("password");
    connect(ui->registor,SIGNAL(clicked()),this,SLOT(registorclicked()));
    connect(ui->login,SIGNAL(clicked()),this,SLOT(loginclicked()));

}

Login::~Login()
{
    delete ui;
}


void Login::registorclicked()
{
    Register *r = new Register;
        r->show();
        this->hide();
}

void Login::loginclicked()
{
    QString username = ui->lineEdituser->text();
    QString password = ui->lineEditpwd->text();
    //Client *a =new Client;
    QByteArray ba = username.toLatin1();
    QByteArray bb = password.toLatin1();

    int c = cli.qt_SignIn(ba.data(),bb.data());
    if(username == ""||password =="")
    {
        QMessageBox::information(this,"warning","The user name and password cannot be empty!",QMessageBox::Ok);
    }else
    {
        switch(c){
        case -1:
            QMessageBox::information(this,"warning","fail in send!",QMessageBox::Ok);
            break;
        case -2:
            QMessageBox::information(this,"warning","Receiving server returned message failed!",QMessageBox::Ok);

            break;
        case 0:
            QMessageBox::information(this,"warning","Login failure, wrong user name or password!",QMessageBox::Ok);

            break;
        case -3:
            QMessageBox::information(this,"warning","Login successful!",QMessageBox::Ok);
            //int mn = cli.qt_firOnlineID();
            FriendList *m=new FriendList;
            m->show();
            this->close();
            break;
        }
//            QMessageBox::information(this,"warning","Login successful!",QMessageBox::Ok);
//            FriendList *m=new FriendList;
//            m->show();
//            this->close();
}


}
