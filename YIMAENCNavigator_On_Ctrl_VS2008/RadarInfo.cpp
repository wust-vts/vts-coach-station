#include "stdafx.h"
#include "RadarInfo.h"

RadarInfo::RadarInfo()
{
	op.Format(_T("0"));
	id.Format(_T("0"));
	ip.Format(_T("0"));
	port = 0;
	lon = 0;
	lan = 0;
	height = 0;
	range = 0;
	level = 0;
}

RadarInfo::~RadarInfo()
{

}