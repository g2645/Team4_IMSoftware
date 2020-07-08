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

int Client::init()//返回-1，初始化WinSock失败，-2建立TCPSocket失败，-3连接服务器失败
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
	if (connect(m_socket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == INVALID_SOCKET)
	{
		cout << "connect() fail" << WSAGetLastError() << endl;
		return -3;
	}
	return 0;
}

void Client::parseMessage(char* oriMsg, int* type, char* sendID, char* msg, char* revID)
{
	//处理1.聊天消息2.账号密码3.成功失败
}

/*vector <char*> Client::onlineID()
{
}
*/
void Client::handleMessage(int tag,char* oriMsg,char* msg1,char* msg2)
{

}

void Client::handleMessage(int tag,char* oriMsg,char* msg1,char* msg2,char* msg3)
{

}

int Client::sendMessage(char* oriMsg)//返回-1发送消息失败
{
	if(send(m_socket,oriMsg,strlen(oriMsg),0)==SOCKET_ERROR)
		return -1;
	else
		return 0;
}

int Client::recvMessage(char* oriMsg)//返回-1接收消息失败
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

int Client::qt_SignIn(char* ID,char* password)//返回-1，发送账号密码失败，-2接收服务器返回消息失败，-3登录失败用户名或密码有误
{
	int len=strlen(ID);
	for(int i=0;i<len;i++)
	{
		m_ID[i]=ID[i];
	}
	//发送给服务器
	char* oriMsg;
	handleMessage(2,oriMsg,ID,password);
	int err = sendMessage(oriMsg);
	if(err = -1)
		return -1;
	else
	{
		//接收服务器发送成功的消息
		err=recvMessage(oriMsg);
		if(err = -1)
			return -2;
		//如果服务器返回成功，修改在线状态为上线，否则返回-3
		/*parseMessage();
		if()
			m_status=true;
		else
			return -3;*/
	}
	init();
}

int Client::qt_Register(char* ID,char* password)
{
	//?注册这部分再讨论下
	return 0;
}

int Client::qt_sendMessage(char* sendID,char* message,char* recvID)
{
	char* oriMsg;
	handleMessage(1,oriMsg,sendID,message,recvID);
	int err = sendMessage(oriMsg);
	if(err = -1)
		return -1;
	else if(err = 0)
		return 0;
}

int Client::qt_onlineID()
{
	//onlineID();
	return 0;
}

int Client::qt_Message()
{
	int* type;
	char* oriMsg,* sendID,* msg,* revID;
	int err = recvMessage(oriMsg);
	parseMessage(oriMsg, type, sendID, msg, revID);
	if(err = -1)
		return -1;
	else if(err = 0)
		return 0;
}

