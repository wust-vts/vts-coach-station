// S63FileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "S63FileDialog.h"
#include "MainFrm.h"
#include "Afxdlgs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CS63FileDialog dialog


CS63FileDialog::CS63FileDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CS63FileDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CS63FileDialog)
	m_strPermitFilePath = _T("");
	m_strCellFilePath = _T("");
	//}}AFX_DATA_INIT
}


void CS63FileDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CS63FileDialog)
	DDX_Text(pDX, IDC_S63_PERMIT_FILE_PATH_EDIT, m_strPermitFilePath);
	DDX_Text(pDX, IDC_S63_CELL_FILE_PATH_EDIT, m_strCellFilePath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CS63FileDialog, CDialog)
	//{{AFX_MSG_MAP(CS63FileDialog)
	ON_BN_CLICKED(IDC_OPEN_PERMIT_FILE_BUTTON, OnOpenPermitFileButton)
	ON_BN_CLICKED(IDC_OPEN_S63_CELL_FILE_BUTTON, OnOpenS63CellFileButton)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CS63FileDialog::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CS63FileDialog message handlers

void CS63FileDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CS63FileDialog::OnOpenPermitFileButton() 
{
	// TODO: Add your control notification handler code here

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);

	CFileDialog fileDlg(TRUE, _T("permit file"), _T(""),
			OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
			_T("S57 Permit files(*.pmt)|*.pmt|All files(*.*)|*.*|")); 
	if (IDOK == fileDlg.DoModal())
	{  
		m_strPermitFilePath = fileDlg.GetPathName();
		UpdateData(false);
	}
}

void CS63FileDialog::OnOpenS63CellFileButton() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);

	CFileDialog fileDlg(TRUE, _T("Cell file"), _T(""),
			OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
			_T("S57 cell files(*.000)|*.000|S57 Update files(*.*)|*.*|")); 
	if (IDOK == fileDlg.DoModal())
	{ 
		m_strCellFilePath = fileDlg.GetPathName(); 
		UpdateData(false);
	}
}

void CS63FileDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
