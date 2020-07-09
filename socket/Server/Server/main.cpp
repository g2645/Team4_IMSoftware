#include "stdafx.h"
#include "IMServer.h"

int main()
{
	IMServer *server = new IMServer();
	server->startUp();
	while (true)
	{

	}
	system("pause");
	return 0;
}