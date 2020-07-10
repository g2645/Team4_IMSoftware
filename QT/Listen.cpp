#include "stdafx.h"
#include "Client.h"


DWORD __stdcall WINAPI Listen(LPVOID pParam)
{
	Client* pClient = (Client*)pParam;

	WSAEVENT lis =WSACreateEvent();
	WSAEventSelect(pClient->m_socket,lis,FD_READ);
	while (TRUE)
	{
		int index = WaitForSingleObject(lis,INFINITE);
		if(index == WAIT_OBJECT_0)
		{
			recv(pClient->m_socket, pClient->recvMsg, 1024, 0);
			//
		}
	}	
	//¹Ø±Õ¼àÌýÌ×½Ó×Ö
	closesocket(pClient->m_socket);
	//Çå³ý
	WSACleanup();
	return 0;
}