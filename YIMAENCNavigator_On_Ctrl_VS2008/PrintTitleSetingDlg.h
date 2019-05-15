#if !defined(AFX_PRINTTITLESETINGDLG_H__B3CA9760_4FBA_499D_ABB9_24357E9488BD__INCLUDED_)
#define AFX_PRINTTITLESETINGDLG_H__B3CA9760_4FBA_499D_ABB9_24357E9488BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrintTitleSetingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrintTitleSetingDlg dialog

class CPrintTitleSetingDlg : public CDialog
{
// Construction
public:
	CPrintTitleSetingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrintTitleSetingDlg)
	enum { IDD = IDD_PRINT_TITLE_DLG };
	CString	m_printTitleEdit;
	CString	m_remarkEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintTitleSetingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrintTitleSetingDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnTitleFontBtn();
	afx_msg void OnRemarkFontBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTTITLESETINGDLG_H__B3CA9760_4FBA_499D_ABB9_24357E9488BD__INCLUDED_)
