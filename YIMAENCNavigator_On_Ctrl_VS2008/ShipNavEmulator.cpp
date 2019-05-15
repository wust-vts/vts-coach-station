// ShipNavEmulator.cpp: implementation of the CShipNavEmulator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "yimaencviewer.h"
#include "ShipNavEmulator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShipNavigator::CShipNavigator()
{

}

CShipNavigator::~CShipNavigator()
{

}

//单位为节, 海里/秒
float CShipNavigator::GetCurrentOwnShipSpeed()
{
     return 200;
}

M_POINT CShipNavigator::GetCurrentOwnShipPosition()
{
	return M_POINT();
}

float CShipNavigator::GetCurrentOwnShipDirection()
{
	return 0;
}

M_POINT CShipNavigator::GetOtherVesselPosition(bool bAisOrArpa,
												 int aisOrArpaVesselPos)
{
	return M_POINT();
}
