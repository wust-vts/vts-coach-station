#pragma once

#include <WinSock2.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")

#define ODU_RECEIVE_PORT 9004

class NetToODU
{
private:
	SOCKET m_socket;		//服务器端
	SOCKADDR_IN addrClient;		//包含客户端IP信息
public:
	BOOL m_hasWSAStartUp;	//是否解除与Socket库的绑定，释放Socket库所占用的系统资源

public:
	NetToODU(void);
	~NetToODU(void);

	int RecvData(char* data);						//接受ODU登录信息
};