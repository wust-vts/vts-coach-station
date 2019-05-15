//{{AFX_INCLUDES() 
#include "Grid.h"
//}}AFX_INCLUDES
#if !defined(AFX_ROUTEEDITDLG_H__C8D17F51_1AB4_4C86_8FBC_05C5D0337F09__INCLUDED_)
#define AFX_ROUTEEDITDLG_H__C8D17F51_1AB4_4C86_8FBC_05C5D0337F09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RouteEditDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRouteEditDlg dialog

class CRouteEditDlg : public CDialog
{
// Construction
public:
	CRouteEditDlg(CWnd* pParent = NULL);   // standard constructor

	long m_editRouteID;

	void RefreshWayPointGrid();	
	void SaveWayPointGrid();

// Dialog Data
	//{{AFX_DATA(CRouteEditDlg)
	enum { IDD = IDD_ROUTE_EDIT_DLG };
	CGrid	m_wayPointGrid;
	CString	m_routeName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRouteEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRouteEditDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnKeyPressRouteWpGrid(short FAR* KeyAscii);
	afx_msg void OnDelWayPointBtn();
	afx_msg void OnAddWayPointBtn();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROUTEEDITDLG_H__C8D17F51_1AB4_4C86_8FBC_05C5D0337F09__INCLUDED_)
