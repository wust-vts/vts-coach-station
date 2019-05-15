// GetAreaOfGeoRegionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "GetAreaOfGeoRegionDlg.h"
#include "MainFrm.h" 


// CGetAreaOfGeoRegionDlg 对话框

IMPLEMENT_DYNAMIC(CGetAreaOfGeoRegionDlg, CDialog)

CGetAreaOfGeoRegionDlg::CGetAreaOfGeoRegionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetAreaOfGeoRegionDlg::IDD, pParent)
	, m_lon1(0)
	, m_lon2(0)
	, m_lon3(0)
	, m_lon4(0)
	, m_lat1(0)
	, m_lat2(0)
	, m_lat3(0)
	, m_lat4(0)
	, m_AreaValue(0)
{	
	m_lon1 = 120.121;
	m_lat1 = 30.34;

	m_lon2 = 124.1689;
	m_lat2 = 29.125678;

	m_lon3 = 125.789;
	m_lat3 = 33.5674;

	m_lon4 = 121.121;
	m_lat4 = 32.3554;

}

CGetAreaOfGeoRegionDlg::~CGetAreaOfGeoRegionDlg()
{
}

void CGetAreaOfGeoRegionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_lon1);
	DDX_Text(pDX, IDC_EDIT3, m_lon2);
	DDX_Text(pDX, IDC_EDIT5, m_lon3);
	DDX_Text(pDX, IDC_EDIT7, m_lon4);
	DDX_Text(pDX, IDC_EDIT2, m_lat1);
	DDX_Text(pDX, IDC_EDIT4, m_lat2);
	DDX_Text(pDX, IDC_EDIT6, m_lat3);
	DDX_Text(pDX, IDC_EDIT8, m_lat4);
	DDX_Text(pDX, IDC_EDIT9, m_AreaValue);
	//UpdateData(false);
}


BEGIN_MESSAGE_MAP(CGetAreaOfGeoRegionDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON3, &CGetAreaOfGeoRegionDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CGetAreaOfGeoRegionDlg 消息处理程序

//计算多边形面积
void CGetAreaOfGeoRegionDlg::OnBnClickedButton3()
{
	UpdateData(true);
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	//计算多边形面积(这里演示是四个顶点的多边形)

	BSTR strLinePoints = ::SysAllocStringLen(NULL, 
				sizeof(M_POINT) * 4);
			
	M_POINT rgnPoints[4];
	rgnPoints[0] = M_POINT((int)(m_lon1 * UNI_GEO_COOR_MULTI_FACTOR), (int)(m_lat1 * UNI_GEO_COOR_MULTI_FACTOR));
	rgnPoints[1] = M_POINT((int)(m_lon2 * UNI_GEO_COOR_MULTI_FACTOR), (int)(m_lat2 * UNI_GEO_COOR_MULTI_FACTOR));
	rgnPoints[2] = M_POINT((int)(m_lon3 * UNI_GEO_COOR_MULTI_FACTOR), (int)(m_lat3 * UNI_GEO_COOR_MULTI_FACTOR));
	rgnPoints[3] = M_POINT((int)(m_lon4 * UNI_GEO_COOR_MULTI_FACTOR), (int)(m_lat4 * UNI_GEO_COOR_MULTI_FACTOR));

	float areaValue = pYimaEncCtrl->GetAreaOfGeoRegion(4,&strLinePoints);//计算多边形面积
	memcpy(strLinePoints, rgnPoints, sizeof(M_POINT) * 4);

	m_AreaValue = areaValue / 1000 / 1000;//平方米转换平方公里
	SysFreeString(strLinePoints);
	UpdateData(false);
}
