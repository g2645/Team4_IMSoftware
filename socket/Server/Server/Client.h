#pragma once
#include "stdafx.h"
class Client
{
public:
	Client();
	~Client();

public:
	//ID客户端ID
	char m_ID[ID_LEN];
	//客户端套接字
	SOCKET m_socket;
	//登录状态
	bool m_status;
};

