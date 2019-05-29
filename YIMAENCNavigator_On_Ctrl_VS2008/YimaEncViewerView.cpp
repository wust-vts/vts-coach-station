// YimaEncViewerView.cpp : implementation of the CYimaEncViewerView class
//

#include "stdafx.h"
#include "YimaEncViewer.h" 
#include "resource.h" 
#include "winuser.h"
#include <afxwin.h>  

#include "MainFrm.h"
#include "YimaEncViewerDoc.h" 
#include "YimaEncViewerView.h" 
#include "SelectedGeoObjectsDlg.h"
#include "CenterRotateMapDlg.h"
#include "NavigationDlgBar.h"
#include "RouteEditDlg.h"
#include "GeoObjectInfoDlg.h"
#include "QueryDialog.h"
#include "LibPointStylesViewDlg.h"
#include "LibLineStylesViewDlg.h"
#include "LibFaceStylesViewDlg.h"
#include "PrintTitleSetingDlg.h" 
#include "SetS63DeviceIDDialog.h"
#include "NewMapDlg.h"
#include "WaterColorSettingDlg.h"
#include "SetAttenTimes.h"
#include "math.h"

#ifndef IDC_HAND
#define IDC_HAND MAKEINTRESOURCE(32649)
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PI 3.14159265
#define MOUSEMOVE_SYSMBOL 38

#define MAP_OPERATION_PANEL_LEFT 50
#define MAP_OPERATION_PANEL_TOP 30

#define RGB_EBL_LINE RGB(255, 255, 0)
#define RGB_DRAGING_WAY_POINT RGB(255, 255, 0)

int nRadarFrameNumber = 0;

NetToODU* m_pNetToODU = new NetToODU();
list<ODU> oduList;		//ODU信息链表
list<Radar> radarList;	//Radar信息链表
Radar curSelectRadar;	//当前选中的Radar信息

/////////////////////////////////////////////////////////////////////////////
// CYimaEncViewerView

IMPLEMENT_DYNCREATE(CYimaEncViewerView, CView)

BEGIN_MESSAGE_MAP(CYimaEncViewerView, CView)
	//{{AFX_MSG_MAP(CYimaEncViewerView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_COMMAND(ID_ZOOM_IN, OnZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, OnZoomOut)
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MOVE_DOWN, OnMoveDown)
	ON_COMMAND(ID_MOVE_LEFT, OnMoveLeft)
	ON_COMMAND(ID_MOVE_RIGHT, OnMoveRight)
	ON_COMMAND(ID_MOVE_UP, OnMoveUp)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_AREA_ZOOM_IN, OnAreaZoomIn)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_CENTER_ROTATE_MAP, OnCenterRotateMap)
	ON_COMMAND(ID_ADD_WAYPOINT, OnAddWaypoint)
	ON_COMMAND(ID_ADD_ROUTE, OnAddRoute)
	ON_COMMAND(ID_DEL_WAYPOINT, OnDelWaypoint)
	ON_COMMAND(ID_DEL_ROUTE, OnDelRoute)
	ON_COMMAND(ID_DIRECT_EDIT_ROUTE, OnDirectEditRoute)
	ON_COMMAND(ID_EBL_LINE, OnEblLine)
	ON_COMMAND(ID_DEL_OBJECT, OnDelObject)
	ON_WM_TIMER()
	ON_WM_CHAR()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_QUERY, OnQuery)
	ON_COMMAND(ID_DEL_LINE_POINT, OnDelLinePoint)
	ON_COMMAND(ID_SET_FIRST_LAYER_NOT_DRAW, OnSetFirstLayerNotDraw)
	ON_COMMAND(ID_ADD_CURVE_LINE, OnAddCurveLine)
	ON_COMMAND(ID_ADD_CLOSED_CURVE_LINE, OnAddClosedCurveLine)
	ON_COMMAND(ID_ADD_SINGLE_ARROW, OnAddSingleArrow)
	ON_COMMAND(ID_ADD_DOUBLE_ARROW, OnAddDoubleArrow)
	ON_COMMAND(ID_ADD_CURVE_WITH_ARROW, OnAddCurveWithArrow)
	ON_COMMAND(ID_ADD_CURVE_WITH_BOTH_ARROW, OnAddCurveWithBothArrow)
	ON_COMMAND(ID_ADD_THREE_ARROW, OnAddThreeArrow)
	ON_COMMAND(ID_UNDO, OnUndo)
	ON_COMMAND(ID_REDO, OnRedo)
	ON_COMMAND(ID_FILE_PRINT, OnMyFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnMyFilePrintPreview)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_AREA_SELECT, OnAreaSelect)
	ON_COMMAND(ID_ROUTE_SAFE_DETECT, OnRouteSafeDetect)
	ON_COMMAND(ID_COPY_OBJECT, OnCopyObject)
	ON_COMMAND(ID_ROTATE_CLOCKWISE, OnRotateClockwise)
	ON_COMMAND(ID_ROTATE_ANTICLOCKWISE, OnRotateAnticlockwise)
	//}}AFX_MSG_MAP
// Standard printing commands		
//ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
//ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
ON_COMMAND(ID_NO_BLANK_MOUSE_DRAG, &CYimaEncViewerView::OnNoBlankMouseDrag)
ON_COMMAND(ID_WHEEL_ZOOM_BY_MOUSE_POSI, &CYimaEncViewerView::OnWheelZoomByMousePosi)
ON_COMMAND(ID_HOLLOW_MAP_EFFECT, &CYimaEncViewerView::OnHollowMapEffect)
ON_COMMAND(ID_DELAY_MAP_EFFECT, &CYimaEncViewerView::OnDelayMapEffect)
ON_COMMAND(ID_CANCEL_MAP_EFFECT, &CYimaEncViewerView::OnCancelMapEffect)
ON_COMMAND(ID_OBJ_ZOOM_OUT, &CYimaEncViewerView::OnObjZoomOut)
ON_COMMAND(ID_OBJ_ZOOM_IN, &CYimaEncViewerView::OnObjZoomIn)
ON_COMMAND(ID_ADD_NEW_MAP_CTRL, &CYimaEncViewerView::OnAddNewMapCtrl)
ON_COMMAND(ID_GLOBAL_VIEW, &CYimaEncViewerView::OnGlobalView)
ON_COMMAND(ID_WATER_COLOR_SETTING, &CYimaEncViewerView::OnWaterColorSetting)
ON_COMMAND(ID_MEASURE_AREA, &CYimaEncViewerView::OnMeasureArea)
ON_COMMAND(ID_CLOSED_LINE_WARN, &CYimaEncViewerView::OnClosedLineWarn)
ON_COMMAND(ID_SHOW_REFREASH_TIME, &CYimaEncViewerView::OnShowRefreashTime)
ON_COMMAND(ID_RUNTIME_DRAGMAP, &CYimaEncViewerView::OnRuntimeDragmap)
ON_COMMAND(ID_ANIMATION_SCALE, &CYimaEncViewerView::OnAnimationScale)
ON_COMMAND(ID_ADD_RADAR, &CYimaEncViewerView::OnAddRadar)
ON_COMMAND(ID_SET_RADAR, &CYimaEncViewerView::OnSetRadar)
ON_COMMAND(ID_DELETE_RADAR, &CYimaEncViewerView::OnDeleteRadar)
ON_COMMAND(ID_MODIFY_RADAR, &CYimaEncViewerView::OnModifyRadar)
ON_COMMAND(ID_RADAR_PROPERTY, &CYimaEncViewerView::OnRadarProperty)
ON_COMMAND(ID_MAP_HAND_ROAM, &CYimaEncViewerView::OnMapHandRoam)
ON_COMMAND(ID_SHIP_START, &CYimaEncViewerView::OnShipStart)
ON_COMMAND(ID_SHIP_STOP, &CYimaEncViewerView::OnShipStop)
ON_UPDATE_COMMAND_UI(ID_SHIP_START, &CYimaEncViewerView::OnUpdateShipStart)
ON_UPDATE_COMMAND_UI(ID_SHIP_STOP, &CYimaEncViewerView::OnUpdateShipStop)
ON_COMMAND(ID_LOAD_ROUTEDATA, &CYimaEncViewerView::OnLoadRoutedata)
END_MESSAGE_MAP()

/* YIMAENC COMMENT: 注意，
在非对话框程序中，YimaEnc Control 的消息响应无法通过Class Wizard自动
建立, 需手工增加消息映射宏 BEGIN_EVENTSINK_MAP 等声明 */
BEGIN_EVENTSINK_MAP(CYimaEncViewerView, CView)
	ON_EVENT(CYimaEncViewerView, ID_YIMAENC_CTRL, 1, OnAfterDrawMapYimaEncCtrl, VTS_NONE)
	ON_EVENT(CYimaEncViewerView, ID_YIMAENC_CTRL, 2, OnDrawRadar, VTS_NONE)
	ON_EVENT(CYimaEncViewerView, ID_YIMAENC_CTRL, 3, OnAfterDrawMarineMapYimaEncCtrl, VTS_NONE)
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYimaEncViewerView construction/destruction

CYimaEncViewerView::CYimaEncViewerView()
{
	// TODO: add construction code here
	m_pYimaEncCtrl = NULL;
	m_curSelectedObjCount = 0;
	m_nEditingLinePointCount = 0;
	m_bHasPressedDragStartPo = false;
	m_bHasDrawDragFirstPo = false;

	m_bOnRouteEditMode = false;
	m_nEditingWayPointID = 0;
	m_nEditingRouteID = 0;

	m_iEditingPointPosOnEditingLine = -1;

	m_iEditingUserMapLayerNum = 0;	//初始化为-1

	m_iMouseStoppedTimerCount = 0;

	m_addingSpecialLineType = NO_SPECIAL_TYPE;

	SetOperation(NO_OPERATION);

	m_nTimerStep = 5;

	m_highlightDepthLowerLimit = 0;
	m_highlightDepthUpLimit = 0;

	m_bMouseZoomModeOrStdZoomMode = true;
	m_bUseMouseDragBufferMode = false;
	m_ScrnOffset = M_POINT(0, 0);
	m_globalView = NULL;
	m_icurEditPos = 0;
	m_ClosedLineTestObj.layerPos = -1;
	m_usedMSecond = 10;
	m_bShowRefreashTime = true;
	m_bRuntimeDragMap = false;
	m_bAnimationScale = false;
	bMouseWheelState = false;
	m_startFillTrans = 100;
	//m_arrColorAttenuationObj = new std::list<M_COLOR_ATTENUATION>(); //记录下所有颜色衰减的物标信息

	m_bShipStart = false;
	sendAisEvent = NULL;
	ipCon = new AisIPConfig(L"AisIPconfig.txt");
}

CYimaEncViewerView::~CYimaEncViewerView()
{
}

BOOL CYimaEncViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CYimaEncViewerView drawing

void CYimaEncViewerView::OnDraw(CDC* pDC)
{
	CYimaEncViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (m_iMouseStoppedTimerCount == 2)
	{
		return;
	}

	RefreshScreenMap();

	if (IsOnOperation(ADD_ROUTE))
	{
		DrawEditingLineBeforeFinish();
	}

	if (IsOnOperation(DRAW_EBL) && m_bHasPressedDragStartPo)
	{
		DrawCurrentEblLine(pDC->m_hDC,
			m_mouseDragFirstPo, m_mouseMoveCurrentPo, NULL);
	}
	long curMapEffect = m_pYimaEncCtrl->GetMapEffect();
	if (curMapEffect != EFFECT_NONE)
	{
		long effectGeoPoX = 0, effectGeoPoY = 0;
		float fradiusByMeter = 0;
		m_pYimaEncCtrl->GetMapEffectParameter(&effectGeoPoX, &effectGeoPoY, &fradiusByMeter);
		M_POINT centerScrnPo;
		int iScrnRadius;
		if (curMapEffect == EFFECT_HOLLOW)
		{
			long retScrnPoX1 = 0, retScrnPoY1 = 0;
			long retScrnPoX2 = 0, retScrnPoY2 = 0;
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(effectGeoPoX, effectGeoPoY - 100, &retScrnPoX1, &retScrnPoY1);
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(effectGeoPoX, effectGeoPoY + 100, &retScrnPoX2, &retScrnPoY2);
			centerScrnPo.y = (long)((retScrnPoY1 + retScrnPoY2) / 2);
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(effectGeoPoX - 100, effectGeoPoY, &retScrnPoX1, &retScrnPoY1);
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(effectGeoPoX + 100, effectGeoPoY, &retScrnPoX2, &retScrnPoY2);
			centerScrnPo.x = (long)((retScrnPoX1 + retScrnPoX2) / 2);
			iScrnRadius = sqrt(pow(retScrnPoX1 - retScrnPoX2, 2.0) + pow(retScrnPoY1 - retScrnPoY2, 2.0)) / 2;
		}
		else if (curMapEffect == EFFECT_DELAY)
		{
			long retScrnPoX = 0, retScrnPoY = 0;
			m_pYimaEncCtrl->SetMapEffectRadius(0);
			iScrnRadius = m_pYimaEncCtrl->GetScrnLenFromGeoLen(fradiusByMeter * 1000);
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(effectGeoPoX, effectGeoPoY, &retScrnPoX, &retScrnPoY);
			centerScrnPo = M_POINT(retScrnPoX, retScrnPoY);
			m_pYimaEncCtrl->SetMapEffectRadius(fradiusByMeter);
		}

		HDC hdc = pDC->m_hDC;
		SetROP2(hdc, R2_XORPEN);
		HPEN hPen = (HPEN)CreatePen(PS_SOLID, 2, RGB_EBL_LINE);
		HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Ellipse(hdc, centerScrnPo.x - iScrnRadius, centerScrnPo.y - iScrnRadius, centerScrnPo.x + iScrnRadius, centerScrnPo.y + iScrnRadius);
		SetROP2(hdc, R2_COPYPEN);
		SelectObject(hdc, hOldPen);
		SelectObject(hdc, hOldBrush);
		DeleteObject(hPen);
	}


}

/*** 悬浮海图操作面板 ***/
void CYimaEncViewerView::DrawMapOperationPanel(HDC hScrnDC)
{
	/* IDB_BITMAP1 为面板的皮肤图片, 在“资源编辑”的绘图工具里可以编辑，
		也可以在画图板上编辑好copy到“资源编辑”工具中  */
	HBITMAP hbmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
	/* IDB_BITMAP2 为面板皮肤图片对应的“掩图”图片, 有了“掩图”图片，就可以实现
		透明贴图的效果，“掩图”图片制作：把皮肤图片的背景部分(即需要被透明掉的部分)凃“纯黑”，
		有内容的部分(即需要显示的部分)涂“纯白” */
	HBITMAP hMaskbmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
	HDC	hImageDC = CreateCompatibleDC(hScrnDC);
	SelectObject(hImageDC, hMaskbmp);
	BitBlt(hScrnDC, MAP_OPERATION_PANEL_LEFT, MAP_OPERATION_PANEL_TOP,
		102, 163, hImageDC, 0, 0, SRCPAINT); //102 和 163 分别为 皮肤图片 的宽度和高度
	SelectObject(hImageDC, hbmp);
	BitBlt(hScrnDC, MAP_OPERATION_PANEL_LEFT, MAP_OPERATION_PANEL_TOP,
		102, 163, hImageDC, 0, 0, SRCAND);
	DeleteDC(hImageDC);
	DeleteObject(hbmp);
	DeleteObject(hMaskbmp);
}

void CYimaEncViewerView::RefreshScreenMap()
{
	//YIMAENC COMMENT:  YimaEnc Control interoped below!
	m_beforeRefesh = GetTickCount();
	if (m_pYimaEncCtrl != NULL)
	{
		HDC hdc = ::GetDC(m_hWnd); //test2013.02.03
		m_pYimaEncCtrl->DrawMapsInScreen((long)hdc);
		//DrawMapOperationPanel(hdc); //显示悬浮海图操作面板

		::ReleaseDC(m_hWnd, hdc);
	}
	/*DWORD usedMSecond = GetTickCount() - m_beforeRefesh;
	if (usedMSecond > 10)
	{
		m_usedMSecond = usedMSecond; //大于10毫秒为有效耗时
	}*/
}

bool CYimaEncViewerView::IsOnDragingObjectOperation()
{
	return IsOnOperation(HAND_ROAM) || IsOnOperation(DRAG_EDITING_OBJECT) || IsOnOperation(ADD_LINE_OBJECT_MOUSEMOVING);
}

HDC hDynamicDC = NULL;
//随当前鼠标位置绘制编辑中的动态物标对象
void CYimaEncViewerView::DrawDynamicScreenMap(M_POINT mousePoint)
{
	//YIMAENC COMMENT:  YimaEnc Control interoped below!
	if (m_pYimaEncCtrl != NULL)
	{
		m_pYimaEncCtrl->SetDrawerPastingByMemScrn(true); /* 设置主海图绘制器模式为贴图模式, 这种模式下下面的DrawMapsInScreen()接口并不真正绘制海图,
		   而是直接将上一帧绘制好的海图直接贴到屏幕上(但不包含绘制的动态物标，即调用接口 tmSetObjectDynamicObjectOrNot() 将其
		   设为动态物标的物标), 由于直接贴图, 故速度快, 可以满足 MOUSE MOVE消息的快速响应 	*/
		   //m_pYimaEncCtrl->DrawMapsInScreen((long)hDynamicDC); //重贴上一帧的静态海图, 从而擦除 DrawDynamicScreenMap() 上一次绘制的动态内容

		long geoPoX, geoPoY;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(mousePoint.x, mousePoint.y, &geoPoX, &geoPoY);

		int objLayerPos = m_editingUserMapObjPos.layerPos;
		int objInLyrPos = m_editingUserMapObjPos.innerLayerObjectPos;

		int geoType = m_pYimaEncCtrl->tmGetGeoObjectType(objLayerPos, objInLyrPos);

		if (geoType == TYPE_POINT)
		{
			m_pYimaEncCtrl->tmSetPointObjectCoor(objLayerPos, objInLyrPos, geoPoX, geoPoY); //如果是点物标, 则直接设置其坐标即移动它 
		}
		else
		{
			if (geoType == TYPE_LINE || geoType == TYPE_FACE)
			{
				m_pYimaEncCtrl->SetIfUseGDIPlus(true);
				if (m_iEditingPointPosOnEditingLine == -1)	//如果编辑节点序号为空, 则认为在拖动物标, 即拖动物标的中心点来移动某个物标对象
				{
					if (IsOnOperation(DRAG_EDITING_OBJECT))
					{
						m_pYimaEncCtrl->tmMoveObjectInScrn(objLayerPos, objInLyrPos, mousePoint.x - m_ScrnOffset.x, mousePoint.y - m_ScrnOffset.y);
					}
				}
				else	//设置物标某个节点的位置
				{
					if (m_addingSpecialLineType == SINGLE_ARROW_LN_TYPE)
					{ //单箭头物标比较复杂特殊, 动态添加物标时不能直接由 tmMoveOnePointOfLineObject() 接口来实现动态效果
						BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * m_nEditingLinePointCount);
						memcpy(strLinePoints, m_editingLineGeoPoints, sizeof(M_POINT) * m_nEditingLinePointCount);
						m_editingLineGeoPoints[m_nEditingLinePointCount - 1] = M_POINT(geoPoX, geoPoY);
						m_pYimaEncCtrl->tmSetLineObjectCoors(objLayerPos, objInLyrPos, m_nEditingLinePointCount, &strLinePoints);
						m_pYimaEncCtrl->tmSetObjectAsSpecialType(objLayerPos, objInLyrPos, m_addingSpecialLineType);
						SysFreeString(strLinePoints);
					}
					else
					{ //其它图形直接由 tmMoveOnePointOfLineObject() 接口来实现动态效果
						m_pYimaEncCtrl->tmMoveOnePointOfLineObject(objLayerPos, objInLyrPos, m_iEditingPointPosOnEditingLine,
							geoPoX, geoPoY);
					}

					m_pYimaEncCtrl->SetIfUseGDIPlus(false);
				}
			}
		}

		m_pYimaEncCtrl->tmSetObjectDynamicObjectOrNot(objLayerPos, objInLyrPos, true);
		HDC hScrnDC = ::GetDC(m_hWnd);
		m_pYimaEncCtrl->DrawMapsInScreen((long)hScrnDC);
		m_pYimaEncCtrl->SetDrawerPastingByMemScrn(false);
		::ReleaseDC(m_hWnd, hScrnDC);
		m_pYimaEncCtrl->tmSetObjectDynamicObjectOrNot(objLayerPos, objInLyrPos, false);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CYimaEncViewerView printing

BOOL CYimaEncViewerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	pInfo->SetMaxPage(1);
	return DoPreparePrinting(pInfo);
}

void CYimaEncViewerView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing  
}

void CYimaEncViewerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CYimaEncViewerView diagnostics

#ifdef _DEBUG
void CYimaEncViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CYimaEncViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CYimaEncViewerDoc* CYimaEncViewerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CYimaEncViewerDoc)));
	return (CYimaEncViewerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CYimaEncViewerView message handlers

int CYimaEncViewerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here  

	return 0;
}

BOOL CYimaEncViewerView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//YIMAENC COMMENT: 注意!! 注销掉下面继承的方法才可克服屏幕闪烁
	//return CView::OnEraseBkgnd(pDC);

	return true;
}

void CYimaEncViewerView::ResizeMapScrn(bool bUseDragBufferScrnMode, float bufferScrnSizeRatio)
{
	if (m_pYimaEncCtrl != NULL)
	{
		CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;

		RECT clientRect;
		GetClientRect(&clientRect);

		int oldDrawerScrnWidth = m_pYimaEncCtrl->GetDrawerScreenWidth();
		int oldDrawerScrnHeight = m_pYimaEncCtrl->GetDrawerScreenHeight();

		M_POINT oldCenterGeoPoint;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(
			oldDrawerScrnWidth / 2, oldDrawerScrnHeight / 2,
			(long*)&oldCenterGeoPoint.x, (long*)&oldCenterGeoPoint.y);

		int nowScrnWidth = clientRect.right - clientRect.left;
		int nowScrnHeight = clientRect.bottom - clientRect.top;
		if (bUseDragBufferScrnMode)
		{
			pFrame->m_expandWidth = nowScrnWidth / 2;
			pFrame->m_expandHeight = nowScrnHeight / 2;
		}
		else
		{
			pFrame->m_expandWidth = 0;
			pFrame->m_expandHeight = 0;
		}

		m_pYimaEncCtrl->SetDrawExpandPixel(pFrame->m_expandWidth, pFrame->m_expandHeight);
		m_pYimaEncCtrl->RefreshDrawer((long)m_hWnd, nowScrnWidth, nowScrnHeight, 0, 0);

		//以下为了实现保持显示海图区域和中心点不变
		if (nowScrnWidth > 50)
		{
			m_pYimaEncCtrl->SetCurrentScale(m_pYimaEncCtrl->GetCurrentScale() * (float)oldDrawerScrnWidth / nowScrnWidth);
			m_pYimaEncCtrl->CenterMap(oldCenterGeoPoint.x, oldCenterGeoPoint.y);
		}

		char chMsg[255];
		memset(chMsg, '\0', 255);
		pFrame->RefreshNavigationDlgBar(chMsg);


		RefreshScaleStatusBar();
		if (strlen(chMsg) > 0)
		{
			AfxMessageBox(chMsg);
		}
	}
}

void CYimaEncViewerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	//YIMAENC COMMENT:  YimaEnc Control interoped below!

	if (m_pYimaEncCtrl != NULL)
	{
		RECT clientRect;
		GetClientRect(&clientRect);

		int oldDrawerScrnWidth = m_pYimaEncCtrl->GetDrawerScreenWidth();
		int oldDrawerScrnHeight = m_pYimaEncCtrl->GetDrawerScreenHeight();

		M_POINT oldCenterGeoPoint;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(
			oldDrawerScrnWidth / 2, oldDrawerScrnHeight / 2,
			(long*)&oldCenterGeoPoint.x, (long*)&oldCenterGeoPoint.y);

		int nowScrnWidth = clientRect.right - clientRect.left;
		int nowScrnHeight = clientRect.bottom - clientRect.top;

		// RefreshDrawer 在初始化屏幕 或 改变海图屏幕大小时应该被调用			
		m_pYimaEncCtrl->RefreshDrawer((long)m_hWnd, nowScrnWidth, nowScrnHeight, 0, 0);

		//以下为了实现保持显示海图区域和中心点不变
		if (nowScrnWidth > 50)
		{
			m_pYimaEncCtrl->SetCurrentScale(m_pYimaEncCtrl->GetCurrentScale() * (float)oldDrawerScrnWidth / nowScrnWidth);
			if (m_pYimaEncCtrl->GetMapEffect() == EFFECT_NONE)
			{
				m_pYimaEncCtrl->CenterMap(oldCenterGeoPoint.x, oldCenterGeoPoint.y);
			}
		}

		CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		char chMsg[255];
		memset(chMsg, '\0', 255);
		pFrame->RefreshNavigationDlgBar(chMsg);

		RefreshScaleStatusBar();

		if (m_globalView != NULL)
		{
			m_globalView->OnMainViewReSize(nowScrnWidth, nowScrnHeight);
			m_globalView->ReSetViewPosion();
		}
		if (strlen(chMsg) > 0)
		{
			AfxMessageBox(chMsg);
		}
	}
}

#define SCALE_ZOOM_STEP_RATIO 1.5
void CYimaEncViewerView::OnZoomIn()
{
	//YIMAENC COMMENT:  YimaEnc Control interoped! 

	m_pYimaEncCtrl->SetCurrentScale(
		m_pYimaEncCtrl->GetCurrentScale() / SCALE_ZOOM_STEP_RATIO);

	RefreshScaleStatusBar();

	Invalidate();
}

void CYimaEncViewerView::OnZoomOut()
{
	//YIMAENC COMMENT:  YimaEnc Control interoped! 

	m_pYimaEncCtrl->SetCurrentScale(
		m_pYimaEncCtrl->GetCurrentScale() * SCALE_ZOOM_STEP_RATIO);

	RefreshScaleStatusBar();

	Invalidate();
}

/* YIMAENC COMMENT: 注意,
	因为CYimaEncViewerView 的 OnSize 在CMainFrame的OnCreate 之前调用，
	所以在第一次 OnSize 函数中 m_pYimaEncCtrl 不能被初始化，所以选择在
	OnSetFocus 时初始化 */
void CYimaEncViewerView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	//YIMAENC COMMENT:  YimaEnc Control interoped!
	if (m_pYimaEncCtrl == NULL)
	{
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);

		if (pFrame != NULL)
		{
			m_pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

			if (!m_pYimaEncCtrl->VerifyUserLicense())
			{
				AfxMessageBox("License file invalid!");
				return;
			}

			if (!m_pYimaEncCtrl->VerifyUserLicense())
			{
				AfxMessageBox("License file invalid!");
				return;
			}

			RECT clientRect;
			GetClientRect(&clientRect);

			int scrnWidth = clientRect.right - clientRect.left;
			int scrnHeight = clientRect.bottom - clientRect.top;

			// RefreshDrawer 在初始化屏幕 或 改变海图屏幕大小时应该被调用  
			m_pYimaEncCtrl->RefreshDrawer((long)m_hWnd, scrnWidth, scrnHeight, 0, 0);
			m_pYimaEncCtrl->SetOwnShipShowSymbol(false, 5, true, 16, 5000000);
			m_pYimaEncCtrl->SetDrawOwnShipSpecialOptions(true, false, true, RGB(255, 0, 0));
			m_pYimaEncCtrl->SetShipTrackStyle(true, 0, true, RGB(255, 0, 0), 2, true, 4, RGB(0, 255, 0));
			//m_pYimaEncCtrl->SetBackgroundColor(0x00D8F4E1); // 0x00F6E6AC);

			bool bSetOnSafeDepthAutoDetect = false;
			if (bSetOnSafeDepthAutoDetect)
			{
				m_pYimaEncCtrl->SetIfUseSafeDepthLineDectect(bSetOnSafeDepthAutoDetect, bSetOnSafeDepthAutoDetect);
				AfxMessageBox("注意! 自动检测水深区功能开启!");
			}

			bool bIfShowOwnShipTrack = true;
			if (bIfShowOwnShipTrack)
			{
				m_pYimaEncCtrl->SetDrawShipOptions(true, true, false, false, 10, false, 1, 100, 50, 60);
				//倒数第2个参数“100”表示内存会存储最近100个当前航迹点；
				//最后1个参数“50”表示只显示内存中存储的100个点其中的50个点
			}
			else
			{
				m_pYimaEncCtrl->SetDrawShipOptions(true, false, false, false, 10, false, 1, 0, 0, 60);	//倒数第2个参数和最后1个参数都设成0, 则不存储和显示当前航迹点了		
			}

			bool bIfShowOtherVesselTrack = true;
			if (bIfShowOtherVesselTrack)
			{
				m_pYimaEncCtrl->SetDrawShipOptions(false, true, true, true, 10, true, 1, 500, 200, 60);
				//倒数第3个参数“500”表示内存会存储最近500个当前航迹点；
				//倒数第2个参数“200”表示只显示内存中存储的500个点其中的200个点
				//最后一个参数60，表示最多只显示60分钟的航迹；

			}
			else
			{
				m_pYimaEncCtrl->SetDrawShipOptions(false, true, true, true, 10, true, 1, 0, 0, 1);//倒数第2个参数和最后1个参数都设成0, 则不存储和显示当前航迹点了	
			}

			m_pYimaEncCtrl->FocusLibMap(0);

			BOOL bTwoOrFourShade = false;
			m_pYimaEncCtrl->SetDepthShadesMode(bTwoOrFourShade, 2, 10, 20);

			/************ 下面开始模拟本船沿第一条航线航行、添加多个AIS目标船沿其它航线航行 **********/
			//m_pYimaEncCtrl->AddRoutesFromFile(TEST_ROUTE_FILE_NAME); //从 TEST_ROUTE_FILE_NAME 文件中添加导入航线数据
			//
			//AIS_TYPE_ID stationTypeID = m_pYimaEncCtrl->AddAisType("station"); //添加AIS类型(AIS TYPE)
			//m_pYimaEncCtrl->SetAisTypeInfo(stationTypeID, _T("station"), false, 1, 1,false, 0, 2, 5000000, true,false, 200000, true);//设置该样式的显示风格

			//AIS_TYPE_ID stationTypeID2 = m_pYimaEncCtrl->AddAisType("station2"); //添加AIS类型(AIS TYPE)
			//m_pYimaEncCtrl->SetAisTypeInfo(stationTypeID2, _T("station2"),  false, 4, 1, false, 0, 6, 5000000, false,false, 200000, true);//设置该样式的显示风格


			//int routeCount = m_pYimaEncCtrl->GetRoutesCount();
			//if(routeCount > 0)
			//{
			//	pFrame->SetOwnShipStartOnRoute(1);//本船模拟在第一条航线上航行 

			//				

			//	for (int addVsNum = 0; addVsNum < routeCount - 1; addVsNum ++)//routeCount - 1; addVsNum ++)
			//	{//为第二条航线起的每条航线增加1个AIS对象, 让它们分别沿着这些航线航行
			//		 
			//			m_pYimaEncCtrl->AddOtherVessel(false, 0, 0, 90, 90, 90, 0, 0);

			//			CString strAddVslName;
			//			
			//			int mmsi = 4200010 + addVsNum;
			//			
			//			int myVsPos = m_pYimaEncCtrl->GetOtherVesselCount() - 1;
			//			
			//			strAddVslName.Format("Test AIS Target %d", myVsPos + 1); 
			//			
			//			m_pYimaEncCtrl->SetOtherVesselBasicInfo(myVsPos,
			//				100, 50, strAddVslName, mmsi, NULL, 0);  
			//			
			//			long shipNavRouteID = m_pYimaEncCtrl->GetRouteIDFromPos(addVsNum + 1);
			//			
			//			pFrame->m_nOtherVesselSelRouteIDs[myVsPos] = shipNavRouteID;
			//			
			//			//初始模拟航行的目标航路点在航线中的位置是1
			//			pFrame->m_nOtherVesselCurAimWpPos[myVsPos] = 1;
			//			
			//			//设置模拟航行的航速一个比一个快 
			//			pFrame->m_nOtherVesselSimulateSpeeds[myVsPos] = 5 * (addVsNum + 1);
			//			
			//			pFrame->SetOtherVesselStartOnRoute(myVsPos, 
			//				pFrame->m_nOtherVesselSelRouteIDs[myVsPos]);
			//			
			//			m_pYimaEncCtrl->SetOtherVesselShowColor(addVsNum, false, 
			//				RGB(addVsNum * 255 / (routeCount - 1), 0, 0), false, 
			//				RGB(addVsNum * 255 / (routeCount - 1), 0, 0));		   //此接口会彻底改变符号的颜色
			//			
			//			CString strVslText;
			//			strVslText.Format(_T("Vsl %d"), m_pYimaEncCtrl->GetOtherVesselID(addVsNum));
			//			m_pYimaEncCtrl->SetOtherVesselShowText(addVsNum, true, strVslText, true, 20, true, RGB(0, 0, 255)); 
			//			m_pYimaEncCtrl->SetShipTrackStyle(false, myVsPos, true, RGB(0, 0, 255), 2, true, 4, RGB(0, 255, 255));
			//			int curTypeId = addVsNum % 2 == 0 ? stationTypeID : stationTypeID2;
			//			m_pYimaEncCtrl->SetAisTargetType(m_pYimaEncCtrl->GetOtherVesselCount() - 1, stationTypeID);
			//	 
			//	}      
			//}
			/*int iShipId = m_pYimaEncCtrl->AddOtherVessel(false,1224000000, 315000000,30,30,30,10,10);
			if(pFrame->m_testDcpaShipId == 0)
			{
				pFrame->m_testDcpaShipId = iShipId;
			}
			int iShipPos = m_pYimaEncCtrl->GetOtherVesselPosOfID(iShipId);
			m_pYimaEncCtrl->SetOtherVesselBasicInfo(iShipPos,100,30,"避碰测试船舶", 5552888, NULL, 0);
			m_pYimaEncCtrl->SetAisTargetType(iShipPos, stationTypeID2);*/

			pFrame->RefreshNavBarRouteList();
			pFrame->RefreshOtherVesselList();
			SetTimer(1, 100, NULL); //动态提示框: 开启定时器判断鼠标停留时间 
			SetTimer(3, 20, NULL);//动画缩放，检测是否该刷新海图定时器
			SetTimer(10, 1000, NULL);//动画缩放，检测是否该刷新海图定时器

			//开启接收ODU登录线程
			pThread_receiveODU = AfxBeginThread(Thread_Receive_ODU, this);

			sendAisEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
			//发送AIS线程
			m_hSendAISThread = ::CreateThread(NULL, 0, SendAISThreadProc, this, 0, NULL);

			SetTimer(TIME_REFRESH_RADARLIST, 500, 0);
			SetTimer(TIME_ODU_PARSE, 3000, 0);
			SetTimer(TIME_SET_ODUCOUNT, 550, 0);
		}

		//test by tcf 2012.08.28
		//测试添加10w条船

		bool bTestHugeNumVessel = false;
		if (bTestHugeNumVessel)
		{
			int typeID = m_pYimaEncCtrl->AddAisType("ais"); //添加AIS类型(AIS TYPE)

			m_pYimaEncCtrl->SetAisTypeInfo(typeID, _T("ais"), false,
				4, 1, false, 0, 6, 500000, true, false, 50000, true);//设置该AIS 类型的显示风格

			for (int vslNum = 0; vslNum < 10; vslNum++)
			{
#define MAX_RAND_VAL 32767
				long vslGeoX = (105 + (float)(rand() % MAX_RAND_VAL) / MAX_RAND_VAL * 28) * UNI_GEO_COOR_MULTI_FACTOR;
				long vslGeoY = (3 + (float)(rand() % MAX_RAND_VAL) / MAX_RAND_VAL * 38) * UNI_GEO_COOR_MULTI_FACTOR;
				float head = (float)(rand() % MAX_RAND_VAL) / MAX_RAND_VAL * 360;
				m_pYimaEncCtrl->AddOtherVessel(false, vslGeoX, vslGeoY, head, 90, 90, 0, 0);
				m_pYimaEncCtrl->SetAisTargetType(m_pYimaEncCtrl->GetOtherVesselCount() - 1, typeID);
			}
		}

	}
}

