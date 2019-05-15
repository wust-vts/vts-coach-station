#pragma once


// CSetAttenTimes 对话框

class CSetAttenTimes : public CDialog
{
	DECLARE_DYNAMIC(CSetAttenTimes)

public:
	CSetAttenTimes(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetAttenTimes();

// 对话框数据
	enum { IDD = IDD_SET_ATTEN_TIMES_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_iAttenTimes;
	afx_msg void OnBnClickedOk();
};
