#if !defined(AFX_LAYERMANDLG_H__2E23F051_BE56_4B01_A4CC_7B74E48E9FCB__INCLUDED_)
#define AFX_LAYERMANDLG_H__2E23F051_BE56_4B01_A4CC_7B74E48E9FCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LayerManDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLayerManDlg dialog

class CLayerManDlg : public CDialog
{
// Construction
public:
	CLayerManDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLayerManDlg)
	enum { IDD = IDD_LAYER_MAN_DLG };
	CListBox	m_layerList;
	BOOL	m_bLayerToDrawOrNot;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLayerManDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLayerManDlg)
	afx_msg void OnShowLayerCheck();
	afx_msg void OnShowAllLayerButton();
	afx_msg void OnHideAllLayerButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeLayerList();
	afx_msg void OnDblclkLayerList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYERMANDLG_H__2E23F051_BE56_4B01_A4CC_7B74E48E9FCB__INCLUDED_)
