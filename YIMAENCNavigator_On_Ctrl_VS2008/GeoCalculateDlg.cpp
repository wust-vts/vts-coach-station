// GeoCalculateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "GeoCalculateDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeoCalculateDlg dialog


CGeoCalculateDlg::CGeoCalculateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGeoCalculateDlg::IDD, pParent)
	, m_dBearing(0)
	, startGeoX(0)
	, startGeoY(0)
	, fDis(0)
	, fBear(0)
	, retGeoX(0)
	, retGeoY(0)
{
	//{{AFX_DATA_INIT(CGeoCalculateDlg)
	m_dbGeoPo1Y = 0.0;
	m_dbGeoPo1X = 0.0;
	m_dbGeoPo2X = 0.0;
	m_dbGeoPo2Y = 0.0;
	m_dbResult = 0.0;
	//}}AFX_DATA_INIT
}


void CGeoCalculateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeoCalculateDlg)
	DDX_Text(pDX, IDC_EDIT_GEO_PO1_Y, m_dbGeoPo1Y);
	DDX_Text(pDX, IDC_EDIT_GEO_PO1_X, m_dbGeoPo1X);
	DDX_Text(pDX, IDC_EDIT_GEO_PO2_X, m_dbGeoPo2X);
	DDX_Text(pDX, IDC_EDIT_GEO_PO2_Y, m_dbGeoPo2Y);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_dbResult);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_RESULT2, m_dBearing);
	DDX_Text(pDX, IDC_EDIT_GEO_PO1_X2, startGeoX);
	DDX_Text(pDX, IDC_EDIT_GEO_PO1_Y2, startGeoY);
	DDX_Text(pDX, IDC_EDIT_RESULT3, fDis);
	DDX_Text(pDX, IDC_EDIT_RESULT4, fBear);
	DDX_Text(pDX, IDC_EDIT_GEO_PO2_X2, retGeoX);
	DDX_Text(pDX, IDC_EDIT_GEO_PO2_Y2, retGeoY);
}


BEGIN_MESSAGE_MAP(CGeoCalculateDlg, CDialog)
	//{{AFX_MSG_MAP(CGeoCalculateDlg)
	ON_BN_CLICKED(IDC_BUTTON_CACULATE, OnButtonCaculate)
	//}}AFX_MSG_MAP
 	ON_BN_CLICKED(IDC_BUTTON_GET_POINT, &CGeoCalculateDlg::OnBnClickedButtonGetPoint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeoCalculateDlg message handlers

void CGeoCalculateDlg::OnButtonCaculate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	m_dbResult = pYimaEncCtrl->GetDistBetwTwoPoint(m_dbGeoPo1X * UNI_GEO_COOR_MULTI_FACTOR,
		m_dbGeoPo1Y * UNI_GEO_COOR_MULTI_FACTOR,
		m_dbGeoPo2X * UNI_GEO_COOR_MULTI_FACTOR,
		m_dbGeoPo2Y * UNI_GEO_COOR_MULTI_FACTOR);

	m_dBearing = pYimaEncCtrl->GetBearingBetwTwoPoint(m_dbGeoPo1X * UNI_GEO_COOR_MULTI_FACTOR,
		m_dbGeoPo1Y * UNI_GEO_COOR_MULTI_FACTOR,
		m_dbGeoPo2X * UNI_GEO_COOR_MULTI_FACTOR,
		m_dbGeoPo2Y * UNI_GEO_COOR_MULTI_FACTOR);

	UpdateData(false);
}
 

void CGeoCalculateDlg::OnBnClickedButtonGetPoint()
{
	UpdateData(TRUE);								  
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	

	long retGeoPoX, retGeoPoY;
	pFrame->m_yimaEncCtrl.GetDesPointOfCrsAndDist( startGeoX* UNI_GEO_COOR_MULTI_FACTOR, startGeoY* UNI_GEO_COOR_MULTI_FACTOR, fDis, fBear, &retGeoPoX, &retGeoPoY); 
	retGeoX = (float)retGeoPoX * 10 / UNI_GEO_COOR_MULTI_FACTOR /10;
	retGeoY = (float)retGeoPoY * 10 / UNI_GEO_COOR_MULTI_FACTOR /10;

	UpdateData(FALSE);
}