UINT CYimaEncViewerView::ThreadFuncDraw(LPVOID lpParam)
{
	while (true)
	{
		CYimaEncViewerView *pThis = (CYimaEncViewerView *)lpParam;

		pThis->m_pYimaEncCtrl->GetLoadMapScaleFactor();
		Sleep(500);
	}

	return 0;
}

/* YIMAENC COMMENT: 注意，
在非对话框程序中，YimaEnc Control 的消息响应无法通过Class Wizard自动
建立, 需手工增加消息映射宏等声明 */
void CYimaEncViewerView::OnAfterDrawMarineMapYimaEncCtrl()
{
	bool bIfTestSelfDrawFunctions = false; //是否演示调用自由绘制函数

	if (bIfTestSelfDrawFunctions)
	{
		////////////测试代码////////////////////
		m_pYimaEncCtrl->SetCurrentPen(2, 0xff0000);
		m_pYimaEncCtrl->SetCurrentBrush(0x00ff000);
		m_pYimaEncCtrl->DrawLine(100, 200, 200, 200);

		int showPoCount = 3;
		BSTR strFacePoints = ::SysAllocStringLen(NULL,
			sizeof(M_POINT) * showPoCount);

		M_POINT polygonRgn1[] = { M_POINT(50, 50), M_POINT(300, 50), M_POINT(300, 300) };
		memcpy(strFacePoints, polygonRgn1, sizeof(M_POINT) * showPoCount);

		m_pYimaEncCtrl->FillPolygon(&strFacePoints, showPoCount, false, 100);

		::SysFreeString(strFacePoints);
	}
}

/* YIMAENC COMMENT: 注意，
在非对话框程序中，YimaEnc Control 的消息响应无法通过Class Wizard自动
建立, 需手工增加消息映射宏等声明 */
void CYimaEncViewerView::OnAfterDrawMapYimaEncCtrl()
{

	//m_pYimaEncCtrl->DrawPointWithLibSymbol(1, 100, 100, false, 0, 1);
	//CString str = L"ddd";
	//m_pYimaEncCtrl->TextOutAtPoint(str,200,200);
	int objNum = 0;
	for (objNum = 0; objNum < m_curSelectedObjCount; objNum++)
	{
		MEM_GEO_OBJ_POS objPos = m_curSelectedObjPoses[objNum];

		BSTR strObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));
		memcpy(strObjPos, &objPos, sizeof(MEM_GEO_OBJ_POS));

		bool bEditingTheObject = objPos.memMapPos == m_pYimaEncCtrl->GetMemMapCount() - 1;

		m_pYimaEncCtrl->HighLightSelectedObject(&strObjPos, RGB(255, 0, 0),
			RGB(0, 0, 255), 4, RGB(0, 0, 255), 30, false, bEditingTheObject,
			m_iEditingPointPosOnEditingLine);

		/* 在物标中心点显示拖拽符号，以方便用户进行拖曳物标操作
		if (bEditingTheObject)
		{
			//获取当前选中的物标的中心点 add by tcf 2011.05.08
			long left, right, top, bottom;
			m_pYimaEncCtrl->GetObjectGeoExtent(&strObjPos, &left, &right, &top, &bottom);
			long centerGeoX, centerGeoY, centerScrnX, centerScrnY;
			centerGeoX = ((double)left + right) / 2;
			centerGeoY = ((double)top + bottom) / 2;
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(centerGeoX, centerGeoY, &centerScrnX, &centerScrnY);
			m_pYimaEncCtrl->DrawPointWithLibSymbol(MOUSEMOVE_SYSMBOL, centerScrnX, centerScrnY, false, 0xff0000, 1);
		}
		*/

		SysFreeString(strObjPos);
	}
	if (m_icurEditPos > 0) //测面积
	{
		int poCount = m_icurEditPos + 1;
		M_POINT* arrScrnPo = new M_POINT[poCount];
		for (int i = 0; i < poCount; i++)
		{
			long retScrnPoX = 0, retScrnPoY = 0;
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(m_arrMeasureGeoPo[i].x, m_arrMeasureGeoPo[i].y, &retScrnPoX, &retScrnPoY);
			arrScrnPo[i].x = retScrnPoX;
			arrScrnPo[i].y = retScrnPoY;
		}
		BSTR bstrScrnPo = ::SysAllocStringLen(NULL, sizeof(M_POINT) * poCount);
		memcpy(bstrScrnPo, arrScrnPo, poCount * sizeof(M_POINT));
		if (poCount >= 3)
		{
			BSTR bstrGeoPo = ::SysAllocStringLen(NULL, sizeof(M_POINT) * poCount);
			memcpy(bstrGeoPo, &m_arrMeasureGeoPo, poCount * sizeof(M_POINT));
			float fAreaValue = (m_pYimaEncCtrl->GetAreaOfGeoRegion(poCount, &bstrGeoPo)) / 1000 / 1000;
			CString strEblInfo;
			strEblInfo.Format("面积%.3f平方千米", fAreaValue);
			::SysFreeString(bstrGeoPo);

			m_pYimaEncCtrl->SetCurrentBrush(RGB(125, 125, 125));
			m_pYimaEncCtrl->SetCurrentPen(2, RGB(0, 0, 255));
			m_pYimaEncCtrl->FillPolygon(&bstrScrnPo, poCount, true, 60);
			m_pYimaEncCtrl->TextOutAtPoint(strEblInfo, arrScrnPo[0].x, arrScrnPo[0].y);
		}
		else if (poCount == 2)
		{
			m_pYimaEncCtrl->DrawDashLine(&bstrScrnPo, poCount, 2, RGB(0, 0, 255), 15, 15);
		}

		::SysFreeString(bstrScrnPo);
		delete[] arrScrnPo;
	}

	bool bIfShowHighlightDepthArea = false; //是否显示高亮水深区
	if (bIfShowHighlightDepthArea)
	{
		if (m_highlightDepthUpLimit > 0)
		{
			MEM_GEO_OBJ_POS curHighlightDepthAreaObjs[SEL_OBJ_MAX_COUNT];
			int lyrPos = m_pYimaEncCtrl->GetLayerPosByToken(-1, "DEPARE");
			if (lyrPos == -1)
			{
				return;
			}

			int nHighlightDepthAreaObjCount = 0;

			int memMapCount = m_pYimaEncCtrl->GetMemMapCount();
			for (int memMapNum = 0; memMapNum < memMapCount; memMapNum++)
			{
				int objCount = m_pYimaEncCtrl->GetLayerObjectCountOfMap(memMapNum, lyrPos);

				for (int objNum = 0; objNum < objCount; objNum++)
				{
					BSTR retObjValString = ::SysAllocStringLen(NULL, 255);
					BSTR pBstrObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));

					MEM_GEO_OBJ_POS objMemPos = MEM_GEO_OBJ_POS(memMapNum, lyrPos, objNum);
					memcpy(pBstrObjPos, &objMemPos, sizeof(MEM_GEO_OBJ_POS));

					m_pYimaEncCtrl->GetObjectAttrString(&pBstrObjPos, 0, &retObjValString);
					CString strVal = retObjValString;
					float fMinDepth = atof(strVal);

					m_pYimaEncCtrl->GetObjectAttrString(&pBstrObjPos, 1, &retObjValString);
					strVal = retObjValString;
					float fMaxDepth = atof(strVal);

					if (fMinDepth >= m_highlightDepthLowerLimit && fMaxDepth <= m_highlightDepthUpLimit)
					{
						curHighlightDepthAreaObjs[nHighlightDepthAreaObjCount] = objMemPos;
						nHighlightDepthAreaObjCount++;
					}

					::SysFreeString(retObjValString);
					::SysFreeString(pBstrObjPos);
				}
			}

			m_pYimaEncCtrl->SetIfUseGDIPlus(true);
			for (objNum = 0; objNum < nHighlightDepthAreaObjCount; objNum++)
			{
				MEM_GEO_OBJ_POS objPos = curHighlightDepthAreaObjs[objNum];

				BSTR strObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));
				memcpy(strObjPos, &objPos, sizeof(MEM_GEO_OBJ_POS));

				bool bEditingTheObject = objPos.memMapPos == m_pYimaEncCtrl->GetMemMapCount() - 1;

				m_pYimaEncCtrl->HighLightSelectedObject(&strObjPos, 0, 0, 0, m_highlightDepthAreaColor, 50, false, false, -1);

				SysFreeString(strObjPos);
			}
			m_pYimaEncCtrl->SetIfUseGDIPlus(false);
		}
	}

	/******************** 以下代码测试自由绘制函数组 ***************************/
	bool bIfTestDrawFunctions = false;

	if (bIfTestDrawFunctions)
	{
		m_pYimaEncCtrl->SetCurrentPen(2, 0xff0000);
		m_pYimaEncCtrl->DrawLine(100, 200, 200, 200);
		m_pYimaEncCtrl->SetCurrentBrush(0x00ff00);

		M_POINT points[3];
		//M_POINT polygonRgn[20] = {
		//	M_POINT(210+150,200 +150),M_POINT(7+150,-37 +150),M_POINT(56+150,-48 +150),M_POINT(70+150,-52 +150),M_POINT(84+150,-62 +150),M_POINT(93+150,-70 +150),M_POINT(124+150,-104 +150),M_POINT(188+150,-123 +150),M_POINT(165+150,-116 +150),M_POINT(150+150,-109 +150),M_POINT(129+150,-95 +150),M_POINT(119+150,-84 +150),M_POINT(108+150,-74 +150),M_POINT(97+150,-59 +150),M_POINT(92+150,-50 +150),M_POINT(91+150,-38 +150),M_POINT(98+150,9 +150),M_POINT(107+150,48 +150),M_POINT(122+150,78 +150),M_POINT(143+150,108 +150)};

		/*
		M_POINT polygonRgn[47] = {	M_POINT(210.8+100, 200.6 +150),
		M_POINT(177.7+100, 200.6 +150),
		M_POINT(148.0+100, 167.0 +150),
		M_POINT(123.2+100, 126.7 +150),
		M_POINT(90.5+100, 79.4 +150),
		M_POINT(62.7+100, 50.9 +150),
		M_POINT(30.0+100, 34.1 +150),
		M_POINT(5.2+100, 28.2 +150),
		M_POINT(-25.4+100, 28.2 +150),
		M_POINT(-37.1+100, 29.8 +150),
		M_POINT(-37.4+100, 11.5 +150),
		M_POINT(-36.9+100, -34.4 +150),
		M_POINT(7.6+100, -37.3 +150),
		M_POINT(40.9+100, -44.2 +150),
		M_POINT(56.8+100, -48.2 +150),
		M_POINT(70.7+100, -52.6 +150),
		M_POINT(84.6+100, -62.1 +150),
		M_POINT(90.1+100, -66.6 +150),
		M_POINT(93.5+100, -70.3 +150),
		M_POINT(103.0+100, -83.2 +150),
		M_POINT(112.2+100, -94.0 +150),
		M_POINT(124.0+100, -104.8 +150),
		M_POINT(145.1+100, -116.2 +150),
		M_POINT(163.4+100, -125.0 +150),
		M_POINT(180.7+100, -129.4 +150),
		M_POINT(195.3+100, -132.8 +150),
		M_POINT(210.8+100, -134.8 +150),
		M_POINT(210.8+100, -126.0 +150),
		M_POINT(188.9+100, -123.7 +150),
		M_POINT(165.8+100, -116.9 +150),
		M_POINT(150.5+100, -109.1 +150),
		M_POINT(129.5+100, -95.6 +150),
		M_POINT(119.0+100, -84.7 +150),
		M_POINT(108.8+100, -74.4 +150),
		M_POINT(104.4+100, -68.7 +150),
		M_POINT(97.6+100, -59.6 +150),
		M_POINT(92.8+100, -50.1 +150),
		M_POINT(91.5+100, -38.7 +150),
		M_POINT(92.4+100, -30.8 +150),
		M_POINT(92.5+100, -30.7 +150),
		M_POINT(98.0+100, 9.9 +150),
		M_POINT(107.9+100, 48.4 +150),
		M_POINT(122.8+100, 78.5 +150),
		M_POINT(143.5+100, 108.0 +150),
		M_POINT(170.8+100, 134.6 +150),
		M_POINT(190.6+100, 145.9 +150),
		M_POINT(210.8+100, 153.8 +150)};
		*/

		//	M_POINT polygonRgn1[15] = {M_POINT(293 ,266 ),M_POINT(296 ,263 ),M_POINT(298 ,259 ),M_POINT(298 ,257 ),M_POINT(295 ,240 ),M_POINT(294 ,237 ),M_POINT(290 ,229 ),M_POINT(289 ,228 ),M_POINT(287 ,228 ),M_POINT(277 ,230 ),M_POINT(272 ,233 ),M_POINT(265 ,247 ),M_POINT(263 ,253 ),M_POINT(262 ,257 ),M_POINT(262 ,263 )};

		M_POINT polygonRgn1[7] = { M_POINT(312 ,200),M_POINT(326 ,239),M_POINT(334 ,249),M_POINT(344 ,180),M_POINT(354 ,100),
			M_POINT(363 ,300),M_POINT(372 ,400) };
		/*M_POINT polygonRgn[5] = {	M_POINT(190, 229),
		M_POINT(191, 111),
		M_POINT(192, 119),
		M_POINT(192, 119),
		M_POINT(198, 159)};*/

		int showPoCount = 7;
		BSTR strFacePoints = ::SysAllocStringLen(NULL,
			sizeof(M_POINT) * showPoCount);

		points[0] = M_POINT(50, 50);
		points[1] = M_POINT(100, 50);
		points[2] = M_POINT(120, 100);

		memcpy(strFacePoints, polygonRgn1, sizeof(M_POINT) * showPoCount);

		m_pYimaEncCtrl->FillPolygon(&strFacePoints, showPoCount, true, 50);

		m_pYimaEncCtrl->SetCurrentPen(5, 0x0000ff);
		//m_pYimaEncCtrl->DrawPolyline(&strFacePoints, 20);

		SysFreeString(strFacePoints);

		m_pYimaEncCtrl->SetCurrentFont("黑体", 40, 0x0000ff, false, false);

		char strText[255];
		char a = 0xB0;
		sprintf(strText, "测试显示文本: 21°30′56″");
		m_pYimaEncCtrl->TextOutAtPoint(strText, 150, 300);

		HBITMAP hbmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
		HBITMAP hMaskbmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
		m_pYimaEncCtrl->PasteBitmap((long)hbmp, (long)hMaskbmp, 170, 250);
		DeleteObject(hbmp);
		DeleteObject(hMaskbmp);

		/*
		m_pYimaEncCtrl->DrawEllipse(240, 180, 100, 60, true, true);
		m_pYimaEncCtrl->DrawCircle(300, 150, 50, true, true);
		m_pYimaEncCtrl->DrawArc(50, 300, 80, 30, 270, 2, true, true, 20);
		*/
	}

	//演示显示悬浮缩放面板
	//DrawMapOperationPanel((HDC)m_pYimaEncCtrl->GetDrawerHDC()); 
	/****************************************************************************/

	if (m_bShowRefreashTime)
	{
		DWORD usedMSecond = GetTickCount() - m_beforeRefesh;
		if (usedMSecond > 10)
		{
			m_usedMSecond = usedMSecond; //大于10毫秒为有效耗时
		}
		CString strUsedTime;
		strUsedTime.Format("刷新耗时：%d 毫秒", m_usedMSecond);
		m_pYimaEncCtrl->SetCurrentFont("", 15, RGB(0, 0, 255), false, false);
		m_pYimaEncCtrl->TextOutAtPoint(strUsedTime, 170, 40);

	}
}

COLORREF m_crWhite = RGB(255, 255, 255);
COLORREF m_crBlack = RGB(0, 0, 0);
void TransPasteDC(HDC scrnDC, HDC destDC, HDC srcDC, int scrnWidth, int scrnHeight, M_COLOR transColor)
{
	COLORREF crOldBack = SetBkColor(destDC, m_crWhite);
	COLORREF crOldText = SetTextColor(destDC, m_crBlack);

	//创建透明层
	HDC tranDC = CreateCompatibleDC(scrnDC);
	HBITMAP tranBmp = CreateBitmap(scrnWidth, scrnHeight, 1, 1, NULL);
	SelectObject(tranDC, tranBmp);

	SetBkColor(srcDC, RGB(transColor.r, transColor.g, transColor.b));
	BitBlt(tranDC, 0, 0, scrnWidth, scrnHeight, srcDC, 0, 0, SRCCOPY);

	//进行透明贴图
	BitBlt(destDC, 0, 0, scrnWidth, scrnHeight, srcDC, 0, 0, SRCINVERT);
	BitBlt(destDC, 0, 0, scrnWidth, scrnHeight, tranDC, 0, 0, SRCAND);
	BitBlt(destDC, 0, 0, scrnWidth, scrnHeight, srcDC, 0, 0, SRCINVERT);

	SetBkColor(destDC, crOldBack);
	SetTextColor(destDC, crOldText);

	DeleteDC(tranDC);
	DeleteObject(tranBmp);
}

//模拟雷达图像叠加
void CYimaEncViewerView::OnDrawRadar()
{
	bool bIfTestDrawRadar = true;

	if (bIfTestDrawRadar)
	{
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);

		if (m_pYimaEncCtrl->GetDrawRadarOrNot())
		{
			HDC hdc = (HDC)m_pYimaEncCtrl->GetDrawerHDC(); /* YIMAENC COMMENT: 注意，必须以海图绘制器的 HDC 为目标DC来绘制雷达图像*/
			HDC hMemDC = CreateCompatibleDC(hdc);

			CBitmap bmp;

			static int radarFrameBmpFileNumber = 0;
			int radarFrameBmpFileCount = 99;

			if (radarFrameBmpFileNumber == 98)
			{
				radarFrameBmpFileNumber = 0;
			}

			CString radarFrameBmpFileName;
			radarFrameBmpFileName.Format("TestRadarFrames\\show%d.bmp", radarFrameBmpFileNumber * 14);

			HBITMAP hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), (LPCTSTR)radarFrameBmpFileName,
				IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

			SelectObject(hMemDC, hBmp);

			/*
			HDC scrnDC = ::GetDC(m_hWnd);
			TransPasteDC(scrnDC, hdc, hMemDC, 1200, 1200, M_COLOR(0, 0, 0));
			::ReleaseDC(m_hWnd, scrnDC);
			*/
			BLENDFUNCTION blend;
			blend.AlphaFormat = 0;
			blend.BlendFlags = 0;
			blend.BlendOp = AC_SRC_OVER;
			blend.SourceConstantAlpha = 100; //该系数可调，数值范围在0~255
			if (!::AlphaBlend(hdc, -100, -50, 1200, 1200, hMemDC, 0, 0, 1200, 1200, blend))
			{
				BitBlt(hdc, -100, -50, 1000, 1000, hMemDC, 0, 0, SRCCOPY);
			}

			DeleteObject(hBmp);

			radarFrameBmpFileNumber++;

			/*
			if (nRadarFrameNumber % 2 == 0)
			{
				bmp.LoadBitmap(IDB_EMULATE_RADAR_BITMAP);
			}
			else
			{
				bmp.LoadBitmap(IDB_EMULATE_RADAR_BITMAP1);
			}

			::SelectObject(hMemDC, bmp.m_hObject);
			BitBlt(hdc, 100, 100, 1000, 1000, hmemdc, 0, 0, SRCCOPY);

			bmp.DeleteObject();
			*/

			DeleteDC(hMemDC);
		}
	}
}

bool CYimaEncViewerView::IsOnOperation(CURRENT_SUB_OPERATION subOperation)
{
	if (subOperation == NO_OPERATION)
	{
		return m_curOperation == NO_OPERATION;
	}
	else
	{
		return (m_curOperation & subOperation) != 0;
	}
}

void CYimaEncViewerView::SetOperation(CURRENT_SUB_OPERATION subOperation)
{
	if (subOperation == NO_OPERATION)
	{
		m_curOperation = NO_OPERATION;
		ReleaseCapture();
	}
	else
	{
		if (subOperation == HAND_ROAM || subOperation == HOLLOW_MAP || subOperation == DELAY_MAP)
		{
			SetCapture();
		}
		m_curOperation |= subOperation;
	}
}

void CYimaEncViewerView::CancelOperation(CURRENT_SUB_OPERATION subOperation)
{
	if (subOperation != NO_OPERATION)
	{
		m_curOperation &= (subOperation ^ 0xFFFFFFFF);
	}
	if (IsOnOperation(NO_OPERATION))
	{
		ReleaseCapture();
	}
}

bool CYimaEncViewerView::SetHighlightObjects(
	MEM_GEO_OBJ_POS* pObjPoses, int objCount)
{
	bool bResult = false;
	if ((objCount > 0 && objCount < SEL_OBJ_MAX_COUNT))
	{
		if (pObjPoses != NULL)
		{
			memcpy(m_curSelectedObjPoses, pObjPoses,
				objCount * sizeof(MEM_GEO_OBJ_POS));

			m_curSelectedObjCount = objCount;
			bResult = true;
		}
	}
	else if (objCount == 0)
	{
		m_curSelectedObjCount = 0;
		bResult = true;
	}

	return bResult;
}

long CYimaEncViewerView::SelectAWayPointByScrnPoint(int scrnPointX, int scrnPointY)
{
	int totalWpCount = m_pYimaEncCtrl->GetWayPointsCount();
	for (int wpPos = 0; wpPos < totalWpCount; wpPos++)
	{
		M_POINT wpPoint;
		long wpID = m_pYimaEncCtrl->GetWayPointIDFromPos(wpPos);
		m_pYimaEncCtrl->GetWayPointCoor(wpID,
			(long*)&wpPoint.x, (long*)&wpPoint.y);
		if (m_pYimaEncCtrl->IsGeoPointSelectByScrnPoint(
			scrnPointX, scrnPointY, wpPoint.x, wpPoint.y, 20))
		{
			return wpID;
		}
	}

	return 0;
}

long CYimaEncViewerView::SelectARouteByScrnPoint(int scrnPointX, int scrnPointY)
{
	int totalRouteCount = m_pYimaEncCtrl->GetRoutesCount();
	for (int rtPos = 0; rtPos < totalRouteCount; rtPos++)
	{
		M_POINT rtPoint;

		long routeID = m_pYimaEncCtrl->GetRouteIDFromPos(rtPos);
		long routeWpCount = m_pYimaEncCtrl->GetRouteWayPointsCount(routeID);

		BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * routeWpCount);
		if (m_pYimaEncCtrl->GetRouteWayPointsCoor(routeID, &strLinePoints))
		{
			if (m_pYimaEncCtrl->IsGeoLineSelectByScrnPoint(
				scrnPointX, scrnPointY, &strLinePoints, routeWpCount, 10))
			{
				return routeID;
			}
		}

		::SysFreeString(strLinePoints);
	}

	return 0;
}

typedef enum MSG_FROM_ENC_PLATFORM
{
	NOTIFY_SHIP_QUERYED = 1001
}MSG_FROM_ENC_PLATFORM;

void CYimaEncViewerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	selectObjPoint = point;
	//自定义海图对象拖动编辑功能实现 -- 单击按下处理部分
	if (IsOnOperation(EDITING_GEO_OBJECT))
	{
		M_GEO_TYPE geoType = (M_GEO_TYPE)m_pYimaEncCtrl->tmGetGeoObjectType(m_editingUserMapObjPos.layerPos,
			m_editingUserMapObjPos.innerLayerObjectPos);
		if (geoType == TYPE_LINE || geoType == TYPE_FACE)
		{
			int selPointPosInLine =
				m_pYimaEncCtrl->tmSelectOnePointOfLineObject(point.x, point.y,
					m_editingUserMapObjPos.layerPos,
					m_editingUserMapObjPos.innerLayerObjectPos); //看看是否选中了某个节点

			if (selPointPosInLine != -1)
			{
				if (m_iEditingPointPosOnEditingLine == selPointPosInLine)
				{ //如果这次点击选中的节点和上次点击选中的相同, 则我们认为用户开始准备拖动该节点了
					m_bHasPressedDragStartPo = true;
					m_bHasDrawDragFirstPo = false;

					m_mouseDragFirstPo = M_POINT(point.x, point.y);
					SetOperation(DRAG_EDITING_OBJECT); //把当前View的操作状态设为 DRAG_EDITING_OBJECT

					m_pYimaEncCtrl->tmSetObjectDynamicObjectOrNot(m_editingUserMapObjPos.layerPos,
						m_editingUserMapObjPos.innerLayerObjectPos, true);

					m_pYimaEncCtrl->tmPushInStackUndoOperation(MOD_GEO_OBJ, m_editingUserMapObjPos.layerPos,
						m_editingUserMapObjPos.innerLayerObjectPos);
				}
				else
				{ //如果这次点击选中的节点和上次点击选中的不同，则重置 m_iEditingPointPosOnEditingLine 成员变量
					m_iEditingPointPosOnEditingLine = selPointPosInLine;
				}
			}
			else
			{
				/* 如果没有选中节点, 则判断在屏幕上点击的坐标点是否在选中的物标对象的范围内
				   如果是则设置当前的状态DRAG_EDITING_OBJECT,表示可以对物标进行拖动操作 */
				BOOL bRetBeSelect;
				bool bResult = m_pYimaEncCtrl->SelectObjectByScrnPo(
					m_pYimaEncCtrl->GetMemMapCount() - 1, m_editingUserMapObjPos.layerPos,
					m_editingUserMapObjPos.innerLayerObjectPos, point.x, point.y, &bRetBeSelect);
				if (bResult && bRetBeSelect)
				{
					SetOperation(DRAG_EDITING_OBJECT);
					m_ScrnOffset = GetCurMouseOffSetObjCenter(m_editingUserMapObjPos, M_POINT(point.x, point.y));
					m_pYimaEncCtrl->tmSetObjectDynamicObjectOrNot(m_editingUserMapObjPos.layerPos,
						m_editingUserMapObjPos.innerLayerObjectPos, true);
					m_pYimaEncCtrl->tmPushInStackUndoOperation(MOD_GEO_OBJ, m_editingUserMapObjPos.layerPos,
						m_editingUserMapObjPos.innerLayerObjectPos);
				}

				/* 在中心点显示拖拽符号 因后来改成整个物标区域都可拖拽 故注释这个代码 应用层也可使用这种机制
				//判断是否选中了该物标的中心点位置
				//获取当前选中的物标的中心点 add by tcf 2011.05.08
				long left, right, top, bottom;

				  MEM_GEO_OBJ_POS objPos = m_editingUserMapObjPos;
				  BSTR strObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));
				  memcpy(strObjPos, &objPos, sizeof(MEM_GEO_OBJ_POS));
				  m_pYimaEncCtrl->GetObjectGeoExtent(&strObjPos, &left, &right, &top, &bottom);

					long centerGeoX, centerGeoY, centerScrnX, centerScrnY;
					centerGeoX = ((double)left + right) / 2;
					centerGeoY = ((double)top + bottom) / 2;
					m_pYimaEncCtrl->GetScrnPoFromGeoPo(centerGeoX, centerGeoY, &centerScrnX, &centerScrnY);
					int objDistInterval = 20;
					if ((point.x + objDistInterval >= centerScrnX && point.x - objDistInterval <= centerScrnX) &&
					(point.y + objDistInterval >= centerScrnY && point.y - objDistInterval <= centerScrnY))
					{
					SetOperation(DRAG_EDITING_OBJECT);
					}

					  SysFreeString(strObjPos);
				*/
			}
		}
		else
		{
			if (geoType == TYPE_POINT)
			{
				long objectPointX, objectPointY;
				m_pYimaEncCtrl->tmGetPointObjectCoor(m_editingUserMapObjPos.layerPos,
					m_editingUserMapObjPos.innerLayerObjectPos, &objectPointX, &objectPointY);

				if (m_pYimaEncCtrl->IsGeoPointSelectByScrnPoint(point.x, point.y,
					objectPointX, objectPointY, 12))
				{ //如果上次点击选中的点物标再次被点击选中，则我们认为用户要开始准备拖动该物标了
					m_bHasPressedDragStartPo = true;
					m_bHasDrawDragFirstPo = false;
					m_ScrnOffset = GetCurMouseOffSetObjCenter(m_editingUserMapObjPos, M_POINT(point.x, point.y));
					m_mouseDragFirstPo = M_POINT(point.x, point.y);
					SetOperation(DRAG_EDITING_OBJECT);
				}
			}
		}
	}

	//判断在航线编辑状态是否选中了航路点(WayPoint)或航线(Route)
	if (m_bOnRouteEditMode && !IsOnOperation(ADD_ROUTE))
	{
		long selectWpID = SelectAWayPointByScrnPoint(point.x, point.y);
		if (selectWpID != 0)
		{
			if (m_nEditingWayPointID == selectWpID)
			{//如果之前也是选中了该航路点, 说明现在用户想拖动该点的位置

				m_bHasPressedDragStartPo = true;
				m_bHasDrawDragFirstPo = false;

				m_mouseDragFirstPo = M_POINT(point.x, point.y);

				SetOperation(DRAG_EDITING_OBJECT);
				return;
			}

			m_pYimaEncCtrl->ClearHighLightPoints();

			M_POINT wpPoint;
			m_pYimaEncCtrl->GetWayPointCoor(
				selectWpID, (long*)&wpPoint.x,
				(long*)&wpPoint.y);

			m_pYimaEncCtrl->AddHighLightPoint(wpPoint.x, wpPoint.y);
			SetOperation(EDITING_WAY_POINT);

			m_nEditingWayPointID = selectWpID;

			return;
		}

		long selectRouteID = SelectARouteByScrnPoint(point.x, point.y);
		if (selectRouteID != 0)
		{
			m_pYimaEncCtrl->ClearHighLightLines();

			long routeWpCount = m_pYimaEncCtrl->GetRouteWayPointsCount(selectRouteID);
			BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * routeWpCount);
			if (m_pYimaEncCtrl->GetRouteWayPointsCoor(m_nEditingRouteID, &strLinePoints))
			{
				m_pYimaEncCtrl->AddHighLightLine(&strLinePoints, routeWpCount);
			}
			::SysFreeString(strLinePoints);

			SetOperation(EDITING_ROUTE);

			m_nEditingRouteID = selectRouteID;

			return;
		}
	}

	//悬浮面板单击操作处理代码
	if (IsOnOperation(NO_OPERATION))
	{
		/********  悬浮海图基本操作面板 *********/
		SIZE panelBtnSize;
		panelBtnSize.cx = panelBtnSize.cy = 19;

		POINT leftBtnLeftTopPoint, rightBtnLeftTopPoint, upBtnLeftTopPoint, downBtnLeftTopPoint, zoomInBtnLeftTopPoint, zoomOutBtnLeftTopPoint;

		/* 提示: 这个15是"向左"按钮相对皮肤图片左上角顶点的横坐标, 可以在“资源编辑”的绘图工具里用鼠标定位查看 */
		leftBtnLeftTopPoint.x = MAP_OPERATION_PANEL_LEFT + 15;
		leftBtnLeftTopPoint.y = MAP_OPERATION_PANEL_TOP + 32;
		CRect rcLeftBtn(leftBtnLeftTopPoint, panelBtnSize);

		rightBtnLeftTopPoint.x = MAP_OPERATION_PANEL_LEFT + 67;
		rightBtnLeftTopPoint.y = MAP_OPERATION_PANEL_TOP + 32;
		CRect rcRightBtn(rightBtnLeftTopPoint, panelBtnSize);

		upBtnLeftTopPoint.x = MAP_OPERATION_PANEL_LEFT + 41;
		upBtnLeftTopPoint.y = MAP_OPERATION_PANEL_TOP + 6;
		CRect rcUpBtn(upBtnLeftTopPoint, panelBtnSize);

		downBtnLeftTopPoint.x = MAP_OPERATION_PANEL_LEFT + 41;
		downBtnLeftTopPoint.y = MAP_OPERATION_PANEL_TOP + 58;
		CRect rcDownBtn(downBtnLeftTopPoint, panelBtnSize);

		zoomInBtnLeftTopPoint.x = MAP_OPERATION_PANEL_LEFT + 41;
		zoomInBtnLeftTopPoint.y = MAP_OPERATION_PANEL_TOP + 84;
		CRect rcZoomInBtn(zoomInBtnLeftTopPoint, panelBtnSize);

		zoomOutBtnLeftTopPoint.x = MAP_OPERATION_PANEL_LEFT + 41;
		zoomOutBtnLeftTopPoint.y = MAP_OPERATION_PANEL_TOP + 110;
		CRect rcZoomOutBtn(zoomOutBtnLeftTopPoint, panelBtnSize);

		if (rcLeftBtn.PtInRect(point))
		{
			OnMoveLeft();
			return;
		}
		else if (rcRightBtn.PtInRect(point))
		{
			OnMoveRight();
			return;
		}
		else if (rcUpBtn.PtInRect(point))
		{
			OnMoveUp();
			return;
		}
		else if (rcDownBtn.PtInRect(point))
		{
			OnMoveDown();
			return;
		}
		else if (rcZoomInBtn.PtInRect(point))
		{
			OnZoomIn();
			return;
		}
		else if (rcZoomOutBtn.PtInRect(point))
		{
			OnZoomOut();
			return;
		}
		/********************************************/

		this->SetCapture();
		SetOperation(HAND_ROAM);
	}

	if (IsOnOperation(AREA_ZOOM_IN) || IsOnOperation(HAND_ROAM) ||
		IsOnOperation(DRAW_EBL) || IsOnOperation(AREA_SELECT))
	{
		m_bHasPressedDragStartPo = true;
		m_bHasDrawDragFirstPo = false;

		m_mouseDragFirstPo = M_POINT(point.x, point.y);

		if (IsOnOperation(HAND_ROAM))
			SetCursor(LoadCursor(NULL, IDC_HAND));
	}

	if (IsOnOperation(ADD_WAYPOINT))
	{
		long wpGeoPoX, wpGeoPoY;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, &wpGeoPoX, &wpGeoPoY);
		m_pYimaEncCtrl->AddWayPoint(wpGeoPoX, wpGeoPoY, "wp1");
		Invalidate();
	}

	if (IsOnOperation(ADD_ROUTE))
	{
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
		int totalWpCount = m_pYimaEncCtrl->GetWayPointsCount();

		long selWayPointID = SelectAWayPointByScrnPoint(point.x, point.y);
		if (selWayPointID != 0)
		{
			M_POINT selWpPoint;
			m_pYimaEncCtrl->GetWayPointCoor(selWayPointID, (long*)&selWpPoint.x,
				(long*)&selWpPoint.y);

			m_nEditingRouteWayPointIDs[m_nEditingLinePointCount] = selWayPointID;
			m_editingLineGeoPoints[m_nEditingLinePointCount]
				= selWpPoint;

			m_nEditingLinePointCount++;

			if (m_nEditingLinePointCount > 1)
			{
				DrawEditingLineBeforeFinish();
			}
		}
	}

	////////////////// 添加自定义物标对象操作 /////////////////////	
	if (IsOnOperation(ADD_USER_LAYER_OBJ))
	{
		long geoPoX, geoPoY;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, &geoPoX, &geoPoY);

		if (m_iEditingUserMapLayerNum != -1)
		{
			//if (IsOnOperation(ADD_ISO_POINT))
			//{
			//	if (m_pYimaEncCtrl->tmAppendObjectInLayer(m_iEditingUserMapLayerNum, TYPE_POINT))
			//	{ 
			//		int innerLayerObjPos = m_pYimaEncCtrl->tmGetLayerObjectCount(m_iEditingUserMapLayerNum) - 1; 

			//		m_pYimaEncCtrl->tmSetPointObjectCoor(m_iEditingUserMapLayerNum,
			//			innerLayerObjPos, geoPoX, geoPoY);   
			//		
			//		SetCursor(LoadCursor(NULL, IDC_ARROW));   

			//		UserObject_SetAttributes(m_iEditingUserMapLayerNum, innerLayerObjPos);
			//		
			//		m_pYimaEncCtrl->tmPushInStackUndoOperation(ADD_GEO_OBJ, m_iEditingUserMapLayerNum, 
			//			m_pYimaEncCtrl->tmGetLayerObjectCount(m_iEditingUserMapLayerNum) - 1);
			//		
			//		m_pYimaEncCtrl->tmSetTargetForRedoOperation();	//用于实现自定义海图编辑的重做(Redo)
			//		
			//		SetOperation(NO_OPERATION);
			//	}
			//}
			//else if (IsOnOperation(ADD_LINE) || IsOnOperation(ADD_FACE))
			//{  
			//	//添加线、面物标对象时，点击屏幕则Append一个物标对象，并且设置物标对象的坐标；
		//		bool bSucAddObject = true;	
			//
			//	int editObjPos = m_pYimaEncCtrl->tmGetLayerObjectCount(m_iEditingUserMapLayerNum) - 1;
			//	if (m_nEditingLinePointCount == 0)
			//	{
			//		if (IsOnOperation(ADD_LINE))
			//		{
			//			bSucAddObject = m_pYimaEncCtrl->tmAppendObjectInLayer(m_iEditingUserMapLayerNum, TYPE_LINE);
			//		}
			//		else if (IsOnOperation(ADD_FACE))
			//		{
			//			bSucAddObject = m_pYimaEncCtrl->tmAppendObjectInLayer(m_iEditingUserMapLayerNum, TYPE_FACE);
			//		}

			//		editObjPos = m_pYimaEncCtrl->tmGetLayerObjectCount(m_iEditingUserMapLayerNum) - 1;	

			//		/* 要设为动态物标，这样在 CYimaEncViewerView::DrawDynamicScreenMap() 方法的 DrawMapsInScreen() 
			//		   语句调用时才不会被主绘制器和背景海图一起画出来 */
			//		m_pYimaEncCtrl->tmSetObjectDynamicObjectOrNot(m_iEditingUserMapLayerNum, editObjPos, true); 
			//	} 

			//	if (m_nEditingLinePointCount > 0)
			//	{//如果编辑对象的节点数不为空时, 则将当前坐标记录到编辑点数组的终点
			//		m_editingLineGeoPoints[m_nEditingLinePointCount - 1] = M_POINT(geoPoX, geoPoY); 
			//	}
			//	else
			//	{//如果之前还没有节点, 则先要在当前位置补一个节点
			//		m_editingLineGeoPoints[0] = M_POINT(geoPoX, geoPoY);	//给第一个坐标点值赋值
			//		m_nEditingLinePointCount = 1;
			//	}

			//	//下面2句重要: 鼠标单击后要增加1个节点，这个节点紧接着就要在 OnMouseMove() 中被拖动, 从而实现动态节点编辑效果
			//	m_nEditingLinePointCount += 1; 
			//	m_editingLineGeoPoints[m_nEditingLinePointCount - 1] = m_editingLineGeoPoints[m_nEditingLinePointCount - 2];
			//	
			//	//当前编辑节点即拖曳节点应为最后1个点
			//	m_iEditingPointPosOnEditingLine = m_nEditingLinePointCount - 1; 
			//	
			//	if (IsOnOperation(ADD_LINE) || IsOnOperation(ADD_FACE))	//添加线、面物标时的处理
			//	{
			//		if (m_addingSpecialLineType == RECTANGLE_LN_TYPE)
			//		{//矩形对象在YIMAENC中是存储4个点的, 动态添加时要拖动第3个节点(索引为2)才是对角拖动 
			//			m_iEditingPointPosOnEditingLine = 2;
			//		} 
			//		
			//		BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * m_nEditingLinePointCount); 
			//		memcpy(strLinePoints, m_editingLineGeoPoints, sizeof(M_POINT) * m_nEditingLinePointCount);
			//		
			//		if (IsOnOperation(ADD_LINE))
			//		{
			//			m_pYimaEncCtrl->tmSetLineObjectCoors(m_iEditingUserMapLayerNum, 
			//				editObjPos, m_nEditingLinePointCount, &strLinePoints);
			//		}
			//		else
			//		{
			//			m_pYimaEncCtrl->tmSetFaceObjectCoors(m_iEditingUserMapLayerNum, 
			//				editObjPos, m_nEditingLinePointCount, &strLinePoints);
			//		}
			//		
			//		::SysFreeString(strLinePoints); 
			//		
			//		if (m_addingSpecialLineType != NO_SPECIAL_TYPE)	//物标类型是特殊类型所做的操作
			//		{  
			//			m_pYimaEncCtrl->tmSetObjectAsSpecialType(m_iEditingUserMapLayerNum,
			//				editObjPos, m_addingSpecialLineType);	//设置物标的特殊类型
			//			
			//			/* 下面给 SECTOR_LN_TYPE、ARC_LN_TYPE、PIE_LN_TYPE、BOW_LN_TYPE 等几种类型设置动态添加时的默认角度参数 */						
			//			if (m_addingSpecialLineType == SECTOR_LN_TYPE)	
			//			{ 	
			//				if (m_nEditingLinePointCount < 3)
			//				{
			//					return;
			//				}
			//				double outRadiusByMeter = 
			//					m_pYimaEncCtrl->GetDistBetwTwoPoint(m_editingLineGeoPoints[0].x, m_editingLineGeoPoints[0].y, 
			//					m_editingLineGeoPoints[1].x, m_editingLineGeoPoints[1].y) * 1852;
			//				double innerRadiusByMeter = 
			//					m_pYimaEncCtrl->GetDistBetwTwoPoint(m_editingLineGeoPoints[0].x, m_editingLineGeoPoints[0].y, 
			//					m_editingLineGeoPoints[2].x, m_editingLineGeoPoints[2].y) * 1852;
			//				
			//				m_pYimaEncCtrl->tmSetSectorTypeLineObjectParams(m_iEditingUserMapLayerNum, 
			//					editObjPos, true, m_editingLineGeoPoints[0].x, m_editingLineGeoPoints[0].y, 
			//					true, innerRadiusByMeter, true, outRadiusByMeter, true, 0, true, 120); //设定SPECIAL_LINE_TYPE 类型的特殊线物标相关参数
			//		 							
			//			}
			//			else if (m_addingSpecialLineType == ARC_LN_TYPE || 
			//				m_addingSpecialLineType == PIE_LN_TYPE || m_addingSpecialLineType == BOW_LN_TYPE)
			//			{  
			//				double radiusByMeter = 
			//					m_pYimaEncCtrl->GetDistBetwTwoPoint(m_editingLineGeoPoints[0].x, m_editingLineGeoPoints[0].y, 
			//					m_editingLineGeoPoints[1].x, m_editingLineGeoPoints[1].y) * 1852;
			//				m_pYimaEncCtrl->tmSetArcTypeLineObjectParams(m_iEditingUserMapLayerNum, 
			//					editObjPos, true, m_editingLineGeoPoints[0].x, m_editingLineGeoPoints[0].y, 
			//					true, radiusByMeter, true, 0, true, 120);  							
			//			}    
			//		}   
			//		
			//		if (m_pYimaEncCtrl->tmGetLayerGeoType(m_iEditingUserMapLayerNum) == MULTIPLE_GEO_TYPE )
			//		{//下面设置物标在动态添加完成之前的动态显示风格
			//			if (IsOnOperation(ADD_LINE))
			//			{//添加线
			//				m_pYimaEncCtrl->tmSetLineObjectStyleRefLib(m_iEditingUserMapLayerNum, editObjPos, 
			//					1, false, 0, false, 0);	/* 设置线物标在完成添加之前动态显示的风格样式为：
			//											    参考样式库lineStyleId 为1的风格 */
			//			}
			//			else
			//			{//
			//				m_pYimaEncCtrl->tmSetFaceObjectStyleRefLib(m_iEditingUserMapLayerNum, editObjPos, 
			//					2, true, RGB(0, 0, 255), true, 40, false, 0x000000); /* 设置线物标在完成添加之前动态显示的风格样式为：
			//											    参考样式库faceStyleId 为1的风格 */
			//			}
			//		}
			//		
			//		m_editingUserMapObjPos = M_GEO_OBJ_POS(m_iEditingUserMapLayerNum, editObjPos); //记录当前编辑物标 
			//		SetOperation(ADD_LINE_OBJECT_MOUSEMOVING);	//设置当前状态为 "添加物标时的动态节点添加状态"

			//		SetCursor(LoadCursor(NULL, IDC_ARROW));	 
			//	} 
			//	
			//	m_pYimaEncCtrl->tmPushInStackUndoOperation(ADD_GEO_OBJ, m_iEditingUserMapLayerNum, 
			//		m_pYimaEncCtrl->tmGetLayerObjectCount(m_iEditingUserMapLayerNum) - 1);	//将编辑动作保存进Undo动作堆栈,用于做Undo操作
			//	
			//	m_pYimaEncCtrl->tmSetTargetForRedoOperation();	//为Undo操作保存操作后物标信息，以实现Redo功能。 

			//	return;
			//}

			if (radar_info != NULL)
			{
				//SetCursor(LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_ARROW_RADAR)));
				//添加雷达物标
				m_pYimaEncCtrl->tmAppendObjectInLayer(m_iEditingUserMapLayerNum, TYPE_POINT);
				radar_info->radInnerLayerPos = m_pYimaEncCtrl->tmGetLayerObjectCount(m_iEditingUserMapLayerNum) - 1;
				//设置该雷达物标的坐标点
				m_pYimaEncCtrl->tmSetPointObjectCoor(m_iEditingUserMapLayerNum, radar_info->radInnerLayerPos, geoPoX, geoPoY);
				//物标样式
				m_pYimaEncCtrl->tmSetPointObjectStyleRefLib(m_iEditingUserMapLayerNum, radar_info->radInnerLayerPos, 9, FALSE, 0, 1, 0);

				bool exist = false;
				Radar curRadarObj;
				curRadarObj.Id = to_string(radar_info->radInnerLayerPos);
				curRadarObj.innerLayerPos = radar_info->radInnerLayerPos;
				curRadarObj.Lon = geoPoX;
				curRadarObj.Lan = geoPoY;
				curRadarObj.Height = 0.0;
				curRadarObj.Range = 0.0;
				curRadarObj.Level = 0.0;
				if (radarList.empty())
				{
					radarList.push_back(curRadarObj);
				}
				else
				{
					list<Radar>::iterator iter;
					for (iter = radarList.begin(); iter != radarList.end(); iter++)
					{
						if ((iter->Id == curRadarObj.Id) && (iter->Lon == curRadarObj.Lon) && (iter->Lan == curRadarObj.Lan))
						{
							exist = true;
						}
					}
					if (!exist)
					{
						radarList.push_back(curRadarObj);
					}
				}
				radar_info = NULL;
			}
			//退出添加雷达物标状态
			SetOperation(NO_OPERATION);
		}

	}

	///////////////////空心延迟////////////////////////////////
	if (IsOnOperation(DELAY_MAP) || IsOnOperation(HOLLOW_MAP))
	{
		long curGeoPoX = 0, curGeoPoY = 0;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, &curGeoPoX, &curGeoPoY);
		if (IsOnOperation(DELAY_MAP))
		{
			m_pYimaEncCtrl->SetMapDelayEffect(curGeoPoX, curGeoPoY, 0);
		}
		else if (IsOnOperation(HOLLOW_MAP))
		{
			m_pYimaEncCtrl->SetMapHollowEffect(curGeoPoX, curGeoPoY, 0);
		}
		m_bHasPressedDragStartPo = true;
		m_mouseDragFirstPo = M_POINT(point.x, point.y);
	}

	if (IsOnOperation(MEASURE_AREA))
	{
		long curGeoPoX = 0, curGeoPoY = 0;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, &curGeoPoX, &curGeoPoY);
		if (m_icurEditPos == 0)
		{
			m_arrMeasureGeoPo[0] = M_POINT(curGeoPoX, curGeoPoY);
		}
		m_icurEditPos += 1;
		m_arrMeasureGeoPo[m_icurEditPos] = M_POINT(curGeoPoX, curGeoPoY);
	}

	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}

void CYimaEncViewerView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default  

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	selectObjPoint = point;

	BOOL bDrawNineNineBoxOrNot = false;//是否显示九九方格
	m_pYimaEncCtrl->GetNineNineBoxCenterGeoPo(NULL, NULL, &bDrawNineNineBoxOrNot);
	if (bDrawNineNineBoxOrNot)
	{
		long retGeoPoX, retGeoPoY;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, &retGeoPoX, &retGeoPoY);

		BSTR bstrNumber = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
		bool bNineNineNuber = m_pYimaEncCtrl->GetNineNineNumberByGeoPo(retGeoPoX, retGeoPoY, &bstrNumber);
		if (bNineNineNuber)
		{
			CString str = bstrNumber;
			::SysFreeString(bstrNumber);
			CString strMsg;
			strMsg.Format(_T("九九方格:%s"), str);
			AfxMessageBox(strMsg); //zcz Test
		}
	}
	if (IsOnOperation(NO_OPERATION))
	{ //点击查询

		BSTR retSelObjPosStrings = ::SysAllocStringLen(NULL,
			SEL_OBJ_MAX_COUNT * sizeof(MEM_GEO_OBJ_POS));

		int selObjCount =
			m_pYimaEncCtrl->SelectObjectsByScrnPoint(&retSelObjPosStrings,
				point.x, point.y);

		/****** 测试新接口 QueryInMapLayerByFieldCondtion: *******
		int obstLyrPos = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("OBSTRN"));
		int A = m_pYimaEncCtrl->QueryInMapLayerByFieldCondtion(0, obstLyrPos, 0, EQUAL,
		"9.8", &retSelObjPosStrings);

		int intPoses[SEL_OBJ_MAX_COUNT];
		memcpy(intPoses, retSelObjPosStrings, A * sizeof(int));
		/*********************************************************/

		if (selObjCount > 0)
		{
			MEM_GEO_OBJ_POS selectedObjPoses[SEL_OBJ_MAX_COUNT];
			memcpy(selectedObjPoses, retSelObjPosStrings,
				selObjCount * sizeof(MEM_GEO_OBJ_POS));

			MEM_GEO_OBJ_POS frstSelectObjectPos = selectedObjPoses[0];

			SetHighlightObjects(&frstSelectObjectPos, 1);

			if (frstSelectObjectPos.memMapPos == m_pYimaEncCtrl->GetMemMapCount() - 1)
			{//如果选中的是自定义海图对象, 则进入编辑状态
				//SetOperation(EDITING_GEO_OBJECT);
				SetOperation(NO_OPERATION);
				//RefreshScreen();
				CMenu menu;
				menu.LoadMenu(IDR_MENU_RADAR);			//载入雷达右键菜单
				CMenu* pM = menu.GetSubMenu(0);
				CPoint pt;
				GetCursorPos(&pt);
				pM->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, AfxGetMainWnd());

				for (list<Radar>::iterator iter = radarList.begin(); iter != radarList.end(); iter++)
				{
					if (m_pYimaEncCtrl->IsGeoPointSelectByScrnPoint(point.x, point.y, iter->Lon, iter->Lan, 12))
					{
						curSelectRadar.Id = iter->Id;
						curSelectRadar.Lon = iter->Lon;
						curSelectRadar.Lan = iter->Lan;
					}
				}

				m_editingUserMapObjPos = M_GEO_OBJ_POS(frstSelectObjectPos.layerPos, frstSelectObjectPos.innerLayerPos);
			}

			Invalidate();

			SetOperation(EDITING_GEO_OBJECT);
		}

		SysFreeString(retSelObjPosStrings);

		return;
	}
	else
	{
		m_pYimaEncCtrl->HighlightOtherVessel(-1); //取消当前可能高亮的目标船
		m_pYimaEncCtrl->ClearHighLightPoints();
		m_pYimaEncCtrl->ClearHighLightLines();
		m_pYimaEncCtrl->ClearHighLightFaces();
		//m_pYimaEncCtrl->tmSetPointObjectStyle

		if (m_bOnRouteEditMode)
		{
			if (m_nEditingRouteID != 0)
			{
				m_nEditingRouteID = 0;
			}

			if (m_nEditingWayPointID != 0)
			{
				m_nEditingWayPointID = 0;
			}
		}

		if (m_curSelectedObjCount > 0)
		{
			m_curSelectedObjCount = 0;
		}

		if (IsOnOperation(ADD_WAYPOINT))
		{
			CancelOperation(ADD_WAYPOINT);
		}

		if (IsOnOperation(ADD_ROUTE))
		{
			if (m_nEditingLinePointCount >= 2)
			{
				CString routeName;
				int routeCount = m_pYimaEncCtrl->GetRoutesCount();
				routeName.Format(_T("Route %d"), routeCount + 1);

				BSTR bstrWpIDs = ::SysAllocStringLen(NULL, ROUTE_WAY_POINTS_MAX_COUNT * 2);
				memcpy(bstrWpIDs, m_nEditingRouteWayPointIDs, m_nEditingLinePointCount * sizeof(int));
				long newRouteID = m_pYimaEncCtrl->AddRoute(&bstrWpIDs, routeName,
					m_nEditingLinePointCount, false);
				SysFreeString(bstrWpIDs);

				CRouteEditDlg routeEditDlg;
				routeEditDlg.m_editRouteID = newRouteID;
				routeEditDlg.DoModal();

				pFrame->RefreshNavBarRouteList();
			}

			m_nEditingLinePointCount = 0;
			CancelOperation(ADD_ROUTE);
		}

		if (IsOnOperation(ADD_USER_LAYER_OBJ))
		{
			if (m_iEditingUserMapLayerNum != -1 && m_iEditingPointPosOnEditingLine >= 0)
			{
				int editObjPos = m_pYimaEncCtrl->tmGetLayerObjectCount(m_iEditingUserMapLayerNum) - 1;
				UserObject_SetAttributes(m_iEditingUserMapLayerNum, editObjPos);	 //完成添加物标的后续操作: 特征属性及样式选择设置

				m_pYimaEncCtrl->tmPushInStackUndoOperation(ADD_GEO_OBJ, m_iEditingUserMapLayerNum,
					m_pYimaEncCtrl->tmGetLayerObjectCount(m_iEditingUserMapLayerNum) - 1); //将编辑动作保存进Undo动作堆栈,用于实现Undo操作

				m_pYimaEncCtrl->tmSetTargetForRedoOperation();	//为Undo操作保存操作后物标信息，以实现Redo功能。

				m_iEditingPointPosOnEditingLine = -1;	//操作完毕,恢复m_iEditingPointPosOnEditingLine的值为-1
				m_addingSpecialLineType = NO_SPECIAL_TYPE;	//操作完毕,恢复m_addingSpecialLineType为NO_SPECIAL_TYPE			
				m_pYimaEncCtrl->tmSetObjectDynamicObjectOrNot(m_iEditingUserMapLayerNum, editObjPos, false);//添加好了, 可以取消其Dynamic的动态属性了 		    
				if (IsOnOperation(ADD_COLOR_ATTENUATION_OBJ))
				{
					static CSetAttenTimes* setAttenTimes = NULL;
					if (setAttenTimes == NULL)
					{
						setAttenTimes = new CSetAttenTimes(this);
					}
					setAttenTimes->DoModal();
					int decreaseValuePreSec = (float)(m_startFillTrans - 11) / (float)(setAttenTimes->m_iAttenTimes);
					long retLayerId, retObjId;
					m_pYimaEncCtrl->tmGetObjectIDFromPos(m_iEditingUserMapLayerNum, editObjPos, &retLayerId, &retObjId);
					M_COLOR_ATTENUATION tmpObj(retLayerId, retObjId, decreaseValuePreSec, true);
					m_arrColorAttenuationObj.push_back(tmpObj);
				}
			}
		}
		if (IsOnOperation(MEASURE_AREA))
		{
			m_icurEditPos -= 1;
		}
		m_bHasPressedDragStartPo = false;
		m_bHasDrawDragFirstPo = false;
		m_iEditingPointPosOnEditingLine = -1;

		SetOperation(NO_OPERATION);

		pFrame->UncheckMenusAndToolBar();

		Invalidate();
	}

	CView::OnRButtonDown(nFlags, point);
}

#define MOVE_STEP_RATIO_TO_SCRN 1 / 3 
void CYimaEncViewerView::OnMoveDown()
{
	// TODO: Add your command handler code here
	m_pYimaEncCtrl->SetMapMoreOffset(0,
		-m_pYimaEncCtrl->GetDrawerScreenHeight() * MOVE_STEP_RATIO_TO_SCRN);

	Invalidate();
}

void CYimaEncViewerView::OnMoveLeft()
{
	// TODO: Add your command handler code here
	m_pYimaEncCtrl->SetMapMoreOffset(
		m_pYimaEncCtrl->GetDrawerScreenWidth() * MOVE_STEP_RATIO_TO_SCRN,
		0);

	Invalidate();
}

void CYimaEncViewerView::OnMoveRight()
{
	// TODO: Add your command handler code here
	m_pYimaEncCtrl->SetMapMoreOffset(
		-m_pYimaEncCtrl->GetDrawerScreenWidth() * MOVE_STEP_RATIO_TO_SCRN,
		0);

	Invalidate();
}

void CYimaEncViewerView::OnMoveUp()
{
	// TODO: Add your command handler code here
	m_pYimaEncCtrl->SetMapMoreOffset(0,
		m_pYimaEncCtrl->GetDrawerScreenHeight() * MOVE_STEP_RATIO_TO_SCRN);


	Invalidate();
}

#define VK_OEM_MINUS 0xBD
#define VK_OEM_PLUS 0xBB

