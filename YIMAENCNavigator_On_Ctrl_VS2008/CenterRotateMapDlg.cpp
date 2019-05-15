// CenterRotateMapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "CenterRotateMapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCenterRotateMapDlg dialog


CCenterRotateMapDlg::CCenterRotateMapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCenterRotateMapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCenterRotateMapDlg)
	m_fCntrGeoPoX = 0.0f;
	m_fCntrGeoPoY = 0.0f;
	m_fRotateDeg = 0.0f;
	//}}AFX_DATA_INIT
}


void CCenterRotateMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCenterRotateMapDlg)
	DDX_Text(pDX, IDC_CENTER_PO_X, m_fCntrGeoPoX);
	DDX_Text(pDX, IDC_CENTER_PO_Y, m_fCntrGeoPoY);
	DDX_Text(pDX, IDC_ROTATE_DEG, m_fRotateDeg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCenterRotateMapDlg, CDialog)
	//{{AFX_MSG_MAP(CCenterRotateMapDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CCenterRotateMapDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCenterRotateMapDlg message handlers

void CCenterRotateMapDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
