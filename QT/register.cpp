#include "register.h"
#include "ui_register.h"
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include "login.h"
//#include "mysqlite.hpp"
#include <QObject>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    ui->lineEdituser->setAlignment(Qt::AlignHCenter);
    ui->lineEdituser->setPlaceholderText("username");
    ui->lineEditpwd->setAlignment(Qt::AlignHCenter);
    ui->lineEditpwd->setEchoMode(QLineEdit::Password);
    ui->lineEditpwd->setPlaceholderText("password");
    connect(ui->return_2,SIGNAL(clicked()),this,SLOT(returnClicked()));
}

Register::~Register()
{
    delete ui;
}

void Register::returnClicked()
{
    Login *a = new Login;
    a->show();
    this->hide();
}

void Register::registerchick()
{
    QString username = ui->lineEdituser->text();
    QString password = ui->lineEditpwd->text();
//    sqlite3 *db = NULL;
//        int ret;
//        ret = sqlite3_open("mmm.db", &db);
//        if (ret != SQLITE_OK)
//        {
//            perror("sqlite3_open");
//           // return -1;
//        }
//        MySqlite *a =new MySqlite;
//        QByteArray ba = username.toLatin1();
//        QByteArray bb = password.toLatin1();
//     a->insert_record(db,ba.data(),bb.data());
//    QSqlQuery query;
//        query.prepare("select username from patient where username=:username");
//        query.bindValue(":username", username);
//        query.exec();
//        if(query.next())
//        {

//            QMessageBox::information(this,"警告","用户名已存在！",QMessageBox::Ok);

//        }
//        else
//        {
//            query.prepare("insert into patient(username,password)"
//                          "values(:username,:password)");
//            query.bindValue(":username", username);
//            query.bindValue(":password",password);

//            query.exec();
//            QMessageBox::information(this,"警告","注册成功！",QMessageBox::Ok);

//        }
}

