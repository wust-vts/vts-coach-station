// SelectedGeoObjectsDlg.cpp : implementation file
//

#include "stdafx.h" 
#include "SelectedGeoObjectsDlg.h" 
#include "MainFrm.h" 
#include "GeoObjectInfoDlg.h"
#include "YimaEncViewerView.h"
#include "UserObjPosionOprator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern list<Radar> radarList;
/////////////////////////////////////////////////////////////////////////////
// CSelectedGeoObjectsDlg dialog 

CSelectedGeoObjectsDlg::CSelectedGeoObjectsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectedGeoObjectsDlg::IDD, pParent)
	, m_bIfShowObj(FALSE)
{
	//{{AFX_DATA_INIT(CSelectedGeoObjectsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT 

	m_pSelectedObjPoses = NULL;
	m_curSelectedObjCount = 0;
}


void CSelectedGeoObjectsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectedGeoObjectsDlg)
	DDX_Control(pDX, IDC_SEL_OBJ_LIST, m_selGeoObjectList);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHK_IF_SHOW_OBJ, m_bIfShowObj);
}


BEGIN_MESSAGE_MAP(CSelectedGeoObjectsDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectedGeoObjectsDlg)
//	ON_LBN_DBLCLK(IDC_SEL_OBJ_LIST, OnDblclkSelObjList)
	ON_LBN_SELCHANGE(IDC_SEL_OBJ_LIST, OnSelchangeSelObjList)
	ON_BN_CLICKED(IDC_DEL_BUTTON, OnDelButton)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CSelectedGeoObjectsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_MODIFY_POSITION, &CSelectedGeoObjectsDlg::OnBnClickedBtnModifyPosition)
	ON_BN_CLICKED(IDC_CHK_IF_SHOW_OBJ, &CSelectedGeoObjectsDlg::OnBnClickedChkIfShowObj) 
	ON_LBN_DBLCLK(IDC_SEL_OBJ_LIST, &CSelectedGeoObjectsDlg::OnDblclkSelObjList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectedGeoObjectsDlg message handlers

void CSelectedGeoObjectsDlg::OnDblclkSelObjList() 
{
	// TODO: Add your control notification handler code here

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	int curSelListPos = m_selGeoObjectList.GetCurSel();
	int curSelObjPos = GetSelObjNumByListCurSel(curSelListPos);

	if (curSelObjPos >= 0)
	{
		CYimaEncViewerView* pView =
			(CYimaEncViewerView*) (((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetActiveView());

		if (pView != NULL)
		{
			pView->SetHighlightObjects(m_pSelectedObjPoses + curSelObjPos, 1);
			pView->Invalidate();
		}
		
		if (m_pSelectedObjPoses[curSelObjPos].memMapPos == pYimaEncCtrl->GetMemMapCount() - 1)
		{
			pView->UserObject_SetAttributes(m_pSelectedObjPoses[curSelObjPos].layerPos,
				m_pSelectedObjPoses[curSelObjPos].innerLayerPos);
		}
		else
		{
			CGeoObjectInfoDlg geoObjInfoDlg;
			geoObjInfoDlg.m_bIsS57OrUserMapObj = true;
			geoObjInfoDlg.m_memObjPos = m_pSelectedObjPoses[curSelObjPos];
			geoObjInfoDlg.DoModal();
		} 
	} 
}

void CSelectedGeoObjectsDlg::OnSelchangeSelObjList() 
{
	// TODO: Add your control notification handler code here
    int curSelListPos = m_selGeoObjectList.GetCurSel();
	int curSelObjPos = GetSelObjNumByListCurSel(curSelListPos);
	  
		
	if (curSelObjPos >= 0)
	{
		MEM_GEO_OBJ_POS objPos = m_pSelectedObjPoses[curSelObjPos]; 
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
		CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
		if (pFrame != NULL)
		{
			if (objPos.memMapPos == pYimaEncCtrl->GetMemMapCount() - 1)
			{ 
				m_bIfShowObj = pYimaEncCtrl->tmGetObjectShowOrNot(objPos.layerPos, objPos.innerLayerPos);
			}
			else
			{
				m_bIfShowObj = pYimaEncCtrl->GetObjectShowOrNot(objPos.memMapPos, objPos.layerPos, objPos.innerLayerPos);
			}

			CYimaEncViewerView* pView = (CYimaEncViewerView*) (((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetActiveView());
 
			pView->SetHighlightObjects(m_pSelectedObjPoses + curSelObjPos, 1);
			pView->Invalidate();
		 
		}
		UpdateData(FALSE);
	}
}

int CSelectedGeoObjectsDlg::GetSelObjNumByListCurSel(int curSelNum)
{
	int iSelObjNum = -1;
	for (int listItemNum = 0; listItemNum < curSelNum + 1; listItemNum ++)
	{
		CString strItem;
		m_selGeoObjectList.GetText(listItemNum, strItem);
		if (strItem[0] == 'M')
		{
			if (listItemNum == curSelNum)
			{
				return -1;
			}

			continue;
		}
		else
		{
			iSelObjNum ++;
		}
	}

	return iSelObjNum;
}

BOOL CSelectedGeoObjectsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog(); 
  
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
 
	int lastObjMemMapPos = -1;
	for (int selObjNum = 0; selObjNum < m_curSelectedObjCount; selObjNum ++)
	{ 		 
		MEM_GEO_OBJ_POS selObjPos = m_pSelectedObjPoses[selObjNum];  

		if (lastObjMemMapPos != selObjPos.memMapPos)
		{
			//int memMapLibPos = pYimaEncCtrl->GetMemMapPosInLib(selObjPos.memMapPos);

			BSTR bstrMapName = ::SysAllocStringLen(NULL, 100);
			BSTR bstrMapType = ::SysAllocStringLen(NULL, 100);

			int mapCount = pYimaEncCtrl->GetMemMapCount();
			pYimaEncCtrl->GetMemMapInfo(selObjPos.memMapPos, &bstrMapType, &bstrMapName, 
				NULL, NULL, NULL, NULL, NULL, NULL, NULL); 
			
			CString strMapType = bstrMapType;
			CString strMapName;
			if (strMapType == MAP_TYPE_ENC)
			{
				strMapName = "Map(S57 ENC): ";
			}
			else if (strMapType == MAP_TYPE_VCF)
			{
				strMapName = "Map(VCF): ";
			} 
			else 
			{
				strMapName = "Map: ";
			}

			strMapName += bstrMapName;
			m_selGeoObjectList.AddString(strMapName); 

			lastObjMemMapPos = selObjPos.memMapPos;

			SysFreeString(bstrMapName);
		}

		BSTR bstrLayerName = ::SysAllocStringLen(NULL, 255);
		BSTR bstrLayerToken = ::SysAllocStringLen(NULL, 255);
		pYimaEncCtrl->GetLayerInfo(selObjPos.memMapPos, selObjPos.layerPos, &bstrLayerName, &bstrLayerToken, NULL); 
 
		CString strGeoObjectInfo = "  |---  Layer:";
		strGeoObjectInfo += bstrLayerName;
		
		CString strObjectPos;
		strObjectPos.Format(", Object Pos:%d", selObjPos.innerLayerPos); 

		strGeoObjectInfo += strObjectPos;

		m_selGeoObjectList.AddString(strGeoObjectInfo);

		SysFreeString(bstrLayerName);
	}

	if (m_curSelectedObjCount > 0)
	{
		m_selGeoObjectList.SetCurSel(1);
		OnSelchangeSelObjList();
	} 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CSelectedGeoObjectsDlg::SetSelectObjectPoses(
						MEM_GEO_OBJ_POS *pSelObjPoses, int selObjCount)
{
	if (pSelObjPoses == NULL)
		return false;

	if (m_pSelectedObjPoses != NULL)
		delete m_pSelectedObjPoses;	

	if (selObjCount <= 0)
		return true;

	m_pSelectedObjPoses = new MEM_GEO_OBJ_POS[selObjCount];

	if (m_pSelectedObjPoses != NULL)
	{
		memcpy(m_pSelectedObjPoses, pSelObjPoses, 
			selObjCount * sizeof(MEM_GEO_OBJ_POS));
		
		m_curSelectedObjCount = selObjCount;

		return true;
	}
	else
	{
		return false;
	} 	
}

void CSelectedGeoObjectsDlg::OnDelButton() 
{
	// TODO: Add your control notification handler code here

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
 
	int curSelListPos = m_selGeoObjectList.GetCurSel();
	int curSelObjPos = GetSelObjNumByListCurSel(curSelListPos);

	/*if (curSelObjPos >= 0)
	{
		CYimaEncViewerView* pView =
			(CYimaEncViewerView*) (((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetActiveView());		
		
		if (AfxMessageBox("确定要删除该物标吗?", MB_YESNO) == IDYES)
		{
			MEM_GEO_OBJ_POS objPos = m_pSelectedObjPoses[curSelObjPos];	 
			if(objPos.memMapPos == (pYimaEncCtrl->GetMemMapCount() - 1))
			{																									 
				pYimaEncCtrl->tmPushInStackUndoOperation(DEL_GEO_OBJ, objPos.layerPos, objPos.innerLayerPos);
				pYimaEncCtrl->tmSetTargetForRedoOperation();
				
			}
			pYimaEncCtrl->DeleteGeoObject(objPos.memMapPos, objPos.layerPos, objPos.innerLayerPos);
			
			if (pView != NULL)
			{ 
				pView->Invalidate();
			}
		}
	}*/
	int mapPos = pYimaEncCtrl->GetMemMapCount() - 1;
	int innerLayerPos = pYimaEncCtrl->tmGetLayerObjectCount(0) - 1;
	pYimaEncCtrl->DeleteGeoObject(mapPos, 0, innerLayerPos);
	CYimaEncViewerView* pView = (CYimaEncViewerView*)(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetActiveView());
	if (pView != NULL)
	{
		pView->Invalidate();
	}
}

void CSelectedGeoObjectsDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CSelectedGeoObjectsDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CSelectedGeoObjectsDlg::OnBnClickedBtnModifyPosition()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	int curSelListPos = m_selGeoObjectList.GetCurSel();
	int curSelObjPos = GetSelObjNumByListCurSel(curSelListPos);

	if (curSelObjPos >= 0)
	{ 
 
		CUserObjPosionOprator userObjPosionOprator;
		userObjPosionOprator.m_curObjPos = m_pSelectedObjPoses[curSelObjPos];
		userObjPosionOprator.DoModal();	   
	}
}

void CSelectedGeoObjectsDlg::OnBnClickedChkIfShowObj()
{ 
	UpdateData(true);
	int curSelListPos = m_selGeoObjectList.GetCurSel();
	int curSelObjPos = GetSelObjNumByListCurSel(curSelListPos);

	if (curSelObjPos >= 0)
	{  
		MEM_GEO_OBJ_POS objPos = m_pSelectedObjPoses[curSelObjPos];
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
		CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
		if (objPos.memMapPos == pYimaEncCtrl->GetMemMapCount() - 1)
		{ 
			pYimaEncCtrl->tmSetObjectShowOrNot(objPos.layerPos, objPos.innerLayerPos, m_bIfShowObj);
		}
		else
		{
			pYimaEncCtrl->SetObjectShowOrNot(objPos.memMapPos, objPos.layerPos, objPos.innerLayerPos, m_bIfShowObj);
		}
		pYimaEncCtrl->ForcelyRefreshMap();
		pFrame->RedrawView();
	}
	
}
 
