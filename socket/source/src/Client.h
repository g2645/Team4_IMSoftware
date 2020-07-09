#pragma once
#include "stdafx.h"
class Client
{
public:
	Client();
	~Client();

public:
	//ID客户端ID
	char m_ID[ID_LEN];
	//客户端套接字
	SOCKET m_socket;
	//登录状态
	bool m_status;
	//端口
	int m_port;

	WORD    wVersionRequested;
	WSADATA wsaData;

	//用户点击登录
	int qt_SignIn(char* ID,char* password);
	//用户点击注册
	int qt_Register(char* ID,char* password);
	//用户点击发送
	int qt_sendMessage(char* sendID,char* message,char* recvID);
	//显示在线列表
	int qt_onlineID(char *ID);
	//显示消息
	int qt_Message(char *sendID, char *msg);
	//初始化
	int init();
	//向服务器发送
	//1.消息2.登录提交7.注册提交
	int sendMessage(char* oriMsg);
	//接收服务器的消息
	int recvMessage(char* oriMsg);
	//处理消息
	string handleMessage(int tag,char* ID,char* password);
	string handleMessage(char* sendID,char* message,char* recvID);
	//解析消息
	int parseMessage(char* oriMsg);//3.登录确认  8.注册确认
	int parseMessage(char* oriMsg, char* msg1);// 4.在线ID 5.‘4’获取结束 6.增加在线用户
	int parseMessage(char* oriMsg, char* msg1, char* msg2, char* msg3);//1.消息
};

