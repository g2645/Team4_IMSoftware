#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QWidget>
#include <QMetaType>
#include <QString>
#include <QModelIndex>

typedef struct {
    QString iconPath;
    QString singer;
    QString songsNb;
} MuItemData;

Q_DECLARE_METATYPE(MuItemData)
class QStandardItemModel;
namespace Ui {
class FriendList;
}

class FriendList : public QWidget
{
    Q_OBJECT

public:
    explicit FriendList(QWidget *parent = nullptr);
    ~FriendList();

private slots:
    void exitlogin();
    void showClick(QModelIndex index);
    void chat(QModelIndex);
private:
    char *Id;
    char *pParam;
    int mm;
private:
    QStandardItemModel *m_model;
    //QStandardItemModel *n_model;
    Ui::FriendList *ui;
};

#endif // FRIENDLIST_H