void CYimaEncViewerView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar)
	{
	case VK_DELETE:
		OnDelRoute();
		OnDelWaypoint();

		if (m_iEditingPointPosOnEditingLine != -1)
		{
			m_pYimaEncCtrl->tmDeleteOnePointOfLineObject(
				m_editingUserMapObjPos.layerPos,
				m_editingUserMapObjPos.innerLayerObjectPos,
				m_iEditingPointPosOnEditingLine);
			Invalidate();
		}
		else
		{
			OnDelObject();
		}

		break;
	case VK_LEFT:
		OnMoveLeft();
		break;
	case VK_RIGHT:
		OnMoveRight();
		break;
	case VK_UP:
		OnMoveUp();
		break;
	case VK_DOWN:
		OnMoveDown();
		break;
	case VK_OEM_MINUS:
	{
		//OnZoomOut();
		break;
	}
	case VK_OEM_PLUS:
		OnZoomIn();
		break;
	case 77: //查看内存海图序列列表快捷键'm'键
	{
		int memMapCount = m_pYimaEncCtrl->GetMemMapCount();
		CString strMemMapNameList = "Mem Maps: ";
		for (int memMapNum = 0; memMapNum < memMapCount; memMapNum++)
		{
			BSTR bstrMapName = ::SysAllocStringLen(NULL, 100);
			m_pYimaEncCtrl->GetMemMapInfo(memMapNum, NULL, &bstrMapName, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
			strMemMapNameList += bstrMapName;
			strMemMapNameList += ", ";
			SysFreeString(bstrMapName);
		}
		AfxMessageBox(strMemMapNameList);
		break;
	}
	case 78:
	{
		///////////////以下代码为了使用按键精灵进行压力测试时尽量防止在无图区域移动使用//////////// 

		static int nowOverViewLibMapPos = 0;
		m_pYimaEncCtrl->OverViewLibMap(nowOverViewLibMapPos);
		nowOverViewLibMapPos++;
		if (nowOverViewLibMapPos > m_pYimaEncCtrl->GetLibMapCount() - 3)
		{
			nowOverViewLibMapPos = 0;
		}

		CStatusBar * pStatus = (CStatusBar *)AfxGetApp()->m_pMainWnd->
			GetDescendantWindow(AFX_IDW_STATUS_BAR);
		CString strStatus;
		strStatus.Format("TestCycleMap %d", nowOverViewLibMapPos);
		pStatus->SetPaneText(INDEX_PANE_FOR_MOUSE_POSITION, strStatus);

		Invalidate();
		///////////////////////////////////////////////////////////////////////////////////////////

		break;
	}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CYimaEncViewerView::DrawCurrentEblLine(HDC hdc,
	M_POINT startPoint,
	M_POINT endPoint,
	M_POINT* pRetEblEndPoint)
{
	SetROP2(hdc, R2_XORPEN);

	HPEN hPen = (HPEN)CreatePen(PS_SOLID, 2, RGB_EBL_LINE);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	float deltx = endPoint.x - startPoint.x;
	float delty = endPoint.y - startPoint.y;
	int radius = sqrt(deltx * deltx + delty * delty);

	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Ellipse(hdc, startPoint.x - radius, startPoint.y - radius,
		startPoint.x + radius, startPoint.y + radius);

	RECT viewRect;
	GetClientRect(&viewRect);
	int scrnWidth = viewRect.right - viewRect.left;
	int scrnHeight = viewRect.bottom - viewRect.top;

	M_POINT eblLineEndPo;
	if (deltx != 0)
	{
		eblLineEndPo.x = deltx > 0 ? scrnWidth : -scrnWidth;
		eblLineEndPo.y = delty / deltx * (eblLineEndPo.x - m_mouseDragFirstPo.x)
			+ startPoint.y;
	}
	else
	{
		if (delty == 0)
		{
			return;
		}

		eblLineEndPo.x = endPoint.x;
		eblLineEndPo.y = delty > 0 ? scrnHeight : -scrnHeight;
	}

	::MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
	::LineTo(hdc, eblLineEndPo.x, eblLineEndPo.y);

	if (pRetEblEndPoint != NULL)
	{
		*pRetEblEndPoint = eblLineEndPo;
	}

	SetROP2(hdc, R2_COPYPEN);
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hPen);
}

#define TIMER_COUNT_TO_SHOW_TEXT_WHEN_MOUSE_STOP 2
void CYimaEncViewerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default  

	if (m_pYimaEncCtrl == NULL)
	{
		return;
	}
	CStatusBar * pStatus = (CStatusBar *)AfxGetApp()->m_pMainWnd->
		GetDescendantWindow(AFX_IDW_STATUS_BAR);

	m_mouseMoveCurrentPo = M_POINT(point.x, point.y);

	/* 动态提示框的例子 -- 这里演示提示航路点 */
	if (IsOnOperation(SHOWING_HINT_TEXT))
	{
		InvalidateRect((LPCRECT)&
			MRECT(m_rectHintText.leftTopPointX - 5,
				m_rectHintText.leftTopPointY - 5,
				m_rectHintText.rightDownPointX + 5,
				m_rectHintText.rightDownPointY + 5));

		CancelOperation(SHOWING_HINT_TEXT);

		m_iMouseStoppedTimerCount = 0;
	}

	//自定义海图对象拖动编辑功能实现 -- MouseMove处理部分
	if (IsOnOperation(DRAG_EDITING_OBJECT) || IsOnOperation(ADD_LINE_OBJECT_MOUSEMOVING)) /* 注意：本例中把自定义海图对象编辑中的节点拖动、航路点编辑的航路点拖动
											操作统一归为 DRAG_EDITING_OBJECT 操作状态，并统一用拖动的小圆圈
											来实现代码 */
	{
		DrawDynamicScreenMap(m_mouseMoveCurrentPo);
		return;
	}

	//画电子方位线	
	CString strEblInfo = "";
	if (IsOnOperation(DRAW_EBL))
	{
		static CPoint lastMouseMoveEndPo;
		static M_POINT lastEblLineEndPo;
		if (m_bHasPressedDragStartPo)
		{
			HDC hdc = GetDC()->m_hDC;
			SetROP2(hdc, R2_XORPEN);

			HPEN hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB_EBL_LINE);
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

			if (m_bHasDrawDragFirstPo)
			{
				float deltx = lastMouseMoveEndPo.x - m_mouseDragFirstPo.x;
				float delty = lastMouseMoveEndPo.y - m_mouseDragFirstPo.y;
				int radius = sqrt(deltx * deltx + delty * delty);

				SelectObject(hdc, GetStockObject(NULL_BRUSH));
				//Ellipse(hdc, m_mouseDragFirstPo.x - radius, m_mouseDragFirstPo.y - radius,
					//m_mouseDragFirstPo.x + radius, m_mouseDragFirstPo.y + radius ); 

				//::MoveToEx(hdc, m_mouseDragFirstPo.x, m_mouseDragFirstPo.y, NULL);
				//::LineTo(hdc, lastEblLineEndPo.x, lastEblLineEndPo.y);
			}
			else
			{
				m_bHasDrawDragFirstPo = true;
			}

			M_POINT eblLineEndPo;
			//DrawCurrentEblLine(hdc, m_mouseDragFirstPo, 
			//	M_POINT(point.x, point.y), &eblLineEndPo); 

			lastMouseMoveEndPo = point;
			lastEblLineEndPo = eblLineEndPo;

			SetROP2(hdc, R2_COPYPEN);
			SelectObject(hdc, hOldPen);
			DeleteObject(hPen);
			::ReleaseDC(m_hWnd, hdc);

			M_POINT sphereStartPo, sphereEndPo;

			m_pYimaEncCtrl->GetGeoPoFromScrnPo(
				m_mouseDragFirstPo.x, m_mouseDragFirstPo.y,
				(long*)&sphereStartPo.x, (long*)&sphereStartPo.y);

			m_pYimaEncCtrl->GetGeoPoFromScrnPo(
				point.x, point.y,
				(long*)&sphereEndPo.x, (long*)&sphereEndPo.y);

			double distByNatMile = m_pYimaEncCtrl->GetDistBetwTwoPoint(
				sphereStartPo.x, sphereStartPo.y,
				sphereEndPo.x, sphereEndPo.y);

			double bearing = m_pYimaEncCtrl->GetBearingBetwTwoPoint(
				sphereStartPo.x, sphereStartPo.y,
				sphereEndPo.x, sphereEndPo.y);

			Invalidate(FALSE);
			strEblInfo.Format("距离: %.4f（海里）%.4f（米）, 角度: %.3f", distByNatMile, distByNatMile * 1852, bearing);
		}
	}

	//区域放大
	if (IsOnOperation(AREA_ZOOM_IN) || IsOnOperation(AREA_SELECT))
	{
		if (m_bHasPressedDragStartPo)
		{
			static CPoint lastMouseMoveRectEndPo;

			HDC hdc = GetDC()->m_hDC;
			SetROP2(hdc, R2_XORPEN);

			HPEN hPen = NULL;
			hPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(0, 255, 0));

			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

			if (m_bHasDrawDragFirstPo)
			{
				::MoveToEx(hdc, m_mouseDragFirstPo.x, m_mouseDragFirstPo.y, NULL);
				::LineTo(hdc, m_mouseDragFirstPo.x, lastMouseMoveRectEndPo.y);
				::LineTo(hdc, lastMouseMoveRectEndPo.x, lastMouseMoveRectEndPo.y);
				::LineTo(hdc, lastMouseMoveRectEndPo.x, m_mouseDragFirstPo.y);
				::LineTo(hdc, m_mouseDragFirstPo.x, m_mouseDragFirstPo.y);
			}
			else
			{
				m_bHasDrawDragFirstPo = true;
			}

			::MoveToEx(hdc, m_mouseDragFirstPo.x, m_mouseDragFirstPo.y, NULL);
			::LineTo(hdc, m_mouseDragFirstPo.x, point.y);
			::LineTo(hdc, point.x, point.y);
			::LineTo(hdc, point.x, m_mouseDragFirstPo.y);
			::LineTo(hdc, m_mouseDragFirstPo.x, m_mouseDragFirstPo.y);

			lastMouseMoveRectEndPo = point;

			SetROP2(hdc, R2_COPYPEN);
			SelectObject(hdc, hOldPen);
			DeleteObject(hPen);
			::ReleaseDC(m_hWnd, hdc);
		}
	}

	if (IsOnOperation(HAND_ROAM))
	{
		if (m_bHasPressedDragStartPo)
		{
			//SetCursor(LoadCursor(NULL, IDC_HAND));  
			//static M_POINT prePoint;
			//static int mouseMoveTick = 0;

			//if (true)//mouseMoveTick % 2 == 0)
			//{
			//	if (!m_bHasDrawDragFirstPo)
			//	{
			//		prePoint = m_mouseDragFirstPo;
			//	}

			//	m_pYimaEncCtrl->SetMapMoreOffset(point.x - prePoint.x, point.y - prePoint.y);

			//	prePoint = M_POINT(point.x, point.y);
			//	m_bHasDrawDragFirstPo = true;

			//	RefreshScreenMap();
			//}

			//mouseMoveTick ++;
			//return ;
			if (m_bRuntimeDragMap)
			{
				long offsetX = point.x - m_mouseDragFirstPo.x;
				long offsetY = point.y - m_mouseDragFirstPo.y;
				if (abs(offsetX) > 2 || abs(offsetY) > 2)
				{
					m_pYimaEncCtrl->SetMapMoreOffset(offsetX, offsetY);
					Invalidate();
					m_mouseDragFirstPo = M_POINT(point.x, point.y);
				}
			}
			else
			{

				HDC hdc = ::GetDC(m_hWnd);
				m_pYimaEncCtrl->DrawDragingMap((long)hdc, point.x, point.y, m_mouseDragFirstPo.x, m_mouseDragFirstPo.y);
				//DrawMapOperationPanel(hdc); //悬浮海图操作面板			
				::ReleaseDC(m_hWnd, hdc);
			}
			SetCursor(LoadCursor(NULL, IDC_HAND));
		}
	}

	if (IsOnOperation(ADD_USER_LAYER_OBJ))
	{
		SetCursor(LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_ARROW_RADAR)));
	}


	//空心延迟
	if (IsOnOperation(DELAY_MAP) || IsOnOperation(HOLLOW_MAP))
	{
		if (m_bHasPressedDragStartPo)
		{
			int scrnLen = sqrt(pow(point.x - m_mouseDragFirstPo.x, 2.0) + pow(point.y - m_mouseDragFirstPo.y, 2.0));
			m_pYimaEncCtrl->SetMapEffectRadius(0);
			float geoLen = m_pYimaEncCtrl->GetGeoLenFromScrnLen(scrnLen) / 1000;
			m_pYimaEncCtrl->SetMapEffectRadius(geoLen);
			Invalidate();
		}
	}
	if (IsOnOperation(MEASURE_AREA) && m_icurEditPos > 0)
	{
		M_POINT curGeoPo;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, (long*)&curGeoPo.x, (long*)&curGeoPo.y);
		m_arrMeasureGeoPo[m_icurEditPos] = curGeoPo;

		Invalidate(FALSE);


	}
	CString strCurPosition;
	M_POINT poGeo;

	TCHAR strGeoCoorX[100];
	TCHAR strGeoCoorY[100];

	long iGeoCoorMultiFactor = m_pYimaEncCtrl->GetGeoCoorMultiFactor();
	m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y,
		(long*)&poGeo.x, (long*)&poGeo.y);

	GetDegreeStringFromGeoCoor(strGeoCoorX, true, poGeo.x, iGeoCoorMultiFactor);
	GetDegreeStringFromGeoCoor(strGeoCoorY, false, poGeo.y, iGeoCoorMultiFactor);

	strCurPosition.Format("屏幕坐标 x: %d, y: %d ;  地理坐标 X:%s, Y:%s; ", point.x, point.y, strGeoCoorX, strGeoCoorY);

	if (strEblInfo != "")
	{
		strCurPosition += strEblInfo;
	}
	pStatus->SetPaneText(INDEX_PANE_FOR_MOUSE_POSITION, strCurPosition);//MOUSE_STATUS_BAR_INDEX 

	CView::OnMouseMove(nFlags, point);
}

void CYimaEncViewerView::RefreshScaleStatusBar()
{
	CStatusBar * pStatusBar = (CStatusBar *)AfxGetApp()->m_pMainWnd->
		GetDescendantWindow(AFX_IDW_STATUS_BAR);

	if (pStatusBar != NULL)
	{
		float curScale = m_pYimaEncCtrl->GetCurrentScale();

		CString strCurScale;
		strCurScale.Format("比例尺 1 : %d", (int)curScale);
		pStatusBar->SetPaneText(INDEX_PANE_FOR_SCALE, strCurScale);
	}
}

void CYimaEncViewerView::OnAreaZoomIn()
{
	// TODO: Add your command handler code here
	SetOperation(AREA_ZOOM_IN);

	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CMenu *pMenu = pFrame->GetMenu();
	CToolBar* pToolBar = (CToolBar*)pFrame->GetDescendantWindow(AFX_IDW_TOOLBAR);
	if (pMenu != NULL && pToolBar != NULL)
	{
		pMenu->CheckMenuItem(ID_AREA_ZOOM_IN, MF_CHECKED);
		pToolBar->GetToolBarCtrl().PressButton(ID_AREA_ZOOM_IN, true);
	}
}
void CYimaEncViewerView::OnLButtonUp(UINT nFlags, CPoint point)
{

	// TODO: Add your message handler code here and/or call default  
	if (!IsOnOperation(MEASURE_AREA))
	{
		m_icurEditPos = 0;
	}
	if (IsOnOperation(DRAG_EDITING_OBJECT))
	{
		if (m_nEditingWayPointID != 0)
		{//如果是在拖动航路点
			M_POINT newWpPoint;
			m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, (long*)&newWpPoint.x, (long*)&newWpPoint.y);

			m_pYimaEncCtrl->SetWayPointCoor(m_nEditingWayPointID, newWpPoint.x, newWpPoint.y);

			m_nEditingWayPointID = 0;
			m_pYimaEncCtrl->ClearHighLightPoints();
			Invalidate();
		}

		//自定义海图对象拖动编辑功能实现 -- 单击Buttton Up处理部分		
		if (IsOnOperation(EDITING_GEO_OBJECT))
		{
			if (m_iEditingPointPosOnEditingLine > -1)//说明正在拖动线和面的某个节点
			{
				M_POINT newPoint;
				m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y,
					(long*)&newPoint.x, (long*)&newPoint.y);

				if ((nFlags & MK_CONTROL) == 0 && (nFlags & MK_SHIFT) == 0)
				{ //如果Ctrl键和Shift键都没有同时按下，则为移动节点操作
					m_pYimaEncCtrl->tmMoveOnePointOfLineObject(m_editingUserMapObjPos.layerPos,
						m_editingUserMapObjPos.innerLayerObjectPos, m_iEditingPointPosOnEditingLine,
						newPoint.x, newPoint.y);
				}
				else
				{
					if ((nFlags & MK_CONTROL) != 0)
					{ //如果Ctrl键按下，则为添加节点操作，且添加到 m_iEditingPointPosOnEditingLine 节点前面
						m_pYimaEncCtrl->tmAddOnePointToLineOrFaceObject(m_editingUserMapObjPos.layerPos,
							m_editingUserMapObjPos.innerLayerObjectPos, m_iEditingPointPosOnEditingLine,
							newPoint.x, newPoint.y);
					}
					else if ((nFlags & MK_SHIFT) != 0)
					{
						//如果Shift键按下，则为添加节点操作，且添加到 m_iEditingPointPosOnEditingLine 节点后面
						m_pYimaEncCtrl->tmAddOnePointToLineOrFaceObject(m_editingUserMapObjPos.layerPos,
							m_editingUserMapObjPos.innerLayerObjectPos, m_iEditingPointPosOnEditingLine + 1,
							newPoint.x, newPoint.y);
					}
				}

				m_iEditingPointPosOnEditingLine = -1; //本次操作完毕，要复位 m_iEditingPointPosOnEditingLine 为无效值
			}
			else //正在拖动点物标
			{
				M_POINT newPoint;
				m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y,
					(long*)&newPoint.x, (long*)&newPoint.y);

				m_pYimaEncCtrl->tmSetPointObjectCoor(m_editingUserMapObjPos.layerPos,
					m_editingUserMapObjPos.innerLayerObjectPos, newPoint.x, newPoint.y); //移动点物标 
			}

			m_pYimaEncCtrl->tmSetObjectDynamicObjectOrNot(m_editingUserMapObjPos.layerPos,
				m_editingUserMapObjPos.innerLayerObjectPos, false);

			m_pYimaEncCtrl->tmSetTargetForRedoOperation();	//为Undo操作保存操作后物标信息，以实现Redo功能。 
		}

		Invalidate();

		CancelOperation(DRAG_EDITING_OBJECT);	//本次操作完毕，取消DRAG_EDITING_OBJECT这个操作状态	

		return;
	}

	if (IsOnOperation(ADD_LINE_OBJECT_MOUSEMOVING) && m_iEditingPointPosOnEditingLine >= 0)	//判断当前状态位于“添加物标时的动态节点添加状态”时做的处理
	{
		if (m_addingSpecialLineType == RECTANGLE_LN_TYPE || m_addingSpecialLineType == CIRCLE_LN_TYPE
			|| m_addingSpecialLineType == ELLIPSE_LN_TYPE || m_addingSpecialLineType == ARC_LN_TYPE
			|| m_addingSpecialLineType == PIE_LN_TYPE || m_addingSpecialLineType == BOW_LN_TYPE
			|| m_addingSpecialLineType == SECTOR_LN_TYPE)	//判断m_addingSpecialLineType的类型如果是以上的一种，
															//则在调用OnLButtonUp时结束该物标的添加，并弹出物标风格窗口选择显示风格
		{
			int editObjPos = m_pYimaEncCtrl->tmGetLayerObjectCount(m_iEditingUserMapLayerNum) - 1;

			bool bSetTwoNearPointForObject = false;
			if (m_nEditingLinePointCount == 2)
			{
				M_POINT scrnStartPo;
				m_pYimaEncCtrl->GetScrnPoFromGeoPo(m_editingLineGeoPoints[0].x, m_editingLineGeoPoints[0].y,
					(long*)&scrnStartPo.x, (long*)&scrnStartPo.y);
				if ((abs(point.x - scrnStartPo.x) + abs(point.y - scrnStartPo.y)) < 50)
				{//如果首尾两点距离"大约"小于50个像素, 则视为"过近"			
					bSetTwoNearPointForObject = true;
					return;
				}
			}
			else if (m_nEditingLinePointCount == 1)
			{
				bSetTwoNearPointForObject = true;
			}

			if (bSetTwoNearPointForObject)
			{//如果首尾两点距离"过近"，则返回不处理，用户需要在继续拖动，直至再单击鼠标后成功添加物标				
				return;
			}

			UserObject_SetAttributes(m_iEditingUserMapLayerNum, editObjPos);

			m_pYimaEncCtrl->tmPushInStackUndoOperation(ADD_GEO_OBJ, m_iEditingUserMapLayerNum,
				m_pYimaEncCtrl->tmGetLayerObjectCount(m_iEditingUserMapLayerNum) - 1);	//将编辑动作保存进Undo动作堆栈,用于做Undo操作
			m_pYimaEncCtrl->tmSetTargetForRedoOperation();	//为Undo操作保存操作后物标信息，以实现Redo功能。 

			m_iEditingPointPosOnEditingLine = -1;	//操作完毕,恢复m_iEditingPointPosOnEditingLine的值为-1  		
			m_pYimaEncCtrl->tmSetObjectDynamicObjectOrNot(m_iEditingUserMapLayerNum, editObjPos, false);//添加好了, 可以取消其Dynamic的动态属性了 	 

			CView::OnLButtonUp(nFlags, point);

			return;
		}
	}

	if (IsOnOperation(DRAW_EBL))
	{
		CancelOperation(DRAW_EBL);
		m_bHasDrawDragFirstPo = false;
		m_bHasPressedDragStartPo = false;
		return;
	}

	if (IsOnOperation(AREA_ZOOM_IN) || IsOnOperation(AREA_SELECT))
	{
		if (m_bHasDrawDragFirstPo)
		{
			if (IsOnOperation(AREA_ZOOM_IN))
			{
				CPoint rectZoomRightDownPo = point;

				m_pYimaEncCtrl->ZoomInByScreenRect(m_mouseDragFirstPo.x, m_mouseDragFirstPo.y,
					rectZoomRightDownPo.x, rectZoomRightDownPo.y);
			}
			else
			{
				BSTR retSelObjPosStrings = ::SysAllocStringLen(NULL,
					SEL_OBJ_MAX_COUNT * sizeof(MEM_GEO_OBJ_POS));

				int selObjCount =
					m_pYimaEncCtrl->SelectObjectsByScrnRect(&retSelObjPosStrings,
						m_mouseDragFirstPo.x, m_mouseDragFirstPo.y, point.x, point.y);

				if (selObjCount > 0)
				{
					MEM_GEO_OBJ_POS selectedObjPoses[SEL_OBJ_MAX_COUNT];
					memcpy(selectedObjPoses, retSelObjPosStrings, selObjCount * sizeof(MEM_GEO_OBJ_POS));

					SetHighlightObjects(selectedObjPoses, 1);

					Invalidate();

					static CSelectedGeoObjectsDlg* pSelGeoObjsDlg = NULL;
					if (pSelGeoObjsDlg != NULL)
					{
						delete pSelGeoObjsDlg;
					}

					pSelGeoObjsDlg = new CSelectedGeoObjectsDlg();

					if (pSelGeoObjsDlg != NULL)
					{
						pSelGeoObjsDlg->m_curSelectedObjCount = selObjCount;
						pSelGeoObjsDlg->SetSelectObjectPoses(selectedObjPoses, selObjCount);

						pSelGeoObjsDlg->Create(IDD_SEL_OBJECTS_DLG);
						pSelGeoObjsDlg->ShowWindow(SW_SHOW);
					}
				}

				SysFreeString(retSelObjPosStrings);
			}
		}

		m_bHasPressedDragStartPo = false;
		m_bHasDrawDragFirstPo = false;

		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);

		if (IsOnOperation(AREA_ZOOM_IN))
		{
			pFrame->UncheckMenusAndToolBarForMenuItem(ID_AREA_ZOOM_IN);
			CancelOperation(AREA_ZOOM_IN);
		}
		else
		{
			pFrame->UncheckMenusAndToolBarForMenuItem(ID_AREA_SELECT);
			CancelOperation(AREA_SELECT);
		}

		Invalidate();
	}

	if (IsOnOperation(HAND_ROAM))
	{
		if (m_bHasPressedDragStartPo)
		{
			m_pYimaEncCtrl->SetMapMoreOffset(point.x - m_mouseDragFirstPo.x, point.y - m_mouseDragFirstPo.y);

			m_bHasPressedDragStartPo = false;

			SetCursor(LoadCursor(NULL, IDC_ARROW));
			Invalidate();
			if (m_globalView != NULL)
			{
				m_globalView->ReSetViewPosion();
			}
		}
		ReleaseCapture();
		CancelOperation(HAND_ROAM);
	}

	if (IsOnOperation(DELAY_MAP) || IsOnOperation(HOLLOW_MAP))
	{
		if ((abs(point.x - m_mouseDragFirstPo.x) + abs(point.y - m_mouseDragFirstPo.y)) < 10)
		{
			return;
		}
		int scrnLen = sqrt(pow(point.x - m_mouseDragFirstPo.x, 2.0) + pow(point.y - m_mouseDragFirstPo.y, 2.0));
		m_pYimaEncCtrl->SetMapEffectRadius(0);
		float geoLen = m_pYimaEncCtrl->GetGeoLenFromScrnLen(scrnLen) / 1000;
		m_pYimaEncCtrl->SetMapEffectRadius(geoLen);
		SetOperation(NO_OPERATION);
		Invalidate();

	}
	CView::OnLButtonUp(nFlags, point);
}


void CYimaEncViewerView::OnCenterRotateMap()
{
	// TODO: Add your command handler code here

	float fGeoCoorMultiFactor = m_pYimaEncCtrl->GetGeoCoorMultiFactor();

	long centerScrnPoX, centerScrnPoY, centerGeoPoX, centerGeoPoY;

	centerScrnPoX = m_pYimaEncCtrl->GetDrawerScreenWidth() / 2;
	centerScrnPoY = m_pYimaEncCtrl->GetDrawerScreenHeight() / 2;

	CCenterRotateMapDlg cntrRotaDlg;
	m_pYimaEncCtrl->GetGeoPoFromScrnPo(centerScrnPoX, centerScrnPoY,
		&centerGeoPoX, &centerGeoPoY);

	cntrRotaDlg.m_fCntrGeoPoX = centerGeoPoX / fGeoCoorMultiFactor;
	cntrRotaDlg.m_fCntrGeoPoY = centerGeoPoY / fGeoCoorMultiFactor;
	cntrRotaDlg.m_fRotateDeg = m_pYimaEncCtrl->GetMapRoatedAngle();

	if (IDOK == cntrRotaDlg.DoModal())
	{
		//注意，要先调用 CenterMap 再调用 RotateMapByScrnCenter
		m_pYimaEncCtrl->CenterMap(
			cntrRotaDlg.m_fCntrGeoPoX * fGeoCoorMultiFactor,
			cntrRotaDlg.m_fCntrGeoPoY * fGeoCoorMultiFactor);

		m_pYimaEncCtrl->RotateMapByScrnCenter(cntrRotaDlg.m_fRotateDeg);
		RefreshScreenMap();
	}
}

void CYimaEncViewerView::PrintTheMapInTheScreen(CDC* pDC, CPrintInfo* pInfo, CString mapTitle, LOGFONT* titleFont,
	int nmapTitleLeftOrMiddleOrRight, CString remarks, LOGFONT* remarkFont, int nremarksLeftOrMiddleOrRight, int nscalenLeftOrMiddleOrRight)//0、居左 ，1、居中，2、居右
{

	int viewScrnWidth = m_pYimaEncCtrl->GetDrawerScreenWidth();
	int viewScrnHeight = m_pYimaEncCtrl->GetDrawerScreenHeight();
	float viewScrnHeightToWidthRate = (float)viewScrnHeight / viewScrnWidth;
	int paperScrnWidthByPixel = pDC->GetDeviceCaps(HORZRES); //得到纸张宽度(像为单位) 注意：在打印预览时使用 GetDeviceCaps(pDC->m_hDC, HORZRES) 不正确
	int paperScrnHeightByPixel = pDC->GetDeviceCaps(VERTRES); //得到纸张高度(像为单位)
	float marginWidthPercent = 0.1; //横向页边距百分比
	float marginHeadHeightPercent = 0.1; //顶部页边距百分比	

	int paperDrawerWidth = paperScrnWidthByPixel * (1 - 2 * marginWidthPercent); //计算出绘图区宽度
	int paperDrawerHeight = paperDrawerWidth * viewScrnHeightToWidthRate; //保持和View同样的长宽比

	int paperDrawerStartX = paperScrnWidthByPixel * marginWidthPercent; //绘图区起始横坐标
	int paperDrawerStartY = paperScrnHeightByPixel * marginHeadHeightPercent;  //绘图区起始纵坐标	

	int paperScrnWidthByMm = pDC->GetDeviceCaps(HORZSIZE);
	double mmToPixelMapFactor = paperScrnWidthByPixel / paperScrnWidthByMm; //得到像素与毫米的转换系数

	m_pYimaEncCtrl->RefreshDrawerForDirectDrawDC((long)pDC->m_hDC,
		paperDrawerWidth, paperDrawerHeight, paperDrawerStartX, paperDrawerStartY,
		false, mmToPixelMapFactor);//把海图绘制器目标环境hdc改为当前打印设备环境

	m_pYimaEncCtrl->DrawMapsInScreen((long)pDC->m_hDC); //重绘海图到目标打印设备  

	//以下打印文档标题	
	int ly = pDC->GetDeviceCaps(LOGPIXELSY);
	int cdcly = pDC->GetDeviceCaps(LOGPIXELSY);
	int cly = mmToPixelMapFactor * 25.4;

	int oldTitleFontHeight = titleFont->lfHeight;
	int oldRemarkFontHeight = remarkFont->lfHeight;

	CFont font;
	titleFont->lfHeight = abs(MulDiv(titleFont->lfHeight, pDC->GetDeviceCaps(LOGPIXELSY), 72));
	font.CreateFontIndirect(titleFont);

	CFont *pOldFont = pDC->SelectObject(&font);
	switch (nmapTitleLeftOrMiddleOrRight)
	{
	case 0:
		pDC->SetTextAlign(TA_LEFT | TA_BOTTOM);
		pDC->TextOut(paperDrawerStartX - 40, paperDrawerStartY - 40, mapTitle);
		break;
	case 1:
		pDC->SetTextAlign(TA_CENTER | TA_BOTTOM);
		pDC->TextOut(paperDrawerStartX + paperDrawerWidth / 2 - 40, paperDrawerStartY - 40, mapTitle);
		break;
	case 2:
		pDC->SetTextAlign(TA_RIGHT | TA_BOTTOM);
		pDC->TextOut(paperDrawerStartX + paperDrawerWidth + 40, paperDrawerStartY - 40, mapTitle);
		break;
	default:
		pDC->SetTextAlign(TA_CENTER | TA_BOTTOM);
		pDC->TextOut(paperDrawerStartX + paperDrawerWidth / 2 - 40, paperDrawerStartY - 40, mapTitle);
		break;

	}
	pDC->SelectObject(pOldFont);

	font.DeleteObject();
	int fontHeight = abs(MulDiv(14, pDC->GetDeviceCaps(LOGPIXELSY), 72));
	font.CreateFont(fontHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, GB2312_CHARSET,
		0, 0, 0, 0, "宋体");
	pOldFont = pDC->SelectObject(&font);

	CString strScaleInfo;
	int scale = m_pYimaEncCtrl->GetCurrentScale();
	strScaleInfo.Format("当前比例尺 1 : %d", scale);
	switch (nscalenLeftOrMiddleOrRight)
	{
	case 0:
		pDC->SetTextAlign(TA_LEFT | TA_TOP);
		pDC->TextOut(paperDrawerStartX - 40, paperDrawerStartY + paperDrawerHeight + 40, strScaleInfo);
		break;
	case 1:
		pDC->SetTextAlign(TA_CENTER | TA_TOP);
		pDC->TextOut(paperDrawerStartX + paperDrawerWidth / 2 + 40, paperDrawerStartY + paperDrawerHeight + 40, strScaleInfo);
		break;
	case 2:
		pDC->SetTextAlign(TA_RIGHT | TA_TOP);
		pDC->TextOut(paperDrawerStartX + paperDrawerWidth + 40, paperDrawerStartY + paperDrawerHeight + 40, strScaleInfo);
		break;
	default:
		pDC->SetTextAlign(TA_CENTER | TA_TOP);
		pDC->TextOut(paperDrawerStartX + paperDrawerWidth / 2 + 40, paperDrawerStartY + paperDrawerHeight + 40, strScaleInfo);
		break;

	}
	pDC->SelectObject(pOldFont);
	font.DeleteObject();

	remarkFont->lfHeight = abs(MulDiv(remarkFont->lfHeight, pDC->GetDeviceCaps(LOGPIXELSY), 72));
	font.CreateFontIndirect(remarkFont);
	pOldFont = pDC->SelectObject(&font);
	switch (nremarksLeftOrMiddleOrRight)
	{
	case 0:
		pDC->SetTextAlign(TA_LEFT | TA_TOP);
		pDC->TextOut(paperDrawerStartX - 40, paperDrawerStartY + paperDrawerHeight + 40, remarks);
		break;
	case 1:
		pDC->SetTextAlign(TA_CENTER | TA_TOP);
		pDC->TextOut(paperDrawerStartX + paperDrawerWidth / 2 + 40, paperDrawerStartY + paperDrawerHeight + 40, remarks);
		break;
	case 2:
		pDC->SetTextAlign(TA_RIGHT | TA_TOP);
		pDC->TextOut(paperDrawerStartX + paperDrawerWidth + 40, paperDrawerStartY + paperDrawerHeight + 40, remarks);
		break;
	default:
		pDC->SetTextAlign(TA_CENTER | TA_BOTTOM);
		pDC->TextOut(paperDrawerStartX + paperDrawerWidth / 2 + 40, paperDrawerStartY + paperDrawerHeight + 40, remarks);
		break;

	}
	pDC->SelectObject(pOldFont);

	//画边框
	CPen penDrawOutLine;
	penDrawOutLine.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&penDrawOutLine);
	POINT point[5];
	point[0].x = point[4].x = paperDrawerStartX;
	point[0].y = point[4].y = paperDrawerStartY;
	point[1].x = paperDrawerStartX + paperDrawerWidth;
	point[1].y = paperDrawerStartY;
	point[2].x = paperDrawerStartX + paperDrawerWidth;
	point[2].y = paperDrawerStartY + paperDrawerHeight;
	point[3].x = paperDrawerStartX;
	point[3].y = paperDrawerStartY + paperDrawerHeight;
	pDC->Polyline(point, 5);

	penDrawOutLine.DeleteObject();
	CPen penDrawInLine;
	penDrawInLine.CreatePen(PS_SOLID, 10, RGB(0, 0, 0));
	pDC->SelectObject(&penDrawInLine);
	point[0].x = point[4].x = paperDrawerStartX - 30;
	point[0].y = point[4].y = paperDrawerStartY - 30;
	point[1].x = paperDrawerStartX + paperDrawerWidth + 30;
	point[1].y = paperDrawerStartY - 30;
	point[2].x = paperDrawerStartX + paperDrawerWidth + 30;
	point[2].y = paperDrawerStartY + paperDrawerHeight + 30;
	point[3].x = paperDrawerStartX - 30;
	point[3].y = paperDrawerStartY + paperDrawerHeight + 30;
	pDC->Polyline(point, 5);
	pDC->SelectObject(pOldPen);
	penDrawInLine.DeleteObject();

	//打印完, 恢复海图绘制器指向当前海图屏幕
	RECT clientRect;
	GetClientRect(&clientRect);
	m_pYimaEncCtrl->RefreshDrawer((long)m_hWnd, clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top, 0, 0);

	titleFont->lfHeight = oldTitleFontHeight;
	remarkFont->lfHeight = oldRemarkFontHeight;
	////////////////////////////////////////////////////////////////////////////////////////////

	CView::OnPrint(pDC, pInfo);
}

