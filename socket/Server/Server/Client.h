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
};

