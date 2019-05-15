#include "afxwin.h"
#if !defined(AFX_USERMAPLAYERSDLG_H__C4249BB6_AD12_4B05_84C1_CFE298E8F97D__INCLUDED_)
#define AFX_USERMAPLAYERSDLG_H__C4249BB6_AD12_4B05_84C1_CFE298E8F97D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserMapLayersDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserMapLayersDlg dialog

class CUserMapLayersDlg : public CDialog
{
// Construction
public:
	CUserMapLayersDlg(CWnd* pParent = NULL);   // standard constructor

    int m_iLayerCount; 
	int m_iSelLayerNum;
 
	CString GetGeoTypeString(LAYER_GEO_TYPE lyrGeoType);
	LAYER_GEO_TYPE GetLayerGeoType(int comBoxIndex); 

// Dialog Data
	//{{AFX_DATA(CUserMapLayersDlg)
	enum { IDD = IDD_USER_LAYER_DLG };
	CListBox	m_layerListCtrl;
	CString	m_curSelLayerName; 
	BOOL	m_bLayerShowOrNot;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserMapLayersDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateListCtrl();

	// Generated message map functions
	//{{AFX_MSG(CUserMapLayersDlg)
//	afx_msg void OnSelchangeUserMapLayerList();
	afx_msg void OnDblclkUserMapLayerList();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowCheck();
	afx_msg void OnNewLayerButton();
	afx_msg void OnSaveNameButton();
	afx_msg void OnDelLayerButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CComboBox m_GeoTypeCombox;  
	CString m_strCurLayerType;
	afx_msg void UpdateDialogWithLayerSelected();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERMAPLAYERSDLG_H__C4249BB6_AD12_4B05_84C1_CFE298E8F97D__INCLUDED_)
