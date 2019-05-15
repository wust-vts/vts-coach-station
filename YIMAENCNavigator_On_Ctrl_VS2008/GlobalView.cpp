// GlobalView.cpp : 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "GlobalView.h"
#include "MainFrm.h"


// CGlobalView 对话框
extern CString g_ymcExt;
extern CString g_ympExt;
extern CString g_strInitPath;

IMPLEMENT_DYNAMIC(CGlobalView, CDialog)

CGlobalView::CGlobalView(CWnd* pParent /*=NULL*/)
	: CDialog(CGlobalView::IDD, pParent)
{
	m_bOpend = false;
	m_bDragingMap = false;
	m_bInit = false;
}

CGlobalView::~CGlobalView()
{
}

void CGlobalView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GLOGAL_VIEW_CTRL, m_globalViewCtrl);
}


BEGIN_MESSAGE_MAP(CGlobalView, CDialog)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CGlobalView, CDialog) 

END_EVENTSINK_MAP()

// CGlobalView 消息处理程序

BOOL CGlobalView::OnInitDialog()
{
	CDialog::OnInitDialog(); 
	bool bInitResult = false;
	m_globalViewCtrl.SetWindowPos(NULL, -100, -100, 0, 0, SWP_NOSIZE|SWP_NOZORDER);//将控件放到用户看不到的位置
	//GetDlgItem(IDC_GLOGAL_VIEW_CTRL)->ShowWindow(SW_HIDE);
	m_globalViewCtrl.SetYimapEncFileExtension(g_ymcExt, g_ympExt);
	if(g_strInitPath != "")
	{
		bInitResult = m_globalViewCtrl.Init(g_strInitPath);
	}
	else
	{
		TCHAR curWorkDir[1024];
		GetCurrentDirectory(1024, curWorkDir);//获取初始化目录
		bInitResult = m_globalViewCtrl.Init(curWorkDir); 
	}
	if (!bInitResult)
	{
		AfxMessageBox(_T("初始化失败"));
	}  
	CRect myRect;
	this->GetClientRect(myRect);
	int width = myRect.right - myRect.left;
	int hight = myRect.bottom - myRect.top;   
	m_globalViewCtrl.RefreshDrawer((long)m_hWnd, width, hight, 0, 0); 
	m_globalViewCtrl.SetIfShowGrid(false); 
	m_globalViewCtrl.SetIfShowGrid(false);
	m_globalViewCtrl.SetIfShowScaleBar(false);
	m_globalViewCtrl.SetIfShowNorthArrow(false);
	m_globalViewCtrl.SetIfShowMapFrame(false);
	m_globalViewCtrl.SetDisplayCategory(DISPLAY_BASE);
	m_globalViewCtrl.SetLayerDrawOrNot(-1, 72,false); //灯标
	m_globalViewCtrl.SetLayerDrawOrNot(-1, 152,false); //灯标
	m_globalViewCtrl.SetLayerDrawOrNot(-1, 85,false); //灯标
	m_globalViewCtrl.SetLayerDrawOrNot(-1, 158,false); //灯标
	m_globalViewCtrl.SetBackgroundColor(RGB(114,114,114));
	m_bInit = bInitResult;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CGlobalView::OnPaint()
{
	CPaintDC dc(this); 
	if(m_bInit)
	{
		HDC hdc = ::GetDC(m_hWnd);   
		m_globalViewCtrl.DrawMapsInScreen((long)hdc);  

		HPEN hPen = NULL;		 
		hPen = (HPEN) CreatePen( PS_SOLID, 2, RGB(0, 0, 255)); 
		HPEN hOldPen = (HPEN) SelectObject(hdc, hPen); 

		CPoint PolyPoints[5];
		PolyPoints[0] = m_rectScrnView.TopLeft();
		PolyPoints[1] = CPoint(m_rectScrnView.right, m_rectScrnView.top);
		PolyPoints[2] = m_rectScrnView.BottomRight();
		PolyPoints[3] = CPoint(m_rectScrnView.left, m_rectScrnView.bottom);
		PolyPoints[4] = m_rectScrnView.TopLeft();
		::MoveToEx(hdc, PolyPoints[0].x, PolyPoints[0].y, NULL);
		::LineTo(hdc, PolyPoints[1].x, PolyPoints[1].y);
		::LineTo(hdc, PolyPoints[2].x, PolyPoints[2].y);
		::LineTo(hdc, PolyPoints[3].x, PolyPoints[3].y);
		::LineTo(hdc, PolyPoints[4].x, PolyPoints[4].y); 

		::ReleaseDC(m_hWnd, hdc);  
	}
}

BOOL CGlobalView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;//CDialog::OnEraseBkgnd(pDC);
}
 