void CYimaEncViewerView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class  

	//////////////////////////////// 打印方法1: 当前屏幕截图打印 //////////////////////////////
	/*
	pDC->SetMapMode(MM_TEXT);

	  CRect rectPage = pInfo->m_rectDraw;

		TEXTMETRIC tm;
		CFont font;
		CSize textSize;
		int cyChar;

		  //Set Margin
		  rectPage.top+=rectPage.bottom/48;
		  rectPage.bottom-=rectPage.bottom/48;
		  rectPage.left+=200;
		  rectPage.right-=200;

			// Print at 85% size within left/right margin
			CSize printSize, chartSize;
			chartSize.cx = m_pYimaEncCtrl->GetDrawerScreenWidth();
			chartSize.cy = m_pYimaEncCtrl->GetDrawerScreenHeight();

			  printSize.cx = (int)(rectPage.right*.85);
			  printSize.cy = (float)printSize.cx / (float)chartSize.cx * chartSize.cy;

				::StretchBlt(pDC->m_hDC, ((rectPage.right+rectPage.left)/2)-
				(printSize.cx/2),
				rectPage.top,
				printSize.cx,
				printSize.cy,
				(HDC)m_pYimaEncCtrl->GetDrawerHDC(),
				0, 0,
				chartSize.cx,
	chartSize.cy, SRCCOPY); */
	////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////// 打印方法2: 当前屏幕截图打印 /////////////////////////////// 
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	PrintTheMapInTheScreen(pDC, pInfo, pFrame->mapTitle, &(pFrame->titleFont), pFrame->nmapTitleLeftOrMiddleOrRight,
		pFrame->remarks, &(pFrame->remarkFont), pFrame->nremarksLeftOrMiddleOrRight, pFrame->nscaleLeftOrMiddleOrRight);
}

void CYimaEncViewerView::OnAddWaypoint()
{
	if (m_bOnRouteEditMode)
	{
		SetOperation(NO_OPERATION);
		SetOperation(ADD_WAYPOINT);
	}
	else
	{
		AfxMessageBox("在进行航路点操作前，请确认已进入航线编辑模式.");
	}
}

void CYimaEncViewerView::OnAddRoute()
{
	if (m_bOnRouteEditMode)
	{
		if (m_pYimaEncCtrl->GetWayPointsCount() > 1)
		{
			SetOperation(NO_OPERATION);
			SetOperation(ADD_ROUTE);
		}
		else
		{
			AfxMessageBox("当前没有足够的航路点来添加航线，请先添加航路点.");
		}
	}
	else
	{
		AfxMessageBox("在进行航线操作前，请确认已进入航线编辑模式.");
	}
}

#define DRAW_EDITING_LINE_COLOR RGB(0, 0, 255)
void CYimaEncViewerView::DrawEditingLineBeforeFinish()
{
	CDC* pDC = GetDC();
	CPen penDrawLine;

	penDrawLine.CreatePen(PS_SOLID, 2, DRAW_EDITING_LINE_COLOR);
	CPen* pOldPen = pDC->SelectObject(&penDrawLine);

	POINT currentPoint;
	m_pYimaEncCtrl->GetScrnPoFromGeoPo(
		m_editingLineGeoPoints[0].x, m_editingLineGeoPoints[0].y,
		(long*)&currentPoint.x, (long*)&currentPoint.y);

	for (int i = 0; i < m_nEditingLinePointCount - 1; i++)
	{
		POINT nextPoint;

		m_pYimaEncCtrl->GetScrnPoFromGeoPo(
			m_editingLineGeoPoints[i + 1].x, m_editingLineGeoPoints[i + 1].y,
			(long*)&nextPoint.x, (long*)&nextPoint.y);

		pDC->MoveTo(currentPoint);
		pDC->LineTo(nextPoint);

		currentPoint = nextPoint;
	}

	pDC->SelectObject(pOldPen);
	penDrawLine.DeleteObject();

	ReleaseDC(pDC);
}

void CYimaEncViewerView::OnDelWaypoint()
{
	// TODO: Add your command handler code here
	if (IsOnOperation(EDITING_WAY_POINT))
	{
		if (m_nEditingWayPointID != 0)
		{
			if (AfxMessageBox("您确定要删除该航路点吗?", MB_YESNO) == IDYES)
			{
				m_pYimaEncCtrl->DeleteWayPoint(m_nEditingWayPointID);
				m_nEditingWayPointID = 0;
				m_pYimaEncCtrl->ClearHighLightPoints();

				Invalidate();
			}
		}
	}
}

void CYimaEncViewerView::OnDelRoute()
{
	// TODO: Add your command handler code here
	if (IsOnOperation(EDITING_ROUTE))
	{
		if (m_nEditingRouteID != 0)
		{
			if (AfxMessageBox("您确定要删除该航线吗?", MB_YESNO) == IDYES)
			{
				m_pYimaEncCtrl->DeleteRoute(m_nEditingRouteID);
				m_nEditingRouteID = 0;
				m_pYimaEncCtrl->ClearHighLightLines();

				CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
				if (pFrame != NULL)
				{
					pFrame->RefreshNavBarRouteList();
				}

				Invalidate();
			}
		}
	}
}

void CYimaEncViewerView::OnDirectEditRoute()
{
	// TODO: Add your command handler code here
	CRouteEditDlg routeEditDlg;

	if (m_nEditingRouteID != 0)
	{
		routeEditDlg.m_editRouteID = m_nEditingRouteID;
		routeEditDlg.DoModal();
	}
	else
	{
		AfxMessageBox("您还没有选中航线!");
	}
}

void CYimaEncViewerView::OnEblLine()
{
	// TODO: Add your command handler code here
	SetOperation(NO_OPERATION);
	SetOperation(DRAW_EBL);
}

void CYimaEncViewerView::OnDelObject()
{
	// TODO: Add your command handler code here 
	if (m_curSelectedObjCount == 1) //如果之前有选中某个自定义海图对象则清楚选中状态
	{
		if (IsOnOperation(EDITING_GEO_OBJECT))
		{
			int layerPos = m_editingUserMapObjPos.layerPos;
			int innerLayerObjPos = m_editingUserMapObjPos.innerLayerObjectPos;

			if (AfxMessageBox("确定要删除该物标吗?", MB_YESNO) == IDYES)
			{
				m_pYimaEncCtrl->tmPushInStackUndoOperation(DEL_GEO_OBJ, layerPos, innerLayerObjPos);
				m_pYimaEncCtrl->tmSetTargetForRedoOperation();

				m_pYimaEncCtrl->tmDeleteGeoObject(layerPos, innerLayerObjPos);

				m_pYimaEncCtrl->ClearHighLightPoints();
				m_pYimaEncCtrl->ClearHighLightLines();
				m_pYimaEncCtrl->ClearHighLightFaces();

				Invalidate();
			}
		}
	}
}

void CYimaEncViewerView::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default    
	if (nIDEvent == 3)
	{
		CheckIfWheelStop();
		return;
	}


	if (IsOnDragingObjectOperation())
	{
		return;
	}

	if (m_pYimaEncCtrl == NULL)
	{
		return;
	}

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);

	/*******  测试移动自定义物标 **********/
	bool bTestMovingUserMapObjects = false;
	if (bTestMovingUserMapObjects)
	{
		int testUserLayerPos = 1;
		for (int objPos = 0; objPos < m_pYimaEncCtrl->tmGetLayerObjectCount(testUserLayerPos); objPos++)
		{
			long geox, geoy;
			m_pYimaEncCtrl->tmGetPointObjectCoor(testUserLayerPos, objPos, &geox, &geoy);
			long sx, sy;
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(geox, geoy, &sx, &sy);
			m_pYimaEncCtrl->GetGeoPoFromScrnPo(sx + 2, sy + 2, &geox, &geoy);
			m_pYimaEncCtrl->tmSetPointObjectCoor(testUserLayerPos, objPos, geox, geoy);

			Invalidate();
		}
	}

	/*******  Test Radar Refresh**********/
	bool bIfTestRadarRefresh = false;
	if (bIfTestRadarRefresh)
	{
		int nMapRefreshForRadarFrameTimeByMs = 20;
		int nMapRefreshForRadarFrameTimerCycle = nMapRefreshForRadarFrameTimeByMs / m_nTimerStep;

		int nMapRefreshFrameTimeByMs = 500;
		int nMapFullRefreshTimerCycle = nMapRefreshFrameTimeByMs / m_nTimerStep;

		static int nTimerTick = 0;
		int a = nTimerTick;

		if (nTimerTick % nMapFullRefreshTimerCycle == 0)
		{
			int nowAngle = m_pYimaEncCtrl->GetMapRoatedAngle();
			m_pYimaEncCtrl->RotateMapByScrnCenter(nowAngle + 10);
			int thenAngle = m_pYimaEncCtrl->GetMapRoatedAngle();
			Invalidate();
			static float scale;
			static bool bSet = false;
			if (!bSet)
			{
				scale = m_pYimaEncCtrl->GetCurrentScale();
				bSet = true;
			}
			else
			{
				float s = scale;
				float s1 = m_pYimaEncCtrl->GetCurrentScale();
				if (s != s1)
				{
					int a = 0;
				}
			}
			RefreshScaleStatusBar();
			return;
		}

		if (nTimerTick % nMapRefreshForRadarFrameTimerCycle == 0)
		{
			nRadarFrameNumber++;

			if (nRadarFrameNumber == 90000000)
			{
				nRadarFrameNumber = 0;
			}
			Invalidate();
		}

		nTimerTick++;

		if (nTimerTick == 90000000)
		{
			nTimerTick = 0;
		}

		return;
	}

	m_iMouseStoppedTimerCount++;

	/* 动态提示框的例子 -- 这里演示"鼠标停留提示"航路点信息 */
	if (m_iMouseStoppedTimerCount == TIMER_COUNT_TO_SHOW_TEXT_WHEN_MOUSE_STOP)
	{  //如果鼠标停留了的时间达到 TIMER_COUNT_TO_SHOW_TEXT_WHEN_MOUSE_STOP
		M_GEO_OBJ_POS selGeoObjPos;

		/* 使用屏幕的点来点击选定1个航路点*/
		long selWayPointID = SelectAWayPointByScrnPoint(
			m_mouseMoveCurrentPo.x, m_mouseMoveCurrentPo.y);
		if (selWayPointID != 0)
		{
			SetOperation(SHOWING_HINT_TEXT);//把当前操作状态设置为正在提示动态提示框,

			M_POINT selWpPoint;
			m_pYimaEncCtrl->GetWayPointCoor(selWayPointID, (long*)&selWpPoint.x,
				(long*)&selWpPoint.y);

			TCHAR strGeoCoorX[100];
			TCHAR strGeoCoorY[100];
			long iGeoCoorMultiFactor = m_pYimaEncCtrl->GetGeoCoorMultiFactor();
			GetDegreeStringFromGeoCoor(strGeoCoorX, true, selWpPoint.x, iGeoCoorMultiFactor);
			GetDegreeStringFromGeoCoor(strGeoCoorY, false, selWpPoint.y, iGeoCoorMultiFactor);

			CString strHintText;
			strHintText.Format("WP: %d \n\r %s \n\r %s", selWayPointID, strGeoCoorX, strGeoCoorY);

			HDC hdc = GetDC()->m_hDC;

			LOGFONT lf;
			memset(&lf, 0, sizeof(LOGFONT));       // zero out structure	0
			lf.lfHeight = 12;
			lf.lfCharSet = GB2312_CHARSET;
			lf.lfWeight = FW_NORMAL;
			lf.lfEscapement = 0;
			lf.lfOrientation = 0;
			strcpy(lf.lfFaceName, "宋体");        // request a face name "Arial"
			HFONT hTextFont = (HFONT)CreateFontIndirect(&lf);
			HFONT oldFont = (HFONT)SelectObject(hdc, hTextFont);

			MRECT textRect(0, 0, 0, 0);

			DrawText(hdc, strHintText, -1, (LPRECT)&textRect, DT_CALCRECT);

			textRect.leftTopPointX += m_mouseMoveCurrentPo.x;
			textRect.leftTopPointY += m_mouseMoveCurrentPo.y;
			textRect.rightDownPointX += m_mouseMoveCurrentPo.x;
			textRect.rightDownPointY += m_mouseMoveCurrentPo.y;

			CBrush brBackGound(RGB(180, 150, 150));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brBackGound.m_hObject);
			CPen rectEdgePen;
			rectEdgePen.CreatePen(PS_SOLID, 1, RGB(50, 50, 50));
			HPEN oldPen = (HPEN)SelectObject(hdc, rectEdgePen.m_hObject);

			m_rectHintText = MRECT(textRect.leftTopPointX, textRect.leftTopPointY,
				textRect.rightDownPointX + 30, textRect.rightDownPointY + 30);

			CPoint rectPoints[5];
			rectPoints[0].x = m_rectHintText.leftTopPointX;
			rectPoints[0].y = m_rectHintText.leftTopPointY;

			rectPoints[1].x = m_rectHintText.rightDownPointX;
			rectPoints[1].y = m_rectHintText.leftTopPointY;

			rectPoints[2].x = m_rectHintText.rightDownPointX;
			rectPoints[2].y = m_rectHintText.rightDownPointY;

			rectPoints[3].x = m_rectHintText.leftTopPointX;
			rectPoints[3].y = m_rectHintText.rightDownPointY;

			rectPoints[4].x = m_rectHintText.leftTopPointX;
			rectPoints[4].y = m_rectHintText.leftTopPointY;

			Polygon(hdc, rectPoints, 5);

			SelectObject(hdc, oldBrush);
			SelectObject(hdc, oldPen);

			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(0, 100, 255));

#define TEXT_OFFSET_VAL_TO_AVOID_MOUSE 20
			textRect.leftTopPointX += TEXT_OFFSET_VAL_TO_AVOID_MOUSE;
			textRect.leftTopPointY += TEXT_OFFSET_VAL_TO_AVOID_MOUSE;
			textRect.rightDownPointX += TEXT_OFFSET_VAL_TO_AVOID_MOUSE;
			textRect.rightDownPointY += TEXT_OFFSET_VAL_TO_AVOID_MOUSE;
			unsigned int drawTextFormat = 0;
			drawTextFormat |= DT_LEFT;

			DrawText(hdc, strHintText, -1, (LPRECT)&textRect, drawTextFormat);

			SelectObject(hdc, oldFont);
			DeleteObject(hTextFont);
			::ReleaseDC(m_hWnd, hdc);
		}
		else
		{
			m_iMouseStoppedTimerCount = 0;
		}
	}
	if (nIDEvent == 10)
	{
		std::list<M_COLOR_ATTENUATION>::iterator i;

		for (i = m_arrColorAttenuationObj.begin(); i != m_arrColorAttenuationObj.end(); ++i)
		{
			if (i->bInAttenuation == false)
			{
				continue;
			}
			long refLibFaceStyleID = 0;
			BOOL bFillColor = FALSE;
			long fillColor, iColorTransparent = 0;
			long fontHeight, fontColor, textOffsetX, textOffsetY;
			BOOL bBold, bItalic;
			BSTR retText, retFontName;
			retText = ::SysAllocStringLen(NULL, 1024);
			retFontName = ::SysAllocStringLen(NULL, 255);
			long layPos, innerLayerPos;
			m_pYimaEncCtrl->tmGetObjectPosFromID(i->layerId, i->objId, &layPos, &innerLayerPos);
			m_pYimaEncCtrl->tmGetFaceObjectStyle(layPos, innerLayerPos, &refLibFaceStyleID,
				&bFillColor, &fillColor, &iColorTransparent, &retText, &retFontName,
				&fontHeight, &fontColor, &bBold, &bItalic, &textOffsetX, &textOffsetY);
			::SysFreeString(retText);
			::SysFreeString(retFontName);

			if (bFillColor == FALSE)
			{
				continue;
			}
			iColorTransparent = iColorTransparent - i->decreaseValuePreSec;
			if (iColorTransparent <= 10)
			{
				i->bInAttenuation = false;
				iColorTransparent = 10;
			}
			m_pYimaEncCtrl->tmSetFaceObjectStyleRefLib(layPos, innerLayerPos, refLibFaceStyleID, bFillColor, fillColor, bFillColor, iColorTransparent, FALSE, 0);
			m_pYimaEncCtrl->ForcelyRefreshMap();
			RefreshScreenMap();
		}
	}

	if (TIME_ODU_PARSE == nIDEvent)
	{
		vector<std::string> cells;
		bool exist = false;
		ODU oduInfo;
		size_t first = recvODUMsg.find("VTS");
		while (string::npos != first)
		{
			first = recvODUMsg.find("VTS", first);
			size_t last = recvODUMsg.find("#", first);
			if (string::npos != first)
			{
				string msgSub = recvODUMsg.substr(first, last);
				cells = split(msgSub, ";");
				if (cells[0] == "VTSODU-LG")			//ODU登录消息
				{
					oduInfo.ID = cells[1];
					oduInfo.IP = cells[2];
					oduInfo.Port = atoi(cells[3].data());
					oduInfo.checkcount = 10;
					if (oduList.empty())
					{
						oduList.push_back(oduInfo);
					}
					else
					{
						list<ODU>::iterator iter;
						for (iter = oduList.begin(); iter != oduList.end(); iter++)
						{
							if ((iter->ID == cells[1]) && (iter->IP == cells[2]) && (iter->Port == atoi(cells[3].data())))
							{
								iter->checkcount++;
								exist = true;
							}
						}
						if (!exist)
						{
							oduList.push_back(oduInfo);
						}
					}
					if (radar_set != NULL)
					{
						radar_set->refreshODUList(oduList);
					}
				}
			}
			//查找下一个报头
			first = last;
		}
	}
	if (TIME_SET_ODUCOUNT == nIDEvent)
	{
		if (!oduList.empty())
		{
			list<ODU>::iterator iter;
			for (iter = oduList.begin(); iter != oduList.end(); )
			{
				iter->checkcount--;
				if (iter->checkcount < 5)
				{
					iter = oduList.erase(iter);
					continue;
				}
				iter++;
			}
		}
	}
	if (TIME_REFRESH_RADARLIST == nIDEvent)
	{
		CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;

		pFrame->RefreshNavBarRadarList();
	}
	if (TIMER_REFRESH_OTHERVESSEL == nIDEvent)
	{
		CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		CYimaEncViewerView* pView = (CYimaEncViewerView*)pFrame->GetActiveView();
		if (pView != NULL)
		{
			if (pView->IsOnDragingObjectOperation())
			{
				return;
			}
			char chMsg[255];
			memset(chMsg, '\0', 255);
			pFrame->RefreshNavigationDlgBar(chMsg);
			pFrame->RefreshOtherVesselPositions(chMsg);

			/* 动态提示框注释 --- 注意如果当前正在显示动态提示框, 则不能刷新屏幕, 否则动态框被刷掉了 */
			if (!pView->IsOnOperation(HAND_ROAM) && !pView->IsOnOperation(SHOWING_HINT_TEXT) && !pView->bMouseWheelState)
			{
				pView->Invalidate();
			}
			if (strlen(chMsg) > 0)
			{
				AfxMessageBox(chMsg);
			}
		}
	}

	CView::OnTimer(nIDEvent);
}

