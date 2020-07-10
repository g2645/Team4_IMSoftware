#ifndef BAOHAN_H
#define BAOHAN_H

#include <QWidget>
#include "Client.h"
#include "login.h"
#include "chatmessage.h"
#include "friendlist.h"
//Client cli;
class baohan : public QWidget
{
    Q_OBJECT

public:
    baohan(QWidget *parent = nullptr);
    ~baohan();
signals:

private slots:

private:
     Client *cli;
     //ChatMessage *b;
};
//extern Client cli;
#endif // BAOHAN_H
