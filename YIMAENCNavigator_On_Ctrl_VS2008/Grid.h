// Grid.h: interface for the CGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRID_H__91679B43_6C53_11D3_BEF7_00C04F755C52__INCLUDED_)
#define AFX_GRID_H__91679B43_6C53_11D3_BEF7_00C04F755C52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "msflexgrid.h" 

class CGrid : public CMSFlexGrid
{
public:
	CGrid();
	virtual ~CGrid();
   
public :
	
	BOOL GoRight();
	BOOL GoLeft();
	BOOL GoDown();
	BOOL GoUp();
	BOOL OnKeyPressGrid(short FAR* KeyAscii) ;
	void OnClickGrid();
	void OnEnterCell();
private :
	CString m_GridData;
	BOOL bEditMode;
	BOOL TransferValue (BOOL ToGrid);
};

#endif // !defined(AFX_GRID_H__91679B43_6C53_11D3_BEF7_00C04F755C52__INCLUDED_)
