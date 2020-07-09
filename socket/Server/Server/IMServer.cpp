#include "stdafx.h"
#include "IMServer.h"

IMServer::IMServer()
{
}

IMServer::~IMServer()
{
}

int IMServer::initData()
{
	m_port = 8888;
	//初始化IP
	sprintf_s(m_ip, sizeof(m_ip), "127.0.0.1");
	m_onlineNum = 0;
	return 0;
}

int IMServer::startUp()
{
	initData();

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		int err = WSAGetLastError();
		printf("WSAStartup 初始化失败！错误代码：%d", err);
		return 1;
	}
	//监听套接字
	m_listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_listenSocket == INVALID_SOCKET)
	{
		return 1;
	}
	//地址
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(m_port);
	saddr.sin_addr.S_un.S_addr = inet_addr(m_ip);
	//saddr.sin_addr.S_un.S_addr = inet_addr(m_ip);
	//绑定
	if (bind(m_listenSocket, (LPSOCKADDR)&saddr, sizeof(saddr)) == SOCKET_ERROR)
	{
		return 1;
	}
	//监听
	listen(m_listenSocket, 5);

	memset(socketArray, 0, sizeof(socketArray));
	memset(eventArray, 0, sizeof(eventArray));
	//创建事件、注册绑定
	WSAEVENT newEvent = WSACreateEvent();
	WSAEventSelect(m_listenSocket, newEvent, FD_ACCEPT | FD_CLOSE);

	socketArray[m_onlineNum] = m_listenSocket;
	eventArray[m_onlineNum] = newEvent;

	Client* newClient = new Client();
	m_client[m_onlineNum] = newClient;
	
	m_onlineNum = 1;
	//开启线程
	m_listenThread = CreateThread(NULL, 0, ListenThreadFunc, (LPVOID)this, 0, &m_listenThreadId);
	
	if (m_listenThreadId == NULL)
	{
		cout << "启动监听线程失败";
		closesocket(m_listenSocket);
	}
	return 0;
}

void IMServer::parseMessage(char* oriMsg, int* type, char* sendID, char* msg, char* revID)
{
	//获取指令
	*type = oriMsg[1] - '0';
	//#号统计
	int flag = 2;
	//原始消息长度
	int len = strlen(oriMsg);
	//计数统计
	int i_sendID = 0;
	int i_msg = 0;
	int i_revID = 0;

	for (int i = 3; i < len; i++)
	{
		if (msg[i] == '#')
		{
			flag++;
			if (flag == 5)
			{
				break;
			}
			continue;
		}
		//如果是发送方的ID
		if (flag == 2)
		{
			sendID[i_sendID] = oriMsg[i];
			i_sendID++;
		}
		//如果是消息
		else if (flag == 3)
		{
			msg[i_msg] = oriMsg[i];
			i_msg++;
		}
		//如果是接收方的ID
		else if (flag == 4)
		{
			revID[i_revID] = oriMsg[i];
			i_revID++;
		}
	}

	sendID[i_sendID] = '\0';
	msg[i_msg] = '\0';
	revID[i_revID] = '\0';
}

int IMServer::senndAllOnlineClient(SOCKET socket)
{
	char buffer[BUFFER_SIZE];
	//一个一个传送在线用户ID
	for (int i = 1; i < m_onlineNum; i++)
	{
		sprintf_s(buffer, sizeof(buffer), "#4#%s###",m_client[i]);
		sendMessage(buffer, socket);
	}
	//传送完毕
	sprintf_s(buffer, sizeof(buffer), "#5#####");
	sendMessage(buffer, socket);
	return 0;
}

int IMServer::Register(char* id, char* passwd)
{
	int ret = selectAccount(id, passwd, false);
	if (ret == 0)
	{
		//用户ID已经存在，注册失败
		return 1;
	}
	//插入数据库，注册成功
	insertAccount(id, passwd);
	return 0;
}

int IMServer::Login(char* ID, char* passwd)
{
	int ret = selectAccount(ID, passwd);
	if (0/*信息不匹配*/)
	{
		return 1;
	}
	if (0/*不存在*/)
	{

		return 2;
	}
	return 0;
}

int IMServer::insertAccount(char* id, char* passwd)
{
	//将账号密码面插入数据库
	return 0;
}

int IMServer::insertData(char* sendID, char* msg, char* revID)
{
	//聊天记录插入数据库
	return 0;
}


int IMServer::selectAccount(char* id, char* passwd, bool needPasswd)
{
	if (needPasswd)
	{
		//带密码查询数据库
	}
	else
	{
		//不带密码查询数据库
	}
	return 0;
}

int IMServer::sendMessage(char* oriMsg, SOCKET socket)
{
	int ret = send(socket, oriMsg, strlen(oriMsg), 0);
	return ret;
}
//增加客户端
int IMServer::addClient(SOCKET socket, WSAEVENT event)
{
	if (m_onlineNum > MAX_ONLINE)
	{
		cout << "套接字超过限制" << endl;
		return 1;
	}
	//存套接字
	socketArray[m_onlineNum] = socket;
	//存事件
	eventArray[m_onlineNum] = event;
	//增加客户端
	Client* newClient = new Client();
	newClient->m_socket = socket;
	m_client[m_onlineNum] = newClient;
	m_onlineNum++;
	return 0;
}
