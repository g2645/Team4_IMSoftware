#include "login.h"
#include <QApplication>
#include <QFile>
#include "friendlist.h"
#include "Client.h"
#include "baohan.h"


void Client()
{

}

void setStyle(const QString &qssFile)
{
    QFile qss(qssFile);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //new class Client(cil);
    Login w;
    w.show();
    return a.exec();
}
