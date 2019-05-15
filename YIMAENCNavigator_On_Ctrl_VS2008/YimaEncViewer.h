// YimaEncViewer.h : main header file for the YIMAENCVIEWER application
//

#if !defined(AFX_YIMAENCVIEWER_H__59EE8357_DC51_4DEF_A538_8A4179E66D89__INCLUDED_)
#define AFX_YIMAENCVIEWER_H__59EE8357_DC51_4DEF_A538_8A4179E66D89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols 
#include "YIMAENCHEAD.H"					  
/////////////////////////////////////////////////////////////////////////////
// CYimaEncViewerApp:
// See YimaEncViewer.cpp for the implementation of this class
//
 
class CYimaEncViewerApp : public CWinApp
{
public:
	CYimaEncViewerApp();
    

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYimaEncViewerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CYimaEncViewerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG

	void OnZczTestButtom();
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YIMAENCVIEWER_H__59EE8357_DC51_4DEF_A538_8A4179E66D89__INCLUDED_)
