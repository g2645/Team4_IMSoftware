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
	int qt_onlineID();
	//显示消息
	int qt_Message();
	//初始化
	int init();
	//向服务器发送
	//1.消息2.账号3.密码
	int sendMessage(char* oriMsg);
	//接收服务器的消息
	int recvMessage(char* oriMsg);
	//处理消息
	void handleMessage(int tag,char* oriMsg,char* msg);
	void handleMessage(int tag,char* oriMsg,char* msg1,char* msg2,char* msg3);
	//解析消息
	void parseMessage(char* oriMsg, int* type, char* sendID, char* msg, char* revID);
	//接收服务器在线列表
	vector <char*> onlineID();
};

