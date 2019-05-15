// RouteEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "RouteEditDlg.h"
#include "MainFrm.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRouteEditDlg dialog


CRouteEditDlg::CRouteEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRouteEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRouteEditDlg)
	m_routeName = _T("");
	//}}AFX_DATA_INIT
}


void CRouteEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRouteEditDlg)
	DDX_Control(pDX, IDC_ROUTE_WP_GRID, m_wayPointGrid);
	DDX_Text(pDX, IDC_ROUTE_NAME_EDIT, m_routeName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRouteEditDlg, CDialog)
	//{{AFX_MSG_MAP(CRouteEditDlg)
	ON_BN_CLICKED(IDC_DEL_WAY_POINT_BTN, OnDelWayPointBtn)
	ON_BN_CLICKED(IDC_ADD_WAY_POINT_BTN, OnAddWayPointBtn)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CRouteEditDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRouteEditDlg message handlers

BOOL CRouteEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd; 
	
	BSTR bstrRouteName = ::SysAllocStringLen(NULL, 255);
	pFrame->m_yimaEncCtrl.GetRouteName(m_editRouteID,
		&bstrRouteName);
	m_routeName = bstrRouteName;
	SysFreeString(bstrRouteName); 
	
	RefreshWayPointGrid();

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRouteEditDlg::OnOK() 
{
	// TODO: Add extra validation here
	SaveWayPointGrid();

	CDialog::OnOK();
}

void CRouteEditDlg::RefreshWayPointGrid()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd; 

	m_wayPointGrid.SetCols(4);
	m_wayPointGrid.SetTextMatrix(0, 0, "航路点序号");
	m_wayPointGrid.SetTextMatrix(0, 1, "航路点ID");
	m_wayPointGrid.SetTextMatrix(0, 2, "经度");
	m_wayPointGrid.SetTextMatrix(0, 3, "纬度");

	int routeWpCount = 
		pFrame->m_yimaEncCtrl.GetRouteWayPointsCount(m_editRouteID);

	m_wayPointGrid.SetRows(routeWpCount + 2); // +2: 标题栏和最下面一个空行
	m_wayPointGrid.Clear();

	long wpIDs[ROUTE_WAY_POINTS_MAX_COUNT];
	BSTR bstrWpIDs = ::SysAllocStringLen(NULL, ROUTE_WAY_POINTS_MAX_COUNT * 2);	
	pFrame->m_yimaEncCtrl.GetRouteWayPointsID(m_editRouteID, &bstrWpIDs);		
	memcpy(wpIDs, bstrWpIDs, routeWpCount * sizeof(int));
	SysFreeString(bstrWpIDs);    

	for (int wpNum = 0; wpNum < routeWpCount; wpNum ++)
	{ 
		long wpID = wpIDs[wpNum];
		M_POINT wpPoint;
		pFrame->m_yimaEncCtrl.GetWayPointCoor(wpID, 
			(long*)&wpPoint.x, (long*)&wpPoint.y);

		CString strWpPos, strWpID, strWpCoorX, strWpCoorY;

		strWpPos.Format("%d", wpNum + 1);
		strWpID.Format("%d", wpID);
		strWpCoorX.Format("%f", 
			(double)wpPoint.x / pFrame->m_yimaEncCtrl.GetGeoCoorMultiFactor());
		strWpCoorY.Format("%f", 
			(double)wpPoint.y / pFrame->m_yimaEncCtrl.GetGeoCoorMultiFactor());
  
		m_wayPointGrid.SetTextMatrix(wpNum + 1, 0, strWpPos);
		m_wayPointGrid.SetTextMatrix(wpNum + 1, 1, strWpID);
		m_wayPointGrid.SetTextMatrix(wpNum + 1, 2, strWpCoorX);
		m_wayPointGrid.SetTextMatrix(wpNum + 1, 3, strWpCoorY);
	}	
}

