// PositionSettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "PositionSettingDlg.h"


// CPositionSettingDlg 对话框

IMPLEMENT_DYNAMIC(CPositionSettingDlg, CDialog)

CPositionSettingDlg::CPositionSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPositionSettingDlg::IDD, pParent)
	, m_fLonD(0)
	, m_fLonF(0)
	, m_fLonM(0)
	, m_fLatD(0)
	, m_fLatF(0)
	, m_fLatM(0)
{
	m_geoPoX = 0;
	m_geoPoY = 0;
	m_bApply = false;
}

CPositionSettingDlg::~CPositionSettingDlg()
{
}

void CPositionSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_LonD, m_fLonD);
	DDV_MinMaxFloat(pDX, m_fLonD, -180, 180);
	DDX_Text(pDX, IDC_EDT_LonF, m_fLonF);
	DDV_MinMaxFloat(pDX, m_fLonF, 0, 60);
	DDX_Text(pDX, IIDC_EDT_LonM, m_fLonM);
	DDV_MinMaxFloat(pDX, m_fLonM, 0, 60);
	DDX_Text(pDX, IDC_EDT_LatD, m_fLatD);
	DDV_MinMaxFloat(pDX, m_fLatD, -90, 90);
	DDX_Text(pDX, IDC_EDT_LatF, m_fLatF);
	DDV_MinMaxFloat(pDX, m_fLatF, 0, 60);
	DDX_Text(pDX, IDC_EDT_LatM, m_fLatM);
	DDV_MinMaxFloat(pDX, m_fLatM, 0, 60);
}


BEGIN_MESSAGE_MAP(CPositionSettingDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CPositionSettingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPositionSettingDlg::OnBnClickedCancel)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPositionSettingDlg 消息处理程序

void CPositionSettingDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	GetpDFMToGeoPo(m_fLonD, m_fLonF, m_fLonM, m_geoPoX);
	GetpDFMToGeoPo(m_fLatD, m_fLatF, m_fLatM, m_geoPoY);
	m_bApply = true;
	OnOK();
}

void CPositionSettingDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bApply = false;
	OnCancel();
}

BOOL CPositionSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetGeoPoTopDFM(m_geoPoX, m_fLonD, m_fLonF, m_fLonM);
	GetGeoPoTopDFM(m_geoPoY, m_fLatD, m_fLatF, m_fLatM); 
	UpdateData(FALSE);
	return TRUE;  
}

void CPositionSettingDlg::GetGeoPoTopDFM(int geoPo, float& pD, float& pF, float& pM)
{
	float flon = (float)geoPo / 10000000;
	pD = (int)flon; 
	pF = (flon - pD) * 60;
	pM = (pF - (int)pF) * 60;
	pF = (int)pF;
}

void CPositionSettingDlg::GetpDFMToGeoPo(float pD, float pF, float pM, int& geoPo)
{
	float flon = pD + pF / 60 + pM / 3600;
	geoPo = (int)(flon * 10000000);
}

void CPositionSettingDlg::OnPaint()
{
	CPaintDC dc(this); 
	CRect rect; 
	this->GetWindowRect(&rect);
	int iwide = rect.right - rect.left - 2;
	int iheight = rect.bottom - rect.top - 2;
	CPen pen(PS_SOLID, 2, RGB(255, 0,0));
	dc.SelectObject(&pen);
	POINT* edgePo = new POINT[5];
	edgePo[0].x = 0;
	edgePo[0].y = 0;
	edgePo[1].x = iwide;
	edgePo[1].y = 0;
	edgePo[2].x = iwide;
	edgePo[2].y = iheight;
	edgePo[3].x = 0;
	edgePo[3].y = iheight;
	edgePo[4].x = 0;
	edgePo[4].y = 0;
	dc.Polyline(edgePo, 5);
	delete edgePo;
}
