#pragma once
#include "afxwin.h"

typedef struct WarnShip
{
	int shipId;
	bool bInArea;
}WarnShip;
// CTestAreaWarnDlg �Ի���

class CTestAreaWarnDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestAreaWarnDlg)

public:
	CTestAreaWarnDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestAreaWarnDlg();

// �Ի�������
	enum { IDD = IDD_TEST_AREA_WARN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strWarnInfo;
	afx_msg void OnBnClickedButtonAddTestData();
	
	WarnShip* m_arrWarnShipInfo;
	bool m_bAddShip;
	int m_iObjPos;
	afx_msg void OnBnClickedButtonCheckWarn();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheckNear();
	CString m_strNearShipId;
	int m_iCheckLen; 
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
};