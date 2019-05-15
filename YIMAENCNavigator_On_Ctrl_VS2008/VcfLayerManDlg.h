#pragma once
#include "afxwin.h"


// CVcfLayerManDlg 对话框

class CVcfLayerManDlg : public CDialog
{
	DECLARE_DYNAMIC(CVcfLayerManDlg)

public:
	CVcfLayerManDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVcfLayerManDlg();

// 对话框数据
	enum { IDD = IDD_VCF_LAYER_MAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_vcfMapPos; 
	virtual BOOL OnInitDialog();
	CCheckListBox m_layerList;
	afx_msg void OnBnClickedOk();  
	afx_msg void OnLbnChkchangelListLayer();
	afx_msg void OnBnClickedBtnShowAllVcfLy();
	afx_msg void OnBnClickedBtnHiddenAllVcfLy();
};
