#pragma once
#include "afxwin.h"


// CUserObjPosionOprator 对话框

class CUserObjPosionOprator : public CDialog
{
	DECLARE_DYNAMIC(CUserObjPosionOprator)

public:
	CUserObjPosionOprator(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserObjPosionOprator();

// 对话框数据
	enum { IDD = IDD_USER_OBJ_POSITION_OPRATOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	MEM_GEO_OBJ_POS m_curObjPos;
	long m_curGeoType;
	M_POINT* m_arrObjPoints;
	int m_iPointCount;
	void UpdateObjPosition();
	afx_msg void OnBnClickedBtnModifyPositon();
	afx_msg void OnBnClickedBtnDelPosition();
	afx_msg void OnBnClickedBtnAddPositon();
	afx_msg void OnBnClickedBtnAppendPositon();
	virtual BOOL OnInitDialog(); 
	CListBox m_ListObjPosition;
};
