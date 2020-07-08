#pragma execution_character_set("utf-8")

#include "friendlist.h"
#include "ui_friendlist.h"
#include "login.h"
#include <QStandardItemModel>
#include "chatmessage.h"
#include <QLabel>
#include <QObject>
#include <QMessageBox>

#include "muitemdelegate.h"


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

    MuItemDelegate *pItemDelegate = new MuItemDelegate(this);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView->setItemDelegate(pItemDelegate);
    ui->listView->setModel(m_model);
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
    this->hide();
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
