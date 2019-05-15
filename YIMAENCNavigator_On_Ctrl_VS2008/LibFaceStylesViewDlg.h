#if !defined(AFX_LIBFACESTYLESVIEWDLG_H__32E21FBB_4393_4114_8A84_1407932919F0__INCLUDED_)
#define AFX_LIBFACESTYLESVIEWDLG_H__32E21FBB_4393_4114_8A84_1407932919F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LibFaceStylesViewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLibFaceStylesViewDlg dialog

class CLibFaceStylesViewDlg : public CDialog
{
// Construction
public:
	bool m_bShowTextOnObjectCenterOrBottom;
	CLibFaceStylesViewDlg(CWnd* pParent = NULL);   // standard constructor

	CString m_strCaption;

// Dialog Data
	//{{AFX_DATA(CLibFaceStylesViewDlg)
	enum { IDD = IDD_FACE_STYLES_DIALOG };
	UINT	m_iFaceColorB;
	UINT	m_iFaceColorG;
	UINT	m_iFaceColorR;
	UINT	m_iFaceWidth;
	UINT	m_iSelFsID;
	BOOL	m_bSetColor;
	BOOL	m_bSetPatternColor;
	UINT	m_iFacePatternColorB;
	UINT	m_iFacePatternColorG;
	UINT	m_iFacePatternColorR;
	BOOL	m_bSetFillColorTransparency;
	int		m_iFillTransparency;
	CString	m_strText;
	int		m_iTextOffsetX;
	int		m_iTextOffsetY;
	UINT	m_nTextFontSize;
	CString	m_strFontName;
	UINT	m_nFontColorR;
	UINT	m_nFontColorG;
	UINT	m_nFontColorB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLibFaceStylesViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLibFaceStylesViewDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnColorBtn();
	afx_msg void OnDemoShowBtn();
	virtual void OnOK();
	afx_msg void OnPatternColorBtn();
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

#endif // !defined(AFX_LIBFACESTYLESVIEWDLG_H__32E21FBB_4393_4114_8A84_1407932919F0__INCLUDED_)
