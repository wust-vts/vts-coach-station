// SetScaleDlg.cpp : implementation file
//

#include "stdafx.h" 
#include "SetScaleDlg.h" 
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetScaleDlg dialog
 
CSetScaleDlg::CSetScaleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetScaleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetScaleDlg)
	m_iScale = 0;
	//}}AFX_DATA_INIT
}


void CSetScaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetScaleDlg)
	DDX_Control(pDX, IDC_SEL_SCALE_COMBOX, m_selScaleCmbx);
	DDX_Text(pDX, IDC_SCALE_EDIT, m_iScale);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetScaleDlg, CDialog)
	//{{AFX_MSG_MAP(CSetScaleDlg)
	ON_CBN_SELCHANGE(IDC_SEL_SCALE_COMBOX, OnSelchangeSelScaleCombox)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CSetScaleDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetScaleDlg message handlers

BOOL CSetScaleDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_presetScales[0] = 1000;
	m_presetScales[1] = 5000;
	m_presetScales[2] = 10000;
	m_presetScales[3] = 50000;
	m_presetScales[4] = 100000;
	m_presetScales[5] = 500000;
	m_presetScales[6] = 1000000;
	m_presetScales[7] = 5000000;
	m_presetScales[8] = 10000000;
 
	for (int preSclaeNum = 0; preSclaeNum < PRESET_SCALE_COUNT; preSclaeNum ++)
	{
		CString strPreScale;
		strPreScale.Format("1 : %d", m_presetScales[preSclaeNum]);
		m_selScaleCmbx.AddString(strPreScale);
	}	

	CString strCurScale;
	strCurScale.Format("1 : %d", m_iScale);
	m_selScaleCmbx.SetWindowText(strCurScale);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetScaleDlg::OnSelchangeSelScaleCombox() 
{
	// TODO: Add your control notification handler code here
	m_iScale = m_presetScales[m_selScaleCmbx.GetCurSel()];
	UpdateData(false);
 
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);

	pFrame->m_yimaEncCtrl.SetCurrentScale(m_iScale);
	pFrame->RedrawView(); 
}

void CSetScaleDlg::OnOK() 
{
	// TODO: Add extra validation here   
	UpdateData(true);

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);

	pFrame->m_yimaEncCtrl.SetCurrentScale(m_iScale);
	pFrame->RedrawView(); 

	CDialog::OnOK();
}

void CSetScaleDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
