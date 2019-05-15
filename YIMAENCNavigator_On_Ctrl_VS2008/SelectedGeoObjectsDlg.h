#if !defined(AFX_SELECTEDGEOOBJECTSDLG_H__BDBAFC26_AA46_40ED_BDCE_F75051C96F12__INCLUDED_)
#define AFX_SELECTEDGEOOBJECTSDLG_H__BDBAFC26_AA46_40ED_BDCE_F75051C96F12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectedGeoObjectsDlg.h : header file
// 

/////////////////////////////////////////////////////////////////////////////
// CSelectedGeoObjectsDlg dialog
#include "YIMAENCHEAD.H"
#include "Resource.h"

class CSelectedGeoObjectsDlg : public CDialog
{
// Construction
public:
	bool SetSelectObjectPoses(MEM_GEO_OBJ_POS* pSelObjPoses, int selObjCount);
	CSelectedGeoObjectsDlg(CWnd* pParent = NULL);   // standard constructor

	~CSelectedGeoObjectsDlg()
	{
		if (m_pSelectedObjPoses != NULL)
			delete m_pSelectedObjPoses;
	}

	int m_curSelectedObjCount; //YIMAENC COMMENT: 当前选中的物标个数
	MEM_GEO_OBJ_POS* m_pSelectedObjPoses;//YIMAENC COMMENT: 当前选中的所有物标位置指针
 	
	int GetSelObjNumByListCurSel(int curSelNum);

// Dialog Data
	//{{AFX_DATA(CSelectedGeoObjectsDlg)
	enum { IDD = IDD_SEL_OBJECTS_DLG };
	CListBox	m_selGeoObjectList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectedGeoObjectsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectedGeoObjectsDlg)
	afx_msg void OnDblclkSelObjList();
	afx_msg void OnSelchangeSelObjList();
	virtual BOOL OnInitDialog();
	afx_msg void OnDelButton();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnModifyPosition();
	BOOL m_bIfShowObj;
	afx_msg void OnBnClickedChkIfShowObj();  
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTEDGEOOBJECTSDLG_H__BDBAFC26_AA46_40ED_BDCE_F75051C96F12__INCLUDED_)
