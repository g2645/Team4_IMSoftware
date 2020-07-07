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

int Client::init()
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
	if (m_socket == INVALID_SOCKET) {
		cout << "socket() fail:" << WSAGetLastError() << endl;
		return -2;
	}
	//获取连接对象  
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(m_port);
	addrSrv.sin_addr.s_addr = inet_addr("127.0.0.1");
	//发起连接
	if (connect(m_socket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == INVALID_SOCKET)
	{
		cout << "connect() fail" << WSAGetLastError() << endl;
		return -1;
	}
	return 0;
}

void Client::parseMessage(char* oriMsg, int* type, char* sendID, char* msg, char* revID)
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
		else if(flag==3)
		{
			msg[i_msg] = oriMsg[i];
			i_msg++;
		}
		//如果是接收方的ID
		else if (flag==4)
		{
			revID[i_revID] = oriMsg[i];
			i_revID++;
		}
	}

	sendID[i_sendID] = '\0';
	msg[i_msg] = '\0';
	revID[i_revID] = '\0';
}

vector <char*> Client::onlineID()
{

}

void Client::handleMessage(int tag,char* oriMsg,char* msg)
{
	if (tag == 2)
		oriMsg = '#'+'2'+'#'+'#'+msg+'#'+'#';
	else
		oriMsg = '#'+'3'+'#'+'#'+msg+'#'+'#';
}

void Client::handleMessage(int tag,char* oriMsg,char* msg1,char* msg2,char* msg3)
{
	oriMsg = '#'+'1'+'#'+msg1+'#'+msg2+'#'+msg3+'#';
}

int Client::sendMessage(char* oriMsg)
{
	if(send(m_socket,oriMsg,strlen(oriMsg),0)==SOCKET_ERROR)
		return -1;
	else
		return 0;
}

int Client::recvMessage(char* oriMsg)
{
	char* recvMsg;
    int len = recv(m_socket,recvMsg, 1024, 0);

    if (len == 0)
        return -1;
    else if (len == SOCKET_ERROR) 
	{
        return WSAGetLastError();
    }
    else
    {
        oriMsg= recvMsg +'\0';
		return 0;
    }
}

int Client::qt_SignIn(char* ID,char* password)
{
	//?注册这部分再讨论下
}

int Client::qt_Register(char* ID,char* password)
{
	//发送给服务器
	char* oriMsg;
	handleMessage(2,oriMsg,ID);
	sendMessage(oriMsg);
	handleMessage(3,oriMsg,password);
	sendMessage(oriMsg);
}

int Client::qt_sendMessage(char* sendID,char* message,char* recvID)
{
	char* oriMsg;
	handleMessage(1,oriMsg,sendID,message,recvID);
	sendMessage(oriMsg);
}

int Client::qt_onlineID()
{
	onlineID();
}

int Client::qt_Message()
{
	int* type;
	char* oriMsg,* sendID,* msg,* revID;
	recvMessage(oriMsg);
	parseMessage(oriMsg, type, sendID, msg, revID);
}

