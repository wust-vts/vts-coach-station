// SetGridLinesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "SetGridLinesDlg.h"
#include "MainFrm.h"
#include "YimaEncViewerView.h"


// CSetGridLinesDlg dialog

IMPLEMENT_DYNAMIC(CSetGridLinesDlg, CDialog)

CSetGridLinesDlg::CSetGridLinesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetGridLinesDlg::IDD, pParent)
	, m_nGridDensityCount(0)
	, m_nGridTextFontSize(0)
{
	m_pEncCtrl = NULL;
}

CSetGridLinesDlg::~CSetGridLinesDlg()
{
}

void CSetGridLinesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SAFE_CONT, m_nGridDensityCount);
	DDX_Text(pDX, IDC_SAFE_CONT2, m_nGridTextFontSize);
}


BEGIN_MESSAGE_MAP(CSetGridLinesDlg, CDialog)
	ON_BN_CLICKED(IDC_GRID_LINE_COLOR_BTN, &CSetGridLinesDlg::OnBnClickedGridLineColorBtn) 
	ON_BN_CLICKED(IDAPPLY, &CSetGridLinesDlg::OnBnClickedApply)
	ON_BN_CLICKED(IDC_LON_TEXT_COLOR_BTN, &CSetGridLinesDlg::OnBnClickedLonTextColorBtn)
	ON_BN_CLICKED(IDC_LAT_TEXT_COLOR_BTN, &CSetGridLinesDlg::OnBnClickedLatTextColorBtn)
	ON_BN_CLICKED(IDOK, &CSetGridLinesDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetGridLinesDlg message handlers

void CSetGridLinesDlg::OnBnClickedGridLineColorBtn()
{
	// TODO: Add your control notification handler code here
	CColorDialog colorDlg;
	colorDlg.DoModal();  
	m_gridLineColor = colorDlg.GetColor();
	m_pEncCtrl->SetGridLines(m_nGridDensityCount, m_gridLineColor, m_latTextColor, m_lonTextColor, m_nGridTextFontSize); 
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEncViewerView* pView = (CYimaEncViewerView*)pFrame->GetActiveView(); 
	pView->Invalidate();
}

void CSetGridLinesDlg::OnBnClickedApply()
{  
	UpdateData(true);  
	m_pEncCtrl->SetGridLines(m_nGridDensityCount, m_gridLineColor, m_latTextColor, m_lonTextColor, m_nGridTextFontSize); 

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEncViewerView* pView = (CYimaEncViewerView*)pFrame->GetActiveView(); 
	pView->Invalidate();
}

void CSetGridLinesDlg::OnBnClickedLonTextColorBtn()
{
	// TODO: Add your control notification handler code here
	CColorDialog colorDlg;
	colorDlg.DoModal(); 
	m_lonTextColor = colorDlg.GetColor();  
	m_pEncCtrl->SetGridLines(m_nGridDensityCount, m_gridLineColor, m_latTextColor, m_lonTextColor, m_nGridTextFontSize);

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEncViewerView* pView = (CYimaEncViewerView*)pFrame->GetActiveView(); 
	pView->Invalidate();
}

void CSetGridLinesDlg::OnBnClickedLatTextColorBtn()
{
	// TODO: Add your control notification handler code here
	CColorDialog colorDlg;
	colorDlg.DoModal(); 
	m_latTextColor = colorDlg.GetColor();  
	m_pEncCtrl->SetGridLines(m_nGridDensityCount, m_gridLineColor, m_latTextColor, m_lonTextColor, m_nGridTextFontSize);

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEncViewerView* pView = (CYimaEncViewerView*)pFrame->GetActiveView(); 
	pView->Invalidate();
}

void CSetGridLinesDlg::OnBnClickedOk()
{ 
	m_pEncCtrl->SetGridLines(m_nGridDensityCount, m_gridLineColor, m_latTextColor, m_lonTextColor, m_nGridTextFontSize); 
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	pFrame->RedrawView();
	OnOK();
}

BOOL CSetGridLinesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_nGridDensityCount = m_pEncCtrl->GetGridLineParams(&m_gridLineColor, &m_lonTextColor, &m_latTextColor, &m_nGridTextFontSize);
	if (m_nGridTextFontSize == 0)
	{
		m_nGridTextFontSize = abs(MulDiv(10, GetDeviceCaps(GetDC()->m_hDC, LOGPIXELSY), 72));
	}
	UpdateData(FALSE);
	return TRUE; 
}
