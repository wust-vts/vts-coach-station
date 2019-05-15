// QueryDialog.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "QueryDialog.h"
#include "MainFrm.h" 
#include "GeoObjectInfoDlg.h"
#include "YimaEncViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQueryDialog dialog


CQueryDialog::CQueryDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQueryDialog)
	m_strQueryKeyString = _T("");
	//}}AFX_DATA_INIT
	m_pSelectedObjPoses = NULL;
}


void CQueryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryDialog)
	DDX_Control(pDX, IDC_SEL_OBJ_LIST, m_selGeoObjectList);
	DDX_Text(pDX, IDC_KEY_WORDS_EDIT, m_strQueryKeyString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQueryDialog, CDialog)
	//{{AFX_MSG_MAP(CQueryDialog)
	ON_BN_CLICKED(IDC_QUERY_BUTTON, OnQueryButton)
	ON_LBN_DBLCLK(IDC_SEL_OBJ_LIST, OnDblclkSelObjList)
	ON_LBN_SELCHANGE(IDC_SEL_OBJ_LIST, OnSelchangeSelObjList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryDialog message handlers

void CQueryDialog::OnQueryButton() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(true);
	
	int listItemCount = m_selGeoObjectList.GetCount();
	for (int itemNum = listItemCount - 1; itemNum > -1; itemNum --)
	{
		m_selGeoObjectList.DeleteString(itemNum);
	} 

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl; 
	
	//再判断有否选中S57海图对象
	BSTR retSelObjPosStrings = ::SysAllocStringLen(NULL, 
		SEL_OBJ_MAX_COUNT * sizeof(MEM_GEO_OBJ_POS)); 
	
	int selObjCount = 
			pYimaEncCtrl->QueryObjectsByKeyWordsString(&retSelObjPosStrings,
			m_strQueryKeyString);  



	if (selObjCount > 0)
	{  			
		MEM_GEO_OBJ_POS selectedObjPoses[SEL_OBJ_MAX_COUNT];
		memcpy(selectedObjPoses, retSelObjPosStrings,
			selObjCount * sizeof(MEM_GEO_OBJ_POS));  
		 
	    m_curSelectedObjCount = selObjCount;
		SetSelectObjectPoses(selectedObjPoses, selObjCount);
	}
	
	SysFreeString(retSelObjPosStrings); 
	
	int lastObjMemMapPos = -1;
	for (int selObjNum = 0; selObjNum < m_curSelectedObjCount; selObjNum ++)
	{ 		 
		MEM_GEO_OBJ_POS selObjPos = m_pSelectedObjPoses[selObjNum];  

		if (lastObjMemMapPos != selObjPos.memMapPos)
		{
			int memMapLibPos = pYimaEncCtrl->GetMemMapPosInLib(selObjPos.memMapPos);

			BSTR bstrMapName = ::SysAllocStringLen(NULL, 100);
			BSTR bstrMapType = ::SysAllocStringLen(NULL, 100);
			pYimaEncCtrl->GetLibMapInfo(memMapLibPos, &bstrMapType, &bstrMapName, 
				NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL); 

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
	} 
}

int CQueryDialog::GetSelObjNumByListCurSel(int curSelNum)
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

void CQueryDialog::OnDblclkSelObjList() 
{
	// TODO: Add your control notification handler code here
	
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

		CGeoObjectInfoDlg geoObjInfoDlg;
		geoObjInfoDlg.m_memObjPos = m_pSelectedObjPoses[curSelObjPos];
		geoObjInfoDlg.DoModal();
	} 
}

void CQueryDialog::OnSelchangeSelObjList() 
{
	// TODO: Add your control notification handler code here
	int curSelListPos = m_selGeoObjectList.GetCurSel();
	int curSelObjPos = GetSelObjNumByListCurSel(curSelListPos);

	if (curSelObjPos >= 0)
	{
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
		CYimaEncViewerView* pView = (CYimaEncViewerView*) pFrame->GetActiveView();
		CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;  
		
		if (pView != NULL)
		{  
			BSTR bstrObjectPos = ::SysAllocStringLen(NULL, 
				sizeof(MEM_GEO_OBJ_POS));
			memcpy(bstrObjectPos, m_pSelectedObjPoses + curSelObjPos, sizeof(MEM_GEO_OBJ_POS));
			
			long left, right, top, bottom;
			pYimaEncCtrl->GetObjectGeoExtent(&bstrObjectPos, &left, &right, &top, &bottom);
			pYimaEncCtrl->CenterMap(((double)left + right) / 2, ((double)top + bottom) / 2);  //聚焦海图到选中的对象

			pView->SetHighlightObjects(m_pSelectedObjPoses + curSelObjPos, 1);

			pView->Invalidate(); 

			SysFreeString(bstrObjectPos);
		}
	}
}

bool CQueryDialog::SetSelectObjectPoses(
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
