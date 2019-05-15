//{{AFX_INCLUDES()
#include "Grid.h"
//}}AFX_INCLUDES
#if !defined(AFX_GEOOBJECTINFODLG_H__07446AD0_EE06_4392_B1E0_ED004D59D75E__INCLUDED_)
#define AFX_GEOOBJECTINFODLG_H__07446AD0_EE06_4392_B1E0_ED004D59D75E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GeoObjectInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGeoObjectInfoDlg dialog

class CGeoObjectInfoDlg : public CDialog
{
// Construction
public:
	CGeoObjectInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGeoObjectInfoDlg)
	enum { IDD = IDD_GEO_OBJECT_INFO_DLG };
	CGrid	m_attrGrid;
	CString	m_strObjGeoType;
	CString	m_strInnerLayerPos;
	CString	m_strLayerPos;
	CString	m_strLayerName;
	float	m_fScaleMin;
	CString	m_strAreaOfFace;
	//}}AFX_DATA

	bool m_bIsS57OrUserMapObj;
	MEM_GEO_OBJ_POS m_memObjPos; //如果显示的是S57海图对象
	M_GEO_OBJ_POS m_userMapObjPos; //如果显示的是自定义海图的对象

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeoObjectInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int	oldCol;
	int oldRow;	

	void MoveEditCtrl(void);
	void SaveEditCtrlToCell();
	void GetEditCtrlTextFromCell();

	// Generated message map functions
	//{{AFX_MSG(CGeoObjectInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnKeyPressMsflexgrid(short FAR* KeyAscii);
	afx_msg void OnClickMsflexgrid();
	afx_msg void OnDblClickMsflexgrid();
	afx_msg void OnOLEStartDragMsflexgrid(LPDISPATCH FAR* Data, long FAR* AllowedEffects);
	afx_msg void OnRowColChangeMsflexgrid();
	virtual void OnOK();
	afx_msg void OnSetScaleminButton();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public: 
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GEOOBJECTINFODLG_H__07446AD0_EE06_4392_B1E0_ED004D59D75E__INCLUDED_)
