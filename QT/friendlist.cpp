#include "friendlist.h"
#include "ui_friendlist.h"
#include "login.h"
#include <QStandardItemModel>
#include "chatmessage.h"
#include <QLabel>
#include <QObject>
#include "baohan.h"
#include "muitemdelegate.h"
#include <QMessageBox>
#include "qdebug.h"

extern Client cli;
//ChatMessage b;

const QStringList icons = {
    ":/images/HotDog.jpg", ":/images/li.jpg", ":/images/logo.jpg",
    ":/images/PACT.jpg", ":/images/yang.jpg", ":/images/zhang.jpg",
};
const QStringList singers = {
    "MC-Hotdog", "li", "Author", "PACT", "yang", "zhang",
};

FriendList::FriendList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendList)
{
    ui->setupUi(this);
    QLabel *label = new QLabel();
    QPixmap pixmap(":/images/logo.jpg");
    ui->label_2->setPixmap(pixmap);
    ui->label_2->show();
    //int mn = cli.qt_firOnlineID(Id);
    int mn=0;
    while(mn==0)
    {
        mn=cli.qt_firOnlineID(Id);
        qDebug("111");
        break;
    }
    QStandardItemModel *pModel = new QStandardItemModel();
    for (int i=0; i<icons.size(); ++i) {
        QStandardItem *pItem = new QStandardItem;
        MuItemData itemData;
        itemData.singer = singers.at(i);
        itemData.songsNb = QString::number(i * i) + "s";
        itemData.iconPath = icons.at(i);
        pItem->setData(QVariant::fromValue(itemData), Qt::UserRole+1);
        pModel->appendRow(pItem);
    }
    m_model = pModel;

//    QStandardItemModel *n_model = new QStandardItemModel();
//    //QStandardItemModel *n_model;
//    QList<QStandardItem*> cItem;

    MuItemDelegate *pItemDelegate = new MuItemDelegate(this);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView->setItemDelegate(pItemDelegate);
    ui->listView->setModel(m_model);

//    cItem.push_back(new QStandardItem(QString("01")));
//    //cItem.push_back(new QStandardItem(QString("02")));
//    n_model->appendRow(cItem);
//    ui->listView_2->setModel(n_model);

    connect(ui->exitlogin,SIGNAL(clicked()),this,SLOT(exitlogin()));
    connect(ui->listView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(chat(QModelIndex)));
    //connect(ui->listView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(showClick(QModelIndex)));
}

FriendList::~FriendList()
{
    delete ui;
}

void FriendList::exitlogin()
{
    Login *c = new Login;
    c->show();
    this->hide();

}

void FriendList::chat(QModelIndex)
{
    ChatMessage *b = new ChatMessage;
    b->show();
    //this->hide();
}

void FriendList::showClick(QModelIndex index)
{
    QString strTemp;
    QVariant var = index.data(Qt::UserRole+1);//.value<MuItemData>.singer();
    MuItemData itemData = var.value<MuItemData>();

    QMessageBox msg;
    msg.setWindowTitle("Info");
    msg.setText(itemData.singer);
    msg.exec();
}