/*** 此函数中均为一些接口调用示例代码 ***/
void CYimaEncViewerView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	int a = m_pYimaEncCtrl->GetMemMapCount();

	bool bSetOwnShipPositionByMouse = true;
	if (bSetOwnShipPositionByMouse)
	{
		long geoPoX, geoPoY;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, &geoPoX, &geoPoY);
		m_pYimaEncCtrl->SetOwnShipCurrentInfo(geoPoX, geoPoY, 0, 0, 0, 0, 0);
		char chMsg[255];
		memset(chMsg, '\0', 255);
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
		pFrame->RefreshNavigationDlgBar(chMsg);
		CYimaEncViewerView* pView = (CYimaEncViewerView*)(pFrame->GetActiveView());
		if (!pView->IsOnOperation(HAND_ROAM) && !pView->IsOnOperation(SHOWING_HINT_TEXT))
		{
			pView->Invalidate();
		}
		if (strlen(chMsg) > 0)
		{
			AfxMessageBox(chMsg);
		}
	}

	bool bTestAPI_IsShipCrossingSafetyContour = false;
	if (bTestAPI_IsShipCrossingSafetyContour)
	{
		long geoPoX, geoPoY;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, &geoPoX, &geoPoY);
		m_pYimaEncCtrl->SetOwnShipCurrentInfo(geoPoX, geoPoY, 0, 0, 0, 0, 0);
		long vslPoX, vslPoY, vslInScrnPoX, vslInScrnPoY;
		BOOL bVslIsArpaOrAis;
		m_pYimaEncCtrl->GetOwnShipCurrentInfo(&vslPoX, &vslPoY, 0, 0, 0, 0, 0);

		if (m_pYimaEncCtrl->IsShipCrossingSafeCenterLine(vslPoX, vslPoY, 10))
		{
			AfxMessageBox("Ship crossing safe center line!");
		}

		if (m_pYimaEncCtrl->IsShipCrossingSafetyContour(vslPoX, vslPoY, 0, 10))
		{
			AfxMessageBox("Ship out safety area!");
		}
	}

	bool bTestAPI_SetObjectAttrValueString = false;
	if (bTestAPI_SetObjectAttrValueString)
	{
		BSTR retObjValString = ::SysAllocStringLen(NULL, 1183 * 4 + 10);
		BSTR retObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));

		int sndLyrPosi = m_pYimaEncCtrl->GetLayerPosByToken(-1, "SOUNDG");
		int sndCount = m_pYimaEncCtrl->GetLayerObjectCountOfMap(0, sndLyrPosi);
		for (int i = 0; i < sndCount; i++)
		{
			char str[1183 * 4];
			for (int n = 0; n < 1183 * 4; n++)
			{
				str[n] = 'a';
			}
			str[1183 * 4 - 1] = 0;

			//char str1[] = "asdfds";
			m_pYimaEncCtrl->SetObjectAttrValueString(0, sndLyrPosi, i, 19, str);

			MEM_GEO_OBJ_POS obp = MEM_GEO_OBJ_POS(0, sndLyrPosi, i);
			memcpy(retObjPos, &obp, sizeof(MEM_GEO_OBJ_POS));
			m_pYimaEncCtrl->GetObjectAttrString(&retObjPos, 19, &retObjValString);

			CString strObjVal = retObjValString;
			AfxMessageBox(strObjVal);
			int a = 0;
		}
	}

	bool bTestAPI_SetSoundingShowColor = false;
	if (bTestAPI_SetSoundingShowColor)
	{
		m_pYimaEncCtrl->SetSoundingShowColor(true, RGB(255, 0, 0), RGB(0, 0, 255));
	}

	/***** 测试本船是否靠近某个线对象函数 *****/
	bool bTestShipNearLine = false;
	if (bTestShipNearLine)
	{
		//准备对第1幅内存海图的第1个等深线对象进行处理
		MEM_GEO_OBJ_POS objPos(m_pYimaEncCtrl->GetMemMapCount() - 1, 0, 0);	//取自定义海图、第1个图层、第1个物标
		BSTR strObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));
		memcpy(strObjPos, &objPos, sizeof(MEM_GEO_OBJ_POS)); //构造BSTR类型的物标索引

		int linePoCount = m_pYimaEncCtrl->GetLineObjectCoorCount(&strObjPos);
		//m_pYimaEncCtrl->GetFaceOutBndryCoorCount(&strObjPos);
		if (linePoCount > 0)
		{
			BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * linePoCount);
			m_pYimaEncCtrl->GetLineObjectCoors(&strObjPos, &strLinePoints); //获取线物标的坐标点 
			//m_pYimaEncCtrl->GetFaceOutBndryCoors(&strObjPos, &strLinePoints);

			long vslPoX, vslPoY, vslInScrnPoX, vslInScrnPoY;
			BOOL bVslIsArpaOrAis;
			m_pYimaEncCtrl->GetOwnShipCurrentInfo(&vslPoX, &vslPoY,
				0, 0, 0, 0, 0);
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(vslPoX, vslPoY, &vslInScrnPoX, &vslInScrnPoY);

			int scrnLen = m_pYimaEncCtrl->GetScrnLenFromGeoLen(2000 * 1000);
			bool bSelect =
				m_pYimaEncCtrl->IsGeoLineSelectByScrnPoint(vslInScrnPoX, vslInScrnPoY, (BSTR*)&strLinePoints, linePoCount, scrnLen);
			//m_pYimaEncCtrl->IsGeoFaceSelectByScrnPoint(vslInScrnPoX, vslInScrnPoY, (BSTR*)&strLinePoints, linePoCount); 

			if (bSelect)
			{
				int a = 0;
			}

			::SysFreeString(strLinePoints);
		}

		::SysFreeString(strObjPos);
	}

	////////////////// 测试水深点相关的接口 Test Sounding Relevant methods /////////////////////
	bool bIfTestSoundingMethods = true;
	if (bIfTestSoundingMethods)
	{
		int sndLyrPos = m_pYimaEncCtrl->GetLayerPosByToken(-1, "SOUNDG");
		//获取水深点图层的物标个数 -- 注意！！该图层的一个物标并非就是一个“水深点”，而是一个“水深点集合”，一个“水深点集合”包含多个水深点
		int sndSetObjCount = m_pYimaEncCtrl->GetSoundingSetPointCount(m_pYimaEncCtrl->GetMemMapCount() - 2, sndLyrPos, 0);
		for (int s = 0; s < sndSetObjCount; s++)
		{
			float depth;
			long sndX, sndY;

			m_pYimaEncCtrl->GetSoundingSetPointDepth(m_pYimaEncCtrl->GetMemMapCount() - 2,
				sndLyrPos, 0, s, &depth, &sndX, &sndY);	  //查询“水深点集合物标”中某个水深点的深度值及坐标
			m_pYimaEncCtrl->SetSoundingSetPointDepth(m_pYimaEncCtrl->GetMemMapCount() - 2,
				sndLyrPos, 0, s, 300); //设置“水深点集合物标”中某个水深点的深度
			m_pYimaEncCtrl->GetSoundingSetPointDepth(m_pYimaEncCtrl->GetMemMapCount() - 2,
				sndLyrPos, 0, s, &depth, &sndX, &sndY);	 //测试检查一下上一句有没有设成功
		}

		long geox, geoy;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, &geox, &geoy);
		float selSndDepth;
		long selSndPosInSndObj = -1;
		BSTR selSndObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));
		bool bSndSelect = m_pYimaEncCtrl->GetSoundPointSelectByGeoPoint(geox, geoy, 1000000, &selSndDepth,
			&selSndObjPos, &selSndPosInSndObj);

		return;
	}
	////////////////////////////////////////////////////////////////////////////////////////////

	bool bIfTestSecureManage = false;
	if (bIfTestSecureManage)
	{
		long geoPoX, geoPoY;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, &geoPoX, &geoPoY);

		if (m_pYimaEncCtrl->IsShipOffRoute(geoPoX, geoPoY, 1, 100))
		{
			AfxMessageBox("Off route!");
		}

		if (m_pYimaEncCtrl->IsShipCrossingSafetyContour(geoPoX, geoPoY, 45, 400))
		{
			AfxMessageBox("Crossing Safety Contour!");
		}

		long retObjMapPos, retObjLayerPos, retObjInnerLayerPos;
		retObjMapPos = retObjLayerPos = retObjInnerLayerPos = -1;
		if (m_pYimaEncCtrl->IsShipApproachingIsolatedDanger(geoPoX, geoPoY, 10000,
			&retObjMapPos, &retObjLayerPos, &retObjInnerLayerPos))
		{
			AfxMessageBox("Approaching IsolatedDanger!");
		}
	}

	bool bTestGetLibMapInfo = false;
	if (bTestGetLibMapInfo)
	{
		float originalScale = 0;
		long left, right, up, down;

		m_pYimaEncCtrl->GetLibMapInfo(0, NULL, NULL, &originalScale,
			&left, &right, &up, &down, NULL, NULL, NULL, NULL, NULL, NULL, NULL); //得到海图库海图信息 

		m_pYimaEncCtrl->SetCurrentScale(originalScale);

		m_pYimaEncCtrl->CenterMap(((float)left + right) / 2,
			((float)up + down) / 2);

		/* YIMAENC COMMENT: 注意!! 由于地理坐标值可能接近4字节
		long 型变量的上限(但不会超出)，所以在做加法或乘法时需要转换为float型
		以防止溢出！*/
	}

	/***** Test Draw OwnShip and Other vessel(s) example below ****/
	bool bIfTestOwnShipFunctions = false;
	if (bIfTestOwnShipFunctions)
	{
		m_pYimaEncCtrl->SetDrawShipOptions(true, true,
			true, true, 0, true, 0, 100, 50, 60);
		m_pYimaEncCtrl->SetDrawShipOptions(false, true,
			true, true, 0, true, 0, 50, 0, 60);
		m_pYimaEncCtrl->SetShipTrackShowOrNot(false, true, -1, false);

		m_pYimaEncCtrl->SetDrawOwnShipSpecialOptions(false, false, false, 0);
		m_pYimaEncCtrl->SetOwnShipBasicInfo(100, 30, "Yuan Wang hao", "12007");
		long ownShpGeoPoX, ownShpGeoPoY;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(125, 125, &ownShpGeoPoX, &ownShpGeoPoY);
		m_pYimaEncCtrl->SetOwnShipCurrentInfo(ownShpGeoPoX,
			ownShpGeoPoY, 30, 45, 60, 30, 20);
	}

	/*****  "Other vessels" management example below  ******/
	bool bIfTestOtherVesselFunctions = false;
	if (bIfTestOtherVesselFunctions)
	{
		long geoPoX, geoPoY;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(100, 100, &geoPoX, &geoPoY);

		int vc = m_pYimaEncCtrl->GetOtherVesselCount();
		SHIP_ID addedVsslID = m_pYimaEncCtrl->AddOtherVessel(false, geoPoX,
			geoPoY, 120, 210, 45, 50, 60);

		vc = m_pYimaEncCtrl->GetOtherVesselCount();

		long geoPoX1, geoPoY1;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(200, 200, &geoPoX1, &geoPoY1);
		m_pYimaEncCtrl->AddOtherVessel(true, geoPoX1,
			geoPoY1, 300, 210, 45, 50, 60);

		//测试选中位于屏幕坐标(200, 200)处的一个Other Vessel, 该对象被红色高亮显示
		SHIP_ID selShipID = m_pYimaEncCtrl->SelectOtherVesselByScrnPoint(200, 200);

		//测试ID和Pos之间的转换
		SHIP_ID frstVesslID = m_pYimaEncCtrl->GetOtherVesselID(0);
		SHIP_ID scndVesslID = m_pYimaEncCtrl->GetOtherVesselID(1);
		int nPosOfFrstID = m_pYimaEncCtrl->GetOtherVesselPosOfID(frstVesslID);
		int nPosOfScndID = m_pYimaEncCtrl->GetOtherVesselPosOfID(scndVesslID);
	}

	/****** 测试读取线物标的坐标结点 ******/
	bool bIfTestReadLineObjectCoors = false;
	if (bIfTestReadLineObjectCoors)
	{
		//得到等深线图层的索引Pos 
		CString strLayerToken = "DEPCNT";
		int depthLineLayerPos = m_pYimaEncCtrl->GetLayerPosByToken(-1, strLayerToken); //获取图层索引

		//准备对第1幅内存海图的第1个等深线对象进行处理
		MEM_GEO_OBJ_POS objPos(0, depthLineLayerPos, 0);
		BSTR strObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));
		memcpy(strObjPos, &objPos, sizeof(MEM_GEO_OBJ_POS));

		//先得到其结点个数
		int linePoCount = m_pYimaEncCtrl->GetLineObjectCoorCount(&strObjPos);

		if (linePoCount > 0)
		{
			//得到其结点坐标到BSTR字符串
			BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * linePoCount);
			m_pYimaEncCtrl->GetLineObjectCoors(&strObjPos, &strLinePoints);

			//拷贝BSTR字符串到M_POINT点数组进行处理
			M_POINT linePoints[10000];
			memcpy(linePoints, strLinePoints, sizeof(M_POINT) * linePoCount);

			SysFreeString(strLinePoints);
		}

		SysFreeString(strObjPos);
	}

	/******  "Route" management example below .******/
	bool bIfTestRouteFunctions = false;
	if (bIfTestRouteFunctions)
	{
		long wpGeoPoX1, wpGeoPoY1;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(300, 300, &wpGeoPoX1, &wpGeoPoY1);

		long wpGeoPoX2, wpGeoPoY2;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(350, 350, &wpGeoPoX2, &wpGeoPoY2);

		long wpGeoPoX3, wpGeoPoY3;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(380, 320, &wpGeoPoX3, &wpGeoPoY3);

		long wpGeoPoX4, wpGeoPoY4;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(400, 300, &wpGeoPoX4, &wpGeoPoY4);

		long wpGeoPoX5, wpGeoPoY5;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(450, 400, &wpGeoPoX5, &wpGeoPoY5);

		long wpID1 = m_pYimaEncCtrl->AddWayPoint(wpGeoPoX1, wpGeoPoY1, "wp1");
		long wpID2 = m_pYimaEncCtrl->AddWayPoint(wpGeoPoX2, wpGeoPoY2, "wp2");
		long wpID3 = m_pYimaEncCtrl->AddWayPoint(wpGeoPoX3, wpGeoPoY3, "wp3");
		long wpID4 = m_pYimaEncCtrl->AddWayPoint(wpGeoPoX4, wpGeoPoY4, "wp4");
		long wpID5 = m_pYimaEncCtrl->AddWayPoint(wpGeoPoX5, wpGeoPoY5, "wp5");

		bool bTestDeleteRoute = false;
		if (bTestDeleteRoute)
		{
			bool suc = m_pYimaEncCtrl->DeleteWayPoint(2);
			long wpID = m_pYimaEncCtrl->GetWayPointIDFromPos(2);
		}

		long wpIDs[5];
		wpIDs[0] = wpID1;
		wpIDs[1] = wpID2;
		wpIDs[2] = wpID3;
		wpIDs[3] = wpID4;
		wpIDs[4] = wpID5;

		//先加5个点中的4个
		BSTR bstrWpIDs = ::SysAllocStringLen(NULL, ROUTE_WAY_POINTS_MAX_COUNT * 2);
		memcpy(bstrWpIDs, wpIDs, 5 * sizeof(int));
		long routeID = m_pYimaEncCtrl->AddRoute(&bstrWpIDs, "Test route", 4, true);
		SysFreeString(bstrWpIDs);
		//再加第5个, 为了测试AddRouteWayPoint函数  

		long rtWpIDs[100];
		M_POINT points[100];

		bstrWpIDs = ::SysAllocStringLen(NULL, ROUTE_WAY_POINTS_MAX_COUNT * 2);
		int rtWpCount = m_pYimaEncCtrl->GetRouteWayPointsID(routeID, &bstrWpIDs);
		memcpy(rtWpIDs, bstrWpIDs, 5 * sizeof(int));
		SysFreeString(bstrWpIDs);

		if (rtWpCount > 0)
		{
			for (int wpNum = 0; wpNum < rtWpCount; wpNum++)
			{
				m_pYimaEncCtrl->GetWayPointCoor(rtWpIDs[wpNum],
					(long*)&points[wpNum].x,
					(long*)&points[wpNum].y);
			}
		}

		/* 测试屏幕鼠标点击选中线物标的函数*/
		bool bTestSelectGeoLine = true;
		if (bTestSelectGeoLine)
		{
			BSTR strLinePoints = ::SysAllocStringLen(NULL,
				sizeof(M_POINT) * rtWpCount);
			memcpy(strLinePoints, points, sizeof(M_POINT) * rtWpCount);

			bool bSelect =
				m_pYimaEncCtrl->IsGeoLineSelectByScrnPoint(350, 320,
				(BSTR*)&strLinePoints, rtWpCount, 5);

			::SysFreeString(strLinePoints);
		}

		m_pYimaEncCtrl->SetRouteName(1, "ccccc");
	}

	/***** GetDistBetwTwoPoint 与 GetGeoLenFromScrnLen 调用范例  ******/
	bool bIfTestGeoCaculateFunctions = false;
	if (bIfTestGeoCaculateFunctions)
	{
		long geoPoX, geoPoY;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(100, 100, &geoPoX, &geoPoY);

		long geoPoX1, geoPoY1;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(200, 200, &geoPoX1, &geoPoY1);

		double dist = m_pYimaEncCtrl->GetDistBetwTwoPoint(
			geoPoX, geoPoY, geoPoX1, geoPoY1);

		double geoLen = m_pYimaEncCtrl->GetGeoLenFromScrnLen(100 * sqrt(2.0));
	}

	/***** 下面为所有 顶层海图接口(所有以"tm"开头的函数)调用范例  *****/
	bool bIfTestUserMapFunctions = false;
	if (bIfTestUserMapFunctions)
	{
		int layerCount = m_pYimaEncCtrl->tmGetLayerCount();
		if (layerCount > 0)
		{
			bool bResult = true;

			long geoPoX, geoPoY;
			m_pYimaEncCtrl->GetGeoPoFromScrnPo(100, 100, &geoPoX, &geoPoY);

			long geoPoX1, geoPoY1;
			m_pYimaEncCtrl->GetGeoPoFromScrnPo(200, 200, &geoPoX1, &geoPoY1);

			bResult = m_pYimaEncCtrl->tmAppendObjectInLayer(0, TYPE_NULL);
			int geoType = m_pYimaEncCtrl->tmGetLayerGeoType(0);

			BSTR strLinePoints = ::SysAllocStringLen(NULL,
				sizeof(M_POINT) * 2);
			M_POINT geoPoints[2];
			geoPoints[0] = M_POINT(geoPoX, geoPoY);
			geoPoints[1] = M_POINT(geoPoX1, geoPoY1);
			memcpy(strLinePoints, geoPoints, sizeof(M_POINT) * 2);

			bResult = m_pYimaEncCtrl->tmSetLineObjectCoors(0, 0, 2, &strLinePoints);

			::SysFreeString(strLinePoints);

			bResult = m_pYimaEncCtrl->tmAppendObjectInLayer(2, TYPE_NULL);
			geoType = m_pYimaEncCtrl->tmGetLayerGeoType(2);

			strLinePoints = ::SysAllocStringLen(NULL,
				sizeof(M_POINT) * 3);

			M_POINT rgnPoints[3];
			rgnPoints[0] = M_POINT(geoPoX, geoPoY);
			rgnPoints[1] = M_POINT(geoPoX1, geoPoY1);
			m_pYimaEncCtrl->GetGeoPoFromScrnPo(100, 200,
				(long*)&rgnPoints[2].x, (long*)&rgnPoints[2].y);

			memcpy(strLinePoints, rgnPoints, sizeof(M_POINT) * 3);

			bResult = m_pYimaEncCtrl->tmSetFaceObjectCoors(2, 0, 3, &strLinePoints);

			int attrCount = m_pYimaEncCtrl->tmGetLayerObjectAttrCount(0);
			BSTR strAttrName = ::SysAllocStringLen(NULL, 256);
			m_pYimaEncCtrl->tmGetLayerObjectAttrName(0, 0, &strAttrName);
			CString strName = strAttrName;
			M_DATA_TYPE_ID dataType = (M_DATA_TYPE_ID)m_pYimaEncCtrl->tmGetLayerObjectAttrType(0, 1);
			m_pYimaEncCtrl->tmSetObjectAttrValueString(0, 0, 0, "sdfsdfdff");
			m_pYimaEncCtrl->tmSetObjectAttrValueString(0, 0, 1, BOOL_BE_FALSE_STRING);
			m_pYimaEncCtrl->tmGetObjectAttrValueString(0, 0, 1, &strAttrName);

			bResult = m_pYimaEncCtrl->tmAppendObjectInLayer(1, TYPE_NULL);
			m_pYimaEncCtrl->tmSetPointObjectCoor(1, 0, geoPoX, geoPoY);
			m_pYimaEncCtrl->tmGetPointObjectCoor(1, 0, &geoPoX1, &geoPoY1);

			int poCount = m_pYimaEncCtrl->tmGetFaceObjectCoors(2, 0, &strLinePoints);
			memcpy(rgnPoints, strLinePoints, sizeof(M_POINT) * poCount);

			M_GEO_OBJ_POS objPoses[255];
			BSTR strRetSelObjPoses = ::SysAllocStringLen(NULL,
				sizeof(M_GEO_OBJ_POS) * 255);
			int selObjCount =
				m_pYimaEncCtrl->tmSelectObjectsByScrnPo(150, 180, &strRetSelObjPoses);
			memcpy(objPoses, strRetSelObjPoses, sizeof(M_GEO_OBJ_POS) * selObjCount);

			strName = strAttrName;
			::SysFreeString(strAttrName);
		}
	}

	bool bTestAPI_IsScrnPointInFaceGeoObject = false;
	if (bTestAPI_IsScrnPointInFaceGeoObject)
	{
		long geoPointX, geoPointY;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, &geoPointX, &geoPointY);
		bool bPoint1InMe = m_pYimaEncCtrl->IsPointInFaceGeoObject(geoPointX, geoPointY,
			m_curSelectedObjPoses[0].memMapPos,
			m_curSelectedObjPoses[0].layerPos, m_curSelectedObjPoses[0].innerLayerPos, true);
		if (bPoint1InMe)
		{
			AfxMessageBox("鼠标位于当前选中面物标内!");
		}
	}

	bool bTestAPI_IsGeoObjectNearPoint = false;
	if (bTestAPI_IsGeoObjectNearPoint)
	{
		BOOL bNear = false;
		long testGeoPoX, testGeoPoY;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, &testGeoPoX, &testGeoPoY);

		if (m_curSelectedObjCount > 0)
		{
			m_pYimaEncCtrl->IsGeoObjectNearPoint(m_curSelectedObjPoses[0].memMapPos,
				m_curSelectedObjPoses[0].layerPos, m_curSelectedObjPoses[0].innerLayerPos,
				testGeoPoX, testGeoPoY, 0, &bNear);
			if (bNear)
			{
				AfxMessageBox("当前选中物标距离鼠标双击处过近");
			}
		}
		return;
	}

	bool bTestOtherVesselTextShow = false;
	if (bTestOtherVesselTextShow)
	{
		m_pYimaEncCtrl->SetOtherVesselShowText(0, true, "aaaa", false, 0, false, 0);
	}

	bool bTestGetWayPointName = false;
	if (bTestGetWayPointName)
	{
		m_pYimaEncCtrl->SetWayPointShowOrNot(true, 0, true, true);
		UINT frstWpID = m_pYimaEncCtrl->GetWayPointIDFromPos(0);
		m_pYimaEncCtrl->SetWayPointName(frstWpID, _T("aaa"));
		BSTR bstrWpName = ::SysAllocStringLen(NULL, 255);
		if (m_pYimaEncCtrl->GetWayPointName(frstWpID, &bstrWpName))
		{
			CString strWpName = bstrWpName;

			SysFreeString(bstrWpName);
		}
		m_pYimaEncCtrl->SetScaleBarPosition(false, 100, 100);

		int wpCount = m_pYimaEncCtrl->GetWayPointsCount();
		for (int wpNum = 0; wpNum < wpCount; wpNum++)
		{
			CString strWpText;
			long wpID = m_pYimaEncCtrl->GetWayPointIDFromPos(wpNum);
			strWpText.Format(_T("编号:%d"), wpID);
			m_pYimaEncCtrl->SetWayPointShowText(wpNum, true, strWpText, true, 28, true, 0x0000ff0);
		}
	}

	/***** 测试航路点安全性 *****/
	bool bIsDemoToTestWayPointSafety = false; //是否执行测试航路点安全性的demo代码
	if (bIsDemoToTestWayPointSafety)
	{
		M_POINT wayPointGeoPo; //航路点坐标

		//这里去鼠标双击的位置作为航路点的示例位置
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, (long *)&wayPointGeoPo.x, (long *)&wayPointGeoPo.y);

		//再判断有否选中S57海图对象
		BSTR retSelObjPosStrings = ::SysAllocStringLen(NULL,
			SEL_OBJ_MAX_COUNT * sizeof(MEM_GEO_OBJ_POS));

		M_POINT wpScrnPoint;
		m_pYimaEncCtrl->GetScrnPoFromGeoPo(wayPointGeoPo.x, wayPointGeoPo.y, (long *)&wpScrnPoint.x, (long *)&wpScrnPoint.y);

		//判断航路点对应的该屏幕点选中了哪些物标
		int selObjCount = m_pYimaEncCtrl->SelectObjectsByScrnPoint(&retSelObjPosStrings, wpScrnPoint.x, wpScrnPoint.y);

		if (selObjCount > 0)
		{
			MEM_GEO_OBJ_POS selectedObjPoses[SEL_OBJ_MAX_COUNT];
			memcpy(selectedObjPoses, retSelObjPosStrings,
				selObjCount * sizeof(MEM_GEO_OBJ_POS));

			//下面在返回的物标里逐个判断是否有属于不宜添加航路点的图层的物标
			for (int objNum = 0; objNum < selObjCount; objNum++)
			{
				CString strMsg;
				int wrkLyrPos = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("WRECKS"));
				int obstLyrPos = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("OBSTRN"));
				int cautionLyrPos = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("PRCARE"));
				int depthAreaLyrPos = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("DEPARE"));
				int objLayerPos = selectedObjPoses[objNum].layerPos;
				if (objLayerPos == wrkLyrPos)
				{
					AfxMessageBox(_T("航点过于靠近沉船!"));
				}
				else if (objLayerPos == obstLyrPos)
				{
					AfxMessageBox(_T("航点过于靠近障碍物!"));
				}
				else if (objLayerPos == cautionLyrPos)
				{
					AfxMessageBox(_T("航点设在了警戒区内!"));
				}
				else if (objLayerPos == depthAreaLyrPos)
				{
					BSTR retObjValString = ::SysAllocStringLen(NULL, 255);
					BSTR pBstrObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));
					memcpy(pBstrObjPos, &selectedObjPoses[objNum], sizeof(MEM_GEO_OBJ_POS));

					m_pYimaEncCtrl->GetObjectAttrString(&pBstrObjPos, 0, &retObjValString);

					CString strVal = retObjValString;
					float fMinDepth = atof(strVal);
					if (fMinDepth < m_pYimaEncCtrl->GetSafetyDepth())
					{
						AfxMessageBox(_T("航点设在了浅水区内!"));
					}
					::SysFreeString(retObjValString);
					::SysFreeString(pBstrObjPos);
				}
			}
		}

		::SysFreeString(retSelObjPosStrings);

		return;
	}

	/***** 自定义图层对象编辑演示 *****/
	bool bTestEditUserMapObject = false;
	if (bTestEditUserMapObject)
	{
		//////////////// 下面演示添加1个圆 ////////////////
		M_POINT circlePoints[2]; //添加圆对象, 须指定2个点, 第1个为圆心，第2个为圆上任意一点

		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y,
			(long*)&circlePoints[0].x, (long*)&circlePoints[0].y);
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x + 100, point.y,
			(long*)&circlePoints[1].x, (long*)&circlePoints[1].y);

		int layerPosOfAnyType = 0; //此例程中自定义海图配置的第一个图层为“自由类型图层”，即 ANYTYPE
		m_pYimaEncCtrl->tmAppendObjectInLayer(layerPosOfAnyType, TYPE_FACE); //添加一个面对象
		int addedObjInnerLayerPos = m_pYimaEncCtrl->tmGetLayerObjectCount(layerPosOfAnyType) - 1; //该对象就是该图层里最后一个对象

		//设置对象的坐标, 注意下面要使用BSTR字符串来打包坐标数组
		BSTR strObjCoors = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 2);
		memcpy(strObjCoors, circlePoints, sizeof(M_POINT) * 2);
		m_pYimaEncCtrl->tmSetFaceObjectCoors(layerPosOfAnyType,
			addedObjInnerLayerPos, 2, &strObjCoors); //设置坐标
		::SysFreeString(strObjCoors);

		m_pYimaEncCtrl->tmSetObjectAsSpecialType(layerPosOfAnyType,
			addedObjInnerLayerPos, CIRCLE_LN_TYPE); //将该对象设为“一个圆”的特殊面类型

		m_pYimaEncCtrl->tmSetFaceObjectStyleRefLib(layerPosOfAnyType, addedObjInnerLayerPos, 1, true, RGB(0, 0, 255),
			true, 50, false, 0x000000); //设置对象的填充风格, 第3个参数"1"表示参考图库填充风格中的第1个风格;
		m_pYimaEncCtrl->tmSetLineObjectStyleRefLib(layerPosOfAnyType, addedObjInnerLayerPos, 1, true, RGB(255, 0, 0),
			true, 3); //设置对象的边界风格 
		////////////////////////////////////////////////////////////

		//////////////// 下面演示添加1个椭圆 ////////////////
		M_POINT ellipsePoints[2]; //添加椭圆对象, 须指定2个点, 第1个为矩形轮廓左上角的点, 第2个为矩形轮廓右下角的点

		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y,
			(long*)&ellipsePoints[0].x, (long*)&ellipsePoints[0].y);
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x + 200, point.y + 100,
			(long*)&ellipsePoints[1].x, (long*)&ellipsePoints[1].y);

		m_pYimaEncCtrl->tmAppendObjectInLayer(layerPosOfAnyType, TYPE_FACE); //添加一个面对象
		addedObjInnerLayerPos = m_pYimaEncCtrl->tmGetLayerObjectCount(layerPosOfAnyType) - 1; //该对象就是该图层里最后一个对象

		//设置对象的坐标, 注意下面要使用BSTR字符串来打包坐标数组
		BSTR strObjCoors1 = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 2);
		memcpy(strObjCoors1, ellipsePoints, sizeof(M_POINT) * 2);
		m_pYimaEncCtrl->tmSetFaceObjectCoors(layerPosOfAnyType,
			addedObjInnerLayerPos, 2, &strObjCoors1); //设置坐标
		::SysFreeString(strObjCoors1);

		m_pYimaEncCtrl->tmSetObjectAsSpecialType(layerPosOfAnyType,
			addedObjInnerLayerPos, ELLIPSE_LN_TYPE); //将该对象设为“一个圆”的特殊面类型

		m_pYimaEncCtrl->tmSetFaceObjectStyleRefLib(layerPosOfAnyType, addedObjInnerLayerPos, 1, true, RGB(0, 255, 0),
			true, 50, false, 0x000000); //设置对象的填充风格, 第3个参数"1"表示参考图库填充风格中的第1个风格;
		m_pYimaEncCtrl->tmSetLineObjectStyleRefLib(layerPosOfAnyType, addedObjInnerLayerPos, 1, true, RGB(0, 0, 0),
			true, 3); //设置对象的边界风格 
		////////////////////////////////////////////////////////////

		//////////////// 下面演示添加1个多边形 ////////////////
		M_POINT polygonPoints[3]; //添加多边形对象

		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y,
			(long*)&polygonPoints[0].x, (long*)&polygonPoints[0].y);
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x + 200, point.y + 100,
			(long*)&polygonPoints[1].x, (long*)&polygonPoints[1].y);
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y + 200,
			(long*)&polygonPoints[2].x, (long*)&polygonPoints[2].y);

		m_pYimaEncCtrl->tmAppendObjectInLayer(layerPosOfAnyType, TYPE_FACE); //添加一个面对象
		addedObjInnerLayerPos = m_pYimaEncCtrl->tmGetLayerObjectCount(layerPosOfAnyType) - 1; //该对象就是该图层里最后一个对象

		//设置对象的坐标, 注意下面要使用BSTR字符串来打包坐标数组
		BSTR strObjCoors2 = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 3);
		memcpy(strObjCoors2, polygonPoints, sizeof(M_POINT) * 3);
		m_pYimaEncCtrl->tmSetFaceObjectCoors(layerPosOfAnyType,
			addedObjInnerLayerPos, 3, &strObjCoors2); //设置坐标
		::SysFreeString(strObjCoors2);

		m_pYimaEncCtrl->tmSetFaceObjectStyleRefLib(layerPosOfAnyType, addedObjInnerLayerPos, 2, true, RGB(0, 255, 0),
			true, 51, false, 0x000000); //设置对象的填充风格, 第3个参数"1"表示参考图库填充风格中的第1个风格;
		m_pYimaEncCtrl->tmSetLineObjectStyleRefLib(layerPosOfAnyType, addedObjInnerLayerPos, 3, true, RGB(255, 0, 0),
			true, 3); //设置对象的边界风格 
		////////////////////////////////////////////////////////////

		///////  以下演示判断某个屏幕坐标点是否位于某个面海图物标内 ////////////
		bool bPoint1InMe = m_pYimaEncCtrl->IsPointInFaceGeoObject(point.x, point.y, m_pYimaEncCtrl->GetMemMapCount() - 1,
			layerPosOfAnyType, addedObjInnerLayerPos, false);
		bool bPoint2InMe = m_pYimaEncCtrl->IsPointInFaceGeoObject(point.x + 120, point.y, m_pYimaEncCtrl->GetMemMapCount() - 1,
			layerPosOfAnyType, addedObjInnerLayerPos, false);
	}
	////////////////////////////////////////////////////////////////////////////////////

	/***** 下面对一些YIMAENC的接口进行调用测试 *****/
	bool bTestSomeAPIs = false;
	if (bTestSomeAPIs)
	{
		m_pYimaEncCtrl->SetRouteShowOrNot(true, 0, true, true, RGB(255, 0, 0));

		/* 颜色3分量RGB分别对应 0xRRGGBB 这样的3个字节, 如此例显示红色 */
		//	m_pYimaEncCtrl->SetWayPointCircle(20, 100, 0xFF0000); 
		m_pYimaEncCtrl->SetWayPointName(20, "我是一个航路点");
		m_pYimaEncCtrl->SetWayPointShowOrNot(true, 0, true, true);
		m_pYimaEncCtrl->SetWayPointAsAimPoint(20, true, 45, -500);
		m_pYimaEncCtrl->SetGridLines(3, 0x000000, 0x00FF00, 0x0000FF, 30);

		BSTR bstrWpName = ::SysAllocStringLen(NULL, 256);
		m_pYimaEncCtrl->GetWayPointName(20, &bstrWpName);
		CString str = bstrWpName;
		::SysFreeString(bstrWpName);

		//	m_pYimaEncCtrl->SetWayPointShowOrNot(false, 20, false, false);
		BOOL bShow, bShowName;
		m_pYimaEncCtrl->GetWayPointShowOrNot(20, &bShow, &bShowName);
		bool suc = m_pYimaEncCtrl->GetRouteShowOrNot(1, &bShow);
		//suc = m_pYimaEncCtrl->SetRouteShowOrNot(false, 1, true);
		suc = m_pYimaEncCtrl->GetRouteShowOrNot(1, &bShow);

		m_pYimaEncCtrl->SetWayPointCircle(20, 50, 0xFF0000, 100, 0x0);
		m_pYimaEncCtrl->SetWayPointRadialLine(20, 60, 0x00FF00, 120, 0x0000FF);

		m_pYimaEncCtrl->SetWayPointCircle(21, 50, 0xFF0000, 100, 0x0);
		m_pYimaEncCtrl->SetWayPointRadialLine(21, 90, 0x00FF00, 230, 0x0000FF);

		UINT newSymbolID = m_pYimaEncCtrl->AddAnEmptySymbol();
		int symbolCount = m_pYimaEncCtrl->GetSymbolCount();
		m_pYimaEncCtrl->SetSymbolAsTrueTypeSymbol(newSymbolID, "chartfont1", 45, 0, 0);
		m_pYimaEncCtrl->SaveSymbolsToFile();

		int lyrCount = m_pYimaEncCtrl->tmGetLayerCount();
		for (int lyrNum = 0; lyrNum < lyrCount; lyrNum++)
		{
			int lyrObjCount = m_pYimaEncCtrl->tmGetLayerObjectCount(lyrNum);
			for (int objNum = 0; objNum < lyrObjCount; objNum++)
			{
				m_pYimaEncCtrl->tmMoveObjectInScrn(lyrNum, objNum, 5, 5);
			}
		}

		m_pYimaEncCtrl->SetIfShowOwnship(false);
		//////////////////////////////////////////////////////////////////////////
	}

	CView::OnLButtonDblClk(nFlags, point);
}

void CYimaEncViewerView::OnQuery()
{
	// TODO: Add your command handler code here
	static CQueryDialog* pQueryDlg = NULL;

	if (pQueryDlg != NULL)
	{
		delete pQueryDlg;
		pQueryDlg = NULL;
	}

	if (pQueryDlg == NULL)
	{
		pQueryDlg = new CQueryDialog();
		pQueryDlg->Create(IDD_QUERY_DIALOG);
	}

	pQueryDlg->ShowWindow(SW_SHOW);
}

void CYimaEncViewerView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default 
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CYimaEncViewerView::OnDelLinePoint()
{
	// TODO: Add your command handler code here

	if (m_iEditingPointPosOnEditingLine != -1)
	{
		m_pYimaEncCtrl->tmDeleteOnePointOfLineObject(m_editingUserMapObjPos.layerPos,
			m_editingUserMapObjPos.innerLayerObjectPos, m_iEditingPointPosOnEditingLine);
		m_pYimaEncCtrl->ForcelyRefreshMap();
		Invalidate();
	}
}

void CYimaEncViewerView::OnSetFirstLayerNotDraw()
{
	// TODO: Add your command handler code here 
	bool bDrawNoNot = true;
	if (m_pYimaEncCtrl->tmGetLayerDrawOrNot(0, (BOOL*)&bDrawNoNot))
	{
		m_pYimaEncCtrl->tmSetLayerDrawOrNot(0, !bDrawNoNot);
		Invalidate();
	}
}

