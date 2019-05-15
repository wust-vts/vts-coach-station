#pragma once


// CTestNineNineBoxDlg 对话框

class CTestNineNineBoxDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestNineNineBoxDlg)

public:
	CTestNineNineBoxDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestNineNineBoxDlg();

// 对话框数据
	enum { IDD = IDD_TEST_NINE_NINE_BOX_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	float m_fCenterLon;
	float m_fCenterLat;
	BOOL m_bShowOrNot;
	float m_fCurLon;
	float m_fCurLat;
	CString m_strCurNumber;
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedCheckShowOrNot();
	BOOL m_bShowText;
	afx_msg void OnBnClickedChkShowText();
};
