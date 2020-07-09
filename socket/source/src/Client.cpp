#include "Client.h"

Client::Client()
{
	m_status = false;
	sprintf_s(m_ID, sizeof(m_ID), "-1");
	m_socket = -1;
}

Client::~Client()
{
}

int Client::init() //返回-1，初始化WinSock失败，-2建立TCPSocket失败，-3连接服务器失败
{
	m_status = true;
	m_port = 8888;

	//初始化WinSock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "Load WinSock Failed!";
		return -1;
	}
	//建立TCPSocket
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		cout << "socket() fail:" << WSAGetLastError() << endl;
		return -2;
	}
	//获取连接对象
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(m_port);
	addrSrv.sin_addr.s_addr = inet_addr("127.0.0.1");
	//发起连接
	if (connect(m_socket, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR)) == INVALID_SOCKET)
	{
		cout << "connect() fail" << WSAGetLastError() << endl;
		return -3;
	}
	return 0;
}

//1.消息 3.登录确认 4.在线ID 5.‘4’获取结束 6.增加在线用户 8.注册确认
int Client::parseMessage(char *oriMsg) //3.登录确认  8.注册确认
{
	if (oriMsg[3] - 48 == '1')
		return 0;
	else
		return -1;
}
int Client::parseMessage(char *oriMsg, char *msg1) // 4.在线ID 5.‘4’获取结束 6.增加在线用户
{
	int len = strlen(oriMsg);
	int tag = oriMsg[1] - 48;
	int flag = 1;
	for (int i = 2, len1 = 0, len2 = 0, len3 = 0; i < len; i++)
	{
		if (flag == 2)
		{
			msg1[len1] = oriMsg[i];
			len1++;
		}
		if (oriMsg[i] == '#')
			flag++;
	}
	return tag;
}
int Client::parseMessage(char *oriMsg, char *msg1, char *msg2, char *msg3) //1.消息
{
	int len = strlen(oriMsg);
	int tag = oriMsg[1] - 48;
	int flag = 1;
	for (int i = 2, len1 = 0, len2 = 0, len3 = 0; i < len; i++)
	{
		if (flag == 2)
		{
			msg1[len1] = oriMsg[i];
			len1++;
		}
		if (flag == 3)
		{
			msg2[len2] = oriMsg[i];
			len2++;
		}
		if (flag == 4)
		{
			msg3[len3] = oriMsg[i];
			len3++;
		}
		if (oriMsg[i] == '#')
			flag++;
	}
	return tag;
}

string Client::handleMessage(int tag, char *ID, char *password)
{
	return string("#" + to_string(tag) + "#" + string(ID) + "#" + string(password) + "#" + "#");
}

string Client::handleMessage(char *sendID, char *message, char *recvID)
{
	return string("#1#" + string(sendID) + "#" + string(message) + "#" + string(recvID) + "#");
}

int Client::sendMessage(char *oriMsg) //返回-1发送消息失败
{

	if (send(m_socket, oriMsg, strlen(oriMsg), 0) == SOCKET_ERROR)
		return -1;
	else
		return 0;
}

int Client::recvMessage(char *oriMsg) //返回-1接收消息失败
{
	char *recvMsg;
	int len = recv(m_socket, recvMsg, 1024, 0);

	if (len == 0)
		return -1;
	else if (len == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}
	else
	{
		oriMsg = recvMsg + '\0';
		return 0;
	}
}

int Client::qt_SignIn(char *ID, char *password) //返回-1，发送账号密码失败，-2接收服务器返回消息失败，-3登录失败用户名或密码有误
{
	int len = strlen(ID);
	for (int i = 0; i < len; i++)
	{
		m_ID[i] = ID[i];
	}
	//发送给服务器
	string temp = handleMessage(2, ID, password);
	char *oriMsg = &temp[0];
	int err = sendMessage(oriMsg);
	if (err = -1)
		return -1;
	else
	{
		//接收服务器发送成功的消息
		err = recvMessage(oriMsg);
		if (err = -1)
			return -2;
		//如果服务器返回成功，修改在线状态为上线，否则返回-3
		int flag = parseMessage(oriMsg);
		if (flag == 0)
			m_status = true;
		else
			return -3;
	}
	init();
	return 0;
}

int Client::qt_Register(char *ID, char *password) //返回-1，发送账号密码失败，-2接收服务器返回消息失败，-3用户名重复，-4，初始化WinSock失败，-5建立TCPSocket失败，-6连接服务器失败
{
	string temp = handleMessage(7, ID, password);
	char *oriMsg = &temp[0];
	int err = sendMessage(oriMsg);
	if (err = -1)
		return -1;
	err = recvMessage(oriMsg);
	if (err = -1)
		return -2;
	int flag = parseMessage(oriMsg);
	if (flag == 0)
		m_status = true;
	else
		return -3;
	int len = strlen(ID);
	for (int i = 0; i < len; i++)
	{
		m_ID[i] = ID[i];
	}
	//注册成功后要直接登录
	err = init();
	return err;
	return 0;
}

int Client::qt_sendMessage(char *sendID, char *message, char *recvID)
{
	string temp = handleMessage(sendID, message, recvID);
	char *oriMsg = &temp[0];
	int err = sendMessage(oriMsg);
	if (err = -1)
		return -1;
	else
		return 0;
}

int Client::qt_onlineID(char *ID)
{
	while (1)
	{
		char *oriMsg;
		char *t;
		recvMessage(oriMsg);
		int tag = parseMessage(oriMsg, t);
		if (tag != 5)
			ID = t;
		return 0;
	}
}

int Client::qt_Message(char *sendID, char *msg)
{
	char *oriMsg , *revID;
	int err = recvMessage(oriMsg);
	parseMessage(oriMsg,sendID, msg, revID);
	if (err = -1)
		return -1;
	else
		return 0;
}
