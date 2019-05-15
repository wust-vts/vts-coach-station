// m_Grid->cpp: implementation of the CGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "msflexgrid.h"
#include "grid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGrid ::CGrid()
{ 
}


CGrid ::~CGrid()
{ 
}


BOOL CGrid ::GoUp() 
{ 
	TransferValue(TRUE);
	if (GetRow () > 1 ) {
		int CurrentRow = GetRow();
		CurrentRow --;
		SetRow (CurrentRow );
		TransferValue (FALSE);
		if (! GetRowIsVisible (CurrentRow)) 
            SetTopRow (CurrentRow  ); 
	}

	return TRUE;  
}


BOOL CGrid ::GoDown()
{ 
	TransferValue(TRUE);
	if ( GetRow () < GetRows () -1) {
		int CurrentRow = GetRow();
		CurrentRow ++;
		SetRow ( CurrentRow);
		TransferValue (FALSE);
		if (! GetRowIsVisible (CurrentRow)) 
            SetTopRow (CurrentRow );
	} 

	return TRUE; 
}


BOOL CGrid ::GoLeft()
{ 
	TransferValue(TRUE);
	if ( GetCol () > 1 ) {
		int CurrentCol = GetCol();
		CurrentCol --;
		SetCol (CurrentCol);
		TransferValue (FALSE);
		if (!GetColIsVisible (CurrentCol))
			 SetLeftCol (CurrentCol);
	}

    return TRUE;  
}


BOOL CGrid ::GoRight()
{ 
	TransferValue(TRUE);
	if ( GetCol () < GetCols() - 1 ) {
		int CurrentCol = GetCol ();
		CurrentCol++;
		SetCol (CurrentCol);
		TransferValue (FALSE);
		if (!GetColIsVisible (CurrentCol))
			 SetLeftCol (CurrentCol);
		
	}
	
	return TRUE;
} 

BOOL CGrid ::TransferValue(BOOL ToGrid)
{
	CString sText;

	if (ToGrid) { //Transfer value to Grid from Edit Box
		SetText(m_GridData  );
	} else {
		m_GridData  = GetText ();
		SetBackColorSel  (RGB(0,255,255));
	}
	return TRUE;
} 


BOOL CGrid ::OnKeyPressGrid(short FAR* KeyAscii) 
{ 
	   switch ( (int) * KeyAscii) {
		   
	   case  VK_BACK : //Backspace - delete the last character
		   m_GridData.Delete  (m_GridData.GetLength ()-1,1);
		   break;
	   default :
		   m_GridData = m_GridData + (TCHAR *) KeyAscii;
		   break;
	   }
	   TransferValue (TRUE);

	   return TRUE;
}


void CGrid ::OnClickGrid()
{ 
	TransferValue (FALSE); 
}


void CGrid::OnEnterCell()
{
	TransferValue (FALSE);
}
