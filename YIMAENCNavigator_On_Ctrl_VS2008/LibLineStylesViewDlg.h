#if !defined(AFX_LIBSTYLESVIEWDLG_H__16D270AF_E776_4879_9F40_D22618B5DB9F__INCLUDED_)
#define AFX_LIBSTYLESVIEWDLG_H__16D270AF_E776_4879_9F40_D22618B5DB9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LibStylesViewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLibLineStylesViewDlg dialog

class CLibLineStylesViewDlg : public CDialog
{
// Construction
public:
	int m_iCurPageNum;
	CString m_strCaption;

	CLibLineStylesViewDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLibLineStylesViewDlg)
	enum { IDD = IDD_LIB_STYLES_DIALOG };
	UINT	m_iSelLsID;
	UINT	m_iLsWidth;
	UINT	m_iLsColorR;
	UINT	m_iLsColorG;
	int		m_iLsColorB;
	BOOL	m_bSetColor;
	BOOL	m_bSetWidth;
	UINT	m_nFontColorB;
	UINT	m_nFontColorG;
	UINT	m_nFontColorR;
	CString	m_strFontName;
	CString	m_strText;
	int		m_iTextOffsetY;
	int		m_iTextOffsetX;
	UINT	m_nFontSize;
	BOOL	m_bShowTextAlongWithLine;
	BOOL	m_bSolidLine;
	BOOL	m_bDashLine;
	int		m_nDashCycle;
	int		m_nDashLen;
	BOOL	m_bSetBasicLineColor;
	int		m_nBscLnWidth;
	UINT	m_nBscLnColorR;
	UINT	m_nBscLnColorG;
	UINT	m_nBscLnColorB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLibLineStylesViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLibLineStylesViewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnColorBtn();
	virtual void OnOK();
	afx_msg void OnDemoShowBtn();
	afx_msg void OnPageupButton();
	afx_msg void OnPageDownButton();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnFontButton();
	afx_msg void OnTextColorButton();
	afx_msg void OnSolidLineCheck();
	afx_msg void OnDashLineCheck();
	afx_msg void OnSetcolorBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	float m_fTextRotatrAngle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIBSTYLESVIEWDLG_H__16D270AF_E776_4879_9F40_D22618B5DB9F__INCLUDED_)
