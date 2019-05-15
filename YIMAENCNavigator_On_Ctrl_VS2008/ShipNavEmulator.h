// ShipNavEmulator.h: interface for the CShipNavEmulator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHIPNAVEMULATOR_H__09D3F467_AD87_4AC5_9134_0240A37D0F6A__INCLUDED_)
#define AFX_SHIPNAVEMULATOR_H__09D3F467_AD87_4AC5_9134_0240A37D0F6A__INCLUDED_

#include "YIMAENCHEAD.H"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CShipNavigator  
{
public:
	M_POINT GetOtherVesselPosition(bool bAisOrArpa, int aisOrArpaVesselPos);
	float GetCurrentOwnShipDirection();
	M_POINT GetCurrentOwnShipPosition();
	float GetCurrentOwnShipSpeed();
	CShipNavigator();
	virtual ~CShipNavigator();
};

#endif // !defined(AFX_SHIPNAVEMULATOR_H__09D3F467_AD87_4AC5_9134_0240A37D0F6A__INCLUDED_)
