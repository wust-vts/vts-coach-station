#pragma once
#include"StdAfx.h"
#include <cstring>

#define IP_RADAR	"192.168.1.112"
#define IP_ODU		"192.168.1.113"

#define PORT_AIS_RADAR	6666
#define PORT_AIS_ODU	6667
#define PORT_ADD_RADAR	8888

class AisIPConfig
{
public:
	AisIPConfig();
	AisIPConfig(CString filePath);
	~AisIPConfig();
private:
	void LoadConfigFile(CString filePath);
	void LoadConfigFile();
public:
	CString IP_Radar;
	CString IP_Odu;

	u_short Port_Ais_Radar;
	u_short Port_Ais_Odu;
	u_short Port_Add_Radar;
};