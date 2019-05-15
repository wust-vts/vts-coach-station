#pragma once
#include "yimaenc.h"


// CGlobalView �Ի���

class CGlobalView : public CDialog
{
	DECLARE_DYNAMIC(CGlobalView)

public:
	CGlobalView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGlobalView();

// �Ի�������
	enum { IDD = IDD_GLOBAL_VIEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	bool m_bOpend;
	bool m_bDragingMap;
	bool m_bInit;
	CPoint m_mouseDragFirstPo;
	CYimaEnc m_globalViewCtrl;
	CYimaEnc* m_mainCtrl;
	CView* m_mainView;
	CRect m_rectScrnView;
	CSize m_mainViewSize;  


	void ReSetViewPosion();
	void OnMainViewReSize(int mainViewWidth = 0, int mainViewHeight = 0);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_EVENTSINK_MAP()
//	void AfterDrawMapGlogalViewCtrl();
//	void OnEndLButtonUpGlogalViewCtrl(unsigned short nFlags, long pointX, long pointY);
//	void OnEndMouseWheelGlogalViewCtrl(unsigned short nFlag, short zDelta, long pointX, long pointY);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};