void CYimaEncViewerView::OnAddCurveLine()
{
	// TODO: Add your command handler code here

	if (m_pYimaEncCtrl->tmGetLayerGeoType(m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	}

	SetOperation(ADD_USER_LAYER_OBJ);
	SetOperation(ADD_LINE);
	m_addingSpecialLineType = CURVE_LN_TYPE;

	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

void CYimaEncViewerView::OnAddClosedCurveLine()
{
	// TODO: Add your command handler code here

	if (m_pYimaEncCtrl->tmGetLayerGeoType(m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	}

	SetOperation(ADD_USER_LAYER_OBJ);
	SetOperation(ADD_LINE);
	m_addingSpecialLineType = CLOSED_CURVE_LN_TYPE;

	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

void CYimaEncViewerView::OnAddSingleArrow()
{
	// TODO: Add your command handler code here

	if (m_pYimaEncCtrl->tmGetLayerGeoType(m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	}

	SetOperation(ADD_USER_LAYER_OBJ);
	SetOperation(ADD_LINE);
	m_addingSpecialLineType = SINGLE_ARROW_LN_TYPE;

	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

void CYimaEncViewerView::OnAddDoubleArrow()
{
	// TODO: Add your command handler code here

	if (m_pYimaEncCtrl->tmGetLayerGeoType(m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	}

	SetOperation(ADD_USER_LAYER_OBJ);
	SetOperation(ADD_LINE);
	m_addingSpecialLineType = DOUBLE_ARROW_LN_TYPE;

	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

void CYimaEncViewerView::OnAddCurveWithArrow()
{
	// TODO: Add your command handler code here

	if (m_pYimaEncCtrl->tmGetLayerGeoType(m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	}

	SetOperation(ADD_USER_LAYER_OBJ);
	SetOperation(ADD_LINE);
	m_addingSpecialLineType = CURVE_LN_TYPE_WITH_HEAD_ARROW;

	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

void CYimaEncViewerView::OnAddCurveWithBothArrow()
{
	// TODO: Add your command handler code here

	if (m_pYimaEncCtrl->tmGetLayerGeoType(m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	}

	SetOperation(ADD_USER_LAYER_OBJ);
	SetOperation(ADD_LINE);
	m_addingSpecialLineType = CURVE_LN_TYPE_WITH_HAED_TAIL_ARROW;

	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

void CYimaEncViewerView::OnAddThreeArrow()
{
	// TODO: Add your command handler code here

	if (m_pYimaEncCtrl->tmGetLayerGeoType(m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	}

	SetOperation(ADD_USER_LAYER_OBJ);
	SetOperation(ADD_LINE);
	m_addingSpecialLineType = THREE_ARROW_LN_TYPE;

	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

void CYimaEncViewerView::OnUndo()
{
	// TODO: Add your command handler code here
	m_pYimaEncCtrl->tmUndo();
	Invalidate();
}

void CYimaEncViewerView::OnRedo()
{
	// TODO: Add your command handler code here
	m_pYimaEncCtrl->tmRedo();
	Invalidate();
}

void CYimaEncViewerView::OnMyFilePrint()
{
	// TODO: Add your command handler code here
	CView::OnFilePrint();
}

void CYimaEncViewerView::OnMyFilePrintPreview()
{
	// TODO: Add your command handler code here
	CPrintTitleSetingDlg  printTitleSetingDlg;
	printTitleSetingDlg.DoModal();
	CView::OnFilePrintPreview();
}

BOOL CYimaEncViewerView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bAnimationScale)
	{
		m_WheelStartTime = GetCurTimeMillis();
		RECT wndRect;
		GetWindowRect(&wndRect);
		int scrnWidth = wndRect.right - wndRect.left;
		int scrnHeight = wndRect.bottom - wndRect.top;

		m_scaleMouseScrnPo = M_POINT(pt.x - wndRect.left, pt.y - wndRect.top);
		float fWheelNum = zDelta / 120;  //滑轮滚动的格数，上滑﹢，下滑﹣
		float fN = 0.3 * fWheelNum; //叠加缩放参数
		if (bMouseWheelState == false)
		{
			float fScaleSize = 1.1; //初始缩放参数
			int isign = fScaleSize * (fWheelNum / fabs(fWheelNum));
			fN = fN + isign;
		}
		m_fScaleIndex += fN;
		bMouseWheelState = true;
		DrawScaledMap();

	}
	else
	{
		if (m_bMouseZoomModeOrStdZoomMode && m_pYimaEncCtrl->GetMapEffect() == EFFECT_NONE)
		{
			RECT wndRect;
			GetWindowRect(&wndRect);
			int scrnWidth = wndRect.right - wndRect.left;
			int scrnHeight = wndRect.bottom - wndRect.top;

			/* 由于OnMouseWheel()传入的鼠标位置参数pt是相对于整个计算机屏幕左上角原点的坐标，
				而非本窗口的原点坐标，所以这里要转换一下 */
			M_POINT cursorPoint(pt.x - wndRect.left, pt.y - wndRect.top);

			//进行标准缩放前先获取鼠标位置对应的地理坐标
			M_POINT mouseGeoPo;
			m_pYimaEncCtrl->GetGeoPoFromScrnPo(cursorPoint.x, cursorPoint.y, (long*)&mouseGeoPo.x, (long*)&mouseGeoPo.y);

			//先进行标准缩放
			if (zDelta > 0)
			{
				m_pYimaEncCtrl->SetCurrentScale(m_pYimaEncCtrl->GetCurrentScale() / 1.5);
			}
			else
			{
				m_pYimaEncCtrl->SetCurrentScale(m_pYimaEncCtrl->GetCurrentScale() * 1.5);
			}

			M_POINT afterStdZoomScrnPo; //标准缩放模式后鼠标的屏幕坐标
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(mouseGeoPo.x, mouseGeoPo.y,
				(long*)&afterStdZoomScrnPo.x, (long*)&afterStdZoomScrnPo.y);

			long deltX, deltY; //标准缩放后鼠标的屏幕坐标和和鼠标缩放模式后的屏幕坐标差
			deltX = afterStdZoomScrnPo.x - cursorPoint.x;
			deltY = afterStdZoomScrnPo.y - cursorPoint.y;

			//求鼠标缩放模式下的屏幕中心点在标准模式缩放后的屏幕坐标
			M_POINT scrnCenterAfterStdZoom = M_POINT(scrnWidth / 2 + deltX, scrnHeight / 2 + deltY);

			//求鼠标缩放模式下的屏幕中心点地理坐标
			M_POINT geoPoOfMouseZoomScrnCenter;
			m_pYimaEncCtrl->GetGeoPoFromScrnPo(scrnCenterAfterStdZoom.x, scrnCenterAfterStdZoom.y,
				(long*)&geoPoOfMouseZoomScrnCenter.x, (long*)&geoPoOfMouseZoomScrnCenter.y);

			//以上面求得的屏幕中心点地理坐标居中定位
			m_pYimaEncCtrl->CenterMap(geoPoOfMouseZoomScrnCenter.x, geoPoOfMouseZoomScrnCenter.y);
		}
		else
		{
			//先进行标准缩放
			if (zDelta > 0)
			{
				m_pYimaEncCtrl->SetCurrentScale(m_pYimaEncCtrl->GetCurrentScale() / 1.5);
			}
			else
			{
				m_pYimaEncCtrl->SetCurrentScale(m_pYimaEncCtrl->GetCurrentScale() * 1.5);
			}
		}

		Invalidate();

		RefreshScaleStatusBar();
		if (m_globalView != NULL)
		{
			m_globalView->ReSetViewPosion();
		}
	}

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CYimaEncViewerView::OnAreaSelect()
{
	// TODO: Add your command handler code here 
	SetOperation(AREA_SELECT);

	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CMenu *pMenu = pFrame->GetMenu();
	CToolBar* pToolBar = (CToolBar*)pFrame->GetDescendantWindow(AFX_IDW_TOOLBAR);
	if (pMenu != NULL && pToolBar != NULL)
	{
		pMenu->CheckMenuItem(ID_AREA_SELECT, MF_CHECKED);
		pToolBar->GetToolBarCtrl().PressButton(ID_AREA_SELECT, true);
	}
}

#define MAX_RET_CROSS_OBJ_COUNT 10

/* 示例航线检测
	目标：
	 1. 检测系统中第1条航线的第1个航线段(Leg)是否穿越4种安全检查物标: 障碍物、沉船、警戒区、安全等深线;
	 2. 要求尽量充分检测图库(MapLib)中所有S57海图图幅包含的数据信息;
	 3. 检测到物标后, 可以提示并高亮显示该物标;
	步骤：
		1. 卸载内存海图序列中的所有图幅;
		2. 然后判断航线段选中哪些图幅；
		3. 将航线段选中的图幅依次调入内存, 1次1副，逐一检测;
		4. 对某一副图的检测过程封装在函数 DetectRouteLegSafteyInMemMap0() 中;
		5. 如果第4步返回航线段非法穿越目标1中里列举的4种物标, 则高亮该物标; */
void CYimaEncViewerView::OnRouteSafeDetect()
{
	// TODO: Add your command handler code here  

	m_pYimaEncCtrl->SetIfOnAutoLoadMapMode(false);

	m_pYimaEncCtrl->SetDisplayCategory(DISPLAY_ALL);

	int frstRouteID = m_pYimaEncCtrl->GetRouteIDFromPos(0);
	int rtWpCount = m_pYimaEncCtrl->GetRouteWayPointsCount(frstRouteID);
	if (rtWpCount < 2)
	{
		char msg[255];
		sprintf(msg, "rtWpCount < 2, frstRouteID %d, rtWpCount %d", frstRouteID, rtWpCount);
		AfxMessageBox(msg);
		return;
	}

	M_POINT* wayPoints = new M_POINT[rtWpCount];
	BSTR bstrWpPoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * rtWpCount);
	//获取航线的航点坐标数组
	m_pYimaEncCtrl->GetRouteWayPointsCoor(frstRouteID, &bstrWpPoints);
	memcpy(wayPoints, bstrWpPoints, sizeof(M_POINT) * rtWpCount);

#define MAX_SEL_LIB_MAP_COUNT 255
	int selLibMapPoses[MAX_SEL_LIB_MAP_COUNT]; //被航线段选中的图幅列表
	float selLibMapOrgScale[MAX_SEL_LIB_MAP_COUNT];
	int selLibMapCount = 0;

	//下面模拟测试第1节航线段, 即取 wayPoints[0]、wayPoints[1]
	M_POINT legLineStartPo = wayPoints[0];
	M_POINT legLineEndPo = wayPoints[1];

	int libMapCount = m_pYimaEncCtrl->GetLibMapCount();
	float minOrgScaleForMapContainLeg = 0; //完全包含航线段的所有图幅的最小原始比例尺
	for (int mapNum = 0; mapNum < libMapCount; mapNum++)
	{
		float orgScale;
		long left, right, up, down;

		BSTR bstrMapType = ::SysAllocStringLen(NULL, 50);
		m_pYimaEncCtrl->GetLibMapInfo(mapNum, &bstrMapType, NULL, &orgScale, &left, &right, &up, &down,
			NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		CString strMapType = bstrMapType;
		if (strMapType != MAP_TYPE_ENC)
		{
			SysFreeString(bstrMapType);
			continue;
		}
		else
		{
			SysFreeString(bstrMapType);
		}

		M_POINT mapRectPoints[4];
		mapRectPoints[0] = M_POINT(left, up);
		mapRectPoints[1] = M_POINT(left, down);
		mapRectPoints[2] = M_POINT(right, up);
		mapRectPoints[3] = M_POINT(right, down);

		BSTR bstrMapRectPoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 4);
		memcpy(bstrMapRectPoints, mapRectPoints, sizeof(M_POINT) * 4);

		BOOL bCross = false;

		MRECT legRect;
		legRect.leftTopPointX = legLineStartPo.x < legLineEndPo.x ? legLineStartPo.x : legLineEndPo.x;
		legRect.rightDownPointX = legLineStartPo.x > legLineEndPo.x ? legLineStartPo.x : legLineEndPo.x;
		legRect.leftTopPointY = legLineStartPo.y > legLineEndPo.y ? legLineStartPo.y : legLineEndPo.y;
		legRect.rightDownPointY = legLineStartPo.y < legLineEndPo.y ? legLineStartPo.y : legLineEndPo.y;

		if (!(legRect.leftTopPointX > right || legRect.rightDownPointX < left ||
			legRect.leftTopPointY < down || legRect.rightDownPointY > up))
		{ //说明航线段与该图幅有区域相交

			if (legRect.leftTopPointX >= left && legRect.rightDownPointX < right &&
				legRect.rightDownPointY >= down && legRect.leftTopPointY < up)
			{//说明航线段必被该图幅区域完全包含
				if (minOrgScaleForMapContainLeg == 0 ||
					(minOrgScaleForMapContainLeg != 0 && orgScale < minOrgScaleForMapContainLeg))
				{
					/* 如果该图幅包含航线段且其原始比例尺比之前
					   记录的 minOrgScaleForMapContainLeg 还小,
						则更新 minOrgScaleForMapContainLeg */
					minOrgScaleForMapContainLeg = orgScale;
				}

				bCross = true; //完全包含也算作穿越"Cross"
			}
			else
			{//如果不是完全包含, 则判断是否相交(穿越) 
				m_pYimaEncCtrl->IsLineSectionCrossPolygon(legLineStartPo.x, legLineStartPo.y, legLineEndPo.x,
					legLineEndPo.y, &bstrMapRectPoints, 4, true, &bCross);
			}

			if (bCross)
			{//如果穿越, 则把该图幅加入 selLibMapPoses "选中图幅"序列中去
				selLibMapPoses[selLibMapCount] = mapNum;
				selLibMapOrgScale[selLibMapCount] = orgScale;
				selLibMapCount++;
			}
		}

		SysFreeString(bstrMapRectPoints);
	}

	int detectLibMapPoses[MAX_SEL_LIB_MAP_COUNT];
	int detectLibMapCount = 0;
	for (int selLibMapNum = 0; selLibMapNum < selLibMapCount; selLibMapNum++)
	{
		if (!(minOrgScaleForMapContainLeg > 0 && selLibMapOrgScale[selLibMapNum] > minOrgScaleForMapContainLeg))
		{/* 如果minOrgScaleForMapContainLeg不为0,
			则只判断"全包含"航线段最小比例尺的那副图 以及 比它更小比例尺但"未全包含"航线段的图,
			其它的小比例尺图不需判断 */
			detectLibMapPoses[detectLibMapCount] = selLibMapPoses[selLibMapNum];
			detectLibMapCount++;
		}
	}

	for (int detectLibMapNum = 0; detectLibMapNum < detectLibMapCount; detectLibMapNum++)
	{
		int dtctLibMapPos = detectLibMapPoses[detectLibMapNum];

		m_pYimaEncCtrl->LoadMapToMemory(dtctLibMapPos);

		int memPosForLibMap = m_pYimaEncCtrl->GetLibMapPosInMem(dtctLibMapPos);

		/* DEBUGING CODE
		BSTR bstrname = ::SysAllocStringLen(NULL, 255);
		m_pYimaEncCtrl->GetMemMapInfo(memPosForLibMap, NULL, &bstrname, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		CString strMapName = bstrname;

		char msg[255];
		sprintf(msg, "+++++++++++++++++++++++++++++++ Begin DetectRouteLegSafteyInMemMap0 %d %s +++++++++++++++++++++++\r\n",
			detectLibMapPoses[detectLibMapNum], strMapName);
		TRACE(msg);
		*/

		M_GEO_OBJ_POS detectRetCrossObjPoses[MAX_RET_CROSS_OBJ_COUNT];
		int retCrossObjCount = DetectRouteLegSafteyInMemMap(memPosForLibMap, wayPoints[0], wayPoints[1], detectRetCrossObjPoses);
		if (retCrossObjCount > 0)
		{
			BSTR bstrMapname = ::SysAllocStringLen(NULL, 255);
			m_pYimaEncCtrl->GetMemMapInfo(memPosForLibMap, NULL, &bstrMapname, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
			CString strMapName = bstrMapname;
			SysFreeString(bstrMapname);

			BSTR bstrLyrName = ::SysAllocStringLen(NULL, 255);
			m_pYimaEncCtrl->GetLayerInfo(-1, detectRetCrossObjPoses[0].layerPos, &bstrLyrName, NULL, NULL);
			CString strLyrName = bstrLyrName;
			char msg[255];
			sprintf(msg, "Route Cross a forbid object in map %s layer %s, objNum %d \r\n, Press Yes to locate it!",
				strMapName, strLyrName, detectRetCrossObjPoses[0].innerLayerObjectPos);
			TRACE(msg);
			SysFreeString(bstrLyrName);

			if (AfxMessageBox(msg, MB_YESNO) == IDYES)
			{
				MEM_GEO_OBJ_POS objPos(memPosForLibMap, detectRetCrossObjPoses[0].layerPos,
					detectRetCrossObjPoses[0].innerLayerObjectPos);
				BSTR bstrObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));
				memcpy(bstrObjPos, &objPos, sizeof(MEM_GEO_OBJ_POS));

				//下面获取物标的经纬度范围
				long left, right, top, down;
				m_pYimaEncCtrl->GetObjectGeoExtent(&bstrObjPos, &left, &right, &top, &down);

				//下面准备定位概览该物标了
				m_pYimaEncCtrl->SetIfOnAutoLoadMapMode(true); //先切换会自动内存调图模式、因为要准备显示海图了
				m_pYimaEncCtrl->OverViewGeoRect(left, down, right, top); //显示之前，定位海图屏幕，让其可以概览该物标

				/* 由于打开OverViewGeoRect()之后在自动内存调图机制的作用下内存海图数量及位置发生了变化,
				   所以在高亮该物标前，要找到其图幅在内存海图序列中的新位置	*/
				int highlightObjMemMapPos = m_pYimaEncCtrl->GetLibMapPosInMem(dtctLibMapPos);

				MEM_GEO_OBJ_POS highlightObjPos(highlightObjMemMapPos,
					detectRetCrossObjPoses[0].layerPos,
					detectRetCrossObjPoses[0].innerLayerObjectPos);

				SetHighlightObjects(&highlightObjPos, 1);  //设置显示时要高亮该物标

				RefreshScreenMap(); //刷新显示海图

				SysFreeString(bstrObjPos);
				break;
			}
		}
	}

	SysFreeString(bstrWpPoints);
	delete[] wayPoints;

	m_pYimaEncCtrl->SetIfOnAutoLoadMapMode(true);
}

/* 检测过程: 调用 SelectGeoObjectByLineSection() 接口遍历检测感兴趣图层的每一个物标 */
int CYimaEncViewerView::DetectRouteLegSafteyInMemMap(int memMapPos, M_POINT legStartGeoPo, M_POINT legEndGeoPo,
	M_GEO_OBJ_POS* retCrossObjPoses)
{
	int retCrossObjCount = 0;

	int detectLayerList[100];//要判断航线是否穿越哪些S57图层

	/* 这里演示测试4个图层，您可以选择更多图层参与检测. */
	detectLayerList[0] = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("OBSTRN")); //障碍物
	detectLayerList[1] = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("WRECKS")); //沉船
	detectLayerList[2] = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("PRCARE")); //警戒区 
	detectLayerList[3] = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("DEPCNT")); //等深线

	// 注意，这个常量的值取为2是因为, S57ObjectClasses文件的DEPCNT类属性列表中的第3个位置
#define ATTR_POS_OF_SAFEDEPTH_TAG_IN_LYR_DEPCNT 2 

	for (int lyrNum = 0; lyrNum < 4; lyrNum++)
	{
		int detectLayerPos = detectLayerList[lyrNum];
		int detectLyrObjCount = m_pYimaEncCtrl->GetLayerObjectCountOfMap(memMapPos, detectLayerPos);

		//这些图层的物标逐一判断
		for (int objNum = 0; objNum < detectLyrObjCount; objNum++)
		{
			if (lyrNum == 3)//如果是判断安全线的图层
			{
				BSTR bstrAttrVal = ::SysAllocStringLen(NULL, MAX_ATTR_VAL_STRING_LEN);
				BSTR bstrObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));
				memcpy(bstrObjPos, &MEM_GEO_OBJ_POS(memMapPos, detectLayerPos, objNum), sizeof(MEM_GEO_OBJ_POS));

				m_pYimaEncCtrl->GetObjectAttrString(&bstrObjPos,
					ATTR_POS_OF_SAFEDEPTH_TAG_IN_LYR_DEPCNT, &bstrAttrVal);

				CString strVal = bstrAttrVal;

				SysFreeString(bstrObjPos);
				SysFreeString(bstrAttrVal);

				if (strVal != BOOL_BE_TRUE_STRING)
				{//BESAFE属性不为true时表示该等深线不是"安全等深线",则不用判断
					continue;
				}
			}

			BOOL bSelect = false;
			m_pYimaEncCtrl->SelectGeoObjectByLineSection(memMapPos, detectLayerPos, objNum,
				legStartGeoPo.x, legStartGeoPo.y, legEndGeoPo.x, legEndGeoPo.y,
				100, &bSelect); /* 该方法判断某个物标是否被线段选中:
								1. 点物标的选定判断依据是"该点距离线段的距离d小于倒数第2个参数100米";
								2. 线物标判断依据是该线物标与线段是否"相交";
								3. 面物标判断依据是该面物标: a.是否与线段"相交"; b.包含线段; */

			if (bSelect && retCrossObjCount < MAX_RET_CROSS_OBJ_COUNT)
			{
				CString strMsg;
				strMsg.Format(_T("wrk sel layer pos %d, obj pos %d"), detectLayerPos, objNum);
				//AfxMessageBox(strMsg);

				retCrossObjPoses[retCrossObjCount] = M_GEO_OBJ_POS(detectLayerPos, objNum);
				retCrossObjCount++;
			}
		}
	}

	return retCrossObjCount;
}

void CYimaEncViewerView::OnCopyObject()
{
	// TODO: Add your command handler code here
	if (m_curSelectedObjCount == 1)
	{
		if (IsOnOperation(EDITING_GEO_OBJECT))
		{
			m_pYimaEncCtrl->tmCopyObject(
				m_editingUserMapObjPos.layerPos, m_editingUserMapObjPos.innerLayerObjectPos, -1);
		}
	}
}

//设置物标特征属性及样式选择设置，可对一个物标多次重复调用设置
bool CYimaEncViewerView::UserObject_SetAttributes(int layerPos, int innerLayerPos)
{
	SetCursor(LoadCursor(NULL, IDC_ARROW));

	//弹出"设置物标的属性值"窗口,对物标属性值进行编辑
	CGeoObjectInfoDlg geoObjInfoDlg;
	geoObjInfoDlg.m_bIsS57OrUserMapObj = false;
	geoObjInfoDlg.m_userMapObjPos = M_GEO_OBJ_POS(layerPos, innerLayerPos);

	geoObjInfoDlg.DoModal();

	m_nEditingLinePointCount = 0;

	M_GEO_TYPE geoType = (M_GEO_TYPE)m_pYimaEncCtrl->tmGetGeoObjectType(layerPos, innerLayerPos);
	if (m_pYimaEncCtrl->tmGetLayerGeoType(layerPos) == MULTIPLE_GEO_TYPE)
	{
		if (geoType == TYPE_POINT)
		{
			CLibPointStylesViewDlg libPointStylesViewDlg;

			long referLibSymbolId;
			long fontHeight, fontColor, symbolOffsetX, symbolOffsetY, textOffsetX, textOffsetY;
			BOOL bBold, bItalic;
			BSTR retText, retFontName;
			retText = ::SysAllocStringLen(NULL, 1024);
			retFontName = ::SysAllocStringLen(NULL, 255);
			if (m_pYimaEncCtrl->tmGetPointObjectStyle(layerPos, innerLayerPos,
				&referLibSymbolId, NULL, NULL, &retText, &retFontName, &fontHeight,
				&fontColor, &bBold, &bItalic, &symbolOffsetX,
				&symbolOffsetY, &textOffsetX, &textOffsetY))
			{
				libPointStylesViewDlg.m_iSelPsID = referLibSymbolId;
				libPointStylesViewDlg.m_strText = retText;
				libPointStylesViewDlg.m_strTextFontName = retFontName;
				M_COLOR mFtClr;
				M_SET_COLOR_BY_INT(mFtClr, fontColor);
				libPointStylesViewDlg.m_nFontSize = fontHeight;
				libPointStylesViewDlg.m_nFontColorR = mFtClr.r;
				libPointStylesViewDlg.m_nFontColorG = mFtClr.g;
				libPointStylesViewDlg.m_nFontColorB = mFtClr.b;
				libPointStylesViewDlg.m_iTextOffsetX = textOffsetX;
				libPointStylesViewDlg.m_iTextOffsetY = textOffsetY;
			}
			libPointStylesViewDlg.m_fTextRotatrAngle = m_pYimaEncCtrl->tmGetObjectTextRotate(layerPos, innerLayerPos);
			::SysFreeString(retText);
			::SysFreeString(retFontName);
			if (libPointStylesViewDlg.DoModal() == IDOK)
			{
				m_pYimaEncCtrl->tmSetPointObjectStyleRefLib(layerPos, innerLayerPos,
					libPointStylesViewDlg.m_iSelPsID, libPointStylesViewDlg.m_bSetColor,
					RGB(libPointStylesViewDlg.m_iPointColorR, libPointStylesViewDlg.m_iPointColorG,
						libPointStylesViewDlg.m_iPointColorB), libPointStylesViewDlg.m_fZoomRatio, 0);

				/* 设置物标标注, 注：此接口可以用于设置点物标的完整风格，
					   包括符号风格、标注风格, 但由于前面的
					   tmSetPointObjectStyleRefLib() 接口调用已经设置了符号风格, 这里只是使用其"标注"设置功能  */
				m_pYimaEncCtrl->tmSetPointObjectStyle(layerPos, innerLayerPos,
					0, false, 0, 0, true, libPointStylesViewDlg.m_strText,
					libPointStylesViewDlg.m_strTextFontName,
					libPointStylesViewDlg.m_nFontSize,
					RGB(libPointStylesViewDlg.m_nFontColorR, libPointStylesViewDlg.m_nFontColorG,
						libPointStylesViewDlg.m_nFontColorB), false, false, 0, 0, libPointStylesViewDlg.m_iTextOffsetX,
					libPointStylesViewDlg.m_iTextOffsetY, 0);
				m_pYimaEncCtrl->tmSetObjectTextRotate(layerPos, innerLayerPos, libPointStylesViewDlg.m_fTextRotatrAngle);
				/*
				int iUserMapPos = m_pYimaEncCtrl->GetMemMapCount() - 1;//自定义图层所在的图幅在内存的索引
				int curLayerPos = 0;//在哪个图层进行查询，我这里0表示自定义的第一个图层，即“Layers”配置文件里面的“综合图层”
				int iFieldPos = 0;//查询物标的哪一个属性,这个要在配置文件“Layers”查看，“综合图层”里面的名称序号是0
				int iCondtionType = 6;//查询条件类型:数字类型（0=等于，1=不等于，2=大于，3=大于等于，4=小于，5=小于等于），字符串（6=包含）
				CString strCondtion = "东海";//查询条件
				BSTR retSelObjPosStrings = ::SysAllocStringLen(NULL, 100 * sizeof(int));
				int arrInt[100];

				bool bSel = m_pYimaEncCtrl->QueryInMapLayerByFieldCondtion(iUserMapPos,layerPos,iFieldPos,iCondtionType,strCondtion,&retSelObjPosStrings);
				memcpy(arrInt, retSelObjPosStrings, sizeof(int) * 100);

				*/
			}
		}
		else
		{
			if (geoType == TYPE_FACE)
			{
				//弹出"选择面填充风格"窗口,选择面填充风格
				CLibFaceStylesViewDlg libFaceStylesViewDlg;
				libFaceStylesViewDlg.m_strCaption = "选择面填充风格";
				long refLibFaceStyleID = 0;
				BOOL bFillColor;
				long fillColor, fillTrans;
				long fontHeight, fontColor, textOffsetX, textOffsetY;
				BOOL bBold, bItalic;
				BSTR retText, retFontName;
				retText = ::SysAllocStringLen(NULL, 1024);
				retFontName = ::SysAllocStringLen(NULL, 255);

				if (m_pYimaEncCtrl->tmGetFaceObjectStyle(layerPos, innerLayerPos, &refLibFaceStyleID,
					&bFillColor, &fillColor, &fillTrans, &retText, &retFontName,
					&fontHeight, &fontColor, &bBold, &bItalic, &textOffsetX, &textOffsetY))
				{
					libFaceStylesViewDlg.m_iSelFsID = refLibFaceStyleID;
					libFaceStylesViewDlg.m_bSetFillColorTransparency = true;
					libFaceStylesViewDlg.m_iFillTransparency = fillTrans;
					libFaceStylesViewDlg.m_bSetColor = bFillColor;
					if (bFillColor)
					{
						M_COLOR mFillColor;
						M_SET_COLOR_BY_INT(mFillColor, fillColor);
						libFaceStylesViewDlg.m_iFaceColorR = mFillColor.r;
						libFaceStylesViewDlg.m_iFaceColorG = mFillColor.g;
						libFaceStylesViewDlg.m_iFaceColorB = mFillColor.b;
					}

					CString strText = retText;
					if (strText.GetLength() > 0)
					{
						libFaceStylesViewDlg.m_strText = retText;
						libFaceStylesViewDlg.m_strFontName = retFontName;
						M_COLOR mFtClr;
						M_SET_COLOR_BY_INT(mFtClr, fontColor);
						libFaceStylesViewDlg.m_nTextFontSize = fontHeight;
						libFaceStylesViewDlg.m_nFontColorR = mFtClr.r;
						libFaceStylesViewDlg.m_nFontColorG = mFtClr.g;
						libFaceStylesViewDlg.m_nFontColorB = mFtClr.b;
						libFaceStylesViewDlg.m_iTextOffsetX = textOffsetX;
						libFaceStylesViewDlg.m_iTextOffsetY = textOffsetY;
					}
				}
				libFaceStylesViewDlg.m_fTextRotatrAngle = m_pYimaEncCtrl->tmGetObjectTextRotate(layerPos, innerLayerPos);

				::SysFreeString(retText);
				::SysFreeString(retFontName);

				if (libFaceStylesViewDlg.DoModal() == IDOK)
				{
					/* 设置物标标注, 注：此接口可以用于设置面物标的完整风格，
					   包括填充色及其透明度、循环填充符号风格、标注风格, 但由于前面的
					   tmSetFaceObjectStyleRefLib() 接口调用已经设置了填充等风格, 这里只是使用其"标注"设置功能  */
					m_pYimaEncCtrl->tmSetFaceObjectStyle(layerPos, innerLayerPos, false, 0, -1, 0, 0, 0,
						libFaceStylesViewDlg.m_strText, libFaceStylesViewDlg.m_strFontName,
						libFaceStylesViewDlg.m_nTextFontSize,
						RGB(libFaceStylesViewDlg.m_nFontColorR, libFaceStylesViewDlg.m_nFontColorG,
							libFaceStylesViewDlg.m_nFontColorB), false, false,
						libFaceStylesViewDlg.m_bShowTextOnObjectCenterOrBottom,
						libFaceStylesViewDlg.m_iTextOffsetX,
						libFaceStylesViewDlg.m_iTextOffsetY);

					if (libFaceStylesViewDlg.m_iSelFsID > 0)
					{
						m_pYimaEncCtrl->tmSetFaceObjectStyleRefLib(layerPos, innerLayerPos,
							libFaceStylesViewDlg.m_iSelFsID, libFaceStylesViewDlg.m_bSetColor,
							RGB(libFaceStylesViewDlg.m_iFaceColorR, libFaceStylesViewDlg.m_iFaceColorG,
								libFaceStylesViewDlg.m_iFaceColorB),
							libFaceStylesViewDlg.m_bSetFillColorTransparency, libFaceStylesViewDlg.m_iFillTransparency,
							libFaceStylesViewDlg.m_bSetPatternColor,
							RGB(libFaceStylesViewDlg.m_iFacePatternColorR, libFaceStylesViewDlg.m_iFacePatternColorG,
								libFaceStylesViewDlg.m_iFacePatternColorB));
						if (libFaceStylesViewDlg.m_bSetFillColorTransparency)
						{
							m_startFillTrans = libFaceStylesViewDlg.m_iFillTransparency;
						}
						else
						{
							m_startFillTrans = 100;
						}
					}
					m_pYimaEncCtrl->tmSetObjectTextRotate(layerPos, innerLayerPos, libFaceStylesViewDlg.m_fTextRotatrAngle);

				}
			}

			//弹出"选择线型风格"窗口,选择线型风格
			CLibLineStylesViewDlg libLineStylesViewDlg;
			bool bLine = false;
			if (geoType == TYPE_FACE)
			{
				libLineStylesViewDlg.m_strCaption = "选择面边界线型风格";
			}
			else
			{
				libLineStylesViewDlg.m_strCaption = "选择线型风格";
				bLine = true;
			}

			BOOL bIsSolid, bIsDash;
			long dashCycle, dashLen, bscLineWidth, bscLineColor;
			BOOL bIsTextBold, bIsTextItalic, bIsTextAlongWithLine;
			BSTR retText, retFontName;
			long fontHeight, fontColor;
			retText = ::SysAllocStringLen(NULL, 1024);
			retFontName = ::SysAllocStringLen(NULL, 255);

			m_pYimaEncCtrl->tmGetLineObjectStyle(layerPos, innerLayerPos, &bIsSolid, &bIsDash,
				&bscLineWidth, &bscLineColor, &dashCycle, &dashLen,
				&retText, &retFontName, &fontHeight, &fontColor, &bIsTextBold, &bIsTextItalic, NULL, NULL, &bIsTextAlongWithLine);
			M_COLOR mlineClr;
			M_SET_COLOR_BY_INT(mlineClr, bscLineColor);
			libLineStylesViewDlg.m_bSolidLine = bIsSolid;
			libLineStylesViewDlg.m_bDashLine = bIsDash;
			libLineStylesViewDlg.m_bSetBasicLineColor = true;//bscLineColor;
			libLineStylesViewDlg.m_nBscLnColorR = mlineClr.r;
			libLineStylesViewDlg.m_nBscLnColorG = mlineClr.g;
			libLineStylesViewDlg.m_nBscLnColorB = mlineClr.b;
			libLineStylesViewDlg.m_nBscLnWidth = bscLineWidth;
			libLineStylesViewDlg.m_nDashCycle = dashCycle;
			libLineStylesViewDlg.m_nDashLen = dashLen;
			libLineStylesViewDlg.m_strFontName = retFontName;
			M_SET_COLOR_BY_INT(mlineClr, fontColor);
			libLineStylesViewDlg.m_nFontColorR = mlineClr.r;
			libLineStylesViewDlg.m_nFontColorG = mlineClr.g;
			libLineStylesViewDlg.m_nFontColorB = mlineClr.b;
			libLineStylesViewDlg.m_nFontSize = fontHeight;
			libLineStylesViewDlg.m_fTextRotatrAngle = m_pYimaEncCtrl->tmGetObjectTextRotate(layerPos, innerLayerPos);
			if (bLine)
			{
				libLineStylesViewDlg.m_strText = retText;
			}
			::SysFreeString(retText);
			::SysFreeString(retFontName);


			if (libLineStylesViewDlg.DoModal() == IDOK)
			{
				/* 设置线物标标注, 注：此接口可以用于设置线物标的完整风格，
				包括基础线型(实线或虚线及其宽度、颜色)、循环符号风格、标注风格, 但由于前面的
					tmSetLineObjectStyleRefLib() 接口调用已经设置了线型等风格, 这里只是使用其"标注"设置功能  */

				m_pYimaEncCtrl->tmSetLineObjectStyle(layerPos, innerLayerPos,
					true, libLineStylesViewDlg.m_bSolidLine,
					libLineStylesViewDlg.m_nDashCycle, libLineStylesViewDlg.m_nDashLen,
					libLineStylesViewDlg.m_nBscLnWidth,
					RGB(libLineStylesViewDlg.m_nBscLnColorR, libLineStylesViewDlg.m_nBscLnColorG,
						libLineStylesViewDlg.m_nBscLnColorB), 0, 0,
					libLineStylesViewDlg.m_strText, libLineStylesViewDlg.m_strFontName, libLineStylesViewDlg.m_nFontSize,
					RGB(libLineStylesViewDlg.m_nFontColorR, libLineStylesViewDlg.m_nFontColorG, libLineStylesViewDlg.m_nFontColorB),
					false, false, libLineStylesViewDlg.m_iTextOffsetX, libLineStylesViewDlg.m_iTextOffsetY,
					libLineStylesViewDlg.m_bShowTextAlongWithLine);

				if (libLineStylesViewDlg.m_iSelLsID > 0)
				{
					m_pYimaEncCtrl->tmSetLineObjectStyleRefLib(layerPos, innerLayerPos,
						libLineStylesViewDlg.m_iSelLsID, libLineStylesViewDlg.m_bSetColor,
						RGB(libLineStylesViewDlg.m_iLsColorR, libLineStylesViewDlg.m_iLsColorG,
							libLineStylesViewDlg.m_iLsColorB),
						libLineStylesViewDlg.m_bSetWidth, libLineStylesViewDlg.m_iLsWidth);
				}
				m_pYimaEncCtrl->tmSetObjectTextRotate(layerPos, innerLayerPos, libLineStylesViewDlg.m_fTextRotatrAngle);

			}
		}
	}

	if (IsOnOperation(DRAG_EDITING_OBJECT) || IsOnOperation(ADD_LINE_OBJECT_MOUSEMOVING)) /* 注意：本例中把自定义海图对象编辑中的节点拖动、航路点编辑的航路点拖动
											操作统一归为 DRAG_EDITING_OBJECT 操作状态，并统一用拖动的小圆圈
											来实现代码 */
	{
		if (IsOnOperation(ADD_COLOR_ATTENUATION_OBJ))
		{
			SetOperation(NO_OPERATION);
			SetOperation(ADD_COLOR_ATTENUATION_OBJ);
		}
		else
		{
			SetOperation(NO_OPERATION);
		}
	}

	Invalidate();

	return true;
}

void CYimaEncViewerView::OnRotateClockwise()
{
	// TODO: Add your command handler code here
	if (m_curSelectedObjCount == 1) //如果之前有选中某个自定义海图对象则清楚选中状态
	{
		if (IsOnOperation(EDITING_GEO_OBJECT))
		{
			int layerPos = m_editingUserMapObjPos.layerPos;
			int innerLayerObjPos = m_editingUserMapObjPos.innerLayerObjectPos;

			BSTR bstrObjectPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));

			memcpy(bstrObjectPos, &MEM_GEO_OBJ_POS(m_pYimaEncCtrl->GetMemMapCount() - 1,
				m_editingUserMapObjPos.layerPos, m_editingUserMapObjPos.innerLayerObjectPos),
				sizeof(MEM_GEO_OBJ_POS));

			long left, right, top, bottom;
			m_pYimaEncCtrl->GetObjectGeoExtent(&bstrObjectPos, &left, &right, &top, &bottom);
			m_pYimaEncCtrl->tmRotateLineObjectInScrn(layerPos, innerLayerObjPos, ((float)left + right) / 2,
				((float)top + bottom) / 2, 5);

			SysFreeString(bstrObjectPos);

			Invalidate();
		}
	}
}

void CYimaEncViewerView::OnRotateAnticlockwise()
{
	// TODO: Add your command handler code here
	if (m_curSelectedObjCount == 1) //如果之前有选中某个自定义海图对象则清楚选中状态
	{
		if (IsOnOperation(EDITING_GEO_OBJECT))
		{
			int layerPos = m_editingUserMapObjPos.layerPos;
			int innerLayerObjPos = m_editingUserMapObjPos.innerLayerObjectPos;

			BSTR bstrObjectPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));

			memcpy(bstrObjectPos, &MEM_GEO_OBJ_POS(m_pYimaEncCtrl->GetMemMapCount() - 1,
				m_editingUserMapObjPos.layerPos, m_editingUserMapObjPos.innerLayerObjectPos),
				sizeof(MEM_GEO_OBJ_POS));

			long left, right, top, bottom;
			m_pYimaEncCtrl->GetObjectGeoExtent(&bstrObjectPos, &left, &right, &top, &bottom);
			m_pYimaEncCtrl->tmRotateLineObjectInScrn(layerPos, innerLayerObjPos, ((float)left + right) / 2,
				((float)top + bottom) / 2, -5);

			SysFreeString(bstrObjectPos);

			Invalidate();
		}
	}
}

void CYimaEncViewerView::OnNoBlankMouseDrag()
{
	// TODO: Add your command handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CMenu *pMenu = pFrame->GetMenu();

	if (!m_bUseMouseDragBufferMode)
	{
		pMenu->CheckMenuItem(ID_NO_BLANK_MOUSE_DRAG, MF_CHECKED);

		ResizeMapScrn(true, 2);
		m_bUseMouseDragBufferMode = true;
	}
	else
	{
		pMenu->CheckMenuItem(ID_NO_BLANK_MOUSE_DRAG, MF_UNCHECKED);
		ResizeMapScrn(false, 2);
		m_bUseMouseDragBufferMode = false;
	}
}

void CYimaEncViewerView::OnWheelZoomByMousePosi()
{
	// TODO: Add your command handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CMenu *pMenu = pFrame->GetMenu();

	if (!m_bMouseZoomModeOrStdZoomMode)
	{
		pMenu->CheckMenuItem(ID_WHEEL_ZOOM_BY_MOUSE_POSI, MF_CHECKED);
		m_bMouseZoomModeOrStdZoomMode = true;
	}
	else
	{
		pMenu->CheckMenuItem(ID_WHEEL_ZOOM_BY_MOUSE_POSI, MF_UNCHECKED);
		m_bMouseZoomModeOrStdZoomMode = false;
	}
}

#pragma region 空心/延迟

void CYimaEncViewerView::OnHollowMapEffect()
{
	// TODO: 在此添加命令处理程序代码
	m_pYimaEncCtrl->CancelMapEffect();
	SetOperation(NO_OPERATION);
	SetOperation(HOLLOW_MAP);
	Invalidate();
}

void CYimaEncViewerView::OnDelayMapEffect()
{
	// TODO: 在此添加命令处理程序代码  	
	m_pYimaEncCtrl->CancelMapEffect();
	SetOperation(NO_OPERATION);
	SetOperation(DELAY_MAP);
	Invalidate();
}

void CYimaEncViewerView::OnCancelMapEffect()
{
	// TODO: 在此添加命令处理程序代码
	m_pYimaEncCtrl->CancelMapEffect();
	Invalidate();
}
#pragma endregion 

//物标缩小
void CYimaEncViewerView::OnObjZoomOut()
{
	if (m_curSelectedObjCount == 1) //如果之前有选中某个自定义海图对象则清楚选中状态
	{
		if (IsOnOperation(EDITING_GEO_OBJECT))
		{
			int layerPos = m_editingUserMapObjPos.layerPos;
			int innerLayerObjPos = m_editingUserMapObjPos.innerLayerObjectPos;

			BSTR bstrObjectPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));

			memcpy(bstrObjectPos, &MEM_GEO_OBJ_POS(m_pYimaEncCtrl->GetMemMapCount() - 1,
				m_editingUserMapObjPos.layerPos, m_editingUserMapObjPos.innerLayerObjectPos),
				sizeof(MEM_GEO_OBJ_POS));

			long left, right, top, bottom;
			m_pYimaEncCtrl->GetObjectGeoExtent(&bstrObjectPos, &left, &right, &top, &bottom);
			m_pYimaEncCtrl->tmZoomLineObject(layerPos, innerLayerObjPos, ((float)left + right) / 2, ((float)top + bottom) / 2, 0.8);

			SysFreeString(bstrObjectPos);
			Invalidate();
		}
	}
}

