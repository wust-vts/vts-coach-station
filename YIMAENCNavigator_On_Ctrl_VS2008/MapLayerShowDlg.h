#if !defined(AFX_MAPLAYERSHOWDLG_H__7B58EF91_06F9_45F7_BC3B_36B22A7BAB1D__INCLUDED_)
#define AFX_MAPLAYERSHOWDLG_H__7B58EF91_06F9_45F7_BC3B_36B22A7BAB1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapLayerShowDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapLayerShowDlg dialog

class CMapLayerShowDlg : public CDialog
{
// Construction
public:
	CMapLayerShowDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CMapLayerShowDlg)
	enum { IDD = IDD_MAPLAYER_SHOW_DLG };
	CButton	m_UserMapShowText;
	CButton	m_S52MapShowText;
	BOOL	m_S52MapShowCheck;
	BOOL	m_UserMapShowCheck;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapLayerShowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMapLayerShowDlg)
	afx_msg void OnS52mapshowCheck();
	afx_msg void OnUsermapshowCheck();
	virtual BOOL OnInitDialog();
	afx_msg void OnUsermapeditBtn();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPLAYERSHOWDLG_H__7B58EF91_06F9_45F7_BC3B_36B22A7BAB1D__INCLUDED_)
