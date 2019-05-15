#if !defined(AFX_LIBPOINTSTYLESVIEWDLG_H__EEE5ED84_8553_44DA_8000_354635F4887B__INCLUDED_)
#define AFX_LIBPOINTSTYLESVIEWDLG_H__EEE5ED84_8553_44DA_8000_354635F4887B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LibPointStylesViewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLibPointStylesViewDlg dialog

class CLibPointStylesViewDlg : public CDialog
{
// Construction
public:
	int m_iCurPageNum;

	CLibPointStylesViewDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLibPointStylesViewDlg)
	enum { IDD = IDD_POINT_STYLES_DIALOG };
	UINT	m_iSelPsID; 
	UINT	m_iPointColorR;
	UINT	m_iPointColorG;
	UINT	m_iPointColorB;
	BOOL	m_bSetColor;
	BOOL	m_bSetRatio;
	float	m_fZoomRatio;
	CString	m_strTextFontName;
	CString	m_strText;
	int		m_iTextOffsetX;
	int		m_iTextOffsetY;
	UINT	m_nFontColorR;
	UINT	m_nFontColorG;
	UINT	m_nFontColorB;
	UINT	m_nFontSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLibPointStylesViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLibPointStylesViewDlg)
	afx_msg void OnPaint();
	afx_msg void OnColorBtn();
	afx_msg void OnDemoShowBtn();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPageUpButton();
	afx_msg void OnPageDownButton();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual void OnCancel();
	afx_msg void OnFontButton();
	afx_msg void OnTextColorButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	float m_fTextRotatrAngle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIBPOINTSTYLESVIEWDLG_H__EEE5ED84_8553_44DA_8000_354635F4887B__INCLUDED_)
