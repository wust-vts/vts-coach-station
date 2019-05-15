// GetDcpaTcpaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "GetDcpaTcpaDlg.h"
#include "MainFrm.h" 

// CGetDcpaTcpaDlg 对话框

IMPLEMENT_DYNAMIC(CGetDcpaTcpaDlg, CDialog)

CGetDcpaTcpaDlg::CGetDcpaTcpaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetDcpaTcpaDlg::IDD, pParent)
	, m_fLon1(0)
	, m_fLat1(0)
	, m_fSpeed1(0)
	, m_fCourse1(0)
	, m_fLon2(0)
	, m_fLat2(0)
	, m_fSpeed2(0)
	, m_fCourse2(0)
	, m_iTcpa(0)
	, m_fDcpa(0)
{

}

CGetDcpaTcpaDlg::~CGetDcpaTcpaDlg()
{
}

void CGetDcpaTcpaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LON1, m_fLon1);
	DDX_Text(pDX, IDC_EDIT_LAT1, m_fLat1);
	DDX_Text(pDX, IDC_EDIT_SPEED1, m_fSpeed1);
	DDX_Text(pDX, IDC_EDIT_COURSE1, m_fCourse1);
	DDX_Text(pDX, IDC_EDIT_LON2, m_fLon2);
	DDX_Text(pDX, IDC_EDIT_LAT2, m_fLat2);
	DDX_Text(pDX, IDC_EDIT_SPEED2, m_fSpeed2);
	DDX_Text(pDX, IDC_EDIT_COURSE2, m_fCourse2);
	DDX_Text(pDX, IDC_EDIT_TCPA, m_iTcpa);
	DDX_Text(pDX, IDC_EDIT_DCPA, m_fDcpa);
}


BEGIN_MESSAGE_MAP(CGetDcpaTcpaDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CGetDcpaTcpaDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CGetDcpaTcpaDlg 消息处理程序

void CGetDcpaTcpaDlg::OnBnClickedOk()
{
	UpdateData(true);
	
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	long iGeoPoX1 = (long)(m_fLon1 * UNI_GEO_COOR_MULTI_FACTOR);
	long iGeoPoY1 = (long)(m_fLat1 * UNI_GEO_COOR_MULTI_FACTOR);
	long iGeoPoX2 = (long)(m_fLon2 * UNI_GEO_COOR_MULTI_FACTOR);
	long iGeoPoY2 = (long)(m_fLat2 * UNI_GEO_COOR_MULTI_FACTOR);
	float retTcpa = 0;
	float retDcpa = 0;
	pYimaEncCtrl->GetTwoShipsDcpaAndTcpa(iGeoPoX1,iGeoPoY1,m_fSpeed1,m_fCourse1,iGeoPoX2,iGeoPoY2,m_fSpeed2,m_fCourse2,&retDcpa,&retTcpa);

	m_iTcpa = retTcpa;//返回单位秒
	m_fDcpa = retDcpa;//返回单位海里
	UpdateData(false);

}