void CRouteEditDlg::SaveWayPointGrid()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd; 

	int routeWpCount = 
		pFrame->m_yimaEncCtrl.GetRouteWayPointsCount(m_editRouteID);

	m_wayPointGrid.SetRows(routeWpCount + 2); // +2: 标题栏和最下面一个空行

	long wpIDs[ROUTE_WAY_POINTS_MAX_COUNT]; 
	BSTR bstrWpIDs = ::SysAllocStringLen(NULL, ROUTE_WAY_POINTS_MAX_COUNT * 2);	
	pFrame->m_yimaEncCtrl.GetRouteWayPointsID(m_editRouteID, &bstrWpIDs);		
	memcpy(wpIDs, bstrWpIDs, routeWpCount * sizeof(int));
	SysFreeString(bstrWpIDs);     
 
	for (int wpNum = 0; wpNum < routeWpCount; wpNum ++)
	{ 
		long wpID = wpIDs[wpNum];
		CString strWpCoorX = m_wayPointGrid.GetTextMatrix(wpNum + 1, 2);
		CString strWpCoorY = m_wayPointGrid.GetTextMatrix(wpNum + 1, 3); 

		pFrame->m_yimaEncCtrl.SetWayPointCoor(wpID, 
			atof(strWpCoorX) * pFrame->m_yimaEncCtrl.GetGeoCoorMultiFactor(), 
			atof(strWpCoorY) * pFrame->m_yimaEncCtrl.GetGeoCoorMultiFactor());
	}	
}

BEGIN_EVENTSINK_MAP(CRouteEditDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CRouteEditDlg)
	ON_EVENT(CRouteEditDlg, IDC_ROUTE_WP_GRID, -603 /* KeyPress */, OnKeyPressRouteWpGrid, VTS_PI2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CRouteEditDlg::OnKeyPressRouteWpGrid(short FAR* KeyAscii) 
{
	// TODO: Add your control notification handler code here
	m_wayPointGrid.OnKeyPressGrid(KeyAscii);
}

void CRouteEditDlg::OnDelWayPointBtn() 
{
	// TODO: Add your control notification handler code here
	long selWpPos = m_wayPointGrid.GetRowSel() - 1;

	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;  
	pFrame->m_yimaEncCtrl.DeleteRouteWayPoint(m_editRouteID, selWpPos, 1);
	
	RefreshWayPointGrid();
	pFrame->RedrawView();
}

void CRouteEditDlg::OnAddWayPointBtn() 
{
	// TODO: Add your control notification handler code here
	long addWpPos = m_wayPointGrid.GetRowSel() - 1;  
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;  
	long newWpID = 0;
	if (addWpPos > -1)
	{
		long wpIDs[ROUTE_WAY_POINTS_MAX_COUNT]; 
		BSTR bstrWpIDs = ::SysAllocStringLen(NULL, ROUTE_WAY_POINTS_MAX_COUNT * 2);	
		int routeWpCount = pFrame->m_yimaEncCtrl.GetRouteWayPointsID(m_editRouteID, &bstrWpIDs);		
		memcpy(wpIDs, bstrWpIDs, routeWpCount * sizeof(int));
		SysFreeString(bstrWpIDs); 

		long lastWpID = wpIDs[addWpPos];
		long lastWpCoorX, lastWpCoorY;
		pFrame->m_yimaEncCtrl.GetWayPointCoor(lastWpID, &lastWpCoorX, 
			&lastWpCoorY);
		
		newWpID = pFrame->m_yimaEncCtrl.AddWayPoint(lastWpCoorX, lastWpCoorY, "");
	}
	else
	{
		newWpID = pFrame->m_yimaEncCtrl.AddWayPoint(0, 0, "");
	}
	
	BSTR bstrWpIDs = ::SysAllocStringLen(NULL, 4);	
	memcpy(bstrWpIDs, &newWpID, 1 * sizeof(int));
	pFrame->m_yimaEncCtrl.AddRouteWayPoint(m_editRouteID, addWpPos, &bstrWpIDs, 1);	 
	SysFreeString(bstrWpIDs);  
	
	RefreshWayPointGrid(); 
}

void CRouteEditDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
