// ChangeDepthLineValDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "ChangeDepthLineValDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeDepthLineValDlg dialog


CChangeDepthLineValDlg::CChangeDepthLineValDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeDepthLineValDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeDepthLineValDlg)
	m_fDpthChgVal = 0.0f;
	//}}AFX_DATA_INIT
}


void CChangeDepthLineValDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeDepthLineValDlg)
	DDX_Text(pDX, IDC_DEPTH_CHG_VAL, m_fDpthChgVal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeDepthLineValDlg, CDialog)
	//{{AFX_MSG_MAP(CChangeDepthLineValDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeDepthLineValDlg message handlers
