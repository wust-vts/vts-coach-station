#pragma once
#include <string>
#include <list>
#include "SendData.h"
using namespace std;

// ModifyRadarDlg 对话框

class ModifyRadarDlg : public CDialog
{
	DECLARE_DYNAMIC(ModifyRadarDlg)

public:
	ModifyRadarDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ModifyRadarDlg();
public:
	double mdRange;
	double mdHeight;
	double mdLevel;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ModifyRadarDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
