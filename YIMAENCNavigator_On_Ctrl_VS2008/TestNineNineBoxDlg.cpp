// TestNineNineBoxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "TestNineNineBoxDlg.h"
#include "MainFrm.h"


// CTestNineNineBoxDlg 对话框

IMPLEMENT_DYNAMIC(CTestNineNineBoxDlg, CDialog)

CTestNineNineBoxDlg::CTestNineNineBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestNineNineBoxDlg::IDD, pParent)
	, m_fCenterLon(0)
	, m_fCenterLat(0)
	, m_bShowOrNot(FALSE)
	, m_fCurLon(0)
	, m_fCurLat(0)
	, m_strCurNumber(_T(""))
	, m_bShowText(FALSE)
{

}

CTestNineNineBoxDlg::~CTestNineNineBoxDlg()
{ 
}

void CTestNineNineBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_fCenterLon);
	DDX_Text(pDX, IDC_EDIT4, m_fCenterLat);
	DDX_Check(pDX, IDC_CHECK_SHOW_OR_NOT, m_bShowOrNot);
	DDX_Text(pDX, IDC_EDIT5, m_fCurLon);
	DDX_Text(pDX, IDC_EDIT6, m_fCurLat);
	DDX_Text(pDX, IDC_EDIT7, m_strCurNumber);
	DDX_Check(pDX, IDC_CHK_SHOW_TEXT, m_bShowText);
}


BEGIN_MESSAGE_MAP(CTestNineNineBoxDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CTestNineNineBoxDlg::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CTestNineNineBoxDlg::OnBnClickedButtonGet)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_CHECK_SHOW_OR_NOT, &CTestNineNineBoxDlg::OnBnClickedCheckShowOrNot)
	ON_BN_CLICKED(IDC_CHK_SHOW_TEXT, &CTestNineNineBoxDlg::OnBnClickedChkShowText)
END_MESSAGE_MAP()


// CTestNineNineBoxDlg 消息处理程序

BOOL CTestNineNineBoxDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	
	long geoPoX,geoPoY;
	BOOL bShowOrNot;
	pYimaEncCtrl->GetNineNineBoxCenterGeoPo(&geoPoX,&geoPoY,&bShowOrNot); 
	m_bShowText = pYimaEncCtrl->GetIfShowNineNineBoxText();
	this->m_fCenterLon = geoPoX / UNI_GEO_COOR_MULTI_FACTOR;
	this->m_fCenterLat = geoPoY / UNI_GEO_COOR_MULTI_FACTOR;
	this->m_bShowOrNot = bShowOrNot;
	UpdateData(0);
	return TRUE;
}

//设置
void CTestNineNineBoxDlg::OnBnClickedButtonSet()
{
	if(UpdateData(1))
	{
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
		CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
		//pYimaEncCtrl->SetShowNineNineBoxOrNot(this->m_bShowOrNot);//设置是否显示
		long geoPoX = this->m_fCenterLon * UNI_GEO_COOR_MULTI_FACTOR;
		long geoPoY = this->m_fCenterLat * UNI_GEO_COOR_MULTI_FACTOR;
		pYimaEncCtrl->SetNineNineBoxCenterGeoPo(geoPoX,geoPoY);//设置中心点
		pYimaEncCtrl->SetDrawNineNineBoxStyle(RGB(255,0,0),RGB(0,100,255),RGB(255,255,100),RGB(150,0,0));//设置九九方格样式
		pYimaEncCtrl->ForcelyRefreshMap();
		pFrame->Invalidate();//重绘海图
	}
}

//计算
void CTestNineNineBoxDlg::OnBnClickedButtonGet()
{
	if(UpdateData(1))
	{
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
		CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

		long geoPoX = this->m_fCurLon * UNI_GEO_COOR_MULTI_FACTOR;
		long geoPoY = this->m_fCurLat * UNI_GEO_COOR_MULTI_FACTOR;
		BSTR bstrNumber = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
		pYimaEncCtrl->GetNineNineNumberByGeoPo(geoPoX,geoPoY,&bstrNumber);
		this->m_strCurNumber = bstrNumber;
		::SysFreeString(bstrNumber);
		UpdateData(0);
	}
}

void CTestNineNineBoxDlg::OnBnClickedCheckShowOrNot()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl; 
	pYimaEncCtrl->SetShowNineNineBoxOrNot(this->m_bShowOrNot);//设置是否显示 
	pYimaEncCtrl->ForcelyRefreshMap(); 
	pFrame->RedrawView();//重绘海图
}

void CTestNineNineBoxDlg::OnBnClickedChkShowText()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl; 
	pYimaEncCtrl->SetIfShowNineNineBoxText(this->m_bShowText); 
	pYimaEncCtrl->ForcelyRefreshMap(); 
	pFrame->RedrawView();//重绘海图

}
