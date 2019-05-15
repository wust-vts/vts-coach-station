// MapLibInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "MapLibInfoDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapLibInfoDlg dialog


CMapLibInfoDlg::CMapLibInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMapLibInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMapLibInfoDlg)
	m_edtNum = 0;
	m_strLeftBndry = _T("");
	m_strRightBndry = _T("");
	m_strUpBndry = _T("");
	m_strBottomBndry = _T("");
	m_uptEdtNum = 0;
	m_nOrgScale = 0; 
	m_fMapShowMinScale = 0.0f;
	m_strEditDate = _T("");
	m_strMapCount = _T("");
	//}}AFX_DATA_INIT
}


void CMapLibInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapLibInfoDlg)
	DDX_Control(pDX, IDC_MAP_LIST, m_mapList);
	DDX_Text(pDX, IDC_EDTION_NUM_EDIT, m_edtNum);
	DDX_Text(pDX, IDC_LEFT_EDIT, m_strLeftBndry);
	DDX_Text(pDX, IDC_RIGHT_EDIT, m_strRightBndry);
	DDX_Text(pDX, IDC_UP_EDIT, m_strUpBndry);
	DDX_Text(pDX, IDC_DOWN_EDIT, m_strBottomBndry);
	DDX_Text(pDX, IDC_UPT_EDT_NUM_EDIT, m_uptEdtNum);
	DDX_Text(pDX, IDC_ORGN_SCALE_EDIT, m_nOrgScale); 
	DDX_Text(pDX, IDC_MAP_SHOW_MINSCALE_EDIT, m_fMapShowMinScale);
	DDX_Text(pDX, IDC_UPT_DATE_EDIT, m_strEditDate);
	DDX_Text(pDX, IDC_STATIC_MAP_COUNT, m_strMapCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMapLibInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CMapLibInfoDlg)
	ON_LBN_SELCHANGE(IDC_MAP_LIST, OnSelchangeMapList)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, OnCloseButton)
	ON_LBN_DBLCLK(IDC_MAP_LIST, OnDblclkMapList)
	ON_BN_CLICKED(IDC_OPEN_MAP_BUTTON, OnOpenMapButton)
	ON_BN_CLICKED(IDC_OVERVIEW_BUTTON, OnOverviewButton)
	ON_BN_CLICKED(IDC_ADD_S63_FILE_BUTTON, OnAddS63FileButton)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SET_MIN_SCALE_BUTTON, OnSetMinScaleButton)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, OnClearButton)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CMapLibInfoDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapLibInfoDlg message handlers

BOOL CMapLibInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	RefreshLibMapList();

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	//pYimaEncCtrl->SetLoadMapScaleFactor(100);

	int libMapCount = pYimaEncCtrl->GetLibMapCount(); 
	if (libMapCount > 0)
	{
		m_mapList.SetCurSel(0);
		ShowLibMapInfo(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMapLibInfoDlg::RefreshLibMapList()
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	int listItemCount = m_mapList.GetCount();
	for (int itemNum = listItemCount - 1; itemNum > -1; itemNum --)
	{
		m_mapList.DeleteString(itemNum);
	}

	int libMapCount = pYimaEncCtrl->GetLibMapCount(); 
	for (int mapNum = 0; mapNum < libMapCount; mapNum ++)
	{ 
		BSTR bstrMapName = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
		BSTR bstrMapType = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
		BSTR bstrMapFileName = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);

		int angencyCode, hdat, vdat, sdat;
		pYimaEncCtrl->GetLibMapInfo(mapNum, &bstrMapType, &bstrMapName, 
		  NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
		  (long*)&angencyCode, (long*)&hdat, (long*)&vdat, (long*)&sdat, &bstrMapFileName); 
		
		CString strMapName = bstrMapName;
		m_mapList.AddString(strMapName);

		CString strMapFileName = bstrMapFileName;

		SysFreeString(bstrMapName);
		SysFreeString(bstrMapType);
		SysFreeString(bstrMapFileName);
	} 

	m_strMapCount.Format(_T("共%d幅海图."), libMapCount); 
	UpdateData(false);
}

