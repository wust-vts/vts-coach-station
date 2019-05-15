// AlarmSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "AlarmSettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmSettingDlg dialog


CAlarmSettingDlg::CAlarmSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmSettingDlg::IDD, pParent)
	, m_fShallowDepthDoor(0)
	, m_fDeepDepthDoor(0)
	, g_fTcpaDoor(0)
	, g_fDcpaDoor(0)
{
	//{{AFX_DATA_INIT(CAlarmSettingDlg)
	m_isoDangerDistDoor = 0;
	m_offRouteDistDoor = 0;
	m_safeContourDistDoor = 0;
	//}}AFX_DATA_INIT
}


void CAlarmSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmSettingDlg)
	DDX_Text(pDX, IDC_ISO_DANGER_DIST_DOOR, m_isoDangerDistDoor);
	DDX_Text(pDX, IDC_OFF_ROUTE_DIST_DOOR, m_offRouteDistDoor);
	DDX_Text(pDX, IDC_SAFE_CONTOUR_DIST_DOOR, m_safeContourDistDoor);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_SHALLOW_DEPTH_DOOR, m_fShallowDepthDoor);
	DDV_MinMaxFloat(pDX, m_fShallowDepthDoor, 0, 999999999);
	DDX_Text(pDX, IDC_DEEP_DEPTH_DOOR, m_fDeepDepthDoor);
	DDX_Text(pDX, IDC_EDIT_TCPA_DOOR, g_fTcpaDoor);
	DDX_Text(pDX, IDC_EDIT_DCPA_DOOR, g_fDcpaDoor);
}


BEGIN_MESSAGE_MAP(CAlarmSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CAlarmSettingDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CAlarmSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmSettingDlg message handlers

void CAlarmSettingDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
