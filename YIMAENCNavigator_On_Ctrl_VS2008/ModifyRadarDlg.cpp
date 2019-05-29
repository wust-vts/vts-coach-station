// ModifyRadarDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "ModifyRadarDlg.h"
#include "afxdialogex.h"
#include "AisIPConfig.h"

extern Radar curSelectRadar;
extern list<Radar> radarList;
AisIPConfig ipCon_Mod(L"AisIPconfig.txt");
// ModifyRadarDlg 对话框

IMPLEMENT_DYNAMIC(ModifyRadarDlg, CDialog)

ModifyRadarDlg::ModifyRadarDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ModifyRadarDlg, pParent)
	, mdRange(0)
	, mdHeight(0)
	, mdLevel(0)
{

}

ModifyRadarDlg::~ModifyRadarDlg()
{
}

void ModifyRadarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MDRadar_Range, mdRange);
	DDX_Text(pDX, IDC_MDRadar_Height, mdHeight);
	DDX_Text(pDX, IDC_MDWater_level, mdLevel);
}


BEGIN_MESSAGE_MAP(ModifyRadarDlg, CDialog)
	ON_BN_CLICKED(IDOK, &ModifyRadarDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ModifyRadarDlg 消息处理程序


void ModifyRadarDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	for (list<Radar>::iterator iter = radarList.begin(); iter != radarList.end(); iter++)
	{
		if (iter->Id == curSelectRadar.Id)
		{
			iter->Height = mdHeight;
			iter->Range = mdRange;
			iter->Level = mdLevel;
		}
	}
	std::string radarModifyMsg = "VTSRADAR-S";
	CString mdRangeStr, mdHeightStr, mdLevelStr, mdLonStr, mdLanStr;
	mdRangeStr.Format(_T("%lf"), mdRange);
	mdHeightStr.Format(_T("%lf"), mdHeight);
	mdLevelStr.Format(_T("%lf"), mdLevel);
	mdLonStr.Format(_T("%lf"), curSelectRadar.Lon*1.0 / UNI_GEO_COOR_MULTI_FACTOR);
	mdLanStr.Format(_T("%lf"), curSelectRadar.Lan*1.0 / UNI_GEO_COOR_MULTI_FACTOR);
	radarModifyMsg = radarModifyMsg + ";ER;" + curSelectRadar.Id + ";;;" + mdLonStr.GetBuffer() + ";" + mdLanStr.GetBuffer() + ";" + mdHeightStr.GetBuffer() + ";" + mdRangeStr.GetBuffer() + ";" + mdLevelStr.GetBuffer() + "#";
	//发送Radar修改信息
	sendRadarData(radarModifyMsg, ipCon_Mod.IP_Radar.GetBuffer(), ipCon_Mod.Port_Add_Radar);
	CDialog::OnOK();
}
