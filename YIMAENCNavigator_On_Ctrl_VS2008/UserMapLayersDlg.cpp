// UserMapLayersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "UserMapLayersDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserMapLayersDlg dialog


CUserMapLayersDlg::CUserMapLayersDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserMapLayersDlg::IDD, pParent)
	, m_strCurLayerType(_T(""))
{
	//{{AFX_DATA_INIT(CUserMapLayersDlg)
	m_curSelLayerName = _T(""); 
	m_bLayerShowOrNot = FALSE;
	//}}AFX_DATA_INIT

	m_iSelLayerNum = 0;
}


void CUserMapLayersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX); 
	DDX_Control(pDX, IDC_USER_MAP_LAYER_LIST, m_layerListCtrl);
	DDX_Text(pDX, IDC_EDIT_LAYER_NAME, m_curSelLayerName); 
	DDX_Check(pDX, IDC_SHOW_CHECK, m_bLayerShowOrNot); 
	DDX_Control(pDX, IDC_COMBO1, m_GeoTypeCombox);
	DDX_Text(pDX, IDC_EDIT3, m_strCurLayerType);
}


BEGIN_MESSAGE_MAP(CUserMapLayersDlg, CDialog)
	//{{AFX_MSG_MAP(CUserMapLayersDlg)
//	ON_LBN_SELCHANGE(IDC_USER_MAP_LAYER_LIST, OnSelchangeUserMapLayerList)
	ON_LBN_DBLCLK(IDC_USER_MAP_LAYER_LIST, OnDblclkUserMapLayerList)
	ON_BN_CLICKED(IDC_SHOW_CHECK, OnShowCheck)
	ON_BN_CLICKED(IDC_NEW_LAYER_BUTTON, OnNewLayerButton)
	ON_BN_CLICKED(IDC_SAVE_NAME_BUTTON, OnSaveNameButton)
	ON_BN_CLICKED(IDC_DEL_LAYER_BUTTON, OnDelLayerButton) 
	ON_BN_CLICKED(IDCANCEL, &CUserMapLayersDlg::OnBnClickedCancel) 
ON_LBN_SELCHANGE(IDC_USER_MAP_LAYER_LIST, &CUserMapLayersDlg::UpdateDialogWithLayerSelected)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserMapLayersDlg message handlers

//void CUserMapLayersDlg::OnSelchangeUserMapLayerList() 
//{
//	// TODO: Add your control notification handler code here 
//    UpdateDialogWithLayerSelected();
//}

void CUserMapLayersDlg::OnDblclkUserMapLayerList() 
{
	// TODO: Add your control notification handler code here
	UpdateDialogWithLayerSelected();
	CDialog::OnOK();
}

CString CUserMapLayersDlg::GetGeoTypeString(LAYER_GEO_TYPE lyrGeoType) 
{
	if (lyrGeoType == ALL_POINT)
	{
		return "点";
	}
	else if (lyrGeoType == ALL_LINE)
	{
		return "线";
	}
	else if (lyrGeoType == ALL_FACE)
	{
		return "面";
	}
	else if (lyrGeoType == MULTIPLE_GEO_TYPE)
	{
		return "多类型";
	}
}

LAYER_GEO_TYPE CUserMapLayersDlg::GetLayerGeoType(int comBoxIndex) 
{
	switch (comBoxIndex)
	{
		case 0: return ALL_POINT;
		case 1: return ALL_LINE;
		case 2: return ALL_FACE;
		case 3: return MULTIPLE_GEO_TYPE;
	} 
}

void CUserMapLayersDlg::UpdateDialogWithLayerSelected()
{ 
    m_iSelLayerNum = m_layerListCtrl.GetCurSel(); 
	
	if (m_iSelLayerNum == -1)
	{
		m_curSelLayerName = "编辑图层尚未选定!"; 
	}
	else
	{
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
		CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl; 
		
		BSTR bstrLayerName = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
		
		pYimaEncCtrl->tmGetLayerName(m_iSelLayerNum, &bstrLayerName);
		LAYER_GEO_TYPE layerGeoType = (LAYER_GEO_TYPE)pYimaEncCtrl->tmGetLayerGeoType(m_iSelLayerNum);
		
		m_curSelLayerName = bstrLayerName;
		m_strCurLayerType = GetGeoTypeString(layerGeoType); 
		pYimaEncCtrl->tmGetLayerDrawOrNot(m_iSelLayerNum, &m_bLayerShowOrNot);
		SysFreeString(bstrLayerName);
	}

	UpdateData(false);
}

