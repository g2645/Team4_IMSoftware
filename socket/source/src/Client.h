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
	int qt_onlineID(char *ID);
	//��ʾ��Ϣ
	int qt_Message(char *sendID, char *msg);
	//��ʼ��
	int init();
	//�����������
	//1.��Ϣ2.��¼�ύ7.ע���ύ
	int sendMessage(char* oriMsg);
	//���շ���������Ϣ
	int recvMessage(char* oriMsg);
	//������Ϣ
	string handleMessage(int tag,char* ID,char* password);
	string handleMessage(char* sendID,char* message,char* recvID);
	//������Ϣ
	int parseMessage(char* oriMsg);//3.��¼ȷ��  8.ע��ȷ��
	int parseMessage(char* oriMsg, char* msg1);// 4.����ID 5.��4����ȡ���� 6.���������û�
	int parseMessage(char* oriMsg, char* msg1, char* msg2, char* msg3);//1.��Ϣ
};

