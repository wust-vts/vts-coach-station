// EmulateParamSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "EmulateParamSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmulateParamSetDlg dialog


CEmulateParamSetDlg::CEmulateParamSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEmulateParamSetDlg::IDD, pParent)
	, m_iMaxStoreTrackPoCount(0)
	, m_iMaxShowTrackPoCount(0)
	, m_iMaxStoreTrackTime(0)
{
	//{{AFX_DATA_INIT(CEmulateParamSetDlg)
	m_fSpeed = 0.0f;
	m_iClockInterval = 0;
	m_bShowSpeedTimeMark = FALSE;
	m_bShowHeadingLine = FALSE;
	m_bShowSpeedVector = FALSE;
	//}}AFX_DATA_INIT
}


void CEmulateParamSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmulateParamSetDlg)
	DDX_Text(pDX, IDC_SPEED, m_fSpeed);
	DDX_Text(pDX, IDC_CLOCK_INTERVAL, m_iClockInterval);
	DDX_Check(pDX, IDC_SPEED_TIME_MARK, m_bShowSpeedTimeMark);
	DDX_Check(pDX, IDC_SHOW_HEADLINE, m_bShowHeadingLine);
	DDX_Check(pDX, IDC_SHOW_SPEED_VECTOR, m_bShowSpeedVector);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_MAX_STORE_COUNT, m_iMaxStoreTrackPoCount);
	DDX_Text(pDX, IDC_EDIT_MAX_SHOW_COUNT, m_iMaxShowTrackPoCount);
	DDX_Text(pDX, IDC_EDIT_MAX_STORE_TIME, m_iMaxStoreTrackTime);
}


BEGIN_MESSAGE_MAP(CEmulateParamSetDlg, CDialog)
	//{{AFX_MSG_MAP(CEmulateParamSetDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CEmulateParamSetDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmulateParamSetDlg message handlers

void CEmulateParamSetDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
