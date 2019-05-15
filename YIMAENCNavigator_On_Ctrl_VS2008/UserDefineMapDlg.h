#if !defined(AFX_USERDEFINEMAPDLG_H__92F7CB86_38AB_4DA4_832C_404A5244F54D__INCLUDED_)
#define AFX_USERDEFINEMAPDLG_H__92F7CB86_38AB_4DA4_832C_404A5244F54D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserDefineMapDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserDefineMapDlg dialog

class CUserDefineMapDlg : public CDialog
{
// Construction
public:
	CUserDefineMapDlg(CWnd* pParent = NULL);   // standard constructor
	int lastcomboxcur;
// Dialog Data
	//{{AFX_DATA(CUserDefineMapDlg)
	enum { IDD = IDD_USER_DEFINE_MAPLAYER_DLG };
	CListBox	m_UserLayerObjectList;
	CComboBox	m_UserLayerSelectComBox;
	CListBox	m_LayerObjectList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserDefineMapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserDefineMapDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddtolayerBtn();
	afx_msg void OnDeleteromlayerBtn();
	afx_msg void OnSelchangeUserlayrSelectCombox();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERDEFINEMAPDLG_H__92F7CB86_38AB_4DA4_832C_404A5244F54D__INCLUDED_)
