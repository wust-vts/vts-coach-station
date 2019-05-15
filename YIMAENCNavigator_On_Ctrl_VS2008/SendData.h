#pragma once

#include <string>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#define UNI_GEO_COOR_MULTI_FACTOR 10000000
#define RADAR_PORT 8888
typedef struct Radar_info
{
	std::string Id;			//雷达编号
	long Lon;				//经度
	long Lan;				//纬度
	double Height;			//高度
	double Range;			//量程
	double Level;			//水平面高度
	long innerLayerPos;		//雷达物标在图层中的索引
}Radar;

void sendRadarData(std::string msg, std::string ip, int port);
void sendAisData(std::string msg, std::string ip, int port);
int GetAISGeoIntFromGeoCoor(INT coorVal, INT coorMultiFactor);