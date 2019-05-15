#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <string>

using namespace std;

class RadarInfo
{
private:
	CString op;				//操作码
	CString id;				//编号
	CString ip;				//IP
	short port;				//Port
	double lon;				//经度
	double lan;				//纬度
	double height;			//高度
	double range;			//量程
	double level;			//水平面高度

public:
	long radInnerLayerPos;		//雷达物标在图层中的索引
public:
	RadarInfo();
	~RadarInfo();
};