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

int Client::init()//����-1����ʼ��WinSockʧ�ܣ�-2����TCPSocketʧ�ܣ�-3���ӷ�����ʧ��
{
	m_status = true;
	m_port = 8888;

	//��ʼ��WinSock  
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "Load WinSock Failed!";
		return -1;
	}
	//����TCPSocket
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET) 
	{
		cout << "socket() fail:" << WSAGetLastError() << endl;
		return -2;
	}
	//��ȡ���Ӷ���  
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(m_port);
	addrSrv.sin_addr.s_addr = inet_addr("127.0.0.1");
	//��������
	if (connect(m_socket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == INVALID_SOCKET)
	{
		cout << "connect() fail" << WSAGetLastError() << endl;
		return -3;
	}
	return 0;
}

void Client::parseMessage(char* oriMsg, int* type, char* sendID, char* msg, char* revID)
{
	//����1.������Ϣ2.�˺�����3.�ɹ�ʧ��
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

int Client::sendMessage(char* oriMsg)//����-1������Ϣʧ��
{
	if(send(m_socket,oriMsg,strlen(oriMsg),0)==SOCKET_ERROR)
		return -1;
	else
		return 0;
}

int Client::recvMessage(char* oriMsg)//����-1������Ϣʧ��
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

int Client::qt_SignIn(char* ID,char* password)//����-1�������˺�����ʧ�ܣ�-2���շ�����������Ϣʧ�ܣ�-3��¼ʧ���û�������������
{
	int len=strlen(ID);
	for(int i=0;i<len;i++)
	{
		m_ID[i]=ID[i];
	}
	//���͸�������
	char* oriMsg;
	handleMessage(2,oriMsg,ID,password);
	int err = sendMessage(oriMsg);
	if(err = -1)
		return -1;
	else
	{
		//���շ��������ͳɹ�����Ϣ
		err=recvMessage(oriMsg);
		if(err = -1)
			return -2;
		//������������سɹ����޸�����״̬Ϊ���ߣ����򷵻�-3
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
	//?ע���ⲿ����������
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

