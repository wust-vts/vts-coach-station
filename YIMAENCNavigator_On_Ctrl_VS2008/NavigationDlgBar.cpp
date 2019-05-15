// NavigationDlgBar.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "NavigationDlgBar.h" 
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern std::list<Radar> radarList;
/////////////////////////////////////////////////////////////////////////////
// CNavigationDlgBar dialog


CNavigationDlgBar::CNavigationDlgBar()
{
	//{{AFX_DATA_INIT(CNavigationDlgBar) 
	//}}AFX_DATA_INIT
}


void CNavigationDlgBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNavigationDlgBar) 
	DDX_Control(pDX, IDC_BUTTON1, m_button); 
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNavigationDlgBar, CDialogBar)
	//{{AFX_MSG_MAP(CNavigationDlgBar) 
	ON_BN_CLICKED(IDC_SET_NAV_ROUTE_BUTTON, OnSetNavRouteButton)
	ON_BN_CLICKED(IDC_DEL_ROUTE_BTN, OnDelRouteBtn)
	ON_LBN_SELCHANGE(IDC_ROUTE_LIST, OnSelchangeRouteList)
	ON_LBN_SELCHANGE(IDC_VESSEL_LIST, OnSelchangeVesselList)
	//}}AFX_MSG_MAP
	ON_LBN_DBLCLK(IDC_RADAR_LIST, &CNavigationDlgBar::OnLbnDblclkRadarList)
	ON_NOTIFY(NM_CLICK, IDC_RADAR_LIST, &CNavigationDlgBar::OnNMClickRadarList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNavigationDlgBar message handlers

BOOL CNavigationDlgBar::Create(CWnd* pParent, UINT nIDTemplate, UINT nStyle, UINT nID) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	BOOL bReturn = CDialogBar::Create(pParent, nIDTemplate, nStyle, nID);
	//获取Radarlist客户区大小
	CListCtrl* pRadarList = (CListCtrl*)GetDlgItem(IDC_RADAR_LIST);
	CRect radarRect;
	pRadarList->GetClientRect(&radarRect);
	pRadarList->SetExtendedStyle(pRadarList->GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//添加列标题
	pRadarList->InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	pRadarList->InsertColumn(1, _T("编号"), LVCFMT_CENTER, radarRect.Width() * 3 / 16);
	pRadarList->InsertColumn(2, _T("高度"), LVCFMT_CENTER, radarRect.Width() * 4 / 16);
	pRadarList->InsertColumn(3, _T("量程"), LVCFMT_CENTER, radarRect.Width() * 5 / 16);
	pRadarList->InsertColumn(4, _T("水平面"), LVCFMT_CENTER, radarRect.Width() * 4 / 16);

	CFont* statusFont = new CFont;
	statusFont->CreateFontA(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("微软雅黑"));

	pRadarList->SetFont(statusFont);
	pRadarList->ShowWindow(SW_SHOW);

	return bReturn;
}  

BOOL CNavigationDlgBar::OnInitDialog() 
{
//	CDialogBar::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
} 

void CNavigationDlgBar::ShowNavigationInfoText(int nXStart, int nYStart, CString textOutString, int charSize, 
										   CString FontString)
{
	HDC hdc = ::GetDC(m_hWnd);
	SetBkMode(hdc,TRANSPARENT);
	
	HFONT hNewFont = CreateFont(-charSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, GB2312_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, FontString); 
	HFONT hOldFont = (HFONT)SelectObject(hdc, hNewFont);  
	
	SetTextColor(hdc, RGB(0, 0, 255));
	
	TextOut(hdc, nXStart, nYStart, textOutString, textOutString.GetLength());
	
	hNewFont = (HFONT)SelectObject(hdc,hOldFont);
	DeleteObject(hNewFont); 
	::ReleaseDC(m_hWnd, hdc);
}

void CNavigationDlgBar::ClearDlgContents(long left, long top, long right, long bottom)
{
	HDC hdc = ::GetDC(m_hWnd);

	RECT clientRect;
	clientRect.left = left;
    clientRect.top  = top;
	clientRect.right = right;
	clientRect.bottom = bottom; 

	HBRUSH hbr = CreateSolidBrush(RGB(212, 208, 200)); //GetPixel(hdc, 50, 50));
	FillRect(hdc, &clientRect, hbr);

	DeleteObject(hbr);

	::ReleaseDC(m_hWnd, hdc);
}

void CNavigationDlgBar::RefreshAlarmBar(long left, long top, 
										long right, long bottom, COLORREF alarmColor)
{
	HDC hdc = ::GetDC(m_hWnd);

	RECT clientRect;
    clientRect.left = left;
    clientRect.top  = top;
	clientRect.right = right;
	clientRect.bottom = bottom;  

	HBRUSH hbr = CreateSolidBrush(alarmColor);
	FillRect(hdc, &clientRect, hbr);
	DeleteObject(hbr);	

	::ReleaseDC(m_hWnd, hdc); 
}

void CNavigationDlgBar::RefreshRadarList()
{
	CListCtrl* pRadarList = (CListCtrl*)GetDlgItem(IDC_RADAR_LIST);
	pRadarList->DeleteAllItems();
	if (!radarList.empty())
	{
		int count = radarList.size();
		for (int itemCount = 0; itemCount < count; itemCount++)
		{
			pRadarList->InsertItem(itemCount, _T(""));
		}
		int row = 0;
		CString strHeight, strRange, strLevel;
		for (std::list<Radar>::iterator iter = radarList.begin(); iter != radarList.end(); iter++)
		{
			strHeight.Format("%.1lf", iter->Height);
			strRange.Format("%.1lf", iter->Range);
			strLevel.Format("%.1lf", iter->Level);
			pRadarList->SetItemText(row, 1, iter->Id.c_str());
			pRadarList->SetItemText(row, 2, strHeight.GetBuffer());
			pRadarList->SetItemText(row, 3, strRange.GetBuffer());
			pRadarList->SetItemText(row, 4, strLevel.GetBuffer());
			row++;
		}
	}
}

void CNavigationDlgBar::RefreshRouteList()
{ 
	CListBox* pRouteList = (CListBox*)GetDlgItem(IDC_ROUTE_LIST); 
	int oldRouteCount = pRouteList->GetCount();
	for (int oldRtNum = oldRouteCount - 1; oldRtNum > -1; oldRtNum --)
	{
		pRouteList->DeleteString(oldRtNum);
	} 

	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;  
 
	int routeCount = pFrame->m_yimaEncCtrl.GetRoutesCount();  
	for (int rtNum = 0; rtNum < routeCount; rtNum ++)
	{
		BSTR bstrRouteName = ::SysAllocStringLen(NULL, 256);

		long routeID = pFrame->m_yimaEncCtrl.GetRouteIDFromPos(rtNum);
		pFrame->m_yimaEncCtrl.GetRouteName(routeID, &bstrRouteName);

		CString strRouteName = bstrRouteName;
		pRouteList->AddString(strRouteName);

		::SysFreeString(bstrRouteName);  
	}
}

void CNavigationDlgBar::RefreshVesselList()
{ 
	CListBox* pVesselList = (CListBox*)GetDlgItem(IDC_VESSEL_LIST); 
	int oldVslCount = pVesselList->GetCount();
	for (int oldVslNum = oldVslCount - 1; oldVslNum > -1; oldVslNum --)
	{
		pVesselList->DeleteString(oldVslNum);
	}

	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;  
 
	int vslCount = pFrame->m_yimaEncCtrl.GetOtherVesselCount();  
	for (int vslNum = 0; vslNum < vslCount; vslNum ++)
	{
		BSTR bstrVslName = ::SysAllocStringLen(NULL, 256);
		long mmsi = 0;
 
		pFrame->m_yimaEncCtrl.GetOtherVesselBasicInfo(
			vslNum, NULL, NULL, &bstrVslName, &mmsi, NULL); 

		CString strVslName = bstrVslName; 

		CString strVslInfo;
		strVslInfo.Format("%s--%d", strVslName, mmsi);

		pVesselList->AddString(strVslInfo);

		::SysFreeString(bstrVslName);   
	} 
}

void CNavigationDlgBar::OnSetNavRouteButton() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd; 
	CListBox* pRouteList = (CListBox*)GetDlgItem(IDC_ROUTE_LIST); 

	int selRoutePos = pRouteList->GetCurSel();
	int routeID = pFrame->m_yimaEncCtrl.GetRouteIDFromPos(selRoutePos);
	pFrame->SetOwnShipStartOnRoute(routeID);
}
 

