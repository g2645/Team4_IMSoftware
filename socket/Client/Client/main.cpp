#include "stdafx.h"
#include "Client.h"

int main()
{
	Client c;
	int t;
	string id= "ID",pas="password";
	char *ID = &id[0];
	char *PA = &pas[0];
	while(cin>>t)
	{
		switch(t)
		{
		case 1:cin >> ID >> PA; cout << c.qt_Register(ID, PA) << endl; break;
			case 2:cout << c.qt_SignIn(ID,PA) << endl;
				/*while (1)
				{
					char *olID="";
					if(c.qt_onlineID(olID)==0)
						cout << olID << endl;
				}*/
		}
	}
	return 0;
}