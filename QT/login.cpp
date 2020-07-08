#include "login.h"
#include "ui_login.h"
#include "friendlist.h"
#include "register.h"
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QPushButton>
#include <QObject>

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
//    if(username == ""||password =="")
//    {
//        QMessageBox::information(this,"警告","输入不能为空",QMessageBox::Ok);
//    }else
//    {
//        QSqlQuery query;
//        query.prepare("select username,password from admin where username=:username and password = :password");

//        query.bindValue(":username",username);
//        query.bindValue(":password",password);
//        query.exec();
//        if(!query.next())
//        {
//            QMessageBox::information(this,"警告","用户名或密码错误!",QMessageBox::Ok);

//        }else{
//            QMessageBox::information(this,"提醒","登录成功!",QMessageBox::Ok);
            FriendList *m=new FriendList;
            m->show();
            this->close();
//        }
//    }
}


