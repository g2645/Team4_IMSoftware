#include "stdafx.h"
#include "IMServer.h"



DWORD __stdcall WINAPI ListenThreadFunc(LPVOID pParam)
{
	IMServer* pServer = (IMServer*)pParam;
	while (TRUE)
	{
		//ֻҪָ���¼������е�һ����ȫ���������ź�״̬�����߳�ʱ��������򷵻ء���������ɹ�������ֵָ����ɺ������ص��¼�����
		int index = WSAWaitForMultipleEvents(pServer->m_onlineNum, pServer->eventArray, FALSE, WSA_INFINITE, NULL);
		/*����¼���������ĳһ���¼��������ˣ������᷵������¼�������ֵ�������������ֵ��Ҫ��ȥԤ����ֵ WSA_WAIT_EVENT_0
		��������¼����¼������е�λ�á�*/
		index = index - WSA_WAIT_EVENT_0;
		//�����Ϊindex�Ŀͻ��˽����¼������жϣ�������Ӧ������
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
				//�������������
				if (event.lNetworkEvents & FD_ACCEPT)
				{
					//����¼���������
					if (event.iErrorCode[FD_ACCEPT_BIT] == 0)
					{
						//�ͻ��˵�ַ
						sockaddr_in clientAddr;
						int Len = sizeof(clientAddr);
						//��ȡ�׽���
						SOCKET newSocke = accept(pServer->socketArray[i], (sockaddr*)&clientAddr, &Len);
						WSAEVENT newEvent = WSACreateEvent();
						//ע���
						WSAEventSelect(newSocke, newEvent, FD_READ | FD_CLOSE);
						//����һ�����û�
						pServer->addClient(newSocke, newEvent);
					}
					else
					{
						cout << "FD_ACCEPT����:" << event.iErrorCode[FD_ACCEPT_BIT] << endl;
					}
				}
				//��Ϣ����
				else if (event.lNetworkEvents & FD_READ)
				{
					char showMsg[BUFFER_SIZE] = { 0 };
					char sendMsg[BUFFER_SIZE] = { 0 };
					//�¼���������
					if (event.iErrorCode[FD_READ_BIT] == 0)//���ڽ���
					{
						//������Ϣ
						char buffer[BUFFER_SIZE] = { 0 };
						int ret = recv(pServer->socketArray[i], buffer, 1024, NULL);
						if (ret >= 0)
						{
							
							//�յ�����Ϣ
							if (ret == 0)
								continue;

							//ָ��
							buffer[ret] = '\0';
							int type;
							char sendID[ID_LEN] = { 0 };
							char revID[ID_LEN] = { 0 };
							char newMsg[1024] = { 0 };
							pServer->parseMessage(buffer, &type, sendID, newMsg, revID);
							//����ָ�������Ϣ����
							if (false)//�ж��Ƿ񱻽���
							{
								//todo
								continue;
							}
							//����
							else if (type == 1)//���û�����Ϣ
							{

								//todo
							}
							//��¼
							else if (type == 2)
							{
								//��֤��¼��Ϣ
								int ret = pServer->Login(sendID,newMsg);
								if (ret==0)
								{
									//��¼�ɹ�
									pServer->m_client[i]->m_status = true;
								}
								else if(ret==1)
								{
									//�������
								}
								else if (ret==2)
								{
									//�˺Ų�����
								}
							}
							//�û�ע��
							else if (type == 3)
							{
								int ret = pServer->Register(sendID, newMsg);
								//ע��ɹ�
								if (ret==0)
								{
									//���ÿͻ���ID
									sprintf_s(pServer->m_client[i]->m_ID, sizeof(pServer->m_client[i]->m_ID), sendID);
									//�ı�Ϊ��¼״̬
									pServer->m_client[i]->m_status = true;
								}
								else if (ret==1)
								{
									//ע��ʧ���û�ID�Ѵ���
								}
								//
							}
							//������Ϣ
							else if (type == 4)
							{
								//
							}
						}
					}
					else if (event.lNetworkEvents & FD_CLOSE)      //�ر�socket
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
	//�رռ����׽���
	closesocket(pServer->m_listenSocket);
	//���
	WSACleanup();
	return 0;
}