void CUserMapLayersDlg::UpdateListCtrl() 
{
	int listItemCount = m_layerListCtrl.GetCount();
	for (int itemNum = listItemCount - 1; itemNum > -1; itemNum --)
	{
		m_layerListCtrl.DeleteString(itemNum);
	}

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl; 
 
	BSTR bstrLayerName = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);

	int layerCount = pYimaEncCtrl->tmGetLayerCount();
	for (int layerNum = 0; layerNum < layerCount; layerNum ++)
	{
		pYimaEncCtrl->tmGetLayerName(layerNum, &bstrLayerName);
		CString strLayerName = bstrLayerName;
		m_layerListCtrl.AddString(strLayerName);
	} 

	SysFreeString(bstrLayerName); 
}
 
BOOL CUserMapLayersDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_GeoTypeCombox.SetCurSel(0);
	UpdateListCtrl();

	m_layerListCtrl.SetCurSel(0);

	UpdateDialogWithLayerSelected(); 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUserMapLayersDlg::OnShowCheck() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	
	m_iSelLayerNum = m_layerListCtrl.GetCurSel(); 
	
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl; 
	
	pYimaEncCtrl->tmSetLayerDrawOrNot(m_iSelLayerNum, m_bLayerShowOrNot);
	pFrame->RedrawView();
}

void CUserMapLayersDlg::OnNewLayerButton() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	
	m_iSelLayerNum = m_layerListCtrl.GetCurSel(); 
	
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl; 
	LAYER_GEO_TYPE  selGeoType = GetLayerGeoType(m_GeoTypeCombox.GetCurSel());
	pYimaEncCtrl->tmAppendLayer(selGeoType);
	CString layerName;
	layerName.Format(_T("LAYER %d"), pYimaEncCtrl->tmGetLayerCount());
	int layerPos = pYimaEncCtrl->tmGetLayerCount() - 1;
	pYimaEncCtrl->tmSetLayerName(layerPos, layerName);
	pYimaEncCtrl->tmAddLayerAttribute(layerPos, 4, "ShowText");
	if (selGeoType == ALL_POINT)
	{
		pYimaEncCtrl->tmSetPointLayerStyleReferLib(layerPos, "", 2, false, 0, 1, 0, true,
			true, "@0", "宋体", 12, RGB(255,0,0), true, false, 0, 0, 18, -5); 
	}
	else if (selGeoType == ALL_LINE)
	{
		pYimaEncCtrl->tmSetLineLayerStyleReferLib("", layerPos, 1, 0, 0, 1, true,
			RGB(0,0,255), 2, true, true, "@0", "宋体", 12, RGB(255,0,0), true, false, true, 0, 0);
	}
	else if (selGeoType == ALL_FACE)
	{
		pYimaEncCtrl->tmSetFaceLayerStyleReferLib("", layerPos, true, 1, true, RGB(125,125,125),
			80, false, 0, true, 1, 0, 0, 1, true, RGB(0,0,255),
			2, true, true, "@0", "宋体", 12, RGB(255,0,0), true, false, true, 0, 0);
	}

	UpdateListCtrl();

	m_layerListCtrl.SetCurSel(pYimaEncCtrl->tmGetLayerCount() - 1);

	UpdateDialogWithLayerSelected();
}

void CUserMapLayersDlg::OnSaveNameButton() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	
	m_iSelLayerNum = m_layerListCtrl.GetCurSel(); 
	
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl; 
	
	pYimaEncCtrl->tmSetLayerName(m_iSelLayerNum, m_curSelLayerName);

	UpdateListCtrl();
	m_layerListCtrl.SetCurSel(m_iSelLayerNum);
}

void CUserMapLayersDlg::OnDelLayerButton() 
{
	// TODO: Add your control notification handler code here

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl; 

	m_iSelLayerNum = m_layerListCtrl.GetCurSel(); 
	pYimaEncCtrl->tmDeleteLayer(m_iSelLayerNum);

	UpdateListCtrl();

	if (m_iSelLayerNum == pYimaEncCtrl->tmGetLayerCount())
	{
		m_iSelLayerNum --;
	}

	m_layerListCtrl.SetCurSel(m_iSelLayerNum);
	UpdateDialogWithLayerSelected();
	pYimaEncCtrl->ForcelyRefreshMap();
	pFrame->RedrawView();
}

void CUserMapLayersDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
 