#pragma once

#include <WinSock2.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")

#define ODU_RECEIVE_PORT 9004

class NetToODU
{
private:
	SOCKET m_socket;		//��������
	SOCKADDR_IN addrClient;		//�����ͻ���IP��Ϣ
public:
	BOOL m_hasWSAStartUp;	//�Ƿ�����Socket��İ󶨣��ͷ�Socket����ռ�õ�ϵͳ��Դ

public:
	NetToODU(void);
	~NetToODU(void);

	int RecvData(char* data);						//����ODU��¼��Ϣ
};