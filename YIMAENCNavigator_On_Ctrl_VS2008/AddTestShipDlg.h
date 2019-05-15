#pragma once


// CAddTestShipDlg 对话框

class CAddTestShipDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddTestShipDlg)

public:
	CAddTestShipDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddTestShipDlg();

// 对话框数据
	enum { IDD = IDD_ADD_TEST_SHIP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	int m_iCurShipCount;
	int m_iAddShipCount;
	afx_msg void OnBnClickedOk();
	int m_iSaveTrackCount;
	int m_iShowTrackCount;
};
