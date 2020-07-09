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
