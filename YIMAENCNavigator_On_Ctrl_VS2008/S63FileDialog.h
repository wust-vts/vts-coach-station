#if !defined(AFX_S63FILEDIALOG_H__E228A9C2_8AE6_4471_BB88_8F119804C2A7__INCLUDED_)
#define AFX_S63FILEDIALOG_H__E228A9C2_8AE6_4471_BB88_8F119804C2A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// S63FileDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CS63FileDialog dialog

class CS63FileDialog : public CDialog
{
// Construction
public:
	CS63FileDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CS63FileDialog)
	enum { IDD = IDD_S63_FILE_DIALOG };
	CString	m_strPermitFilePath;
	CString	m_strCellFilePath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CS63FileDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CS63FileDialog)
	virtual void OnOK();
	afx_msg void OnOpenPermitFileButton();
	afx_msg void OnOpenS63CellFileButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_S63FILEDIALOG_H__E228A9C2_8AE6_4471_BB88_8F119804C2A7__INCLUDED_)
