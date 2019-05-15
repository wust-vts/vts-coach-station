#if !defined(AFX_CHANGEDEPTHLINEVALDLG_H__0BC5E49D_944B_4AF6_8FC8_E02AD191C328__INCLUDED_)
#define AFX_CHANGEDEPTHLINEVALDLG_H__0BC5E49D_944B_4AF6_8FC8_E02AD191C328__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangeDepthLineValDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangeDepthLineValDlg dialog

class CChangeDepthLineValDlg : public CDialog
{
// Construction
public:
	CChangeDepthLineValDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChangeDepthLineValDlg)
	enum { IDD = IDD_CHG_DPTH_LN_DLG };
	float	m_fDpthChgVal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeDepthLineValDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangeDepthLineValDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEDEPTHLINEVALDLG_H__0BC5E49D_944B_4AF6_8FC8_E02AD191C328__INCLUDED_)
