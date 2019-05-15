#if !defined(AFX_SETSAFECONTOURDLG_H__456DA19B_16BA_4DC3_801D_A8B7F9C6ABE7__INCLUDED_)
#define AFX_SETSAFECONTOURDLG_H__456DA19B_16BA_4DC3_801D_A8B7F9C6ABE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetSafeContourDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetSafeContourDlg dialog
#include "Resource.h"

class CSetSafeContourDlg : public CDialog
{
// Construction
public:
	CSetSafeContourDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetSafeContourDlg)
	enum { IDD = IDD_SAFE_CONTOUR_DLG };
	float	m_fSafeCont;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetSafeContourDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetSafeContourDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	bool m_bTwoOrFourDepthShades;
	float m_fShallowDepth;
	float m_fDeepDepth;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETSAFECONTOURDLG_H__456DA19B_16BA_4DC3_801D_A8B7F9C6ABE7__INCLUDED_)
