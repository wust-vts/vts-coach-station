// ScrnPlaneGeoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "ScrnPlaneGeoDlg.h"
#include "MainFrm.h" 
// CScrnPlaneGeoDlg 对话框

IMPLEMENT_DYNAMIC(CScrnPlaneGeoDlg, CDialog)

CScrnPlaneGeoDlg::CScrnPlaneGeoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScrnPlaneGeoDlg::IDD, pParent)
	, m_iScrnX(0)
	, m_iScrnY(0)
	, m_iPlaneX(0)
	, m_iPlaneY(0)
	, m_fLon(0)
	, m_fLat(0)
{

}

CScrnPlaneGeoDlg::~CScrnPlaneGeoDlg()
{
}

void CScrnPlaneGeoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SCRNX, m_iScrnX);
	DDX_Text(pDX, IDC_EDIT_SCRNY, m_iScrnY);
	DDX_Text(pDX, IDC_EDIT_PLANEX, m_iPlaneX);
	DDX_Text(pDX, IDC_EDIT_PLANEY, m_iPlaneY);
	DDX_Text(pDX, IDC_EDIT_LON, m_fLon);
	DDX_Text(pDX, IDC_EDIT_LAT, m_fLat);
}


BEGIN_MESSAGE_MAP(CScrnPlaneGeoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BY_SCRN, &CScrnPlaneGeoDlg::OnBnClickedButtonByScrn)
	ON_BN_CLICKED(IDC_BUTTON_BY_PLANE, &CScrnPlaneGeoDlg::OnBnClickedButtonByPlane)
	ON_BN_CLICKED(IDC_BUTTON_BY_LONLAT, &CScrnPlaneGeoDlg::OnBnClickedButtonByLonlat)
END_MESSAGE_MAP()


// CScrnPlaneGeoDlg 消息处理程序

void CScrnPlaneGeoDlg::OnBnClickedButtonByScrn()
{
	UpdateData(true);

	//屏幕坐标转经纬度坐标
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	long retGeoX = 0;
	long retGeoY = 0;
	pYimaEncCtrl->GetGeoPoFromScrnPo(m_iScrnX, m_iScrnY, &retGeoX, &retGeoY);

	m_fLon = double(retGeoX) / UNI_GEO_COOR_MULTI_FACTOR;
	m_fLat = double(retGeoY) / UNI_GEO_COOR_MULTI_FACTOR;

	//屏幕坐标转换平面坐标
	long retPlaneX = 0;
	long retPlaneY = 0;
	pYimaEncCtrl->GetPlaneCoorFromGeoCoor(m_fLon * UNI_GEO_COOR_MULTI_FACTOR,m_fLat * UNI_GEO_COOR_MULTI_FACTOR,&retPlaneX,&retPlaneY);
	m_iPlaneX = (int)retPlaneX;
	m_iPlaneY = (int)retPlaneY;

	UpdateData(false);

	// TODO: 在此添加控件通知处理程序代码
}

void CScrnPlaneGeoDlg::OnBnClickedButtonByPlane()
{
	UpdateData(true);
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	
	//平面坐标转换经纬度坐标
	long geoPoX = 0;
	long geoPoY = 0;
	pYimaEncCtrl->GetGeoPoByPlanePo(m_iPlaneX, m_iPlaneY, &geoPoX,&geoPoY);
	m_fLon = (double) geoPoX  / UNI_GEO_COOR_MULTI_FACTOR;;
	m_fLat = (double) geoPoY  / UNI_GEO_COOR_MULTI_FACTOR;;


	//平面坐标转换屏幕坐标
	long scrnPoX = 0;
	long scrnPoY = 0;
	pYimaEncCtrl->GetScrnPoFromGeoPo(geoPoX, geoPoY, &scrnPoX,&scrnPoY);
	m_iScrnX = scrnPoX;
	m_iScrnY = scrnPoY;

	UpdateData(false);
}

void CScrnPlaneGeoDlg::OnBnClickedButtonByLonlat()
{
	UpdateData(true);

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	long lGeoX = m_fLon * UNI_GEO_COOR_MULTI_FACTOR;
	long lGeoY = m_fLat * UNI_GEO_COOR_MULTI_FACTOR;

	//经纬度坐标转换屏幕坐标
	long lScrnX = 0;
	long lScrnY = 0;
	pYimaEncCtrl->GetScrnPoFromGeoPo(lGeoX, lGeoY, &lScrnX, &lScrnY);	
	m_iScrnX = (int)lScrnX;
	m_iScrnY = (int)lScrnY;

	//经纬度坐标转换平面坐标
	long lPlanePoX = 0;
	long lPlanePoY = 0;
	pYimaEncCtrl->GetPlaneCoorFromGeoCoor(lGeoX, lGeoY, &lPlanePoX, &lPlanePoY);
	m_iPlaneX = (int)lPlanePoX;
	m_iPlaneY = (int)lPlanePoY;

	UpdateData(false);
	// TODO: 在此添加控件通知处理程序代码
}
