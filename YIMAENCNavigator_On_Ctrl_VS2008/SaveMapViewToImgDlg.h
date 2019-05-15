#pragma once


// CSaveMapViewToImgDlg 对话框

class CSaveMapViewToImgDlg : public CDialog
{
	DECLARE_DYNAMIC(CSaveMapViewToImgDlg)

public:
	CSaveMapViewToImgDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSaveMapViewToImgDlg();

// 对话框数据
	enum { IDD = IDD_SAVE_MAP_VIEW_TO_IMG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	bool m_bSavePng;
	bool m_bSaveJpg;
	bool m_bSaveBmp;
	bool m_bSaveGif;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRadioPng();
	afx_msg void OnBnClickedRadioJpg();
	afx_msg void OnBnClickedRadioBmp(); 
	afx_msg void OnBnClickedRadioGif();
};
