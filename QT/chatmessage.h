#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QWidget>
#include <QListWidgetItem>
#include "chatmessage/qnchatmessage.h"

namespace Ui {
class ChatMessage;
}

class ChatMessage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatMessage(QWidget *parent = nullptr);
    ~ChatMessage();
    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
    void dealMessageTime(QString curMsgTime);
protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void sendclicked();
private:
    Ui::ChatMessage *ui;
};

#endif // CHATMESSAGE_H
