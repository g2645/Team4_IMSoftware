#include "chatmessage.h"
#include "ui_chatmessage.h"

ChatMessage::ChatMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatMessage)
{
    ui->setupUi(this);
}

ChatMessage::~ChatMessage()
{
    delete ui;
}
