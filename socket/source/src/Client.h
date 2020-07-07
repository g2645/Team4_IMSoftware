#pragma once
#include "stdafx.h"
class Client
{
public:
	Client();
	~Client();

public:
	//ID�ͻ���ID
	char m_ID[ID_LEN];
	//�ͻ����׽���
	SOCKET m_socket;
	//��¼״̬
	bool m_status;
	//�˿�
	int m_port;

	WORD    wVersionRequested;
	WSADATA wsaData;

	//�û������¼
	int qt_SignIn(char* ID,char* password);
	//�û����ע��
	int qt_Register(char* ID,char* password);
	//�û��������
	int qt_sendMessage(char* sendID,char* message,char* recvID);
	//��ʾ�����б�
	int qt_onlineID();
	//��ʾ��Ϣ
	int qt_Message();
	//��ʼ��
	int init();
	//�����������
	//1.��Ϣ2.�˺�3.����
	int sendMessage(char* oriMsg);
	//���շ���������Ϣ
	int recvMessage(char* oriMsg);
	//������Ϣ
	void handleMessage(int tag,char* oriMsg,char* msg);
	void handleMessage(int tag,char* oriMsg,char* msg1,char* msg2,char* msg3);
	//������Ϣ
	void parseMessage(char* oriMsg, int* type, char* sendID, char* msg, char* revID);
	//���շ����������б�
	vector <char*> onlineID();
};

