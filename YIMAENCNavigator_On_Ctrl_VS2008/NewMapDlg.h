#pragma once
#include "yimaenc.h"


// CNewMapDlg �Ի���

class CNewMapDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewMapDlg)

public:
	CNewMapDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewMapDlg();

// �Ի�������
	enum { IDD = IDD_NEW_MAP_DLG };
	bool m_bInit;
	bool m_bDrag;
	M_POINT m_mouseDragFirstPo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CYimaEnc m_newMapCtrl;
	void ReDrawMap();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonMapRotate();
	afx_msg void OnBnClickedButtonSetLandColor();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt); 
};