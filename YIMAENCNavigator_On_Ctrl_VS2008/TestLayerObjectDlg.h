#pragma once


// CTestLayerObjectDlg 对话框

class CTestLayerObjectDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestLayerObjectDlg)

public:
	CTestLayerObjectDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestLayerObjectDlg();

// 对话框数据
	enum { IDD = IDD_TEST_LAYER_OBJECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddLayers();
	int m_arrLayerPos[10];
	bool m_bAddLayer;
	int m_iLayerCount;
	int m_startLayerPos;
	afx_msg void OnBnClickedButtonAddObj();
};
