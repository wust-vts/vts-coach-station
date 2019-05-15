#pragma once

#include <string>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#define UNI_GEO_COOR_MULTI_FACTOR 10000000
#define RADAR_PORT 8888
typedef struct Radar_info
{
	std::string Id;			//�״���
	long Lon;				//����
	long Lan;				//γ��
	double Height;			//�߶�
	double Range;			//����
	double Level;			//ˮƽ��߶�
	long innerLayerPos;		//�״������ͼ���е�����
}Radar;

void sendRadarData(std::string msg, std::string ip, int port);
void sendAisData(std::string msg, std::string ip, int port);
int GetAISGeoIntFromGeoCoor(INT coorVal, INT coorMultiFactor);