void CNavigationDlgBar::OnDelRouteBtn() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd; 
	CListBox* pRouteList = (CListBox*)GetDlgItem(IDC_ROUTE_LIST); 

	int selRoutePos = pRouteList->GetCurSel();
	int routeID = pFrame->m_yimaEncCtrl.GetRouteIDFromPos(selRoutePos);
	pFrame->m_yimaEncCtrl.DeleteRoute(routeID);

	RefreshRouteList();

	if (pRouteList->GetCount() > selRoutePos)
	{
		pRouteList->SetCurSel(selRoutePos);
	}

	pFrame->RedrawView();
}

void CNavigationDlgBar::OnSelchangeRouteList() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd; 
	CListBox* pRouteList = (CListBox*)GetDlgItem(IDC_ROUTE_LIST); 

	int selRoutePos = pRouteList->GetCurSel();
	int routeID = pFrame->m_yimaEncCtrl.GetRouteIDFromPos(selRoutePos);

	long routeWpCount = pFrame->m_yimaEncCtrl.GetRouteWayPointsCount(routeID);
	BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * routeWpCount);
	if (pFrame->m_yimaEncCtrl.GetRouteWayPointsCoor(routeID, &strLinePoints))
	{
		pFrame->m_yimaEncCtrl.ClearHighLightLines();
		pFrame->m_yimaEncCtrl.AddHighLightLine(&strLinePoints, routeWpCount);
	}			
	::SysFreeString(strLinePoints); 

	pFrame->RedrawView();
}

