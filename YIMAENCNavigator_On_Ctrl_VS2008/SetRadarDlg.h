#pragma once

#include <list>
#include <string>
using namespace std;

typedef struct ODU_info
{
	string ID;			//ODU编号
	string IP;
	u_short Port;
	int checkcount;			//ODU登录计时
}ODU;

// SetRadarDlg 对话框

class SetRadarDlg : public CDialog
{
	DECLARE_DYNAMIC(SetRadarDlg)

public:
	SetRadarDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SetRadarDlg();

public:
	double range;		//量程
	double height;		//高度
	double level;		//水面高度

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SetRadarDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl selectODUlist;		//选择已登录ODU设备
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();

	void refreshODUList(list<ODU>& oduList);
	afx_msg void OnBnClickedOk();
};
