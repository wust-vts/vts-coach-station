#include "StdAfx.h"
#include "SendData.h"

//std::string radarIP = "127.0.0.1";
void sendRadarData(std::string msg, std::string ip, int port)
{
	//WSACleanup();
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);//第一个参数为低位字节；第二个参数为高位字节  

	err = WSAStartup(wVersionRequested, &wsaData);//对winsock DLL（动态链接库文件）进行初始化，协商Winsock的版本支持，并分配必要的资源。  
	if (err != 0)
	{
		return;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)//LOBYTE（）取得16进制数最低位；HIBYTE（）取得16进制数最高（最左边）那个字节的内容        
	{
		WSACleanup();
		return;
	}
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrClt;//需要包含服务端IP信息  
	addrClt.sin_addr.S_un.S_addr = inet_addr(ip.data());	// inet_addr将IP地址从点数格式转换成网络字节格式整型。  
	addrClt.sin_family = AF_INET;
	addrClt.sin_port = htons(port);

	connect(sockClient, (SOCKADDR*)&addrClt, sizeof(SOCKADDR));//客户机向服务器发出连接请求  
	send(sockClient, msg.data(), msg.size(), 0);

	closesocket(sockClient);
	WSACleanup();
}

void sendAisData(std::string msg, std::string ip, int port)
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET m_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	//设置广播功能
	BOOL bBroadcast = TRUE;
	setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, (char*)&bBroadcast, sizeof(BOOL));

	int imode = 1; // 0:阻塞
	//设置非阻塞模式
	ioctlsocket(m_socket, FIONBIO, (u_long FAR*)&imode);

	SOCKADDR_IN addrSrv;
	
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(ip.data());
	addrSrv.sin_port = htons(port);

	int len = sizeof(addrSrv);
	sendto(m_socket, msg.data(), msg.size(), 0, (sockaddr*)&addrSrv, len);

	closesocket(m_socket);
	WSACleanup();
}

int GetAISGeoIntFromGeoCoor(INT coorVal, INT coorMultiFactor)
{
	if (coorMultiFactor == 0)
		return false;

	int retGeoInt;
	double fArcByDegree = coorVal / (float)coorMultiFactor;
	double fArcByMin = 60 * (fArcByDegree - (int)fArcByDegree);
	fArcByDegree = (int)fArcByDegree;

	retGeoInt = (int)((fArcByMin / 60 + fArcByDegree) * 600000);

	//*retGeoInt = ((int)fArcByDegree * 60 + fArcByMin) * 60 * 10000;
	return retGeoInt;
}
