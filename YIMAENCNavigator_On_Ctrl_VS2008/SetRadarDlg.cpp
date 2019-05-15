// SetRadarDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "SetRadarDlg.h"
#include "afxdialogex.h"
#include "SendData.h"

extern Radar curSelectRadar;
extern list<Radar> radarList;

// SetRadarDlg 对话框

IMPLEMENT_DYNAMIC(SetRadarDlg, CDialog)

SetRadarDlg::SetRadarDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SetRadarDlg, pParent)
	, range(0)
	, height(0)
	, level(0)
{

}

SetRadarDlg::~SetRadarDlg()
{
}

void SetRadarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Radar_Range, range);
	DDX_Text(pDX, IDC_Radar_Height, height);
	DDX_Text(pDX, IDC_Water_level, level);
	DDX_Control(pDX, IDC_Select_ODUList, selectODUlist);
}


BEGIN_MESSAGE_MAP(SetRadarDlg, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &SetRadarDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// SetRadarDlg 消息处理程序


BOOL SetRadarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//获取ODU SelectODUlist客户区大小
	CRect oduRect;
	selectODUlist.GetClientRect(&oduRect);
	selectODUlist.SetExtendedStyle(selectODUlist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	//添加列标题
	selectODUlist.InsertColumn(0, _T("选取"), LVCFMT_CENTER, oduRect.Width() * 2 / 16);
	selectODUlist.InsertColumn(1, _T("ODU编号"), LVCFMT_CENTER, oduRect.Width() * 4 / 16);
	selectODUlist.InsertColumn(2, _T("IP"), LVCFMT_CENTER, oduRect.Width() * 6 / 16);
	selectODUlist.InsertColumn(3, _T("PORT"), LVCFMT_CENTER, oduRect.Width() * 4 / 16);

	CFont* statusFont = new CFont;
	statusFont->CreateFontA(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("微软雅黑"));

	selectODUlist.SetFont(statusFont);
	//**********data 测试用************
	selectODUlist.InsertItem(0, _T(""));
	selectODUlist.SetItemText(0, 1, "123");
	selectODUlist.SetItemText(0, 2, "192.168.0.1");
	selectODUlist.SetItemText(0, 3, "6001");

	selectODUlist.InsertItem(1, _T(""));
	selectODUlist.SetItemText(1, 1, "456");
	selectODUlist.SetItemText(1, 2, "192.168.0.2");
	selectODUlist.SetItemText(1, 3, "6002");

	selectODUlist.InsertItem(2, _T(""));
	selectODUlist.SetItemText(2, 1, "789");
	selectODUlist.SetItemText(2, 2, "192.168.0.3");
	selectODUlist.SetItemText(2, 3, "6003");
	//*********************************
	selectODUlist.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void SetRadarDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DestroyWindow();
	CDialog::OnClose();
}

void SetRadarDlg::refreshODUList(list<ODU>& oduList)
{
	//读取ODU列表信息显示
	if (!oduList.empty())
	{
		selectODUlist.DeleteAllItems();			//清空显示数据
		int count = oduList.size();
		for (int j = 0; j < count; j++)
		{
			selectODUlist.InsertItem(j, _T(""));
		}

		int i = 0;

		list<ODU>::iterator iter;
		CString PortStr;
		for (iter = oduList.begin(); iter != oduList.end(); iter++)
		{
			PortStr.Format(_T("%u"), iter->Port);

			selectODUlist.SetItemText(i, 1, iter->ID.data());
			selectODUlist.SetItemText(i, 2, iter->IP.data());
			selectODUlist.SetItemText(i, 3, PortStr.GetBuffer());
			i++;
		}
	}
}


void SetRadarDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	for (list<Radar>::iterator iter = radarList.begin(); iter != radarList.end(); iter++)
	{
		if (iter->Id == curSelectRadar.Id)
		{
			iter->Height = height;
			iter->Range = range;
			iter->Level = level;
		}
	}
	string radarAddMsg = "VTSRADAR-S";
	string OduTarget = "";
	CString lonStr, lanStr, rangeStr, heightStr, levelStr;
	lonStr.Format(_T("%lf"), curSelectRadar.Lon*1.0 / UNI_GEO_COOR_MULTI_FACTOR);
	lanStr.Format(_T("%lf"), curSelectRadar.Lan*1.0 / UNI_GEO_COOR_MULTI_FACTOR);
	rangeStr.Format(_T("%lf"), range);
	heightStr.Format(_T("%lf"), height);
	levelStr.Format(_T("%lf"), level);
	for (int nItem = 0; nItem < selectODUlist.GetItemCount(); nItem++)
	{
		bool bCheckState = selectODUlist.GetCheck(nItem);		//获取checkbox选中项
		if (bCheckState)
		{
			CString ip = selectODUlist.GetItemText(nItem, 2);
			CString port = selectODUlist.GetItemText(nItem, 3);
			OduTarget = OduTarget + ip.GetBuffer() + ";" + port.GetBuffer() + ";";
		}
	}
	if (OduTarget != "")
	{
		radarAddMsg = radarAddMsg + ";AR&AT" + ";" + curSelectRadar.Id + ";" + OduTarget + lonStr.GetBuffer() + ";" + lanStr.GetBuffer() + ";" + heightStr.GetBuffer() + ";" + rangeStr.GetBuffer() + ";" + levelStr.GetBuffer() + "#";
	}
	else
	{
		radarAddMsg = radarAddMsg + ";AR" + ";" + curSelectRadar.Id + ";" + ";" + ";" + lonStr.GetBuffer() + ";" + lanStr.GetBuffer() + ";" + heightStr.GetBuffer() + ";" + rangeStr.GetBuffer() + ";" + levelStr.GetBuffer() + "#";
	}
	//发送Radar添加信息
	sendRadarData(radarAddMsg, "127.0.0.1", RADAR_PORT);
	CDialog::OnOK();
}
