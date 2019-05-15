#if !defined(AFX_ALARMSETTINGDLG_H__6B04BEBD_B00E_4288_8EAD_B88B45BF9C07__INCLUDED_)
#define AFX_ALARMSETTINGDLG_H__6B04BEBD_B00E_4288_8EAD_B88B45BF9C07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmSettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlarmSettingDlg dialog

class CAlarmSettingDlg : public CDialog
{
// Construction
public:
	CAlarmSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmSettingDlg)
	enum { IDD = IDD_ALARM_SETTING_DLG };
	UINT	m_isoDangerDistDoor;
	UINT	m_offRouteDistDoor;
	UINT	m_safeContourDistDoor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmSettingDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	float m_fShallowDepthDoor;
	float m_fDeepDepthDoor;
	float g_fTcpaDoor;
	float g_fDcpaDoor;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMSETTINGDLG_H__6B04BEBD_B00E_4288_8EAD_B88B45BF9C07__INCLUDED_)