void CMapLibInfoDlg::ShowLibMapInfo(int libMapPos)
{ 	
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	if (libMapPos < 0 || libMapPos >= pYimaEncCtrl->GetLibMapCount())
		return;

	float originalScale = 0;
	long left, right, up, down;
	long editionNum, updateEdtNum;
	long angencyCode, hdat, vdat, sdat;
	
	pYimaEncCtrl->GetLibMapInfo(libMapPos, NULL, NULL, 
		&originalScale, &left, &right, 
		&up, &down, &editionNum, &updateEdtNum, &angencyCode, &hdat, &vdat, &sdat, NULL); 

	TCHAR strBndryDegree[100]; 
	long iGeoCoorMultiFactor = pYimaEncCtrl->GetGeoCoorMultiFactor();	 

	GetDegreeStringFromGeoCoor(strBndryDegree, true, left, iGeoCoorMultiFactor);
	m_strLeftBndry = strBndryDegree;

	GetDegreeStringFromGeoCoor(strBndryDegree, true, right, iGeoCoorMultiFactor);
	m_strRightBndry = strBndryDegree;

	GetDegreeStringFromGeoCoor(strBndryDegree, false, up, iGeoCoorMultiFactor);
	m_strUpBndry = strBndryDegree;

	GetDegreeStringFromGeoCoor(strBndryDegree, false, down, iGeoCoorMultiFactor);
	m_strBottomBndry = strBndryDegree;

    m_nOrgScale = originalScale;

	m_edtNum = editionNum;

	m_uptEdtNum = updateEdtNum;
	
	BSTR bstrMapEditDate = ::SysAllocStringLen(NULL, MAX_NAMES_LEN); 
	pYimaEncCtrl->GetLibMapEditionIssueDate(libMapPos, updateEdtNum, &bstrMapEditDate);	
	m_strEditDate = bstrMapEditDate; 
	SysFreeString(bstrMapEditDate);

	UpdateData(false);
}

void CMapLibInfoDlg::OnSelchangeMapList() 
{
	// TODO: Add your control notification handler code here
	ShowLibMapInfo(m_mapList.GetCurSel());
}

void CMapLibInfoDlg::OnCloseButton() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	int curSelMapPos = m_mapList.GetCurSel();
	pYimaEncCtrl->DeleteLibMap(curSelMapPos);

	RefreshLibMapList();

	if (curSelMapPos < pYimaEncCtrl->GetLibMapCount())
	{
		m_mapList.SetCurSel(curSelMapPos);
		ShowLibMapInfo(curSelMapPos);
	}		
	pFrame->m_yimaEncCtrl.ForcelyRefreshMap();
	pFrame->RedrawView();
}

void CMapLibInfoDlg::OnDblclkMapList() 
{
	// TODO: Add your control notification handler code here
    OverViewCurrentSelectedMap();
}

void CMapLibInfoDlg::OverViewCurrentSelectedMap() 
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	SetCursor(LoadCursor(NULL, IDC_WAIT)); 

	pYimaEncCtrl->OverViewLibMap(m_mapList.GetCurSel());
	pFrame->RedrawView();

	SetCursor(LoadCursor(NULL, IDC_ARROW)); 
}

#define MAX_OPEN_LIB_MAP_COUNT 10000 

typedef enum ADDMAP_RETURN_VAL
{
	RET__OK = 0,
	RET__FILE_PATH_WRONG = 1001,
	RET__FILE_INVALID = 1002,
	RET__FILE_VERSION_LOW = 1003, 
	RET__PERMIT_FILE_INVALID = 1004,
    RET__UPDATE_FILE_VERSION_BASE_VERSION_NOT_EQUAL = 1005, 
	RET__UPDATE_FILE_VERSION_LOW = 1006,
	RET__UPDATE_FILE_VERSION_HIGH = 1007,
	RET__UPDATE_FILE_CANNOT_FIND_LIBMAP = 1008,
	RET__OTHER_ERROR = 10000
}ADDMAP_RETURN_VAL;

