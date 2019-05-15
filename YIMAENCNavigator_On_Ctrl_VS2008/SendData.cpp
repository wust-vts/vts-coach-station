#include "StdAfx.h"
#include "SendData.h"

//std::string radarIP = "127.0.0.1";
void sendRadarData(std::string msg, std::string ip, int port)
{
	//WSACleanup();
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);//��һ������Ϊ��λ�ֽڣ��ڶ�������Ϊ��λ�ֽ�  

	err = WSAStartup(wVersionRequested, &wsaData);//��winsock DLL����̬���ӿ��ļ������г�ʼ����Э��Winsock�İ汾֧�֣��������Ҫ����Դ��  
	if (err != 0)
	{
		return;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)//LOBYTE����ȡ��16���������λ��HIBYTE����ȡ��16��������ߣ�����ߣ��Ǹ��ֽڵ�����        
	{
		WSACleanup();
		return;
	}
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrClt;//��Ҫ���������IP��Ϣ  
	addrClt.sin_addr.S_un.S_addr = inet_addr(ip.data());	// inet_addr��IP��ַ�ӵ�����ʽת���������ֽڸ�ʽ���͡�  
	addrClt.sin_family = AF_INET;
	addrClt.sin_port = htons(port);

	connect(sockClient, (SOCKADDR*)&addrClt, sizeof(SOCKADDR));//�ͻ����������������������  
	send(sockClient, msg.data(), msg.size(), 0);

	closesocket(sockClient);
	WSACleanup();
}

void sendAisData(std::string msg, std::string ip, int port)
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET m_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	//���ù㲥����
	BOOL bBroadcast = TRUE;
	setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, (char*)&bBroadcast, sizeof(BOOL));

	int imode = 1; // 0:����
	//���÷�����ģʽ
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