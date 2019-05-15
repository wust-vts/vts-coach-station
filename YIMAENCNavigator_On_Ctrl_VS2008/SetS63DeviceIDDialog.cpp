// SetS63DeviceIDDialog.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "SetS63DeviceIDDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetS63DeviceIDDialog dialog


CSetS63DeviceIDDialog::CSetS63DeviceIDDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSetS63DeviceIDDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetS63DeviceIDDialog)
	m_nDeviceID = 0;
	//}}AFX_DATA_INIT
}


void CSetS63DeviceIDDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetS63DeviceIDDialog)
	DDX_Text(pDX, IDC_DEVIC_ID_EDIT, m_nDeviceID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetS63DeviceIDDialog, CDialog)
	//{{AFX_MSG_MAP(CSetS63DeviceIDDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetS63DeviceIDDialog message handlers
