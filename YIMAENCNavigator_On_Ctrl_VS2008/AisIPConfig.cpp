#include "StdAfx.h"
#include "AisIPConfig.h"
#include <fstream>

AisIPConfig::AisIPConfig()
{
	IP_Radar = IP_RADAR;
	IP_Odu = IP_ODU;
	Port_Ais_Radar = PORT_AIS_RADAR;
	Port_Ais_Odu = PORT_AIS_ODU;
	Port_Add_Radar = PORT_ADD_RADAR;

	LoadConfigFile();
}

AisIPConfig::AisIPConfig(CString filePath)
{
	IP_Radar = IP_RADAR;
	IP_Odu = IP_ODU;
	Port_Ais_Radar = PORT_AIS_RADAR;
	Port_Ais_Odu = PORT_AIS_ODU;
	Port_Add_Radar = PORT_ADD_RADAR;

	LoadConfigFile(filePath);
}

AisIPConfig::~AisIPConfig()
{
}

void AisIPConfig::LoadConfigFile(CString filePath)
{
	std::ifstream inFile;
	inFile.open(filePath);
	if (!inFile.is_open())
		return;

	while (!inFile.eof())
	{
		char head[100], mid[10], tail[50];
		inFile >> head >> mid >> tail;
		if (strcmp(head, "IP_RADAR") == 0)
			IP_Radar = tail;
		else if (strcmp(head, "IP_ODU") == 0)
			IP_Odu = tail;
		else if (strcmp(head, "PORT_AIS_RADAR") == 0)
			Port_Ais_Radar = atoi(tail);
		else if (strcmp(head, "PORT_AIS_ODU") == 0)
			Port_Ais_Odu = atoi(tail);
		else if (strcmp(head, "PORT_ADD_RADAR") == 0)
			Port_Add_Radar = atoi(tail);
	}

	inFile.close();
}

void AisIPConfig::LoadConfigFile()
{
	LoadConfigFile(_T("AisIPconfig.txt"));
}
