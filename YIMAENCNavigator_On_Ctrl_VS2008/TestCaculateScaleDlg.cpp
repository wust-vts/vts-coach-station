// TestCaculateScaleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "TestCaculateScaleDlg.h"
#include "MainFrm.h"
#include "math.h"


// CTestCaculateScaleDlg 对话框

IMPLEMENT_DYNAMIC(CTestCaculateScaleDlg, CDialog)

CTestCaculateScaleDlg::CTestCaculateScaleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestCaculateScaleDlg::IDD, pParent)
	, m_iCurPx(0)
	, m_fCurDis(0)
	, m_iScale(0)
	, m_iCurScale(0)
	, m_iPxDis(0)
	, m_fDis(0)
{

}

CTestCaculateScaleDlg::~CTestCaculateScaleDlg()
{
}

void CTestCaculateScaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT9, m_iCurPx);
	DDX_Text(pDX, IDC_EDIT10, m_fCurDis);
	DDX_Text(pDX, IDC_EDIT11, m_iScale);
	DDX_Text(pDX, IDC_EDIT7, m_iCurScale);
	DDX_Text(pDX, IDC_EDIT4, m_iPxDis);
	DDX_Text(pDX, IDC_EDIT6, m_fDis);
}


BEGIN_MESSAGE_MAP(CTestCaculateScaleDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CTestCaculateScaleDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestCaculateScaleDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestCaculateScaleDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestCaculateScaleDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CTestCaculateScaleDlg 消息处理程序

BOOL CTestCaculateScaleDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	float fScale = pYimaEncCtrl->GetCurrentScale();
	this->m_iCurScale = (int)fScale;
	UpdateData(0);
	return TRUE;
}

//计算量程-->比例尺
void CTestCaculateScaleDlg::OnBnClickedButton1()
{
	UpdateData(1);
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	
	long centerGeoPoX, centerGeoPoY;
	
	float mapViewSizeSrnX = pYimaEncCtrl->GetDrawerScreenHeight();
	float mapViewSizeSrnY = pYimaEncCtrl->GetDrawerScreenWidth();
	pYimaEncCtrl->GetGeoPoFromScrnPo((long)(mapViewSizeSrnX / 2),(long)(mapViewSizeSrnY / 2),&centerGeoPoX, &centerGeoPoY);
	float disPx = this->m_iCurPx;
	float disMeter = this->m_fCurDis * 1852;
	
	/*
	M_POINT mCenterGeoPo;//中心点坐标
	M_POINT mLeftTopGeoPo;//左上顶点

	long lViewHeight = pYimaEncCtrl->GetDrawerScreenHeight();//海图视图的屏幕大小（px）
	long lViewWidth = pYimaEncCtrl->GetDrawerScreenWidth();
	
	long lScrnDis = sqrt(pow(lViewHeight / 2 , 2) + pow(lViewWidth / 2 , 2)); //中心点到左上顶点的屏幕距离(px)
	long lDis = pYimaEncCtrl->GetDistBetwTwoPoint(mCenterGeoPo.x, mCenterGeoPo.y, mLeftTopGeoPo.x, mLeftTopGeoPo.y);//海图中心点到左上顶点的平面距离(海里)
	long disMeter = lDis * 1852;//把海里转换成米
	long lNewScale = pYimaEncCtrl->CaculateScale(mCenterGeoPo.x,mCenterGeoPo.y,lScrnDis,disMeter);//得到新的比例尺

	pYimaEncCtrl->SetCurrentScale(lNewScale);//设置比例尺
	pYimaEncCtrl->CenterMap(mCenterGeoPo.x, mCenterGeoPo.y);//设置中心点
	*/


	
	float fScale = pYimaEncCtrl->CaculateScale(centerGeoPoX,centerGeoPoY,disPx,disMeter);
	this->m_iScale = fScale + 0.5;
	UpdateData(0);
}

//比例尺 --> 计算量程
void CTestCaculateScaleDlg::OnBnClickedButton4()
{
		// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	long firstGeoPoX,firstGeoPoY,secondGeoPoX,secondGeoPoY;
	float mapViewSizeSrnX = pYimaEncCtrl->GetDrawerScreenHeight();
	float mapViewSizeSrnY = pYimaEncCtrl->GetDrawerScreenWidth();
	pYimaEncCtrl->GetGeoPoFromScrnPo(mapViewSizeSrnX, mapViewSizeSrnY, &firstGeoPoX, &firstGeoPoY);//点(0,0)的经纬度坐标
	pYimaEncCtrl->GetGeoPoFromScrnPo(mapViewSizeSrnX + 200, mapViewSizeSrnY + 200, &secondGeoPoX, &secondGeoPoY);//点(200,200)的经纬度坐标

	double allDis = pYimaEncCtrl->GetDistBetwTwoPoint(firstGeoPoX, firstGeoPoY, secondGeoPoX, secondGeoPoY);//两点之间距离(海里)
	
	float pxDis = (200 * 200 +  200 * 200);
	float onePxDis = (float) allDis / sqrt(pxDis);//一个像素的距离（海里）
	this->m_iPxDis = 100;
	this->m_fDis = onePxDis * 100;//100像素距离
	UpdateData(0);
}

//切换量程
void CTestCaculateScaleDlg::OnBnClickedButton3()
{
	float fScale =(float) this->m_iScale;
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	pYimaEncCtrl->SetCurrentScale(fScale);
	pYimaEncCtrl->Invalidate();//刷新海图 
	m_iCurScale = fScale;
	UpdateData(FALSE);
}



void CTestCaculateScaleDlg::OnBnClickedOk()
{
	OnOK();
}
