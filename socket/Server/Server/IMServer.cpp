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
	//��ʼ��IP
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
		printf("WSAStartup ��ʼ��ʧ�ܣ�������룺%d", err);
		return 1;
	}
	//�����׽���
	m_listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_listenSocket == INVALID_SOCKET)
	{
		return 1;
	}
	//��ַ
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(m_port);
	saddr.sin_addr.S_un.S_addr = inet_addr(m_ip);
	//saddr.sin_addr.S_un.S_addr = inet_addr(m_ip);
	//��
	if (bind(m_listenSocket, (LPSOCKADDR)&saddr, sizeof(saddr)) == SOCKET_ERROR)
	{
		return 1;
	}
	//����
	listen(m_listenSocket, 5);

	memset(socketArray, 0, sizeof(socketArray));
	memset(eventArray, 0, sizeof(eventArray));
	//�����¼���ע���
	WSAEVENT newEvent = WSACreateEvent();
	WSAEventSelect(m_listenSocket, newEvent, FD_ACCEPT | FD_CLOSE);

	socketArray[m_onlineNum] = m_listenSocket;
	eventArray[m_onlineNum] = newEvent;

	Client* newClient = new Client();
	m_client[m_onlineNum] = newClient;
	
	m_onlineNum = 1;
	//�����߳�
	m_listenThread = CreateThread(NULL, 0, ListenThreadFunc, (LPVOID)this, 0, &m_listenThreadId);
	
	if (m_listenThreadId == NULL)
	{
		cout << "���������߳�ʧ��";
		closesocket(m_listenSocket);
	}
	return 0;
}

void IMServer::parseMessage(char* oriMsg, int* type, char* sendID, char* msg, char* revID)
{
	//��ȡָ��
	*type = oriMsg[1] - '0';
	//#��ͳ��
	int flag = 2;
	//ԭʼ��Ϣ����
	int len = strlen(oriMsg);
	//����ͳ��
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
		//����Ƿ��ͷ���ID
		if (flag == 2)
		{
			sendID[i_sendID] = oriMsg[i];
			i_sendID++;
		}
		//�������Ϣ
		else if (flag == 3)
		{
			msg[i_msg] = oriMsg[i];
			i_msg++;
		}
		//����ǽ��շ���ID
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
	//һ��һ�����������û�ID
	for (int i = 1; i < m_onlineNum; i++)
	{
		sprintf_s(buffer, sizeof(buffer), "#4#%s###",m_client[i]);
		sendMessage(buffer, socket);
	}
	//�������
	sprintf_s(buffer, sizeof(buffer), "#5#####");
	sendMessage(buffer, socket);
	return 0;
}

int IMServer::Register(char* id, char* passwd)
{
	int ret = selectAccount(id, passwd, false);
	if (ret == 0)
	{
		//�û�ID�Ѿ����ڣ�ע��ʧ��
		return 1;
	}
	//�������ݿ⣬ע��ɹ�
	insertAccount(id, passwd);
	return 0;
}

int IMServer::Login(char* ID, char* passwd)
{
	int ret = selectAccount(ID, passwd);
	if (0/*��Ϣ��ƥ��*/)
	{
		return 1;
	}
	if (0/*������*/)
	{

		return 2;
	}
	return 0;
}

int IMServer::insertAccount(char* id, char* passwd)
{
	//���˺�������������ݿ�
	return 0;
}

int IMServer::insertData(char* sendID, char* msg, char* revID)
{
	//�����¼�������ݿ�
	return 0;
}


int IMServer::selectAccount(char* id, char* passwd, bool needPasswd)
{
	if (needPasswd)
	{
		//�������ѯ���ݿ�
	}
	else
	{
		//���������ѯ���ݿ�
	}
	return 0;
}

int IMServer::sendMessage(char* oriMsg, SOCKET socket)
{
	int ret = send(socket, oriMsg, strlen(oriMsg), 0);
	return ret;
}
//���ӿͻ���
int IMServer::addClient(SOCKET socket, WSAEVENT event)
{
	if (m_onlineNum > MAX_ONLINE)
	{
		cout << "�׽��ֳ�������" << endl;
		return 1;
	}
	//���׽���
	socketArray[m_onlineNum] = socket;
	//���¼�
	eventArray[m_onlineNum] = event;
	//���ӿͻ���
	Client* newClient = new Client();
	newClient->m_socket = socket;
	m_client[m_onlineNum] = newClient;
	m_onlineNum++;
	return 0;
}