//物标放大
void CYimaEncViewerView::OnObjZoomIn()
{
	if (m_curSelectedObjCount == 1) //如果之前有选中某个自定义海图对象则清楚选中状态
	{
		if (IsOnOperation(EDITING_GEO_OBJECT))
		{
			int layerPos = m_editingUserMapObjPos.layerPos;
			int innerLayerObjPos = m_editingUserMapObjPos.innerLayerObjectPos;

			BSTR bstrObjectPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));

			memcpy(bstrObjectPos, &MEM_GEO_OBJ_POS(m_pYimaEncCtrl->GetMemMapCount() - 1,
				m_editingUserMapObjPos.layerPos, m_editingUserMapObjPos.innerLayerObjectPos),
				sizeof(MEM_GEO_OBJ_POS));

			long left, right, top, bottom;
			m_pYimaEncCtrl->GetObjectGeoExtent(&bstrObjectPos, &left, &right, &top, &bottom);
			m_pYimaEncCtrl->tmZoomLineObject(layerPos, innerLayerObjPos, ((float)left + right) / 2, ((float)top + bottom) / 2, 1.2);
			SysFreeString(bstrObjectPos);
			Invalidate();
		}
	}

}

M_POINT CYimaEncViewerView::GetCurMouseOffSetObjCenter(M_GEO_OBJ_POS ObjPos, M_POINT curMouseScrnPo)
{
	MEM_GEO_OBJ_POS objectPos(m_pYimaEncCtrl->GetMemMapCount() - 1, ObjPos.layerPos, ObjPos.innerLayerObjectPos);
	M_POINT objCenterGeoPo(0, 0);
	BSTR strObjPos = ::SysAllocStringByteLen(NULL, sizeof(MEM_GEO_OBJ_POS));
	memcpy(strObjPos, &objectPos, sizeof(MEM_GEO_OBJ_POS));
	long retLeft, retRight, retTop, retButtom;

	m_pYimaEncCtrl->GetObjectGeoExtent(&strObjPos, &retLeft, &retRight, &retTop, &retButtom);
	objCenterGeoPo.x = (float)retLeft / 2 + (float)retRight / 2;
	objCenterGeoPo.y = (float)(retTop + retButtom) / 2;
	M_POINT objCenterScrnPo;
	m_pYimaEncCtrl->GetScrnPoFromGeoPo(objCenterGeoPo.x, objCenterGeoPo.y, (long*)&objCenterScrnPo.x, (long*)&objCenterScrnPo.y);

	M_POINT scrnOffset = curMouseScrnPo - objCenterScrnPo;
	::SysFreeString(strObjPos);
	return scrnOffset;
}


//新窗体
void CYimaEncViewerView::OnAddNewMapCtrl()
{
	static CNewMapDlg* newMapDlg = NULL;
	if (newMapDlg == NULL)
	{
		newMapDlg = new CNewMapDlg();
		newMapDlg->Create(IDD_NEW_MAP_DLG);
	}
	newMapDlg->ShowWindow(SW_SHOW);
}

//鹰眼视图
void CYimaEncViewerView::OnGlobalView()
{
	//static CGlobalView* m_globalView = NULL; 
	if (m_globalView == NULL)
	{
		m_globalView = new CGlobalView();
		m_globalView->Create(IDD_GLOBAL_VIEW_DLG, this);
		m_globalView->m_mainCtrl = m_pYimaEncCtrl;
		m_globalView->m_mainView = this;
		m_globalView->OnMainViewReSize();
	}
	if (m_globalView->m_bOpend == false)
	{
		m_globalView->m_bOpend = true;
		m_globalView->ReSetViewPosion();
		m_globalView->ShowWindow(SW_SHOW);
	}
	else
	{
		m_globalView->ShowWindow(SW_HIDE);
		m_globalView->m_bOpend = false;
	}
}

void CYimaEncViewerView::OnWaterColorSetting()
{
	// TODO: 在此添加命令处理程序代码
	CWaterColorSettingDlg waterColorSettingDlg;
	waterColorSettingDlg.DoModal();
}

void CYimaEncViewerView::OnMeasureArea()
{
	if (IsOnOperation(NO_OPERATION))
	{
		SetOperation(MEASURE_AREA);

		m_icurEditPos = 0;
	}
	else
	{
		AfxMessageBox("请先退出其他操作");
	}
}

void CYimaEncViewerView::OnClosedLineWarn()
{
	if (m_ClosedLineTestObj.layerPos == -1)
	{
		m_pYimaEncCtrl->tmAppendLayer(ALL_LINE);//添加一个多类型的图层,（一般可以在配置文件里面写好）
		int iUserLayerPos = m_pYimaEncCtrl->tmGetLayerCount() - 1;//得到图层的索引
		m_pYimaEncCtrl->tmSetLayerName(iUserLayerPos, "TestClosedLineLayer");
		bool bAddResult = m_pYimaEncCtrl->tmAppendObjectInLayer(iUserLayerPos, TYPE_LINE);
		if (bAddResult)
		{
			int linePos = m_pYimaEncCtrl->tmGetLayerObjectCount(iUserLayerPos) - 1;
			M_GEO_OBJ_POS lineGeoPos = M_GEO_OBJ_POS(iUserLayerPos, linePos);

			M_POINT geoPoints[3];
			geoPoints[0] = M_POINT(1223503800, 333828243);//pEncMapMan->GetGeoPoFromScrnPo(M_POINT(50, 20));
			geoPoints[1] = M_POINT(1223632582, 333763436);//pEncMapMan->GetGeoPoFromScrnPo(M_POINT(150, 80));
			geoPoints[2] = M_POINT(1223825684, 333785037);//pEncMapMan->GetGeoPoFromScrnPo(M_POINT(300, 60)); 
			BSTR bstrGeoPoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 3);
			memcpy(bstrGeoPoints, geoPoints, sizeof(M_POINT) * 3);
			m_pYimaEncCtrl->tmSetLineObjectCoors(iUserLayerPos, linePos, 3, &bstrGeoPoints);//设置点物标坐标
			m_pYimaEncCtrl->tmSetLineObjectStyle(iUserLayerPos, linePos, true, true, 0, 0, 2, RGB(0, 0, 255), 0, 0, "近线、过线报警测试", "宋体", 14, RGB(255, 0, 0), false, false, 0, 50, false);
			m_ClosedLineTestObj = lineGeoPos;
			::SysFreeString(bstrGeoPoints);
		}
	}
	else
	{
		AfxMessageBox("近线报警测试物标已添加");
	}
	m_pYimaEncCtrl->CenterMap(1223503800, 333828243);
	m_pYimaEncCtrl->SetCurrentScale(15935);
	Invalidate();

}

void CYimaEncViewerView::OnShowRefreashTime()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CMenu *pMenu = pFrame->GetMenu();
	if (!m_bShowRefreashTime)
	{
		pMenu->CheckMenuItem(ID_SHOW_REFREASH_TIME, MF_CHECKED);
		m_bShowRefreashTime = true;
	}
	else
	{
		pMenu->CheckMenuItem(ID_SHOW_REFREASH_TIME, MF_UNCHECKED);
		m_bShowRefreashTime = false;
	}
	Invalidate();
}


//实时漫游
void CYimaEncViewerView::OnRuntimeDragmap()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CMenu *pMenu = pFrame->GetMenu();

	m_bRuntimeDragMap = !m_bRuntimeDragMap;
	if (m_bRuntimeDragMap)
	{
		pMenu->CheckMenuItem(ID_RUNTIME_DRAGMAP, MF_CHECKED);
	}
	else
	{
		pMenu->CheckMenuItem(ID_RUNTIME_DRAGMAP, MF_UNCHECKED);
	}
}

//动画缩放
void CYimaEncViewerView::OnAnimationScale()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CMenu *pMenu = pFrame->GetMenu();
	m_bAnimationScale = !m_bAnimationScale;
	if (m_bAnimationScale)
	{
		pMenu->CheckMenuItem(ID_ANIMATION_SCALE, MF_CHECKED);
	}
	else
	{
		pMenu->CheckMenuItem(ID_ANIMATION_SCALE, MF_UNCHECKED);
	}
}

//获取毫秒时间
__int64 CYimaEncViewerView::GetCurTimeMillis()
{
	SYSTEMTIME wtm;
	struct tm tm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	time_t clock = mktime(&tm);
	return (__int64)(clock) * 1000 + wtm.wMilliseconds;
}

//绘制缩放时的动画
void CYimaEncViewerView::DrawScaledMap()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	int iDrawWidth = m_pYimaEncCtrl->GetDrawerScreenWidth();
	int iDrawHeight = m_pYimaEncCtrl->GetDrawerScreenHeight();
	float fScaleIndex = m_fScaleIndex;
	if (m_fScaleIndex < 0)
		fScaleIndex = fabs(1 / m_fScaleIndex);
	int scrnX = (pFrame->m_expandWidth + m_scaleMouseScrnPo.x) *(1 - fScaleIndex);
	int scrnY = (pFrame->m_expandHeight + m_scaleMouseScrnPo.y) *(1 - fScaleIndex);
	int pasteWidth = iDrawWidth * fScaleIndex;
	int pasteHeight = iDrawHeight * fScaleIndex;
	HDC hdc = ::GetDC(m_hWnd);
	m_pYimaEncCtrl->DrawScaledMap((long)hdc, scrnX, scrnY, pasteWidth, pasteHeight);
	::ReleaseDC(m_hWnd, hdc);
	//pEncMapMan->PasteToScrn(painter, scrnX, scrnY, pasteWidth, pasteHeight);

}

void CYimaEncViewerView::CheckIfWheelStop()
{
	if (bMouseWheelState)
	{
		__int64 mSec = GetCurTimeMillis() - m_WheelStartTime;
		if (mSec > 280)
		{
			bMouseWheelState = false;
			//当前鼠标位置
			M_POINT mMouseGeoPo;
			m_pYimaEncCtrl->GetGeoPoFromScrnPo(m_scaleMouseScrnPo.x, m_scaleMouseScrnPo.y, (long*)&mMouseGeoPo.x, (long*)&mMouseGeoPo.y);

			//屏幕中心点
			M_POINT mCenterScrnPo = M_POINT(m_pYimaEncCtrl->GetDrawerScreenWidth() / 2, m_pYimaEncCtrl->GetDrawerScreenHeight() / 2);
			M_POINT mCenterGeoPo;
			m_pYimaEncCtrl->GetGeoPoFromEncScrnPo(mCenterScrnPo.x, mCenterScrnPo.y, (long*)&mCenterGeoPo.x, (long*)&mCenterGeoPo.y);

			//新中心点的地理坐标
			M_POINT mNewCenterGeoPo;
			float fN = m_fScaleIndex;


			if (fN >= 0)
			{
				m_pYimaEncCtrl->SetCurrentScale(m_pYimaEncCtrl->GetCurrentScale() / fN); //放大
				mNewCenterGeoPo.x = mMouseGeoPo.x - (mMouseGeoPo.x - mCenterGeoPo.x) / fN;
				mNewCenterGeoPo.y = mMouseGeoPo.y - (mMouseGeoPo.y - mCenterGeoPo.y) / fN;
			}
			else
			{
				fN = fN * -1;
				float fScale = m_pYimaEncCtrl->GetCurrentScale() * fN;
				fScale = fScale >= 70000000 ? 70000000 : fScale;
				fN = (fScale >= 70000000) ? (70000000 / m_pYimaEncCtrl->GetCurrentScale()) : fN;
				m_pYimaEncCtrl->SetCurrentScale(fScale);// 缩小
				mNewCenterGeoPo.x = mMouseGeoPo.x - (mMouseGeoPo.x - mCenterGeoPo.x) *fN;
				mNewCenterGeoPo.y = mMouseGeoPo.y - (mMouseGeoPo.y - mCenterGeoPo.y) *fN;
			}
			if (m_pYimaEncCtrl->GetMapEffect() == EFFECT_NONE)
			{
				m_pYimaEncCtrl->CenterMap(mNewCenterGeoPo.x, mNewCenterGeoPo.y);
			}
			m_fScaleIndex = 0;

			Invalidate();
			RefreshScaleStatusBar();
			if (m_globalView != NULL)
			{
				m_globalView->ReSetViewPosion();
			}
		}
	}
}

void CYimaEncViewerView::OnAddRadar()
{
	// TODO: 在此添加命令处理程序代码
	radar_info = new RadarInfo();

	SetOperation(NO_OPERATION);
	SetOperation(ADD_USER_LAYER_OBJ);
}


void CYimaEncViewerView::OnSetRadar()
{
	// TODO: 在此添加命令处理程序代码
	//雷达量程、高度、水平面高度设置
	radar_set = new SetRadarDlg();
	radar_set->Create(IDD_SetRadarDlg, this);
	radar_set->ShowWindow(SW_SHOW);
}


void CYimaEncViewerView::OnDeleteRadar()
{
	// TODO: 在此添加命令处理程序代码
	int  mapPos = m_pYimaEncCtrl->GetMemMapCount() - 1;
	string radarDeleteMsg = "VTSRADAR-S";
	/*BSTR curSelObjPosStrings = ::SysAllocStringLen(NULL,
		SEL_OBJ_MAX_COUNT * sizeof(MEM_GEO_OBJ_POS));

	int curSelObjCount =
		m_pYimaEncCtrl->SelectObjectsByScrnPoint(&curSelObjPosStrings,
			point.x, point.y);

	MEM_GEO_OBJ_POS curSelectedObjPoses[SEL_OBJ_MAX_COUNT];
	memcpy(curSelectedObjPoses, curSelObjPosStrings,
		curSelObjCount * sizeof(MEM_GEO_OBJ_POS));

	MEM_GEO_OBJ_POS firstSelectObjPos = curSelectedObjPoses[0];
	SetHighlightObjects(&firstSelectObjPos, 1);*/

	for (list<Radar>::iterator iter = radarList.begin(); iter != radarList.end(); )
	{
		CPoint testPt;
		testPt = selectObjPoint;
		bool res = m_pYimaEncCtrl->IsGeoPointSelectByScrnPoint(selectObjPoint.x, selectObjPoint.y, iter->Lon, iter->Lan, 12);
		if (res)
		{
			//该物标被屏幕上一点所选中
			if (AfxMessageBox("确定删除该雷达？", MB_YESNO) == IDYES)
			{
				bool res = m_pYimaEncCtrl->DeleteGeoObject(mapPos, m_iEditingUserMapLayerNum, iter->innerLayerPos);
				Invalidate();

				radarDeleteMsg = radarDeleteMsg + ";DR" + ";" + iter->Id + ";;;;;;;#";
				//发送Radar删除信息
				sendRadarData(radarDeleteMsg, ipCon->IP_Radar.GetBuffer(), ipCon->Port_Add_Radar);

				iter = radarList.erase(iter);		//返回iter指向被删除元素的下一个元素
				continue;
			}
		}
		iter++;
	}

	/*static CSelectedGeoObjectsDlg* pSelGeoObjsDlg = NULL;
	if (pSelGeoObjsDlg != NULL)
	{
		delete pSelGeoObjsDlg;
	}

	pSelGeoObjsDlg = new CSelectedGeoObjectsDlg();

	if (pSelGeoObjsDlg != NULL)
	{
		pSelGeoObjsDlg->m_curSelectedObjCount = curSelObjCount;
		pSelGeoObjsDlg->SetSelectObjectPoses(curSelectedObjPoses, curSelObjCount);

		pSelGeoObjsDlg->Create(IDD_SEL_OBJECTS_DLG);
		pSelGeoObjsDlg->ShowWindow(SW_SHOW);
	}*/
	//SysFreeString(curSelObjPosStrings);
}


void CYimaEncViewerView::OnModifyRadar()
{
	// TODO: 在此添加命令处理程序代码
	radar_modify = new ModifyRadarDlg();
	radar_modify->Create(IDD_ModifyRadarDlg, this);
	radar_modify->ShowWindow(SW_SHOW);
}


void CYimaEncViewerView::OnRadarProperty()
{
	// TODO: 在此添加命令处理程序代码
	radar_property = new RadarPropertyDlg();
	radar_property->Create(IDD_RadarPropertyDlg, this);
	radar_property->ShowWindow(SW_SHOW);
}

std::vector<std::string> CYimaEncViewerView::split(const std::string& src, const std::string& key)
{
	using namespace std;
	vector<string> v;
	size_t first = 0;
	size_t last = src.find(key);
	while (string::npos != last) {
		v.push_back(src.substr(first, (last - first)));
		first = last + 1;
		last = src.find(key, first);
	}
	v.push_back(src.substr(first));
	return v;
}

UINT Thread_Receive_ODU(LPVOID para)
{
	CYimaEncViewerView* pThis = (CYimaEncViewerView*)para;
	char buff[100];
	int recvLen = 0;
	while (true)
	{
		recvLen = m_pNetToODU->RecvData(buff);
		if (recvLen > 0)
		{
			pThis->recvODUMsg = buff;
		}
		Sleep(100);
	}
	return 1;
}

//void sendData(std::string msg, std::string ip, int port)
//{
//	//WSACleanup();
//	WORD wVersionRequested;
//	WSADATA wsaData;
//	int err;
//
//	wVersionRequested = MAKEWORD(1, 1);//第一个参数为低位字节；第二个参数为高位字节  
//
//	err = WSAStartup(wVersionRequested, &wsaData);//对winsock DLL（动态链接库文件）进行初始化，协商Winsock的版本支持，并分配必要的资源。  
//	if (err != 0)
//	{
//		return;
//	}
//
//	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)//LOBYTE（）取得16进制数最低位；HIBYTE（）取得16进制数最高（最左边）那个字节的内容        
//	{
//		WSACleanup();
//		return;
//	}
//	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
//
//	SOCKADDR_IN addrClt;//需要包含服务端IP信息  
//	addrClt.sin_addr.S_un.S_addr = inet_addr(ip.data());	// inet_addr将IP地址从点数格式转换成网络字节格式整型。  
//	addrClt.sin_family = AF_INET;
//	addrClt.sin_port = htons(port);
//
//	connect(sockClient, (SOCKADDR*)&addrClt, sizeof(SOCKADDR));//客户机向服务器发出连接请求  
//	send(sockClient, msg.data(), msg.size(), 0);
//
//	closesocket(sockClient);
//	WSACleanup();
//}


void CYimaEncViewerView::OnMapHandRoam()
{
	// TODO: 在此添加命令处理程序代码
	SetOperation(HAND_ROAM);
}


void CYimaEncViewerView::OnShipStart()
{
	// TODO: 在此添加命令处理程序代码
	SetEvent(sendAisEvent);		//设置sendAisEvent为有信号状态

	SetTimer(TIMER_REFRESH_OTHERVESSEL, 1000, NULL);
	m_bShipStart = true;
}


void CYimaEncViewerView::OnShipStop()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(TIMER_REFRESH_OTHERVESSEL);
	m_bShipStart = false;
}


void CYimaEncViewerView::OnUpdateShipStart(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!m_bShipStart)
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}


void CYimaEncViewerView::OnUpdateShipStop(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (m_bShipStart)
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}


void CYimaEncViewerView::OnLoadRoutedata()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	/************ 下面开始模拟本船沿第一条航线航行、添加多个AIS目标船沿其它航线航行 **********/
	m_pYimaEncCtrl->AddRoutesFromFile(TEST_ROUTE_FILE_NAME); //从 TEST_ROUTE_FILE_NAME 文件中添加导入航线数据

	AIS_TYPE_ID stationTypeID = m_pYimaEncCtrl->AddAisType("station"); //添加AIS类型(AIS TYPE)
	m_pYimaEncCtrl->SetAisTypeInfo(stationTypeID, _T("station"), false, 1, 1, false, 0, 2, 5000000, true, false, 200000, true);//设置该样式的显示风格

	AIS_TYPE_ID stationTypeID2 = m_pYimaEncCtrl->AddAisType("station2"); //添加AIS类型(AIS TYPE)
	m_pYimaEncCtrl->SetAisTypeInfo(stationTypeID2, _T("station2"), false, 4, 1, false, 0, 6, 5000000, false, false, 200000, true);//设置该样式的显示风格


	int routeCount = m_pYimaEncCtrl->GetRoutesCount();
	if (routeCount > 0)
	{
		pFrame->SetOwnShipStartOnRoute(1);//本船模拟在第一条航线上航行 



		for (int addVsNum = 0; addVsNum < routeCount - 1; addVsNum++)//routeCount - 1; addVsNum ++)
		{//为第二条航线起的每条航线增加1个AIS对象, 让它们分别沿着这些航线航行

			m_pYimaEncCtrl->AddOtherVessel(false, 0, 0, 90, 90, 90, 0, 0);

			CString strAddVslName;

			int mmsi = 4200010 + addVsNum;

			int myVsPos = m_pYimaEncCtrl->GetOtherVesselCount() - 1;

			strAddVslName.Format("AIS Target %d", myVsPos + 1);

			m_pYimaEncCtrl->SetOtherVesselBasicInfo(myVsPos,
				100, 50, strAddVslName, mmsi, NULL, 0);

			long shipNavRouteID = m_pYimaEncCtrl->GetRouteIDFromPos(addVsNum + 1);

			pFrame->m_nOtherVesselSelRouteIDs[myVsPos] = shipNavRouteID;

			//初始模拟航行的目标航路点在航线中的位置是1
			pFrame->m_nOtherVesselCurAimWpPos[myVsPos] = 1;

			//设置模拟航行的航速一个比一个快 
			pFrame->m_nOtherVesselSimulateSpeeds[myVsPos] = 5 * (addVsNum + 1);

			pFrame->SetOtherVesselStartOnRoute(myVsPos,
				pFrame->m_nOtherVesselSelRouteIDs[myVsPos]);

			m_pYimaEncCtrl->SetOtherVesselShowColor(addVsNum, false,
				RGB(addVsNum * 255 / (routeCount - 1), 0, 0), false,
				RGB(addVsNum * 255 / (routeCount - 1), 0, 0));		   //此接口会彻底改变符号的颜色

			CString strVslText;
			strVslText.Format(_T("Vsl %d"), m_pYimaEncCtrl->GetOtherVesselID(addVsNum));
			m_pYimaEncCtrl->SetOtherVesselShowText(addVsNum, true, strVslText, true, 20, true, RGB(0, 0, 255));
			m_pYimaEncCtrl->SetShipTrackStyle(false, myVsPos, true, RGB(0, 0, 255), 2, true, 4, RGB(0, 255, 255));
			int curTypeId = addVsNum % 2 == 0 ? stationTypeID : stationTypeID2;
			m_pYimaEncCtrl->SetAisTargetType(m_pYimaEncCtrl->GetOtherVesselCount() - 1, stationTypeID);
		}
	}
	pFrame->RefreshNavBarRouteList();		//
	pFrame->RefreshOtherVesselList();
	pFrame->RedrawView();
}

DWORD __stdcall CYimaEncViewerView::SendAISThreadProc(LPVOID pvoid)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CYimaEncViewerView* pView = (CYimaEncViewerView*)pFrame->GetActiveView();
	WaitForSingleObject(pView->sendAisEvent, INFINITE);
	long ownGeoPosx, ownGeoPosy, otherGeoPosx, otherGeoPosy;
	float ownHead, ownCOG, ownSOG, otherHead, otherCOG, otherSOG;
	BSTR ownMMSI;
	long otherMMSI;
	CString aisOwnMsg, aisOtherMsg;
	CString aisOwnEncodeMsg, aisOtherEncodeMsg;
	BOOL isArpaOrAis;
	long iGeoCoorMultiFactor = pView->m_pYimaEncCtrl->GetGeoCoorMultiFactor();
	int otherVesselCount = pView->m_pYimaEncCtrl->GetOtherVesselCount();
	while (true)
	{
		pView->m_pYimaEncCtrl->GetOwnShipCurrentInfo(&ownGeoPosx, &ownGeoPosy, &ownHead, &ownCOG, NULL, &ownSOG, NULL);
		//pView->m_pYimaEncCtrl->GetOwnShipBasicInfo(NULL, NULL, NULL, &ownMMSI);
		aisOwnMsg.Format("1,0,%s,0,%f,%f,0,X:%d,Y:%d,%f,%f,18,0,0",
			"4200020",
			5.0,						//转向率5.0
			ownSOG * 10,				//航速
			GetAISGeoIntFromGeoCoor(ownGeoPosx, iGeoCoorMultiFactor),
			GetAISGeoIntFromGeoCoor(ownGeoPosy, iGeoCoorMultiFactor),
			ownCOG * 10,				//航向		
			ownCOG);					//船首向
		aisOwnEncodeMsg = pView->m_aisSend.sendStr(aisOwnMsg, TRUE);
		aisOwnEncodeMsg.AppendChar('\r');
		aisOwnEncodeMsg.AppendChar('\n');
		sendAisData(aisOwnEncodeMsg.GetBuffer(), pView->ipCon->IP_Radar.GetBuffer(), pView->ipCon->Port_Ais_Radar);
		sendAisData(aisOwnEncodeMsg.GetBuffer(), pView->ipCon->IP_Odu.GetBuffer(), pView->ipCon->Port_Ais_Odu);
		for (int otherVesselNum = 0; otherVesselNum < otherVesselCount; otherVesselNum++)
		{
			bool res = pView->m_pYimaEncCtrl->GetOtherVesselCurrentInfo(otherVesselNum, &isArpaOrAis, &otherGeoPosx, &otherGeoPosy, &otherHead, &otherCOG, NULL, &otherSOG, NULL, NULL, NULL);
			pView->m_pYimaEncCtrl->GetOtherVesselBasicInfo(otherVesselNum, NULL, NULL, NULL, &otherMMSI, NULL);
			aisOtherMsg.Format("1,0,%s,0,%f,%f,0,X:%d,Y:%d,%f,%f,18,0,0",
				otherMMSI,
				5.0,						//转向率5.0
				otherSOG * 10,				//航速
				GetAISGeoIntFromGeoCoor(otherGeoPosx, iGeoCoorMultiFactor),
				GetAISGeoIntFromGeoCoor(otherGeoPosy, iGeoCoorMultiFactor),
				otherCOG * 10,				//航向		
				otherCOG);					//船首向
			aisOtherEncodeMsg = pView->m_aisSend.sendStr(aisOtherMsg, FALSE);
			aisOtherEncodeMsg.AppendChar('\r');
			aisOtherEncodeMsg.AppendChar('\n');
			sendAisData(aisOtherEncodeMsg.GetBuffer(), pView->ipCon->IP_Radar.GetBuffer(), pView->ipCon->Port_Ais_Radar);
			sendAisData(aisOtherEncodeMsg.GetBuffer(), pView->ipCon->IP_Odu.GetBuffer(), pView->ipCon->Port_Ais_Odu);
		}
		Sleep(500);
	}
	return 0;
}
