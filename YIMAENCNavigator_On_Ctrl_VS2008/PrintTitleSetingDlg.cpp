// PrintTitleSetingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "PrintTitleSetingDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintTitleSetingDlg dialog


CPrintTitleSetingDlg::CPrintTitleSetingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintTitleSetingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrintTitleSetingDlg)
	m_printTitleEdit = _T("");
	m_remarkEdit = _T("");
	//}}AFX_DATA_INIT
}


void CPrintTitleSetingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintTitleSetingDlg)
	DDX_Text(pDX, IDC_PRINT_TITLE_EDIT, m_printTitleEdit);
	DDX_Text(pDX, IDC_REMARK_EDIT, m_remarkEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrintTitleSetingDlg, CDialog)
	//{{AFX_MSG_MAP(CPrintTitleSetingDlg)
	ON_BN_CLICKED(IDC_TITLE_FONT_BTN, OnTitleFontBtn)
	ON_BN_CLICKED(IDC_REMARK_FONT_BTN, OnRemarkFontBtn)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CPrintTitleSetingDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintTitleSetingDlg message handlers

BOOL CPrintTitleSetingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
   CMainFrame* pFrame =(CMainFrame*)(AfxGetApp()->m_pMainWnd);
    m_printTitleEdit=pFrame->mapTitle;
	m_remarkEdit=pFrame->remarks;
	
	UpdateData(false);
	// TODO: Add extra initialization here
	switch(pFrame->nmapTitleLeftOrMiddleOrRight)
	{
	case 0:
		CheckRadioButton(IDC_TITLE_ALIGN_LEFT_RADIO,IDC_TITLE_ALIGN_RIGHT_RADIO,IDC_TITLE_ALIGN_LEFT_RADIO);
		break;
	case 1:
        CheckRadioButton(IDC_TITLE_ALIGN_LEFT_RADIO,IDC_TITLE_ALIGN_RIGHT_RADIO,IDC_TITLE_ALIGN_MIDDLE_RADIO);
		break;
	case 2:
		CheckRadioButton(IDC_TITLE_ALIGN_LEFT_RADIO,IDC_TITLE_ALIGN_RIGHT_RADIO,IDC_TITLE_ALIGN_RIGHT_RADIO);
		break;
	default:
		CheckRadioButton(IDC_TITLE_ALIGN_LEFT_RADIO,IDC_TITLE_ALIGN_RIGHT_RADIO,IDC_TITLE_ALIGN_MIDDLE_RADIO);
		break;

	}
	
	switch( pFrame->nremarksLeftOrMiddleOrRight)
	{
	case 0:
		CheckRadioButton(IDC_REMARK_LEFT_RADIO,IDC_REMARK_RIGHT_RADIO,IDC_REMARK_LEFT_RADIO);
		break;
	case 1:
		CheckRadioButton(IDC_REMARK_LEFT_RADIO,IDC_REMARK_RIGHT_RADIO,IDC_REMARK_MIDDLE_RADIO);
		break;
	case 2:
		CheckRadioButton(IDC_REMARK_LEFT_RADIO,IDC_REMARK_RIGHT_RADIO,IDC_REMARK_RIGHT_RADIO);
		break;
	default:
		CheckRadioButton(IDC_REMARK_LEFT_RADIO,IDC_REMARK_RIGHT_RADIO,IDC_REMARK_MIDDLE_RADIO);
		break;
	}
	
	switch(pFrame->nscaleLeftOrMiddleOrRight)
	{
	case 0:
		CheckRadioButton(IDC_SCALE_LEFT_RADIO,IDC_SCALE_RIGHT_RADIO,IDC_SCALE_LEFT_RADIO);
		break;
	case 1:
		CheckRadioButton(IDC_SCALE_LEFT_RADIO,IDC_SCALE_RIGHT_RADIO,IDC_SCALE_MIDDLE_RADIO);
		break;
	case 2:
		CheckRadioButton(IDC_SCALE_LEFT_RADIO,IDC_SCALE_RIGHT_RADIO,IDC_SCALE_RIGHT_RADIO);
		break;
	default:
		CheckRadioButton(IDC_SCALE_LEFT_RADIO,IDC_SCALE_RIGHT_RADIO,IDC_SCALE_MIDDLE_RADIO);
		break;
	}
	

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrintTitleSetingDlg::OnOK() 
{
	// TODO: Add extra validation her
		UpdateData(true);
		CMainFrame* pFrame =(CMainFrame*)(AfxGetApp()->m_pMainWnd);
		pFrame->mapTitle=m_printTitleEdit;
		pFrame->remarks=m_remarkEdit;
		int nID;
		nID = GetCheckedRadioButton( IDC_TITLE_ALIGN_LEFT_RADIO, IDC_TITLE_ALIGN_RIGHT_RADIO );
		if(nID==IDC_TITLE_ALIGN_LEFT_RADIO)    
			pFrame->nmapTitleLeftOrMiddleOrRight=0;
		else if(nID==IDC_TITLE_ALIGN_MIDDLE_RADIO)   
			pFrame->nmapTitleLeftOrMiddleOrRight=1;
		else 
			pFrame->nmapTitleLeftOrMiddleOrRight=2;  
		nID = GetCheckedRadioButton(IDC_REMARK_LEFT_RADIO,IDC_REMARK_RIGHT_RADIO );
		if(nID==IDC_REMARK_LEFT_RADIO)  
			pFrame->nremarksLeftOrMiddleOrRight=0;
		else if(nID==IDC_REMARK_MIDDLE_RADIO)  
			pFrame->nremarksLeftOrMiddleOrRight=1;
		else 
			pFrame->nremarksLeftOrMiddleOrRight=2;
		nID=GetCheckedRadioButton(IDC_SCALE_LEFT_RADIO,IDC_SCALE_RIGHT_RADIO);
		if(nID==IDC_SCALE_LEFT_RADIO)   
			pFrame->nscaleLeftOrMiddleOrRight=0;
		else if(nID==IDC_SCALE_MIDDLE_RADIO)  
			pFrame->nscaleLeftOrMiddleOrRight=1;
		else 
			pFrame->nscaleLeftOrMiddleOrRight=2;
		CDialog::OnOK();
}

void CPrintTitleSetingDlg::OnTitleFontBtn() 
{
	// TODO: Add your control notification handler code here  

	CMainFrame* pFrame =(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CFontDialog fDlg; 
	if(fDlg.DoModal()==IDOK)   
	{   
		fDlg.GetCurrentFont(&pFrame->titleFont);		
	} 
}

void CPrintTitleSetingDlg::OnRemarkFontBtn() 
{
	// TODO: Add your control notification handler code here
	
	CMainFrame* pFrame =(CMainFrame*)(AfxGetApp()->m_pMainWnd);
    CFontDialog  fDlg; 
    if (fDlg.DoModal() == IDOK)   
	{   
        fDlg.GetCurrentFont(&pFrame->remarkFont);
	}
} 
	

void CPrintTitleSetingDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
