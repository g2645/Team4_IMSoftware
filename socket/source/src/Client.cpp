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

int Client::init() //����-1����ʼ��WinSockʧ�ܣ�-2����TCPSocketʧ�ܣ�-3���ӷ�����ʧ��
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
	if (connect(m_socket, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR)) == INVALID_SOCKET)
	{
		cout << "connect() fail" << WSAGetLastError() << endl;
		return -3;
	}
	return 0;
}

//1.��Ϣ 3.��¼ȷ�� 4.����ID 5.��4����ȡ���� 6.���������û� 8.ע��ȷ��
int Client::parseMessage(char *oriMsg) //3.��¼ȷ��  8.ע��ȷ��
{
	if (oriMsg[3] - 48 == '1')
		return 0;
	else
		return -1;
}
int Client::parseMessage(char *oriMsg, char *msg1) // 4.����ID 5.��4����ȡ���� 6.���������û�
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
int Client::parseMessage(char *oriMsg, char *msg1, char *msg2, char *msg3) //1.��Ϣ
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

int Client::sendMessage(char *oriMsg) //����-1������Ϣʧ��
{

	if (send(m_socket, oriMsg, strlen(oriMsg), 0) == SOCKET_ERROR)
		return -1;
	else
		return 0;
}

int Client::recvMessage(char *oriMsg) //����-1������Ϣʧ��
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

int Client::qt_SignIn(char *ID, char *password) //����-1�������˺�����ʧ�ܣ�-2���շ�����������Ϣʧ�ܣ�-3��¼ʧ���û�������������
{
	int len = strlen(ID);
	for (int i = 0; i < len; i++)
	{
		m_ID[i] = ID[i];
	}
	//���͸�������
	string temp = handleMessage(2, ID, password);
	char *oriMsg = &temp[0];
	int err = sendMessage(oriMsg);
	if (err = -1)
		return -1;
	else
	{
		//���շ��������ͳɹ�����Ϣ
		err = recvMessage(oriMsg);
		if (err = -1)
			return -2;
		//������������سɹ����޸�����״̬Ϊ���ߣ����򷵻�-3
		int flag = parseMessage(oriMsg);
		if (flag == 0)
			m_status = true;
		else
			return -3;
	}
	init();
	return 0;
}

int Client::qt_Register(char *ID, char *password) //����-1�������˺�����ʧ�ܣ�-2���շ�����������Ϣʧ�ܣ�-3�û����ظ���-4����ʼ��WinSockʧ�ܣ�-5����TCPSocketʧ�ܣ�-6���ӷ�����ʧ��
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
	//ע��ɹ���Ҫֱ�ӵ�¼
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
