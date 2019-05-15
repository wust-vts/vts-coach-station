#pragma once
#include <string>
#include <list>
#include "SendData.h"

using namespace std;
// RadarPropertyDlg 对话框

class RadarPropertyDlg : public CDialog
{
	DECLARE_DYNAMIC(RadarPropertyDlg)

public:
	RadarPropertyDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~RadarPropertyDlg();
public:
	CString ptId;
	double ptLon;
	double ptLan;
	double ptRange;
	double ptHeight;
	double ptLevel;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RadarPropertyDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnBnClickedOk();
	CString toCString(string str);		//string to CString
};
