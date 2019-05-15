#include "StdAfx.h"
#include "NetToODU.h"

NetToODU::NetToODU(void)
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		MessageBox(NULL, "Win Sock Version error !", "警告", MB_OK);
		WSACleanup();
		m_hasWSAStartUp = FALSE;
		return;
	}
	m_hasWSAStartUp = TRUE;

	m_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SOCKET_ERROR == m_socket)
	{
		MessageBox(NULL, "Create Socket Failure !", "警告", MB_OK);
		return;
	}
	//设置广播功能
	BOOL bBroadcast = TRUE;
	setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, (char*)&bBroadcast, sizeof(BOOL));

	int imode = 1; // 0:阻塞
	//设置非阻塞模式
	ioctlsocket(m_socket, FIONBIO, (u_long FAR*)&imode);

	SOCKADDR_IN addrSrv;
	int len = sizeof(addrSrv);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_addr.s_addr = htonl(INADDR_ANY);
	addrSrv.sin_port = htons(ODU_RECEIVE_PORT);

	int state = bind(m_socket, (sockaddr*)&addrSrv, len);		//绑定服务器接受端口
	if (SOCKET_ERROR == state)
	{
		MessageBox(NULL, "bind address and ip error!", "警告", MB_OK);
	}
}

NetToODU::~NetToODU(void)
{
	if (SOCKET_ERROR != m_socket)
	{
		closesocket(m_socket);
	}
	if (m_hasWSAStartUp == TRUE)
	{
		WSACleanup();
	}
}

int NetToODU::RecvData(char* data)
{
	int addrClientSize = sizeof(addrClient);
	int len = recvfrom(m_socket, data, 100, 0, (sockaddr*)&addrClient, &addrClientSize);
	return len;
}