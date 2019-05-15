#if !defined(AFX_CENTERROTATEMAPDLG_H__0428B1A6_CFEB_4ECF_83D7_BAFF6B9D15B1__INCLUDED_)
#define AFX_CENTERROTATEMAPDLG_H__0428B1A6_CFEB_4ECF_83D7_BAFF6B9D15B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CenterRotateMapDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCenterRotateMapDlg dialog

class CCenterRotateMapDlg : public CDialog
{
// Construction
public:
	CCenterRotateMapDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCenterRotateMapDlg)
	enum { IDD = IDD_CENTER_ROTATE_DLG };
	float	m_fCntrGeoPoX;
	float	m_fCntrGeoPoY;
	float	m_fRotateDeg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCenterRotateMapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCenterRotateMapDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CENTERROTATEMAPDLG_H__0428B1A6_CFEB_4ECF_83D7_BAFF6B9D15B1__INCLUDED_)
