#if !defined(AFX_SETS63DEVICEIDDIALOG_H__68B3087D_1232_4936_9460_CBA6EBD3EB87__INCLUDED_)
#define AFX_SETS63DEVICEIDDIALOG_H__68B3087D_1232_4936_9460_CBA6EBD3EB87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetS63DeviceIDDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetS63DeviceIDDialog dialog

class CSetS63DeviceIDDialog : public CDialog
{
// Construction
public:
	CSetS63DeviceIDDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetS63DeviceIDDialog)
	enum { IDD = IDD_SET_DEVICE_ID_DIALOG };
	UINT	m_nDeviceID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetS63DeviceIDDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetS63DeviceIDDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETS63DEVICEIDDIALOG_H__68B3087D_1232_4936_9460_CBA6EBD3EB87__INCLUDED_)
