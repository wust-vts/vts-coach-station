// MapLayerShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "MapLayerShowDlg.h"
#include "UserDefineMapDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapLayerShowDlg dialog


CMapLayerShowDlg::CMapLayerShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMapLayerShowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMapLayerShowDlg)
	m_S52MapShowCheck = FALSE;
	m_UserMapShowCheck = FALSE;
	//}}AFX_DATA_INIT
}


void CMapLayerShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapLayerShowDlg)
	DDX_Control(pDX, IDC_USERMAP_SHOW_TEXT, m_UserMapShowText);
	DDX_Control(pDX, IDC_S52MAP_SHOW_TEXT, m_S52MapShowText);
	DDX_Check(pDX, IDC_S52MAPSHOW_CHECK, m_S52MapShowCheck);
	DDX_Check(pDX, IDC_USERMAPSHOW_CHECK, m_UserMapShowCheck);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMapLayerShowDlg, CDialog)
	//{{AFX_MSG_MAP(CMapLayerShowDlg)
	ON_BN_CLICKED(IDC_S52MAPSHOW_CHECK, OnS52mapshowCheck)
	ON_BN_CLICKED(IDC_USERMAPSHOW_CHECK, OnUsermapshowCheck)
	ON_BN_CLICKED(IDC_USERMAPEDIT_BTN, OnUsermapeditBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapLayerShowDlg message handlers

void CMapLayerShowDlg::OnS52mapshowCheck() 
{
	// TODO: Add your control notification handler code here
	m_S52MapShowCheck=true;
	m_UserMapShowCheck=false;
	UpdateData(false);
	CButton *ptn;
	ptn=(CButton*)GetDlgItem(IDC_USERSTANDARD_RADIO);
    ptn->EnableWindow(false);
	ptn=(CButton*)GetDlgItem(IDC_USERBASIC_RADIO);
	ptn->EnableWindow(false);
	ptn=(CButton*)GetDlgItem(IDC_USERFULLMAP_RADIO);
    ptn->EnableWindow(false);
	ptn=(CButton*)GetDlgItem(IDC_S52STANDARDMAP_RADIO);
    ptn->EnableWindow(true);
	ptn=(CButton*)GetDlgItem(IDC_S52BASICMAP_RADIO);
	ptn->EnableWindow(true);
	ptn=(CButton*)GetDlgItem(IDC_S52ALLMAP_RADIO);
    ptn->EnableWindow(true);
}

void CMapLayerShowDlg::OnUsermapshowCheck() 
{
	// TODO: Add your control notification handler code here
	m_S52MapShowCheck=false;
	m_UserMapShowCheck=true;
	UpdateData(false);
	CButton *ptn;
	ptn=(CButton*)GetDlgItem(IDC_S52STANDARDMAP_RADIO);
    ptn->EnableWindow(false);
	ptn=(CButton*)GetDlgItem(IDC_S52BASICMAP_RADIO);
	ptn->EnableWindow(false);
	ptn=(CButton*)GetDlgItem(IDC_S52ALLMAP_RADIO);
    ptn->EnableWindow(false);
	ptn=(CButton*)GetDlgItem(IDC_USERSTANDARD_RADIO);
    ptn->EnableWindow(true);
	ptn=(CButton*)GetDlgItem(IDC_USERBASIC_RADIO);
	ptn->EnableWindow(true);
	ptn=(CButton*)GetDlgItem(IDC_USERFULLMAP_RADIO);
    ptn->EnableWindow(true);
}	




BOOL CMapLayerShowDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CButton *ptn;
    CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	if(pFrame->S52oruser)
	{
		m_S52MapShowCheck=true;
	    m_UserMapShowCheck=false;
		ptn=(CButton*)GetDlgItem(IDC_USERSTANDARD_RADIO);
		ptn->EnableWindow(false);
		ptn=(CButton*)GetDlgItem(IDC_USERBASIC_RADIO);
		ptn->EnableWindow(false);
		ptn=(CButton*)GetDlgItem(IDC_USERFULLMAP_RADIO);
		ptn->EnableWindow(false);
		ptn=(CButton*)GetDlgItem(IDC_S52STANDARDMAP_RADIO);
		ptn->EnableWindow(true);
		ptn=(CButton*)GetDlgItem(IDC_S52BASICMAP_RADIO);
		ptn->EnableWindow(true);
		ptn=(CButton*)GetDlgItem(IDC_S52ALLMAP_RADIO);
		ptn->EnableWindow(true);
		switch(pFrame->s52RadioButtonNum)
		{
	     	case 0:
			CheckRadioButton(IDC_S52STANDARDMAP_RADIO,IDC_S52ALLMAP_RADIO,IDC_S52STANDARDMAP_RADIO);
			break;
		    case 1:
			CheckRadioButton(IDC_S52STANDARDMAP_RADIO,IDC_S52ALLMAP_RADIO,IDC_S52BASICMAP_RADIO);
			break;
		    case 2:
			CheckRadioButton(IDC_S52STANDARDMAP_RADIO,IDC_S52ALLMAP_RADIO,IDC_S52ALLMAP_RADIO);
			break;
		}
	}
	else
	{
		m_S52MapShowCheck=false;
	    m_UserMapShowCheck=true;
		ptn=(CButton*)GetDlgItem(IDC_S52STANDARDMAP_RADIO);
		ptn->EnableWindow(false);
		ptn=(CButton*)GetDlgItem(IDC_S52BASICMAP_RADIO);
		ptn->EnableWindow(false);
		ptn=(CButton*)GetDlgItem(IDC_S52ALLMAP_RADIO);
		ptn->EnableWindow(false);
		ptn=(CButton*)GetDlgItem(IDC_USERSTANDARD_RADIO);
		ptn->EnableWindow(true);
		ptn=(CButton*)GetDlgItem(IDC_USERBASIC_RADIO);
		ptn->EnableWindow(true);
		ptn=(CButton*)GetDlgItem(IDC_USERFULLMAP_RADIO);
		ptn->EnableWindow(true);
		switch(pFrame->userRadioButtonNum)
		{
		    case 0:
			CheckRadioButton(IDC_USERSTANDARD_RADIO,IDC_USERFULLMAP_RADIO,IDC_USERSTANDARD_RADIO);
			break;
		    case 1:
			CheckRadioButton(IDC_USERSTANDARD_RADIO,IDC_USERFULLMAP_RADIO,IDC_USERBASIC_RADIO);
			break;
		    case 2:
			CheckRadioButton(IDC_USERSTANDARD_RADIO,IDC_USERFULLMAP_RADIO,IDC_USERFULLMAP_RADIO);
			break;
		}
	}
	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMapLayerShowDlg::OnUsermapeditBtn() 
{
	// TODO: Add your control notification handler code here
    CUserDefineMapDlg  userDefineMapDlg;
    userDefineMapDlg.DoModal();
	
}

void CMapLayerShowDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd; 
    pFrame->m_yimaEncCtrl.SetAllLayerDrawOrNot(-1, true);
	int nID;
	if(m_S52MapShowCheck)
	{
		 nID=GetCheckedRadioButton(IDC_S52STANDARDMAP_RADIO,IDC_S52ALLMAP_RADIO);
		switch(nID)
		{
		case IDC_S52STANDARDMAP_RADIO:
			pFrame->m_yimaEncCtrl.SetDisplayCategory(DISPLAY_STANDARD); 
            pFrame->RedrawView();
		    pFrame->s52RadioButtonNum=0;

            break;
		case IDC_S52BASICMAP_RADIO:
			pFrame->m_yimaEncCtrl.SetDisplayCategory(DISPLAY_BASE); 
			pFrame->RedrawView();
			pFrame->s52RadioButtonNum=1;
			break;
		case IDC_S52ALLMAP_RADIO:
			pFrame->m_yimaEncCtrl.SetDisplayCategory(DISPLAY_ALL); 
            pFrame->RedrawView();
			pFrame->s52RadioButtonNum=2;
			break;
		}
       pFrame->S52oruser=true;
	}
	else
	{
         nID=GetCheckedRadioButton(IDC_USERSTANDARD_RADIO,IDC_USERFULLMAP_RADIO);
		 pFrame->m_yimaEncCtrl.SetAllLayerDrawOrNot(-1, false);
		  pFrame->RedrawView();
		int i;
		switch(nID)
		{
		case IDC_USERSTANDARD_RADIO:
		for(i=0;i<pFrame->userDefineStandardLayer.userDefineLayerPosCount;i++)
			{
			  pFrame->m_yimaEncCtrl.SetLayerDrawOrNot(-1,pFrame->userDefineStandardLayer.userDefineLayerPos[i], 
		      true);
			}
            pFrame->RedrawView();
            pFrame->userRadioButtonNum=0;
			break;
		case IDC_USERBASIC_RADIO:
			for(i=0;i<pFrame->userDefineBasicLayer.userDefineLayerPosCount;i++)
			{
			pFrame->m_yimaEncCtrl.SetLayerDrawOrNot(-1,pFrame->userDefineBasicLayer.userDefineLayerPos[i], 
		    true);
			}
            pFrame->RedrawView();
            pFrame->userRadioButtonNum=1;
			break;
		case IDC_USERFULLMAP_RADIO:
            for(i=0;i<pFrame->userDefineAllLayer.userDefineLayerPosCount;i++)
			{
			pFrame->m_yimaEncCtrl.SetLayerDrawOrNot(-1,pFrame->userDefineAllLayer.userDefineLayerPos[i], 
		    true);
			}
            pFrame->RedrawView();
			pFrame->userRadioButtonNum=2;
			break;
		}
		pFrame->S52oruser=false;
	}
	CDialog::OnOK();
}
