#if !defined(AFX_NAVIGATIONDLGBAR_H__5053D4D0_8D32_4DA3_85D8_33A51261B8C1__INCLUDED_)
#define AFX_NAVIGATIONDLGBAR_H__5053D4D0_8D32_4DA3_85D8_33A51261B8C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <list>
#include "SendData.h"
// NavigationDlgBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNavigationDlgBar dialog

class CNavigationDlgBar : public CDialogBar
{
// Construction
public: 
	void RefreshRadarList();
	void RefreshRouteList();
	void RefreshVesselList();
	void RefreshAlarmBar(long left, long top, long right, long bottom, COLORREF alarmColor);
	void ClearDlgContents( long left, long top, long right, long bottom);
	void ShowNavigationInfoText(int nXStart, int nYStart, CString textOutString, int charSize, CString FontString);
	CNavigationDlgBar();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNavigationDlgBar)
	enum { IDD = IDD_NAVIGATION_DLG };
	CButton	m_button; 
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavigationDlgBar)
	public:
	virtual BOOL Create(CWnd* pParent, UINT nIDTemplate, UINT nStyle, UINT nID);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNavigationDlgBar)
	virtual BOOL OnInitDialog(); 
	afx_msg void OnSetNavRouteButton();
	afx_msg void OnDelRouteBtn();
	afx_msg void OnSelchangeRouteList();
	afx_msg void OnSelchangeVesselList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnDblclkRadarList();
	afx_msg void OnNMClickRadarList(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVIGATIONDLGBAR_H__5053D4D0_8D32_4DA3_85D8_33A51261B8C1__INCLUDED_)
