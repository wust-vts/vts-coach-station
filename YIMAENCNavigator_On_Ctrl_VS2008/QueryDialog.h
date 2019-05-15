#if !defined(AFX_QUERYDIALOG_H__7E6BECA3_56BE_4648_9C9B_A05BBC6BA5B6__INCLUDED_)
#define AFX_QUERYDIALOG_H__7E6BECA3_56BE_4648_9C9B_A05BBC6BA5B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QueryDialog.h : header file
//

#include "YIMAENCHEAD.H"

/////////////////////////////////////////////////////////////////////////////
// CQueryDialog dialog

class CQueryDialog : public CDialog
{
// Construction
public:
	CQueryDialog(CWnd* pParent = NULL);   // standard constructor

	~CQueryDialog()
	{
		if (m_pSelectedObjPoses != NULL)
			delete m_pSelectedObjPoses;
	}

	int m_curSelectedObjCount; //YIMAENC COMMENT: 当前查询出的物标个数
	MEM_GEO_OBJ_POS* m_pSelectedObjPoses;//YIMAENC COMMENT: 当前查询出的所有物标位置指针

	bool SetSelectObjectPoses(MEM_GEO_OBJ_POS *pSelObjPoses, int selObjCount);

private:
	int GetSelObjNumByListCurSel(int curSelNum);

public:

// Dialog Data
	//{{AFX_DATA(CQueryDialog)
	enum { IDD = IDD_QUERY_DIALOG };
	CListBox	m_selGeoObjectList;
	CString	m_strQueryKeyString;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQueryDialog)
	afx_msg void OnQueryButton();
	afx_msg void OnDblclkSelObjList();
	afx_msg void OnSelchangeSelObjList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYDIALOG_H__7E6BECA3_56BE_4648_9C9B_A05BBC6BA5B6__INCLUDED_)
