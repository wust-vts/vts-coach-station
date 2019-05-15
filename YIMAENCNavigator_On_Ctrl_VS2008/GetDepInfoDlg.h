#pragma once


// CGetDepInfoDlg 对话框

class CGetDepInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetDepInfoDlg)

public:
	CGetDepInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGetDepInfoDlg();

// 对话框数据
	enum { IDD = IDD_GET_DEP_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

	int m_iMemMapPos;
	int m_iMemMapCount;
	CString m_strCurMapName;
	CString m_strDepcntInfo;
	CString m_strCoalneInfo;
};