void CNavigationDlgBar::OnSelchangeVesselList() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd; 
	CListBox* pVesselList = (CListBox*)GetDlgItem(IDC_VESSEL_LIST); 

	int selVesselPos = pVesselList->GetCurSel();  

	M_POINT vslPoint;
	BOOL bVslIsArpaOrAis;
	pFrame->m_yimaEncCtrl.GetOtherVesselCurrentInfo(
		selVesselPos, &bVslIsArpaOrAis, (long*)&vslPoint.x, (long*)&vslPoint.y,
		NULL, NULL, NULL, NULL, NULL, NULL, NULL);

	M_POINT vslScrnPoint;
	pFrame->m_yimaEncCtrl.GetScrnPoFromGeoPo(
		vslPoint.x, vslPoint.y, 
		(long*)&vslScrnPoint.x, (long*)&vslScrnPoint.y);

	RECT scrnRect;
	GetClientRect(&scrnRect);
	if ( !(vslScrnPoint.x > 0 && 
		  vslScrnPoint.x < pFrame->m_yimaEncCtrl.GetDrawerScreenWidth()
		  && vslScrnPoint.y > 0 && 
		  vslScrnPoint.y < pFrame->m_yimaEncCtrl.GetDrawerScreenHeight()) )
	{//如果该目标船不在屏幕中，则将其居中
		pFrame->m_yimaEncCtrl.CenterMap(vslPoint.x, vslPoint.y);
	} 

	pFrame->m_yimaEncCtrl.HighlightOtherVessel(selVesselPos); 

	pFrame->RedrawView();
}


void CNavigationDlgBar::OnLbnDblclkRadarList()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CNavigationDlgBar::OnNMClickRadarList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CListCtrl* pRadarLists = (CListCtrl*)GetDlgItem(IDC_RADAR_LIST);
	//获取选中行行号
	CString strID;
	POSITION pos = pRadarLists->GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("no item was selected!");
	else
	{
		while (pos)
		{
			int nItem = pRadarLists->GetNextSelectedItem(pos);
			strID = pRadarLists->GetItemText(nItem, 1);
		}
	}
	for (std::list<Radar>::iterator iter = radarList.begin(); iter != radarList.end(); iter++)
	{
		if (iter->Id.compare(strID.GetBuffer()) == 0)
		{
			pFrame->m_yimaEncCtrl.CenterMap(iter->Lon, iter->Lan);
		}
	}
	pFrame->RedrawView();
	*pResult = 0;
}
