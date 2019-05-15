// LayerManDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "LayerManDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLayerManDlg dialog


CLayerManDlg::CLayerManDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLayerManDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLayerManDlg)
	m_bLayerToDrawOrNot = FALSE;
	//}}AFX_DATA_INIT
}


void CLayerManDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLayerManDlg)
	DDX_Control(pDX, IDC_LAYER_LIST, m_layerList);
	DDX_Check(pDX, IDC_SHOW_LAYER_CHECK, m_bLayerToDrawOrNot);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLayerManDlg, CDialog)
	//{{AFX_MSG_MAP(CLayerManDlg)
	ON_BN_CLICKED(IDC_SHOW_LAYER_CHECK, OnShowLayerCheck)
	ON_BN_CLICKED(ID_SHOW_ALL_LAYER_BUTTON, OnShowAllLayerButton)
	ON_BN_CLICKED(ID_HIDE_ALL_LAYER_BUTTON, OnHideAllLayerButton)
	ON_LBN_SELCHANGE(IDC_LAYER_LIST, OnSelchangeLayerList)
	ON_LBN_DBLCLK(IDC_LAYER_LIST, OnDblclkLayerList)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CLayerManDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLayerManDlg message handlers

void CLayerManDlg::OnShowLayerCheck() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
 
	UpdateData(true);
	
	//CString strLayerName = "LIGHTS";//从S57ObjectClasses文件中查看“灯标”的Token值为“LIGHTS”，即文件中的Acronym值
	//LPCTSTR strLayerToken = (LPCTSTR)strLayerName;
	//long layerPos = pYimaEncCtrl->GetLayerPosByToken(-1,strLayerToken);
	//pYimaEncCtrl->SetLayerDrawOrNot(-1, layerPos, false);

	pYimaEncCtrl->SetLayerDrawOrNot(-1, m_layerList.GetCurSel(), 
		m_bLayerToDrawOrNot);

	pFrame->RedrawView();
}

void CLayerManDlg::OnShowAllLayerButton() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
 
	pYimaEncCtrl->SetAllLayerDrawOrNot(-1, true);

	m_bLayerToDrawOrNot = true;

	UpdateData(false); 

	pFrame->RedrawView();
}

void CLayerManDlg::OnHideAllLayerButton() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
 
	pYimaEncCtrl->SetAllLayerDrawOrNot(-1, false);

	m_bLayerToDrawOrNot = false;

	UpdateData(false); 

	pFrame->RedrawView();
}

BOOL CLayerManDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	int layerCount = pYimaEncCtrl->GetLayerCount(-1);
	for (int layerNum = 0; layerNum < layerCount; layerNum ++)
	{
		BSTR bstrLayerName = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
		pYimaEncCtrl->GetLayerInfo(-1, layerNum, &bstrLayerName, 
			NULL, NULL);

		CString strLayerName = bstrLayerName;
		m_layerList.AddString(strLayerName);

		SysFreeString(bstrLayerName);
	}

	m_layerList.SetCurSel(0);
	m_bLayerToDrawOrNot = pYimaEncCtrl->GetLayerDrawOrNot(-1, 0);

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLayerManDlg::OnSelchangeLayerList() 
{
	// TODO: Add your control notification handler code here 
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	m_bLayerToDrawOrNot = 
		pYimaEncCtrl->GetLayerDrawOrNot(-1, m_layerList.GetCurSel());

	UpdateData(false); 
}

void CLayerManDlg::OnDblclkLayerList() 
{
	// TODO: Add your control notification handler code here
	
}

void CLayerManDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
