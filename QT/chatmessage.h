#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QWidget>

namespace Ui {
class ChatMessage;
}

class ChatMessage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatMessage(QWidget *parent = nullptr);
    ~ChatMessage();

private:
    Ui::ChatMessage *ui;
};

#endif // CHATMESSAGE_H