void CMapLibInfoDlg::OnOpenMapButton() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
 
	if (pFrame != NULL)
	{
		CFileDialog dlg(TRUE, _T("map"), _T(""),
			OFN_ALLOWMULTISELECT | OFN_OVERWRITEPROMPT,
			_T("S57 files(*.000)|*.000|YIMA ENC files(*.ymc)|*.ymc|YIMAP files(*.ymp)|*.ymp|S57 Update files(*.*)|*.*|"));

		dlg.m_ofn.lpstrFile = new char[MAX_OPEN_LIB_MAP_COUNT * sizeof(char)];
		dlg.m_ofn.nMaxFile = MAX_OPEN_LIB_MAP_COUNT;
		ZeroMemory( dlg.m_ofn.lpstrFile, MAX_OPEN_LIB_MAP_COUNT * sizeof(char) );

		dlg.DoModal();
		
		POSITION pos = dlg.GetStartPosition(); 
		
		CString strFailedMapArray[1024];
		int failedArrayCount = 0;

		int openMapCount = 0;

		while (pos != NULL) 
		{ 
			CString strFileName = dlg.GetNextPathName(pos); 	
			
			if (strFileName != "")
			{
				CString strOperationReport = "Loading Map : ";
				CString strMapName = strFileName.Right( 
					strFileName.GetLength() - strFileName.ReverseFind('\\') - 1);
				strOperationReport += strMapName;
				strOperationReport += " ...";
				pFrame->SetOperationStatusBarText(strOperationReport);

				int retCode = pFrame->m_yimaEncCtrl.AddMapToLib(strFileName);  //YIMAENC COMMENT:  YimaEnc Control interoped! 
				if (retCode != RET__OK)
				{ 
					CString strMsg;
					switch(retCode)
					{
						case RET__FILE_PATH_WRONG:
							strMsg.Format("导入海图文件%s失败!文件路径不对.", strFileName);
							break;
						case RET__FILE_INVALID:
							strMsg.Format("导入海图文件%s失败!文件格式非法.", strFileName);
							break;
						case RET__FILE_VERSION_LOW:
							strMsg.Format("导入海图文件%s失败!要导入海图文件在海图库中已有,应导入更高升级版本.", strFileName);
							break;
						case RET__UPDATE_FILE_CANNOT_FIND_LIBMAP:
							strMsg.Format("导入海图升级文件%s失败!在海图库中没有找到对应海图.", strFileName);
							break;
						case RET__UPDATE_FILE_VERSION_BASE_VERSION_NOT_EQUAL:
							strMsg.Format("导入海图升级文件%s失败!升级文件基础版本号与海图版本号不匹配.", strFileName);
							break;
						case RET__UPDATE_FILE_VERSION_LOW:
							strMsg.Format("导入海图升级文件%s失败!升级文件版本过低.", strFileName);
							break;
						case RET__UPDATE_FILE_VERSION_HIGH:
							strMsg.Format("导入海图升级文件%s失败!升级文件版本过低过高.", strFileName);
							break;  
						case RET__OTHER_ERROR:
							strMsg.Format("导入海图文件%s失败!其他错误.", strFileName); 
							break;
					} 

					openMapCount ++;
					
					AfxMessageBox(strMsg);

					//strFailedMapArray[] = ;
				}

				pFrame->SetOperationStatusBarText("Finished to load the Map.");
				Sleep(200);
			}
		}	
		
		if (openMapCount > 1)
		{
			AfxMessageBox("导入完毕");
		}
		pFrame->m_yimaEncCtrl.ForcelyRefreshMap();
		pFrame->RedrawView();
		
		delete[] dlg.m_ofn.lpstrFile; 
		
		RefreshLibMapList();   

		pFrame->SetOperationStatusBarText(DEFAULT_OPERATION_STATUS_TEXT);
	}
}

