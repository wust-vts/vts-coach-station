// SetSafeContourDlg.cpp : implementation file
//

#include "stdafx.h" 
#include "SetSafeContourDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetSafeContourDlg dialog


CSetSafeContourDlg::CSetSafeContourDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetSafeContourDlg::IDD, pParent)
	, m_fShallowDepth(0)
	, m_fDeepDepth(0)
{
	//{{AFX_DATA_INIT(CSetSafeContourDlg)
	m_fSafeCont = 0;
	//}}AFX_DATA_INIT
}


void CSetSafeContourDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetSafeContourDlg)
	DDX_Text(pDX, IDC_SAFE_CONT, m_fSafeCont);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_SHALLOW_CONTOUR, m_fShallowDepth);
	DDX_Text(pDX, IDC_DEEP_CONTOUR, m_fDeepDepth);
}


BEGIN_MESSAGE_MAP(CSetSafeContourDlg, CDialog)
	//{{AFX_MSG_MAP(CSetSafeContourDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CSetSafeContourDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetSafeContourDlg message handlers

BOOL CSetSafeContourDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, m_bTwoOrFourDepthShades ? IDC_RADIO1 : IDC_RADIO2);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetSafeContourDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_bTwoOrFourDepthShades = (GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2) == IDC_RADIO1);

	OnOK();
}
