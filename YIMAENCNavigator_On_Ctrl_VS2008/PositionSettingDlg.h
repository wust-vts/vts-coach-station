#pragma once


// CPositionSettingDlg 对话框

class CPositionSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CPositionSettingDlg)

public:
	CPositionSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPositionSettingDlg();

// 对话框数据
	enum { IDD = IDD_POSITION_SETTING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	void GetGeoPoTopDFM(int geoPo, float& pD, float& pF, float& pM);
	void GetpDFMToGeoPo(float pD, float pF, float pM, int& geoPo);
	float m_fLonD;
	float m_fLonF;
	float m_fLonM;
	float m_fLatD;
	float m_fLatF;
	float m_fLatM;
	int m_geoPoX;
	int m_geoPoY;
	bool m_bApply;
	afx_msg void OnPaint();
};
