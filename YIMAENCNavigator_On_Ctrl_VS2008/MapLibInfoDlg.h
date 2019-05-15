#if !defined(AFX_MAPLIBINFODLG_H__1DBD4FBD_5E29_421B_BC44_B648FCB964A2__INCLUDED_)
#define AFX_MAPLIBINFODLG_H__1DBD4FBD_5E29_421B_BC44_B648FCB964A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapLibInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapLibInfoDlg dialog

#include "S63FileDialog.h" 

class CMapLibInfoDlg : public CDialog
{
// Construction
public:
	CMapLibInfoDlg(CWnd* pParent = NULL);   // standard constructor
	
	void OverViewCurrentSelectedMap(); 
	
	CS63FileDialog m_s63fileDlg;

// Dialog Data
	//{{AFX_DATA(CMapLibInfoDlg)
	enum { IDD = IDD_MAP_LIB_DLG };
	CListBox	m_mapList;
	int		m_edtNum;
	CString	m_strLeftBndry;
	CString	m_strRightBndry;
	CString	m_strUpBndry;
	CString	m_strBottomBndry;
	int		m_uptEdtNum;
	int	m_nOrgScale; 
	float	m_fMapShowMinScale;
	CString	m_strEditDate;
	CString	m_strMapCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapLibInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RefreshLibMapList();
	void ShowLibMapInfo(int libMapPos);

	// Generated message map functions
	//{{AFX_MSG(CMapLibInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeMapList();
	afx_msg void OnCloseButton();
	afx_msg void OnDblclkMapList();
	afx_msg void OnOpenMapButton();
	afx_msg void OnOverviewButton();
	afx_msg void OnAddS63FileButton();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnSetMinScaleButton();
	afx_msg void OnClearButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPLIBINFODLG_H__1DBD4FBD_5E29_421B_BC44_B648FCB964A2__INCLUDED_)
