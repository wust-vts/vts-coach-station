#pragma once
#include "afxwin.h"


// CVcfLayerManDlg �Ի���

class CVcfLayerManDlg : public CDialog
{
	DECLARE_DYNAMIC(CVcfLayerManDlg)

public:
	CVcfLayerManDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVcfLayerManDlg();

// �Ի�������
	enum { IDD = IDD_VCF_LAYER_MAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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