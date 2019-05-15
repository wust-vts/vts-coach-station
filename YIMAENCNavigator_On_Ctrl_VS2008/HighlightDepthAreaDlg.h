#if !defined(AFX_HIGHLIGHTDEPTHAREADLG_H__9C537E20_6443_48AD_B072_5213356118D1__INCLUDED_)
#define AFX_HIGHLIGHTDEPTHAREADLG_H__9C537E20_6443_48AD_B072_5213356118D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HighlightDepthAreaDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHighlightDepthAreaDlg dialog

class CHighlightDepthAreaDlg : public CDialog
{
// Construction
public:
	CHighlightDepthAreaDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHighlightDepthAreaDlg)
	enum { IDD = IDD_HIGHLIGHT_DEPTHAREA_DIALOG };
	float	m_fDepthLowerLimit;
	float	m_fDepthUpLimit;
	UINT	m_fillColorG;
	UINT	m_fillColorB;
	UINT	m_fillColorR;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHighlightDepthAreaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHighlightDepthAreaDlg)
	afx_msg void OnColorBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIGHLIGHTDEPTHAREADLG_H__9C537E20_6443_48AD_B072_5213356118D1__INCLUDED_)