void CGlobalView::ReSetViewPosion()
{
	if(m_bOpend == false)
	{
		return;
	} 
	int centScrnX = m_mainCtrl->GetDrawerScreenWidth() / 2;
	int centScrnY = m_mainCtrl->GetDrawerScreenHeight() / 2;
	long retGeoPoX, retGeoPoY;
	m_mainCtrl->GetGeoPoFromEncScrnPo(centScrnX, centScrnY, &retGeoPoX, &retGeoPoY);
	int mainMapScale = (int)m_mainCtrl->GetCurrentScale();
	m_globalViewCtrl.CenterMap(retGeoPoX, retGeoPoY);
	m_globalViewCtrl.SetCurrentScale(mainMapScale << 3);
	

	M_POINT leftTopGeoPo, RightButtomGeoPo;
	m_mainCtrl->GetGeoPoFromScrnPo(0, 0, (long*)&leftTopGeoPo.x, (long*)&leftTopGeoPo.y);
	m_mainCtrl->GetGeoPoFromScrnPo(m_mainViewSize.cx, m_mainViewSize.cy, (long*)&RightButtomGeoPo.x, (long*)&RightButtomGeoPo.y);
	M_POINT leftTopScrnPo, rightButtomScrnPo;
	m_globalViewCtrl.GetScrnPoFromGeoPo(leftTopGeoPo.x, leftTopGeoPo.y, (long*)&leftTopScrnPo.x, (long*)&leftTopScrnPo.y);
	m_globalViewCtrl.GetScrnPoFromGeoPo(RightButtomGeoPo.x, RightButtomGeoPo.y, (long*)&rightButtomScrnPo.x, (long*)&rightButtomScrnPo.y);
	m_rectScrnView = CRect(CPoint(leftTopScrnPo.x, leftTopScrnPo.y), CPoint(rightButtomScrnPo.x, rightButtomScrnPo.y));
	Invalidate(FALSE);
}

void CGlobalView::OnMainViewReSize(int mainViewWidth, int mainViewHeight)
{ 
	//if(mainViewWidth == 0 || mainViewHeight == 0)
	//{ 
		CRect mainViewRect;
		m_mainView->GetWindowRect(mainViewRect);
		mainViewWidth = mainViewRect.right - mainViewRect.left;
		mainViewHeight = mainViewRect.bottom - mainViewRect.top; 
	//} 
	CRect myRect;
	this->GetWindowRect(myRect);
	int width = myRect.right - myRect.left;
	int hight = myRect.bottom - myRect.top;  
	int newLeft = mainViewRect.right - width;
	int newTop = mainViewRect.bottom - hight; 
	this->SetWindowPos(NULL, newLeft, newTop, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	m_mainViewSize = CSize(mainViewWidth, mainViewHeight);
}
 
void CGlobalView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->SetCapture();
	m_bDragingMap = true;
	m_mouseDragFirstPo = CPoint(point.x, point.y);
	CDialog::OnLButtonDown(nFlags, point);
}

void CGlobalView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ReleaseCapture();
	if(m_bDragingMap)
	{ 
		m_globalViewCtrl.SetMapMoreOffset(point.x - m_mouseDragFirstPo.x, point.y - m_mouseDragFirstPo.y); 
		m_bDragingMap = false;
		Invalidate(FALSE);
		long centerGeoPoX, centerGeoPoY;
		long centerScrnPoX = m_globalViewCtrl.GetDrawerScreenWidth() / 2;
		long centerScrnPoY = m_globalViewCtrl.GetDrawerScreenHeight() / 2;
		m_globalViewCtrl.GetGeoPoFromEncScrnPo(centerScrnPoX, centerScrnPoY, &centerGeoPoX, &centerGeoPoY);
		m_mainCtrl->CenterMap(centerGeoPoX, centerGeoPoY);
		m_mainView->Invalidate(FALSE);
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CGlobalView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_bDragingMap)
	{
		if (abs(point.x - m_mouseDragFirstPo.x)== 0 &&(abs(point.y - m_mouseDragFirstPo.y)== 0))
		{
			return;
		}
		m_globalViewCtrl.SetMapMoreOffset(point.x - m_mouseDragFirstPo.x, point.y - m_mouseDragFirstPo.y);
		m_mouseDragFirstPo = point;
		Invalidate(FALSE);
		/*SetCursor(LoadCursor(NULL, IDC_HAND));  
		HDC hdc = ::GetDC(m_hWnd); 
		m_globalViewCtrl.DrawDragingMap((long)hdc, point.x, point.y, m_mouseDragFirstPo.x, m_mouseDragFirstPo.y);  		
		
		HPEN hPen = NULL;		 
		hPen = (HPEN) CreatePen( PS_SOLID, 2, RGB(0, 255, 0)); 
		HPEN hOldPen = (HPEN) SelectObject(hdc, hPen); 
		 
		CPoint PolyPoints[5];
		PolyPoints[0] = m_rectScrnView.TopLeft();
		PolyPoints[1] = CPoint(m_rectScrnView.right, m_rectScrnView.top);
		PolyPoints[2] = m_rectScrnView.BottomRight();
		PolyPoints[3] = CPoint(m_rectScrnView.left, m_rectScrnView.bottom);
		PolyPoints[4] = m_rectScrnView.TopLeft();
		::MoveToEx(hdc, PolyPoints[0].x, PolyPoints[0].y, NULL);
		::LineTo(hdc, PolyPoints[1].x, PolyPoints[1].y);
		::LineTo(hdc, PolyPoints[2].x, PolyPoints[2].y);
		::LineTo(hdc, PolyPoints[3].x, PolyPoints[3].y);
		::LineTo(hdc, PolyPoints[4].x, PolyPoints[4].y);
		 
		::ReleaseDC(m_hWnd, hdc); */
	}
	CDialog::OnMouseMove(nFlags, point);
}
