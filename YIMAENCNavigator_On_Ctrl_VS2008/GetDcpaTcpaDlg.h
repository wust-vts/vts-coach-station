#pragma once


// CGetDcpaTcpaDlg 对话框

class CGetDcpaTcpaDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetDcpaTcpaDlg)

public:
	CGetDcpaTcpaDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGetDcpaTcpaDlg();

// 对话框数据
	enum { IDD = IDD_GET_DCPA_TCPA_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_fLon1;
	float m_fLat1;
	float m_fSpeed1;
	float m_fCourse1;
	float m_fLon2;
	float m_fLat2;
	float m_fSpeed2;
	float m_fCourse2;
	int m_iTcpa;
	float m_fDcpa;
	afx_msg void OnBnClickedOk();
};
