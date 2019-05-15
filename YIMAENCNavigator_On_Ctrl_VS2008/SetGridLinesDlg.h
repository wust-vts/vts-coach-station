#pragma once

#include "YimaEnc.h"

// CSetGridLinesDlg dialog

class CSetGridLinesDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetGridLinesDlg)

public:
	CSetGridLinesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetGridLinesDlg();

	long m_gridLineColor;
	long m_lonTextColor;
	long m_latTextColor;

// Dialog Data
	enum { IDD = IDD_SET_GRID_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_nGridDensityCount;
	long m_nGridTextFontSize;
	CYimaEnc* m_pEncCtrl;
	afx_msg void OnBnClickedGridLineColorBtn(); 
	afx_msg void OnBnClickedApply();
	afx_msg void OnBnClickedLonTextColorBtn();
	afx_msg void OnBnClickedLatTextColorBtn();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};