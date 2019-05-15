// UserDefineMapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "UserDefineMapDlg.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserDefineMapDlg dialog


CUserDefineMapDlg::CUserDefineMapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserDefineMapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserDefineMapDlg)
	//}}AFX_DATA_INIT
  
    lastcomboxcur=0;

}


void CUserDefineMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserDefineMapDlg)
	DDX_Control(pDX, IDC_USERLAYER_OBJECT_LIST, m_UserLayerObjectList);
	DDX_Control(pDX, IDC_USERLAYR_SELECT_COMBOX, m_UserLayerSelectComBox);
	DDX_Control(pDX, IDC_LAYER_OBJECT_LIST, m_LayerObjectList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserDefineMapDlg, CDialog)
	//{{AFX_MSG_MAP(CUserDefineMapDlg)
	ON_BN_CLICKED(IDC_ADDTOLAYER_BTN, OnAddtolayerBtn)
	ON_BN_CLICKED(IDC_DELETEROMLAYER_BTN, OnDeleteromlayerBtn)
	ON_CBN_SELCHANGE(IDC_USERLAYR_SELECT_COMBOX, OnSelchangeUserlayrSelectCombox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserDefineMapDlg message handlers

BOOL CUserDefineMapDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here	
	CMainFrame* pFrame =(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	BSTR bstrLayerName;
	CString strLayerName;

	int layerCount = pYimaEncCtrl->GetLayerCount(-1);
	for (int layerNum = 0; layerNum < layerCount; layerNum ++)
	{
	    bstrLayerName = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
		pYimaEncCtrl->GetLayerInfo(-1, layerNum, &bstrLayerName, 
			NULL, NULL);

	    strLayerName = bstrLayerName;
		m_LayerObjectList.AddString(strLayerName);
	}
	m_LayerObjectList.SetCurSel(0);
	UpdateData(false);
    m_UserLayerSelectComBox.AddString("显示标准信息");
	m_UserLayerSelectComBox.AddString("显示基本信息");
	m_UserLayerSelectComBox.AddString("显示全部信息");
	m_UserLayerSelectComBox.SetCurSel(0);
    USER_DEFINE_DISPLAY_LAYER_UNION  userlaypos=pFrame->userDefineStandardLayer;
    for( int i=0;i<userlaypos.userDefineLayerPosCount;i++)
	{
		bstrLayerName = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
		pYimaEncCtrl->GetLayerInfo(-1,userlaypos.userDefineLayerPos[i], &bstrLayerName, 
			NULL, NULL);

	     strLayerName = bstrLayerName;
		 m_UserLayerObjectList.AddString(strLayerName);
	}




	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUserDefineMapDlg::OnAddtolayerBtn() 
{
	// TODO: Add your control notification handler code here
	CString strLayerName;
	int cout=0;
	CMainFrame* pFrame =(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	int cursel=m_LayerObjectList.GetCurSel();
	switch(m_UserLayerSelectComBox.GetCurSel())
	{
	case 0:
			 cout=m_UserLayerObjectList.GetCount();
			 pFrame->userDefineStandardLayer.userDefineLayerPos[cout]=cursel;
             pFrame->userDefineStandardLayer.userDefineLayerPosCount=cout+1;
			 break;

	case 1:
		     cout=m_UserLayerObjectList.GetCount();
			 pFrame->userDefineBasicLayer.userDefineLayerPos[cout]=cursel;
             pFrame->userDefineBasicLayer.userDefineLayerPosCount=cout+1;
			 break;

	case 2:
		     cout=m_UserLayerObjectList.GetCount();
			 pFrame->userDefineAllLayer.userDefineLayerPos[cout]=cursel;
             pFrame->userDefineAllLayer.userDefineLayerPosCount=cout+1;
		      
			 break;
	}
	m_LayerObjectList.GetText(cursel,strLayerName);
	m_UserLayerObjectList.AddString(strLayerName);
    m_UserLayerObjectList.SetCurSel(m_UserLayerObjectList.GetCount()-1);
	if(cursel==m_LayerObjectList.GetCount()-1)  m_LayerObjectList.SetCurSel(cursel-1);
	else m_LayerObjectList.SetCurSel(cursel+1);
	
}
void CUserDefineMapDlg::OnDeleteromlayerBtn() 
{
	// TODO: Add your control notification handler code her

   
	CMainFrame* pFrame =(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	int cout;
	int cursel=m_UserLayerObjectList.GetCurSel();
	m_UserLayerObjectList.DeleteString(cursel);
	switch(m_UserLayerSelectComBox.GetCurSel())
	{
	case 0:
			cout=m_UserLayerObjectList.GetCount()+1;
	        for(cursel;cursel<cout;cursel++)
			{
                pFrame->userDefineStandardLayer.userDefineLayerPos[cursel]=pFrame->userDefineStandardLayer.userDefineLayerPos[cursel+1];
			}
             pFrame->userDefineStandardLayer.userDefineLayerPosCount=cout-1;
			 break;

	case 1:
		    cout=m_UserLayerObjectList.GetCount()+1;
	        for(cursel;cursel<cout;cursel++)
			{
                pFrame->userDefineBasicLayer.userDefineLayerPos[cursel]=pFrame->userDefineBasicLayer.userDefineLayerPos[cursel+1];
			}
             pFrame->userDefineBasicLayer.userDefineLayerPosCount=cout-1;
			 break;

	case 2:
		     cout=m_UserLayerObjectList.GetCount()+1;
	        for(cursel;cursel<cout;cursel++)
			{
                pFrame->userDefineAllLayer.userDefineLayerPos[cursel]=pFrame->userDefineAllLayer.userDefineLayerPos[cursel+1];
			}
             pFrame->userDefineAllLayer.userDefineLayerPosCount=cout-1;
			 break;
	}
    m_UserLayerObjectList.SetCurSel(m_UserLayerObjectList.GetCount()-1);
	
}

void CUserDefineMapDlg::OnSelchangeUserlayrSelectCombox() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame =(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	CString strLayerName;
    int i;
	for(i=m_UserLayerObjectList.GetCount()-1;i>-1;i--)
	{
	    m_UserLayerObjectList.DeleteString(i);
	}
	switch(m_UserLayerSelectComBox.GetCurSel())
	{
    case 0:  
	     for(i=0;i<pFrame->userDefineStandardLayer.userDefineLayerPosCount;i++)
		 {
			 BSTR bstrLayerName = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
		    pYimaEncCtrl->GetLayerInfo(-1,pFrame->userDefineStandardLayer.userDefineLayerPos[i], &bstrLayerName, 
			NULL, NULL);
	        strLayerName = bstrLayerName;
		    m_UserLayerObjectList.AddString(strLayerName);
			SysFreeString(bstrLayerName);
		 }
   break;
   case 1:
	    for(i=0;i<pFrame->userDefineBasicLayer.userDefineLayerPosCount;i++)
		 {
			BSTR bstrLayerName = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
            bstrLayerName = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
		    pYimaEncCtrl->GetLayerInfo(-1,pFrame->userDefineBasicLayer.userDefineLayerPos[i], &bstrLayerName, 
			NULL, NULL);

	       strLayerName = bstrLayerName;
		    m_UserLayerObjectList.AddString(strLayerName);
			SysFreeString(bstrLayerName);
		 }
	   
   break;
   case 2:
	    for(i=0;i<pFrame->userDefineAllLayer.userDefineLayerPosCount;i++)
		 {
            BSTR bstrLayerName = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
		    bstrLayerName = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
		    pYimaEncCtrl->GetLayerInfo(-1,pFrame->userDefineAllLayer.userDefineLayerPos[i], &bstrLayerName, 
			NULL, NULL);

	         strLayerName = bstrLayerName;
		    m_UserLayerObjectList.AddString(strLayerName);
		    SysFreeString(bstrLayerName);
		 }
		
   break;
  
	}	
}

void CUserDefineMapDlg::OnOK() 
{
	// TODO: Add extra validation here

	CDialog::OnOK();
}
