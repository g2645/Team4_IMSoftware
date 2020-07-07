#pragma once
#include <vector> 
#include <string>
#include <WinSock2.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

#define  HOST_IP "127.0.0.1"
#define  BUFFER_SIZE 1024
#define  NAME_SIZE 200
#define  IP_SIZE 32
#define  DEF_SIZE 48
#define  ID_LEN 48
#define  MAX_ONLINE 48


//Ïß³Ìº¯Êý
DWORD WINAPI ListenThreadFunc(LPVOID pParam);