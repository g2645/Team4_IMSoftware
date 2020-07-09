#pragma once
#include "stdafx.h"
#include "Client.h"
class IMServer
{
public:
	IMServer();
	~IMServer();



public:
	//监听套接字
	SOCKET m_listenSocket;
	//端口
	int m_port;
	//启动指定IP
	char m_ip[IP_SIZE];
	//套接字数组
	SOCKET socketArray[51];
	//绑定的事件
	WSAEVENT eventArray[51];
	//客户端数组信息
	Client* m_client[51];
	//在线人数
	int m_onlineNum;
	//启动标志
	bool m_start;
	//监听线程句柄
	HANDLE m_listenThread;
	//监听线程ID
	DWORD  m_listenThreadId;
	//数据初始化
	int initData();
	//启动
	int startUp();
	//解析数据
	void parseMessage(char* oriMsg, int* type, char* sendID, char* msg, char* revID);
	//向客户端发送在线用户信息
	int senndAllOnlineClient(SOCKET socket);
	//用户注册
	int Register(char* id, char* passwd);
	//用户登录
	int Login(char* id, char* passwd);
	//插入账号和密码
	int insertAccount(char* id, char* passwd);
	//插入聊天记录
	int insertData(char* sendID, char* msg, char* revID);
	//获取账号密码
	int selectAccount(char* ID, char* passwd, bool needPasswd = true);
	//发送数据
	int sendMessage(char* oriMsg, SOCKET socket);
	//增加一个客户端
	int addClient(SOCKET socket, WSAEVENT event);

};

