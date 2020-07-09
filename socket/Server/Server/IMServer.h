#pragma once
#include "stdafx.h"
#include "Client.h"
class IMServer
{
public:
	IMServer();
	~IMServer();



public:
	//�����׽���
	SOCKET m_listenSocket;
	//�˿�
	int m_port;
	//����ָ��IP
	char m_ip[IP_SIZE];
	//�׽�������
	SOCKET socketArray[51];
	//�󶨵��¼�
	WSAEVENT eventArray[51];
	//�ͻ���������Ϣ
	Client* m_client[51];
	//��������
	int m_onlineNum;
	//������־
	bool m_start;
	//�����߳̾��
	HANDLE m_listenThread;
	//�����߳�ID
	DWORD  m_listenThreadId;
	//���ݳ�ʼ��
	int initData();
	//����
	int startUp();
	//��������
	void parseMessage(char* oriMsg, int* type, char* sendID, char* msg, char* revID);
	//��ͻ��˷��������û���Ϣ
	int senndAllOnlineClient(SOCKET socket);
	//�û�ע��
	int Register(char* id, char* passwd);
	//�û���¼
	int Login(char* id, char* passwd);
	//�����˺ź�����
	int insertAccount(char* id, char* passwd);
	//���������¼
	int insertData(char* sendID, char* msg, char* revID);
	//��ȡ�˺�����
	int selectAccount(char* ID, char* passwd, bool needPasswd = true);
	//��������
	int sendMessage(char* oriMsg, SOCKET socket);
	//����һ���ͻ���
	int addClient(SOCKET socket, WSAEVENT event);

};

