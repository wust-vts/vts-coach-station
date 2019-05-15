#pragma once


// CTestShipNearObjWarningDlg 对话框

class CTestShipNearObjWarningDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestShipNearObjWarningDlg)

public:
	CTestShipNearObjWarningDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestShipNearObjWarningDlg();

// 对话框数据
	enum { IDD = IDD_TEST_SHIP_NEAR_OBJ_WARNING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
