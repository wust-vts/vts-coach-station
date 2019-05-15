#if !defined(AFX_SETSCALEDLG_H__745CA526_B8A2_4059_9628_1429BE6AE451__INCLUDED_)
#define AFX_SETSCALEDLG_H__745CA526_B8A2_4059_9628_1429BE6AE451__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetScaleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetScaleDlg dialog
#include "Resource.h"

#define PRESET_SCALE_COUNT 9
class CSetScaleDlg : public CDialog
{
// Construction
public:
	CSetScaleDlg(CWnd* pParent = NULL);   // standard constructor

	int m_presetScales[PRESET_SCALE_COUNT];

// Dialog Data
	//{{AFX_DATA(CSetScaleDlg)
	enum { IDD = IDD_SET_SCALE_DLG };
	CComboBox	m_selScaleCmbx;
	int		m_iScale;
	//}}AFX_DATA  

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetScaleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetScaleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSelScaleCombox();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETSCALEDLG_H__745CA526_B8A2_4059_9628_1429BE6AE451__INCLUDED_)
