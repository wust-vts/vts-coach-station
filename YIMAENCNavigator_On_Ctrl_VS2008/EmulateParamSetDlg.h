#if !defined(AFX_EMULATEPARAMSETDLG_H__0AD0B11E_9FAC_45FB_A293_08DC2AC5DEEC__INCLUDED_)
#define AFX_EMULATEPARAMSETDLG_H__0AD0B11E_9FAC_45FB_A293_08DC2AC5DEEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EmulateParamSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEmulateParamSetDlg dialog

class CEmulateParamSetDlg : public CDialog
{
// Construction
public:
	CEmulateParamSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEmulateParamSetDlg)
	enum { IDD = IDD_EMULATE_PARAM_DLG };
	float	m_fSpeed;
	UINT	m_iClockInterval;
	BOOL	m_bShowSpeedTimeMark;
	BOOL	m_bShowHeadingLine;
	BOOL	m_bShowSpeedVector;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmulateParamSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEmulateParamSetDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_iMaxStoreTrackPoCount;
	int m_iMaxShowTrackPoCount;
	int m_iMaxStoreTrackTime;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMULATEPARAMSETDLG_H__0AD0B11E_9FAC_45FB_A293_08DC2AC5DEEC__INCLUDED_)