void CMapLibInfoDlg::OnOverviewButton() 
{
	// TODO: Add your control notification handler code here
	OverViewCurrentSelectedMap();
}

void CMapLibInfoDlg::OnAddS63FileButton() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	
	if (pFrame != NULL)
	{
		if (m_s63fileDlg.DoModal() == IDOK && m_s63fileDlg.m_strCellFilePath != "" && 
				m_s63fileDlg.m_strPermitFilePath != "")
		{ 
			/*if (!pFrame->m_yimaEncCtrl.AddS63MapLib(
				m_s63fileDlg.m_strCellFilePath, m_s63fileDlg.m_strPermitFilePath, false))
			{
				AfxMessageBox("打开文件失败!");
				return;
			}*/
			
			int retCode = pFrame->m_yimaEncCtrl.AddS63MapLib(
				 m_s63fileDlg.m_strCellFilePath, m_s63fileDlg.m_strPermitFilePath, true);  //YIMAENC COMMENT:  YimaEnc Control interoped! 
			
			if (retCode != RET__OK)
			{ 
				CString strMsg;
				switch(retCode)
				{
				case RET__FILE_PATH_WRONG:
					strMsg.Format("导入海图文件%s失败!文件路径不对.", m_s63fileDlg.m_strCellFilePath);
					break;
				case RET__FILE_INVALID:
					strMsg.Format("导入海图文件%s失败!文件格式非法.", m_s63fileDlg.m_strCellFilePath);
					break;
				case RET__FILE_VERSION_LOW:
					strMsg.Format("导入海图文件%s失败!要导入海图文件在海图库中已有,应导入更高升级版本.", m_s63fileDlg.m_strCellFilePath);
					break;
				case RET__UPDATE_FILE_VERSION_LOW:
					strMsg.Format("导入海图升级文件%s失败!升级文件版本过低.", m_s63fileDlg.m_strCellFilePath);
					break;
				case RET__PERMIT_FILE_INVALID:
					strMsg.Format("导入海图文件%s失败!permit许可文件无效.", m_s63fileDlg.m_strPermitFilePath);
					break;
				case RET__OTHER_ERROR:
					strMsg.Format("导入海图文件%s失败!其他错误.", m_s63fileDlg.m_strCellFilePath); 
					break;
				} 
				
				AfxMessageBox(strMsg);
			}			
			pFrame->m_yimaEncCtrl.ForcelyRefreshMap();
			pFrame->RedrawView();
			RefreshLibMapList();   
		}
	}
}

void CMapLibInfoDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

void CMapLibInfoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl; 
	
	//pYimaEncCtrl->SetLoadMapScaleFactor(5);
}

void CMapLibInfoDlg::OnSetMinScaleButton() 
{
	// TODO: Add your control notification handler code here

	UpdateData(true);

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl; 
	
	if (pYimaEncCtrl->SetLibMapLoadScale(m_mapList.GetCurSel(), m_fMapShowMinScale))
	{
		pYimaEncCtrl->SaveMapLibBasicInfo();
		AfxMessageBox("设置成功");
	}
	else 
	{
		AfxMessageBox("设置失败");
	}
}

void CMapLibInfoDlg::OnClearButton() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl; 

	int libMapCount = pYimaEncCtrl->GetLibMapCount();
	for (int mapNum = libMapCount - 1; mapNum >= 0; mapNum --)
	{
		pYimaEncCtrl->DeleteLibMap(mapNum);
	}

	int listItemCount = m_mapList.GetCount();
	for (int itemNum = listItemCount - 1; itemNum > -1; itemNum --)
	{
		m_mapList.DeleteString(itemNum);
	}		
	pFrame->m_yimaEncCtrl.ForcelyRefreshMap();
	pFrame->RedrawView();
}

void CMapLibInfoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
