#pragma once


// CTestCaculateScaleDlg 对话框

class CTestCaculateScaleDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestCaculateScaleDlg)

public:
	CTestCaculateScaleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestCaculateScaleDlg();

// 对话框数据
	enum { IDD = IDD_TEST_CACULATE_SCALE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_iCurPx;
	float m_fCurDis;
	int m_iScale;
	int m_iCurScale;
	int m_iPxDis;
	float m_fDis;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
};
