#include "stdafx.h"
#include "IMServer.h"



DWORD __stdcall WINAPI ListenThreadFunc(LPVOID pParam)
{
	IMServer* pServer = (IMServer*)pParam;
	while (TRUE)
	{
		//只要指定事件对象中的一个或全部处于有信号状态，或者超时间隔到，则返回。如果函数成功，返回值指出造成函数返回的事件对象。
		int index = WSAWaitForMultipleEvents(pServer->m_onlineNum, pServer->eventArray, FALSE, WSA_INFINITE, NULL);
		/*如果事件数组中有某一个事件被传信了，函数会返回这个事件的索引值，但是这个索引值需要减去预定义值 WSA_WAIT_EVENT_0
		才是这个事件在事件数组中的位置。*/
		index = index - WSA_WAIT_EVENT_0;
		//对序号为index的客户端进行事件类型判断，做出相应动作。
		for (int i = index; i < pServer->m_onlineNum; i++)
		{
			index = WSAWaitForMultipleEvents(1, &pServer->eventArray[i], FALSE, 1000, NULL);
			WSAResetEvent(pServer->eventArray[i]);
			if (index == WSA_WAIT_FAILED || index == WSA_WAIT_TIMEOUT)
			{
				continue;
			}
			else
			{
				WSANETWORKEVENTS event;
				WSAEnumNetworkEvents(pServer->socketArray[i], pServer->eventArray[i], &event);
				//如果是连接请求
				if (event.lNetworkEvents & FD_ACCEPT)
				{
					//如果事件处理正常
					if (event.iErrorCode[FD_ACCEPT_BIT] == 0)
					{
						//客户端地址
						sockaddr_in clientAddr;
						int Len = sizeof(clientAddr);
						//获取套接字
						SOCKET newSocke = accept(pServer->socketArray[i], (sockaddr*)&clientAddr, &Len);
						WSAEVENT newEvent = WSACreateEvent();
						//注册绑定
						WSAEventSelect(newSocke, newEvent, FD_READ | FD_CLOSE);
						//增加一个新用户
						pServer->addClient(newSocke, newEvent);
					}
					else
					{
						cout << "FD_ACCEPT错误:" << event.iErrorCode[FD_ACCEPT_BIT] << endl;
					}
				}
				//消息请求
				else if (event.lNetworkEvents & FD_READ)
				{
					char showMsg[BUFFER_SIZE] = { 0 };
					char sendMsg[BUFFER_SIZE] = { 0 };
					//事件处理正常
					if (event.iErrorCode[FD_READ_BIT] == 0)//用于接收
					{
						//接收消息
						char buffer[BUFFER_SIZE] = { 0 };
						int ret = recv(pServer->socketArray[i], buffer, 1024, NULL);
						if (ret >= 0)
						{
							
							//收到空信息
							if (ret == 0)
								continue;

							//指令
							buffer[ret] = '\0';
							int type;
							char sendID[ID_LEN] = { 0 };
							char revID[ID_LEN] = { 0 };
							char newMsg[1024] = { 0 };
							pServer->parseMessage(buffer, &type, sendID, newMsg, revID);
							//根据指令进行消息处理
							if (false)//判断是否被禁言
							{
								//todo
								continue;
							}
							//单播
							else if (type == 1)//对用户发消息
							{

								//todo
							}
							//登录
							else if (type == 2)
							{
								//验证登录信息
								int ret = pServer->Login(sendID,newMsg);
								if (ret==0)
								{
									//登录成功
									pServer->m_client[i]->m_status = true;
								}
								else if(ret==1)
								{
									//密码错误
								}
								else if (ret==2)
								{
									//账号不存在
								}
							}
							//用户注册
							else if (type == 3)
							{
								int ret = pServer->Register(sendID, newMsg);
								//注册成功
								if (ret==0)
								{
									//设置客户端ID
									sprintf_s(pServer->m_client[i]->m_ID, sizeof(pServer->m_client[i]->m_ID), sendID);
									//改变为登录状态
									pServer->m_client[i]->m_status = true;
								}
								else if (ret==1)
								{
									//注册失败用户ID已存在
								}
								//
							}
							//更新信息
							else if (type == 4)
							{
								//
							}
						}
					}
					else if (event.lNetworkEvents & FD_CLOSE)      //关闭socket
					{
						if (event.iErrorCode[FD_CLOSE_BIT] == 0)
						{
							//todo
						}
					}
				}
			}
		}
	}
	//关闭监听套接字
	closesocket(pServer->m_listenSocket);
	//清除
	WSACleanup();
	return 0;
}