// RadarPropertyDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "RadarPropertyDlg.h"
#include "afxdialogex.h"

extern Radar curSelectRadar;
extern list<Radar> radarList;
// RadarPropertyDlg 对话框

IMPLEMENT_DYNAMIC(RadarPropertyDlg, CDialog)

RadarPropertyDlg::RadarPropertyDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_RadarPropertyDlg, pParent)
	, ptId(_T("0"))
	, ptLon(0)
	, ptLan(0)
	, ptRange(0)
	, ptHeight(0)
	, ptLevel(0)
{
	ptId = toCString(curSelectRadar.Id);
	ptLon = curSelectRadar.Lon*1.0 / UNI_GEO_COOR_MULTI_FACTOR;
	ptLan = curSelectRadar.Lan*1.0 / UNI_GEO_COOR_MULTI_FACTOR;
	for (list<Radar>::iterator iter = radarList.begin(); iter != radarList.end(); iter++)
	{
		if (iter->Id == curSelectRadar.Id)
		{
			ptHeight = iter->Height;
			ptRange = iter->Range;
			ptLevel = iter->Level;
		}
	}
}

RadarPropertyDlg::~RadarPropertyDlg()
{
}

void RadarPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PTRadar_ID, ptId);
	DDX_Text(pDX, IDC_PTRadar_Lon, ptLon);
	DDX_Text(pDX, IDC_PTRADAR_Lan, ptLan);
	DDX_Text(pDX, IDC_PTRadar_Range, ptRange);
	DDX_Text(pDX, IDC_PTRadar_Height, ptHeight);
	DDX_Text(pDX, IDC_PTWater_level, ptLevel);
}

CString RadarPropertyDlg::toCString(string str)
{
#ifdef _UNICODE
	//如果是unicode工程
	USES_CONVERSION;
	CString s(str.c_str());
	CString ans(str.c_str());
	return ans;
#else
	//如果是多字节工程
	CString ans;
	ans.Format("%s", str.c_str());
	return ans;
#endif
}


BEGIN_MESSAGE_MAP(RadarPropertyDlg, CDialog)
	//ON_BN_CLICKED(IDOK, &RadarPropertyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// RadarPropertyDlg 消息处理程序



//void RadarPropertyDlg::OnBnClickedOk()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CDialog::OnOK();
//}
