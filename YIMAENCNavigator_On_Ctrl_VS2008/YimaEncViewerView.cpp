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
list<ODU> oduList;		//ODU��Ϣ����
list<Radar> radarList;	//Radar��Ϣ����
Radar curSelectRadar;	//��ǰѡ�е�Radar��Ϣ

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

/* YIMAENC COMMENT: ע�⣬
�ڷǶԻ�������У�YimaEnc Control ����Ϣ��Ӧ�޷�ͨ��Class Wizard�Զ�
����, ���ֹ�������Ϣӳ��� BEGIN_EVENTSINK_MAP ������ */
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
	
	m_iEditingUserMapLayerNum = 0;	//��ʼ��Ϊ-1
	
	m_iMouseStoppedTimerCount = 0;
	
	m_addingSpecialLineType = NO_SPECIAL_TYPE;
	
	SetOperation(NO_OPERATION); 

	m_nTimerStep = 5;

	m_highlightDepthLowerLimit = 0;
	m_highlightDepthUpLimit = 0;

	m_bMouseZoomModeOrStdZoomMode = true;
	m_bUseMouseDragBufferMode = false;
	m_ScrnOffset = M_POINT(0,0);
	m_globalView = NULL;
	m_icurEditPos = 0;
	m_ClosedLineTestObj.layerPos = -1;
	m_usedMSecond = 10;	
	m_bShowRefreashTime = true;
	m_bRuntimeDragMap = false;
	m_bAnimationScale = false;
	bMouseWheelState = false;
	m_startFillTrans = 100;
	//m_arrColorAttenuationObj = new std::list<M_COLOR_ATTENUATION>(); //��¼��������ɫ˥���������Ϣ

	m_bShipStart = false;
	sendAisEvent = NULL;

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
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(effectGeoPoX, effectGeoPoY -100, &retScrnPoX1, &retScrnPoY1);
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(effectGeoPoX, effectGeoPoY +100, &retScrnPoX2, &retScrnPoY2);   
			centerScrnPo.y = (long)((retScrnPoY1 + retScrnPoY2) / 2);  
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(effectGeoPoX - 100, effectGeoPoY, &retScrnPoX1, &retScrnPoY1);
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(effectGeoPoX + 100, effectGeoPoY, &retScrnPoX2, &retScrnPoY2);    
			centerScrnPo.x = (long)((retScrnPoX1 + retScrnPoX2) / 2);
			iScrnRadius = sqrt(pow(retScrnPoX1 - retScrnPoX2, 2.0) + pow(retScrnPoY1 - retScrnPoY2, 2.0)) / 2; 
		}
		else if(curMapEffect == EFFECT_DELAY)
		{									
			long retScrnPoX = 0, retScrnPoY = 0;
			m_pYimaEncCtrl->SetMapEffectRadius(0);	 
			iScrnRadius = m_pYimaEncCtrl->GetScrnLenFromGeoLen(fradiusByMeter *1000);
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(effectGeoPoX, effectGeoPoY, &retScrnPoX, &retScrnPoY);
			centerScrnPo = M_POINT(retScrnPoX, retScrnPoY);
			m_pYimaEncCtrl->SetMapEffectRadius(fradiusByMeter);								    
		}  		 
		
		HDC hdc = pDC->m_hDC;
		SetROP2(hdc, R2_XORPEN);    
		HPEN hPen = (HPEN) CreatePen(PS_SOLID, 2, RGB_EBL_LINE); 
		HPEN hOldPen = (HPEN) SelectObject(hdc, hPen);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Ellipse(hdc, centerScrnPo.x - iScrnRadius, centerScrnPo.y - iScrnRadius, centerScrnPo.x + iScrnRadius, centerScrnPo.y + iScrnRadius);
		SetROP2(hdc, R2_COPYPEN);
		SelectObject(hdc, hOldPen);		
		SelectObject(hdc, hOldBrush);
		DeleteObject(hPen);
	}
	

} 

/*** ������ͼ������� ***/
void CYimaEncViewerView::DrawMapOperationPanel(HDC hScrnDC)
{ 
	/* IDB_BITMAP1 Ϊ����Ƥ��ͼƬ, �ڡ���Դ�༭���Ļ�ͼ��������Ա༭��
	    Ҳ�����ڻ�ͼ���ϱ༭��copy������Դ�༭��������  */
	HBITMAP hbmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1)); 
	/* IDB_BITMAP2 Ϊ���Ƥ��ͼƬ��Ӧ�ġ���ͼ��ͼƬ, ���ˡ���ͼ��ͼƬ���Ϳ���ʵ��
	    ͸����ͼ��Ч��������ͼ��ͼƬ��������Ƥ��ͼƬ�ı�������(����Ҫ��͸�����Ĳ���)�򡰴��ڡ���
	    �����ݵĲ���(����Ҫ��ʾ�Ĳ���)Ϳ�����ס� */
	HBITMAP hMaskbmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2)); 		
	HDC	hImageDC = CreateCompatibleDC(hScrnDC);
	SelectObject(hImageDC, hMaskbmp);
	BitBlt(hScrnDC, MAP_OPERATION_PANEL_LEFT, MAP_OPERATION_PANEL_TOP, 
		102, 163, hImageDC, 0, 0, SRCPAINT); //102 �� 163 �ֱ�Ϊ Ƥ��ͼƬ �Ŀ��Ⱥ͸߶�
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
	m_beforeRefesh =  GetTickCount();
	if (m_pYimaEncCtrl != NULL)
	{			    
		HDC hdc = ::GetDC(m_hWnd); //test2013.02.03
		m_pYimaEncCtrl->DrawMapsInScreen((long)hdc);  
		//DrawMapOperationPanel(hdc); //��ʾ������ͼ�������

		::ReleaseDC(m_hWnd, hdc);
	} 
	/*DWORD usedMSecond = GetTickCount() - m_beforeRefesh;
	if (usedMSecond > 10)
	{
		m_usedMSecond = usedMSecond; //����10����Ϊ��Ч��ʱ
	}*/
}

bool CYimaEncViewerView::IsOnDragingObjectOperation()
{
	return IsOnOperation(HAND_ROAM) || IsOnOperation(DRAG_EDITING_OBJECT) || IsOnOperation(ADD_LINE_OBJECT_MOUSEMOVING);
}

HDC hDynamicDC = NULL; 
//�浱ǰ���λ�û��Ʊ༭�еĶ�̬������
void CYimaEncViewerView::DrawDynamicScreenMap(M_POINT mousePoint)
{ 
	//YIMAENC COMMENT:  YimaEnc Control interoped below!
 	if (m_pYimaEncCtrl != NULL)
	{   
 		m_pYimaEncCtrl->SetDrawerPastingByMemScrn(true); /* ��������ͼ������ģʽΪ��ͼģʽ, ����ģʽ�������DrawMapsInScreen()�ӿڲ����������ƺ�ͼ, 
		   ����ֱ�ӽ���һ֡���ƺõĺ�ͼֱ��������Ļ��(�����������ƵĶ�̬��꣬�����ýӿ� tmSetObjectDynamicObjectOrNot() ����
		   ��Ϊ��̬�������), ����ֱ����ͼ, ���ٶȿ�, �������� MOUSE MOVE��Ϣ�Ŀ�����Ӧ 	*/
		//m_pYimaEncCtrl->DrawMapsInScreen((long)hDynamicDC); //������һ֡�ľ�̬��ͼ, �Ӷ����� DrawDynamicScreenMap() ��һ�λ��ƵĶ�̬����
		  
 		long geoPoX, geoPoY;
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(mousePoint.x, mousePoint.y, &geoPoX, &geoPoY); 

 		int objLayerPos = m_editingUserMapObjPos.layerPos;
		int objInLyrPos = m_editingUserMapObjPos.innerLayerObjectPos;

		int geoType = m_pYimaEncCtrl->tmGetGeoObjectType(objLayerPos, objInLyrPos);

		if (geoType == TYPE_POINT)
		{  
 			m_pYimaEncCtrl->tmSetPointObjectCoor(objLayerPos, objInLyrPos, geoPoX, geoPoY); //����ǵ����, ��ֱ�����������꼴�ƶ��� 
		}
		else
		{
			if (geoType == TYPE_LINE || geoType == TYPE_FACE)
			{
				m_pYimaEncCtrl->SetIfUseGDIPlus(true);
				if (m_iEditingPointPosOnEditingLine == -1)	//����༭�ڵ����Ϊ��, ����Ϊ���϶����, ���϶��������ĵ����ƶ�ĳ��������
				{
					if (IsOnOperation(DRAG_EDITING_OBJECT))
					{
  						m_pYimaEncCtrl->tmMoveObjectInScrn(objLayerPos, objInLyrPos, mousePoint.x - m_ScrnOffset.x, mousePoint.y - m_ScrnOffset.y); 
					}
				}
				else	//�������ĳ���ڵ��λ��
				{
  					if (m_addingSpecialLineType == SINGLE_ARROW_LN_TYPE)
					{ //����ͷ���Ƚϸ�������, ��̬�������ʱ����ֱ���� tmMoveOnePointOfLineObject() �ӿ���ʵ�ֶ�̬Ч��
						BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * m_nEditingLinePointCount); 						
						memcpy(strLinePoints, m_editingLineGeoPoints, sizeof(M_POINT) * m_nEditingLinePointCount); 
						m_editingLineGeoPoints[m_nEditingLinePointCount - 1] = M_POINT(geoPoX, geoPoY); 
						m_pYimaEncCtrl->tmSetLineObjectCoors(objLayerPos, objInLyrPos, m_nEditingLinePointCount, &strLinePoints);
						m_pYimaEncCtrl->tmSetObjectAsSpecialType(objLayerPos, objInLyrPos, m_addingSpecialLineType);
						SysFreeString(strLinePoints);
					}
					else
					{ //����ͼ��ֱ���� tmMoveOnePointOfLineObject() �ӿ���ʵ�ֶ�̬Ч��
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
	
	//YIMAENC COMMENT: ע��!! ע��������̳еķ����ſɿ˷���Ļ��˸
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
				
		//����Ϊ��ʵ�ֱ�����ʾ��ͼ��������ĵ㲻��
		if (nowScrnWidth > 50)
		{	
			m_pYimaEncCtrl->SetCurrentScale(m_pYimaEncCtrl->GetCurrentScale() * (float)oldDrawerScrnWidth / nowScrnWidth);
			m_pYimaEncCtrl->CenterMap(oldCenterGeoPoint.x, oldCenterGeoPoint.y);
		}
		
		char chMsg[255];
		memset(chMsg,'\0', 255); 
		pFrame->RefreshNavigationDlgBar(chMsg);


		RefreshScaleStatusBar();		
		if(strlen(chMsg) > 0)
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
		
		// RefreshDrawer �ڳ�ʼ����Ļ �� �ı亣ͼ��Ļ��СʱӦ�ñ�����			
		m_pYimaEncCtrl->RefreshDrawer((long)m_hWnd, nowScrnWidth, nowScrnHeight, 0, 0);  			
				
		//����Ϊ��ʵ�ֱ�����ʾ��ͼ��������ĵ㲻��
		if (nowScrnWidth > 50)
		{	
			m_pYimaEncCtrl->SetCurrentScale(m_pYimaEncCtrl->GetCurrentScale() * (float)oldDrawerScrnWidth / nowScrnWidth);
			if(m_pYimaEncCtrl->GetMapEffect() == EFFECT_NONE)
			{ 
				m_pYimaEncCtrl->CenterMap(oldCenterGeoPoint.x, oldCenterGeoPoint.y);
			}
		}
		
		CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		char chMsg[255];
		memset(chMsg,'\0', 255); 
		pFrame->RefreshNavigationDlgBar(chMsg);
		
		RefreshScaleStatusBar();

		if(m_globalView != NULL)
		{
			m_globalView->OnMainViewReSize(nowScrnWidth, nowScrnHeight); 
			m_globalView->ReSetViewPosion();
		}
		if(strlen(chMsg) > 0)
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

/* YIMAENC COMMENT: ע��,
	��ΪCYimaEncViewerView �� OnSize ��CMainFrame��OnCreate ֮ǰ���ã�
	�����ڵ�һ�� OnSize ������ m_pYimaEncCtrl ���ܱ���ʼ��������ѡ����
	OnSetFocus ʱ��ʼ�� */
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
			
			// RefreshDrawer �ڳ�ʼ����Ļ �� �ı亣ͼ��Ļ��СʱӦ�ñ�����  
			m_pYimaEncCtrl->RefreshDrawer((long)m_hWnd,	scrnWidth, scrnHeight, 0, 0); 	
			m_pYimaEncCtrl->SetOwnShipShowSymbol(false, 5, true, 16, 5000000);
			m_pYimaEncCtrl->SetDrawOwnShipSpecialOptions(true, false, true, RGB(255,0,0));			    
			m_pYimaEncCtrl->SetShipTrackStyle(true, 0, true, RGB(255,0,0), 2, true, 4, RGB(0, 255, 0));
			//m_pYimaEncCtrl->SetBackgroundColor(0x00D8F4E1); // 0x00F6E6AC);

			bool bSetOnSafeDepthAutoDetect = false;
			if (bSetOnSafeDepthAutoDetect)
			{
				m_pYimaEncCtrl->SetIfUseSafeDepthLineDectect(bSetOnSafeDepthAutoDetect, bSetOnSafeDepthAutoDetect);
				AfxMessageBox("ע��! �Զ����ˮ�������ܿ���!"); 
			} 

			bool bIfShowOwnShipTrack = true;
			if (bIfShowOwnShipTrack)
			{
				m_pYimaEncCtrl->SetDrawShipOptions(true, true, false, false, 10, false, 1, 100, 50, 60);
				//������2��������100����ʾ�ڴ��洢���100����ǰ�����㣻
				//���1��������50����ʾֻ��ʾ�ڴ��д洢��100�������е�50����
			}
			else
			{
				m_pYimaEncCtrl->SetDrawShipOptions(true, false, false, false, 10, false, 1, 0, 0, 60);	//������2�����������1�����������0, �򲻴洢����ʾ��ǰ��������		
			}

			bool bIfShowOtherVesselTrack = true;
			if (bIfShowOtherVesselTrack)
			{ 
				m_pYimaEncCtrl->SetDrawShipOptions(false, true, true, true, 10, true, 1, 500, 200, 60);
				//������3��������500����ʾ�ڴ��洢���500����ǰ�����㣻
				//������2��������200����ʾֻ��ʾ�ڴ��д洢��500�������е�200����
				//���һ������60����ʾ���ֻ��ʾ60���ӵĺ�����
				
			}
			else
			{
				m_pYimaEncCtrl->SetDrawShipOptions(false, true, true, true, 10, true, 1, 0, 0, 1);//������2�����������1�����������0, �򲻴洢����ʾ��ǰ��������	
			}  
						
			m_pYimaEncCtrl->FocusLibMap(0);   			

			BOOL bTwoOrFourShade = false; 
			m_pYimaEncCtrl->SetDepthShadesMode(bTwoOrFourShade, 2, 10, 20); 
  
			/************ ���濪ʼģ�Ȿ���ص�һ�����ߺ��С����Ӷ��AISĿ�괬���������ߺ��� **********/
			//m_pYimaEncCtrl->AddRoutesFromFile(TEST_ROUTE_FILE_NAME); //�� TEST_ROUTE_FILE_NAME �ļ������ӵ��뺽������
			//
			//AIS_TYPE_ID stationTypeID = m_pYimaEncCtrl->AddAisType("station"); //����AIS����(AIS TYPE)
			//m_pYimaEncCtrl->SetAisTypeInfo(stationTypeID, _T("station"), false, 1, 1,false, 0, 2, 5000000, true,false, 200000, true);//���ø���ʽ����ʾ���

			//AIS_TYPE_ID stationTypeID2 = m_pYimaEncCtrl->AddAisType("station2"); //����AIS����(AIS TYPE)
			//m_pYimaEncCtrl->SetAisTypeInfo(stationTypeID2, _T("station2"),  false, 4, 1, false, 0, 6, 5000000, false,false, 200000, true);//���ø���ʽ����ʾ���


			//int routeCount = m_pYimaEncCtrl->GetRoutesCount();
			//if(routeCount > 0)
			//{
			//	pFrame->SetOwnShipStartOnRoute(1);//����ģ���ڵ�һ�������Ϻ��� 

			//				

			//	for (int addVsNum = 0; addVsNum < routeCount - 1; addVsNum ++)//routeCount - 1; addVsNum ++)
			//	{//Ϊ�ڶ����������ÿ����������1��AIS����, �����Ƿֱ�������Щ���ߺ���
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
			//			//��ʼģ�⺽�е�Ŀ�꺽·���ں����е�λ����1
			//			pFrame->m_nOtherVesselCurAimWpPos[myVsPos] = 1;
			//			
			//			//����ģ�⺽�еĺ���һ����һ���� 
			//			pFrame->m_nOtherVesselSimulateSpeeds[myVsPos] = 5 * (addVsNum + 1);
			//			
			//			pFrame->SetOtherVesselStartOnRoute(myVsPos, 
			//				pFrame->m_nOtherVesselSelRouteIDs[myVsPos]);
			//			
			//			m_pYimaEncCtrl->SetOtherVesselShowColor(addVsNum, false, 
			//				RGB(addVsNum * 255 / (routeCount - 1), 0, 0), false, 
			//				RGB(addVsNum * 255 / (routeCount - 1), 0, 0));		   //�˽ӿڻ᳹�׸ı���ŵ���ɫ
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
			m_pYimaEncCtrl->SetOtherVesselBasicInfo(iShipPos,100,30,"�������Դ���", 5552888, NULL, 0); 
			m_pYimaEncCtrl->SetAisTargetType(iShipPos, stationTypeID2);*/

			pFrame->RefreshNavBarRouteList();
			pFrame->RefreshOtherVesselList();  		
			SetTimer(1, 100, NULL); //��̬��ʾ��: ������ʱ���ж����ͣ��ʱ�� 
			SetTimer(3, 20, NULL);//�������ţ�����Ƿ��ˢ�º�ͼ��ʱ��
			SetTimer(10, 1000, NULL);//�������ţ�����Ƿ��ˢ�º�ͼ��ʱ��

			//��������ODU��¼�߳�
			pThread_receiveODU = AfxBeginThread(Thread_Receive_ODU, this);
			
			sendAisEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
			//����AIS�߳�
			m_hSendAISThread = ::CreateThread(NULL, 0, SendAISThreadProc, this, 0, NULL);
			
			SetTimer(TIME_REFRESH_RADARLIST, 500, 0);
			SetTimer(TIME_ODU_PARSE, 100, 0);
			SetTimer(TIME_SET_ODUCOUNT, 550, 0);
		}  

		//test by tcf 2012.08.28
		//��������10w����
		
		bool bTestHugeNumVessel = false;
		if (bTestHugeNumVessel)
		{
			int typeID = m_pYimaEncCtrl->AddAisType("ais"); //����AIS����(AIS TYPE)

			m_pYimaEncCtrl->SetAisTypeInfo(typeID, _T("ais"), false, 
							4, 1, false, 0, 6, 500000, true,false, 50000, true);//���ø�AIS ���͵���ʾ���

			for (int vslNum = 0; vslNum < 10; vslNum++)
			{
#define MAX_RAND_VAL 32767
				long vslGeoX = (105 + (float)(rand() % MAX_RAND_VAL)/MAX_RAND_VAL * 28) * UNI_GEO_COOR_MULTI_FACTOR;
				long vslGeoY = (3 + (float)(rand() % MAX_RAND_VAL)/MAX_RAND_VAL * 38) * UNI_GEO_COOR_MULTI_FACTOR;
				float head = (float)(rand() % MAX_RAND_VAL)/MAX_RAND_VAL * 360;
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

/* YIMAENC COMMENT: ע�⣬
�ڷǶԻ�������У�YimaEnc Control ����Ϣ��Ӧ�޷�ͨ��Class Wizard�Զ�
����, ���ֹ�������Ϣӳ�������� */
void CYimaEncViewerView::OnAfterDrawMarineMapYimaEncCtrl()
{  
	bool bIfTestSelfDrawFunctions = false; //�Ƿ���ʾ�������ɻ��ƺ���

	if (bIfTestSelfDrawFunctions)
	{
		////////////���Դ���////////////////////
		m_pYimaEncCtrl->SetCurrentPen(2, 0xff0000);
		m_pYimaEncCtrl->SetCurrentBrush(0x00ff000);
		m_pYimaEncCtrl->DrawLine(100, 200, 200, 200);

		int showPoCount = 3;
		BSTR strFacePoints = ::SysAllocStringLen(NULL, 
			sizeof(M_POINT) * showPoCount);

		M_POINT polygonRgn1[] = {M_POINT(50, 50), M_POINT(300, 50), M_POINT(300, 300)}; 	
		memcpy(strFacePoints, polygonRgn1, sizeof(M_POINT) * showPoCount);

		m_pYimaEncCtrl->FillPolygon(&strFacePoints, showPoCount, false, 100);	

		::SysFreeString(strFacePoints);
	}
}

/* YIMAENC COMMENT: ע�⣬
�ڷǶԻ�������У�YimaEnc Control ����Ϣ��Ӧ�޷�ͨ��Class Wizard�Զ�
����, ���ֹ�������Ϣӳ�������� */
void CYimaEncViewerView::OnAfterDrawMapYimaEncCtrl()
{   

	//m_pYimaEncCtrl->DrawPointWithLibSymbol(1, 100, 100, false, 0, 1);
	//CString str = L"ddd";
	//m_pYimaEncCtrl->TextOutAtPoint(str,200,200);
	int objNum = 0;
	for (objNum = 0; objNum < m_curSelectedObjCount; objNum ++)
	{ 
		MEM_GEO_OBJ_POS objPos = m_curSelectedObjPoses[objNum];
		
		BSTR strObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS)); 
		memcpy(strObjPos, &objPos, sizeof(MEM_GEO_OBJ_POS));
		
		bool bEditingTheObject = objPos.memMapPos == m_pYimaEncCtrl->GetMemMapCount() - 1;
		
		m_pYimaEncCtrl->HighLightSelectedObject(&strObjPos, RGB(255, 0, 0),
			RGB(0, 0, 255), 4, RGB(0, 0, 255), 30, false, bEditingTheObject,
			m_iEditingPointPosOnEditingLine);  

		/* ��������ĵ���ʾ��ק���ţ��Է����û�������ҷ������
		if (bEditingTheObject)
		{
			//��ȡ��ǰѡ�е��������ĵ� add by tcf 2011.05.08
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
	if (m_icurEditPos > 0) //�����
	{
		int poCount = m_icurEditPos + 1;						  
		M_POINT* arrScrnPo = new M_POINT[poCount];	  
		for (int i = 0; i < poCount; i ++)
		{
			long retScrnPoX = 0, retScrnPoY = 0;
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(m_arrMeasureGeoPo[i].x, m_arrMeasureGeoPo[i].y, &retScrnPoX, &retScrnPoY);
			arrScrnPo[i].x = retScrnPoX;
			arrScrnPo[i].y = retScrnPoY;
		}	
		BSTR bstrScrnPo = ::SysAllocStringLen(NULL, sizeof(M_POINT) * poCount);
		memcpy(bstrScrnPo, arrScrnPo, poCount * sizeof(M_POINT));
		if(poCount >= 3) 
		{										 
			BSTR bstrGeoPo = ::SysAllocStringLen(NULL, sizeof(M_POINT) * poCount);
			memcpy(bstrGeoPo, &m_arrMeasureGeoPo, poCount * sizeof(M_POINT));
			float fAreaValue = (m_pYimaEncCtrl->GetAreaOfGeoRegion(poCount, &bstrGeoPo))/ 1000 / 1000;
			CString strEblInfo;
			strEblInfo.Format("���%.3fƽ��ǧ��", fAreaValue);
			::SysFreeString(bstrGeoPo);				  
			
			m_pYimaEncCtrl->SetCurrentBrush(RGB(125,125,125));   
			m_pYimaEncCtrl->SetCurrentPen(2, RGB(0,0,255));
			m_pYimaEncCtrl->FillPolygon(&bstrScrnPo, poCount, true, 60);
			m_pYimaEncCtrl->TextOutAtPoint(strEblInfo, arrScrnPo[0].x, arrScrnPo[0].y);
		}
		else if (poCount == 2)
		{
			m_pYimaEncCtrl->DrawDashLine(&bstrScrnPo, poCount, 2, RGB(0,0,255), 15, 15);
		}

		::SysFreeString(bstrScrnPo);
		delete[] arrScrnPo;
	}

	bool bIfShowHighlightDepthArea = false; //�Ƿ���ʾ����ˮ����
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
			for (int memMapNum = 0; memMapNum < memMapCount; memMapNum ++)
			{
				int objCount = m_pYimaEncCtrl->GetLayerObjectCountOfMap(memMapNum, lyrPos); 
				
				for (int objNum = 0; objNum < objCount; objNum ++)
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
						nHighlightDepthAreaObjCount ++;
					}
					
					::SysFreeString(retObjValString);   
					::SysFreeString(pBstrObjPos);    
				}  
			}
			
			m_pYimaEncCtrl->SetIfUseGDIPlus(true);
			for (objNum = 0; objNum < nHighlightDepthAreaObjCount; objNum ++)
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
	
	/******************** ���´���������ɻ��ƺ����� ***************************/
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

		M_POINT polygonRgn1[7] = {M_POINT(312 ,200 ),M_POINT(326 ,239 ),M_POINT(334 ,249 ),M_POINT(344 ,180 ),M_POINT(354 ,100 ),
			M_POINT(363 ,300 ),M_POINT(372 ,400 )};
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
		 
		m_pYimaEncCtrl->SetCurrentFont("����", 40, 0x0000ff, false, false);
		
		char strText[255];
		char a = 0xB0;
		sprintf(strText, "������ʾ�ı�: 21��30��56��");
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

	//��ʾ��ʾ�����������
	//DrawMapOperationPanel((HDC)m_pYimaEncCtrl->GetDrawerHDC()); 
	/****************************************************************************/ 

	if (m_bShowRefreashTime)
	{
		DWORD usedMSecond = GetTickCount() - m_beforeRefesh;
		if (usedMSecond > 10)
		{
			m_usedMSecond = usedMSecond; //����10����Ϊ��Ч��ʱ
		}
		CString strUsedTime;
		strUsedTime.Format("ˢ�º�ʱ��%d ����", m_usedMSecond);
		m_pYimaEncCtrl->SetCurrentFont("", 15, RGB(0,0,255), false, false);
		m_pYimaEncCtrl->TextOutAtPoint(strUsedTime, 170,40);

	}
}

COLORREF m_crWhite = RGB(255, 255, 255);
COLORREF m_crBlack = RGB(0, 0, 0);
void TransPasteDC(HDC scrnDC, HDC destDC, HDC srcDC, int scrnWidth, int scrnHeight, M_COLOR transColor)
{	 
	COLORREF crOldBack = SetBkColor(destDC, m_crWhite);
	COLORREF crOldText = SetTextColor(destDC, m_crBlack); 

	//����͸����
	HDC tranDC = CreateCompatibleDC(scrnDC);
	HBITMAP tranBmp = CreateBitmap(scrnWidth, scrnHeight, 1, 1, NULL); 
	SelectObject(tranDC, tranBmp);
	
	SetBkColor(srcDC, RGB(transColor.r, transColor.g, transColor.b)); 
	BitBlt(tranDC, 0, 0, scrnWidth, scrnHeight, srcDC, 0, 0, SRCCOPY); 
 
	//����͸����ͼ
	BitBlt(destDC, 0, 0, scrnWidth, scrnHeight, srcDC, 0, 0, SRCINVERT);
	BitBlt(destDC, 0, 0, scrnWidth, scrnHeight, tranDC, 0, 0, SRCAND);
	BitBlt(destDC, 0, 0, scrnWidth, scrnHeight, srcDC, 0, 0, SRCINVERT);   
	 
    SetBkColor(destDC, crOldBack);
	SetTextColor(destDC, crOldText); 

	DeleteDC(tranDC);  
	DeleteObject(tranBmp); 
} 

//ģ���״�ͼ�����
void CYimaEncViewerView::OnDrawRadar()
{    
	bool bIfTestDrawRadar = true;
	
	if (bIfTestDrawRadar)
	{
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
		
		if (m_pYimaEncCtrl->GetDrawRadarOrNot())
		{			
			HDC hdc = (HDC)m_pYimaEncCtrl->GetDrawerHDC(); /* YIMAENC COMMENT: ע�⣬�����Ժ�ͼ�������� HDC ΪĿ��DC�������״�ͼ��*/
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
			blend.SourceConstantAlpha = 100; //��ϵ���ɵ�����ֵ��Χ��0~255
			if (!::AlphaBlend(hdc, -100, -50, 1200, 1200, hMemDC, 0, 0, 1200, 1200, blend))
			{ 
				BitBlt(hdc, -100, -50, 1000, 1000, hMemDC, 0, 0, SRCCOPY); 
			}  
			
			DeleteObject(hBmp); 

			radarFrameBmpFileNumber ++;

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
				objCount * sizeof (MEM_GEO_OBJ_POS));
			
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
	for (int wpPos = 0; wpPos < totalWpCount; wpPos ++)
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
	for (int rtPos = 0; rtPos < totalRouteCount; rtPos ++)
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
	//�Զ��庣ͼ�����϶��༭����ʵ�� -- �������´�������
	if (IsOnOperation(EDITING_GEO_OBJECT))
	{   	
		M_GEO_TYPE geoType = (M_GEO_TYPE)m_pYimaEncCtrl->tmGetGeoObjectType(m_editingUserMapObjPos.layerPos, 
			m_editingUserMapObjPos.innerLayerObjectPos);
		if (geoType == TYPE_LINE || geoType == TYPE_FACE)
		{ 
			int selPointPosInLine = 
				m_pYimaEncCtrl->tmSelectOnePointOfLineObject(point.x, point.y, 
				m_editingUserMapObjPos.layerPos, 
				m_editingUserMapObjPos.innerLayerObjectPos); //�����Ƿ�ѡ����ĳ���ڵ�
			
			if (selPointPosInLine != -1)
			{
				if (m_iEditingPointPosOnEditingLine == selPointPosInLine)
				{ //�����ε��ѡ�еĽڵ���ϴε��ѡ�е���ͬ, ��������Ϊ�û���ʼ׼���϶��ýڵ���
					m_bHasPressedDragStartPo = true;
					m_bHasDrawDragFirstPo = false;
					
					m_mouseDragFirstPo = M_POINT(point.x, point.y);
					SetOperation(DRAG_EDITING_OBJECT); //�ѵ�ǰView�Ĳ���״̬��Ϊ DRAG_EDITING_OBJECT

					m_pYimaEncCtrl->tmSetObjectDynamicObjectOrNot(m_editingUserMapObjPos.layerPos,
						m_editingUserMapObjPos.innerLayerObjectPos, true);

					m_pYimaEncCtrl->tmPushInStackUndoOperation(MOD_GEO_OBJ, m_editingUserMapObjPos.layerPos,
						m_editingUserMapObjPos.innerLayerObjectPos);
				}
				else
				{ //�����ε��ѡ�еĽڵ���ϴε��ѡ�еĲ�ͬ�������� m_iEditingPointPosOnEditingLine ��Ա����
					m_iEditingPointPosOnEditingLine = selPointPosInLine;
				}
			}
			else  
			{
				/* ���û��ѡ�нڵ�, ���ж�����Ļ�ϵ����������Ƿ���ѡ�е�������ķ�Χ��
				   ����������õ�ǰ��״̬DRAG_EDITING_OBJECT,��ʾ���Զ��������϶����� */
				BOOL bRetBeSelect;
				bool bResult = m_pYimaEncCtrl->SelectObjectByScrnPo(
					m_pYimaEncCtrl->GetMemMapCount() - 1, m_editingUserMapObjPos.layerPos, 
					m_editingUserMapObjPos.innerLayerObjectPos, point.x, point.y, &bRetBeSelect); 
				if (bResult && bRetBeSelect)
				{
					SetOperation(DRAG_EDITING_OBJECT); 
					m_ScrnOffset = GetCurMouseOffSetObjCenter(m_editingUserMapObjPos, M_POINT(point.x,point.y));
					m_pYimaEncCtrl->tmSetObjectDynamicObjectOrNot(m_editingUserMapObjPos.layerPos,
						m_editingUserMapObjPos.innerLayerObjectPos, true);
					m_pYimaEncCtrl->tmPushInStackUndoOperation(MOD_GEO_OBJ, m_editingUserMapObjPos.layerPos,
						m_editingUserMapObjPos.innerLayerObjectPos);
				}
				
				/* �����ĵ���ʾ��ק���� ������ĳ�����������򶼿���ק ��ע��������� Ӧ�ò�Ҳ��ʹ�����ֻ���
				//�ж��Ƿ�ѡ���˸��������ĵ�λ��
				//��ȡ��ǰѡ�е��������ĵ� add by tcf 2011.05.08
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
				{ //����ϴε��ѡ�еĵ�����ٴα����ѡ�У���������Ϊ�û�Ҫ��ʼ׼���϶��������
					m_bHasPressedDragStartPo = true;
					m_bHasDrawDragFirstPo = false; 
					m_ScrnOffset = GetCurMouseOffSetObjCenter(m_editingUserMapObjPos, M_POINT(point.x,point.y));
					m_mouseDragFirstPo = M_POINT(point.x, point.y);
					SetOperation(DRAG_EDITING_OBJECT); 
				}
			}
		} 
	}
	
	//�ж��ں��߱༭״̬�Ƿ�ѡ���˺�·��(WayPoint)����(Route)
	if (m_bOnRouteEditMode && !IsOnOperation(ADD_ROUTE))
	{  
		long selectWpID = SelectAWayPointByScrnPoint(point.x, point.y);
		if (selectWpID != 0)
		{
			if (m_nEditingWayPointID == selectWpID)
			{//���֮ǰҲ��ѡ���˸ú�·��, ˵�������û����϶��õ��λ��
				
				m_bHasPressedDragStartPo = true;
				m_bHasDrawDragFirstPo = false;
				
				m_mouseDragFirstPo = M_POINT(point.x, point.y);
				
				SetOperation(DRAG_EDITING_OBJECT); 
				return ;
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
	
	//������嵥��������������
	if (IsOnOperation(NO_OPERATION))
	{    
	   /********  ������ͼ����������� *********/
		SIZE panelBtnSize;
		panelBtnSize.cx = panelBtnSize.cy = 19;

		POINT leftBtnLeftTopPoint, rightBtnLeftTopPoint, upBtnLeftTopPoint, downBtnLeftTopPoint, zoomInBtnLeftTopPoint, zoomOutBtnLeftTopPoint; 

		/* ��ʾ: ���15��"����"��ť���Ƥ��ͼƬ���ϽǶ���ĺ�����, �����ڡ���Դ�༭���Ļ�ͼ����������궨λ�鿴 */
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
			
			m_nEditingLinePointCount ++;   
			
			if (m_nEditingLinePointCount > 1)
			{
				DrawEditingLineBeforeFinish();
			}
		} 
	}  
	
	////////////////// �����Զ������������ /////////////////////	
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
			//		m_pYimaEncCtrl->tmSetTargetForRedoOperation();	//����ʵ���Զ��庣ͼ�༭������(Redo)
			//		
			//		SetOperation(NO_OPERATION);
			//	}
			//}
			//else if (IsOnOperation(ADD_LINE) || IsOnOperation(ADD_FACE))
			//{  
			//	//�����ߡ���������ʱ�������Ļ��Appendһ�������󣬲�����������������ꣻ
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

			//		/* Ҫ��Ϊ��̬��꣬������ CYimaEncViewerView::DrawDynamicScreenMap() ������ DrawMapsInScreen() 
			//		   ������ʱ�Ų��ᱻ���������ͱ�����ͼһ�𻭳��� */
			//		m_pYimaEncCtrl->tmSetObjectDynamicObjectOrNot(m_iEditingUserMapLayerNum, editObjPos, true); 
			//	} 

			//	if (m_nEditingLinePointCount > 0)
			//	{//����༭����Ľڵ�����Ϊ��ʱ, �򽫵�ǰ�����¼���༭��������յ�
			//		m_editingLineGeoPoints[m_nEditingLinePointCount - 1] = M_POINT(geoPoX, geoPoY); 
			//	}
			//	else
			//	{//���֮ǰ��û�нڵ�, ����Ҫ�ڵ�ǰλ�ò�һ���ڵ�
			//		m_editingLineGeoPoints[0] = M_POINT(geoPoX, geoPoY);	//����һ�������ֵ��ֵ
			//		m_nEditingLinePointCount = 1;
			//	}

			//	//����2����Ҫ: ��굥����Ҫ����1���ڵ㣬����ڵ�����ž�Ҫ�� OnMouseMove() �б��϶�, �Ӷ�ʵ�ֶ�̬�ڵ�༭Ч��
			//	m_nEditingLinePointCount += 1; 
			//	m_editingLineGeoPoints[m_nEditingLinePointCount - 1] = m_editingLineGeoPoints[m_nEditingLinePointCount - 2];
			//	
			//	//��ǰ�༭�ڵ㼴��ҷ�ڵ�ӦΪ���1����
			//	m_iEditingPointPosOnEditingLine = m_nEditingLinePointCount - 1; 
			//	
			//	if (IsOnOperation(ADD_LINE) || IsOnOperation(ADD_FACE))	//�����ߡ������ʱ�Ĵ���
			//	{
			//		if (m_addingSpecialLineType == RECTANGLE_LN_TYPE)
			//		{//���ζ�����YIMAENC���Ǵ洢4�����, ��̬����ʱҪ�϶���3���ڵ�(����Ϊ2)���ǶԽ��϶� 
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
			//		if (m_addingSpecialLineType != NO_SPECIAL_TYPE)	//����������������������Ĳ���
			//		{  
			//			m_pYimaEncCtrl->tmSetObjectAsSpecialType(m_iEditingUserMapLayerNum,
			//				editObjPos, m_addingSpecialLineType);	//����������������
			//			
			//			/* ����� SECTOR_LN_TYPE��ARC_LN_TYPE��PIE_LN_TYPE��BOW_LN_TYPE �ȼ����������ö�̬����ʱ��Ĭ�ϽǶȲ��� */						
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
			//					true, innerRadiusByMeter, true, outRadiusByMeter, true, 0, true, 120); //�趨SPECIAL_LINE_TYPE ���͵������������ز���
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
			//		{//������������ڶ�̬�������֮ǰ�Ķ�̬��ʾ���
			//			if (IsOnOperation(ADD_LINE))
			//			{//������
			//				m_pYimaEncCtrl->tmSetLineObjectStyleRefLib(m_iEditingUserMapLayerNum, editObjPos, 
			//					1, false, 0, false, 0);	/* ������������������֮ǰ��̬��ʾ�ķ����ʽΪ��
			//											    �ο���ʽ��lineStyleId Ϊ1�ķ�� */
			//			}
			//			else
			//			{//
			//				m_pYimaEncCtrl->tmSetFaceObjectStyleRefLib(m_iEditingUserMapLayerNum, editObjPos, 
			//					2, true, RGB(0, 0, 255), true, 40, false, 0x000000); /* ������������������֮ǰ��̬��ʾ�ķ����ʽΪ��
			//											    �ο���ʽ��faceStyleId Ϊ1�ķ�� */
			//			}
			//		}
			//		
			//		m_editingUserMapObjPos = M_GEO_OBJ_POS(m_iEditingUserMapLayerNum, editObjPos); //��¼��ǰ�༭��� 
			//		SetOperation(ADD_LINE_OBJECT_MOUSEMOVING);	//���õ�ǰ״̬Ϊ "�������ʱ�Ķ�̬�ڵ�����״̬"

			//		SetCursor(LoadCursor(NULL, IDC_ARROW));	 
			//	} 
			//	
			//	m_pYimaEncCtrl->tmPushInStackUndoOperation(ADD_GEO_OBJ, m_iEditingUserMapLayerNum, 
			//		m_pYimaEncCtrl->tmGetLayerObjectCount(m_iEditingUserMapLayerNum) - 1);	//���༭���������Undo������ջ,������Undo����
			//	
			//	m_pYimaEncCtrl->tmSetTargetForRedoOperation();	//ΪUndo������������������Ϣ����ʵ��Redo���ܡ� 

			//	return;
			//}

			if (radar_info != NULL)
			{
				//SetCursor(LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_ARROW_RADAR)));
				//�����״����
				m_pYimaEncCtrl->tmAppendObjectInLayer(m_iEditingUserMapLayerNum, TYPE_POINT);
				radar_info->radInnerLayerPos = m_pYimaEncCtrl->tmGetLayerObjectCount(m_iEditingUserMapLayerNum) - 1;
				//���ø��״����������
				m_pYimaEncCtrl->tmSetPointObjectCoor(m_iEditingUserMapLayerNum, radar_info->radInnerLayerPos, geoPoX, geoPoY);
				//�����ʽ
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
			//�˳������״����״̬
			SetOperation(NO_OPERATION);
		}
		
	}
	
	///////////////////�����ӳ�////////////////////////////////
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

	BOOL bDrawNineNineBoxOrNot = false;//�Ƿ���ʾ�žŷ���
	m_pYimaEncCtrl->GetNineNineBoxCenterGeoPo(NULL,NULL,&bDrawNineNineBoxOrNot);
	if(bDrawNineNineBoxOrNot)
	{
		long retGeoPoX,retGeoPoY;						
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y,&retGeoPoX,&retGeoPoY);

		BSTR bstrNumber = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
		bool bNineNineNuber = m_pYimaEncCtrl->GetNineNineNumberByGeoPo(retGeoPoX,retGeoPoY,&bstrNumber);
		if(bNineNineNuber)
		{
			CString str = bstrNumber;
			::SysFreeString(bstrNumber);
			CString strMsg;
			strMsg.Format(_T("�žŷ���:%s"),str);
			AfxMessageBox(strMsg); //zcz Test
		}
	}
	if (IsOnOperation(NO_OPERATION))
	{ //�����ѯ
		   
		BSTR retSelObjPosStrings = ::SysAllocStringLen(NULL, 
			SEL_OBJ_MAX_COUNT * sizeof(MEM_GEO_OBJ_POS));   
	 
		int selObjCount = 
			m_pYimaEncCtrl->SelectObjectsByScrnPoint(&retSelObjPosStrings, 
			point.x, point.y); 
	
		/****** �����½ӿ� QueryInMapLayerByFieldCondtion: *******
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
			{//���ѡ�е����Զ��庣ͼ����, �����༭״̬
				//SetOperation(EDITING_GEO_OBJECT);
				SetOperation(NO_OPERATION);
				//RefreshScreen();
				CMenu menu;
				menu.LoadMenu(IDR_MENU_RADAR);			//�����״��Ҽ��˵�
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
		m_pYimaEncCtrl->HighlightOtherVessel(-1); //ȡ����ǰ���ܸ�����Ŀ�괬
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
				UserObject_SetAttributes(m_iEditingUserMapLayerNum, editObjPos);	 //����������ĺ�������: �������Լ���ʽѡ������
				
				m_pYimaEncCtrl->tmPushInStackUndoOperation(ADD_GEO_OBJ, m_iEditingUserMapLayerNum, 
					m_pYimaEncCtrl->tmGetLayerObjectCount(m_iEditingUserMapLayerNum) - 1); //���༭���������Undo������ջ,����ʵ��Undo����
				
				m_pYimaEncCtrl->tmSetTargetForRedoOperation();	//ΪUndo������������������Ϣ����ʵ��Redo���ܡ�
				
				m_iEditingPointPosOnEditingLine = -1;	//�������,�ָ�m_iEditingPointPosOnEditingLine��ֵΪ-1
				m_addingSpecialLineType = NO_SPECIAL_TYPE;	//�������,�ָ�m_addingSpecialLineTypeΪNO_SPECIAL_TYPE			
				m_pYimaEncCtrl->tmSetObjectDynamicObjectOrNot(m_iEditingUserMapLayerNum, editObjPos, false);//���Ӻ���, ����ȡ����Dynamic�Ķ�̬������ 		    
				if (IsOnOperation(ADD_COLOR_ATTENUATION_OBJ))
				{
					static CSetAttenTimes* setAttenTimes = NULL;
					if(setAttenTimes == NULL)
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
		if(IsOnOperation(MEASURE_AREA))
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
		- m_pYimaEncCtrl->GetDrawerScreenHeight() * MOVE_STEP_RATIO_TO_SCRN); 
	
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
		- m_pYimaEncCtrl->GetDrawerScreenWidth() * MOVE_STEP_RATIO_TO_SCRN,
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
	case 77: //�鿴�ڴ溣ͼ�����б���ݼ�'m'��
		{
			int memMapCount = m_pYimaEncCtrl->GetMemMapCount();
			CString strMemMapNameList = "Mem Maps: ";
			for (int memMapNum = 0; memMapNum < memMapCount; memMapNum ++)
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
			///////////////���´���Ϊ��ʹ�ð����������ѹ������ʱ������ֹ����ͼ�����ƶ�ʹ��//////////// 
		 
				static int nowOverViewLibMapPos = 0;
				m_pYimaEncCtrl->OverViewLibMap(nowOverViewLibMapPos);
				nowOverViewLibMapPos ++;
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
	
	HPEN hPen = (HPEN) CreatePen(PS_SOLID, 2, RGB_EBL_LINE); 
	HPEN hOldPen = (HPEN) SelectObject(hdc, hPen);  
	
	float deltx = endPoint.x - startPoint.x;
	float delty = endPoint.y - startPoint.y;
	int radius = sqrt(deltx * deltx + delty * delty);
	
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Ellipse(hdc, startPoint.x - radius, startPoint.y - radius,
		startPoint.x + radius, startPoint.y + radius );    
	
	RECT viewRect;
	GetClientRect(&viewRect);
	int scrnWidth = viewRect.right - viewRect.left;
	int scrnHeight = viewRect.bottom - viewRect.top;
	
	M_POINT eblLineEndPo;			
	if (deltx != 0)
	{
		eblLineEndPo.x = deltx > 0 ? scrnWidth : - scrnWidth; 
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
		eblLineEndPo.y = delty > 0 ? scrnHeight : - scrnHeight;
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
	
	/* ��̬��ʾ������� -- ������ʾ��ʾ��·�� */
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
	
 	//�Զ��庣ͼ�����϶��༭����ʵ�� -- MouseMove��������
	if (IsOnOperation(DRAG_EDITING_OBJECT) || IsOnOperation(ADD_LINE_OBJECT_MOUSEMOVING)) /* ע�⣺�����а��Զ��庣ͼ����༭�еĽڵ��϶�����·��༭�ĺ�·���϶�
											����ͳһ��Ϊ DRAG_EDITING_OBJECT ����״̬����ͳһ���϶���СԲȦ
											��ʵ�ִ��� */
	{ 
 		DrawDynamicScreenMap(m_mouseMoveCurrentPo);
 		return; 
	}
	
	//�����ӷ�λ��	
	CString strEblInfo = "";
	if (IsOnOperation(DRAW_EBL))
	{  
		static CPoint lastMouseMoveEndPo;
		static M_POINT lastEblLineEndPo;
		if (m_bHasPressedDragStartPo)
		{					
			HDC hdc = GetDC()->m_hDC;
			SetROP2( hdc, R2_XORPEN );
						    
			HPEN hPen = (HPEN) CreatePen( PS_SOLID, 1, RGB_EBL_LINE); 
			HPEN hOldPen = (HPEN) SelectObject( hdc, hPen );		
			
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
			SelectObject( hdc, hOldPen );
			DeleteObject( hPen );
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
			strEblInfo.Format("����: %.4f�����%.4f���ף�, �Ƕ�: %.3f", distByNatMile, distByNatMile*1852, bearing);
		} 
	}
	
	//����Ŵ�
    if (IsOnOperation(AREA_ZOOM_IN) || IsOnOperation(AREA_SELECT))
	{ 
		if (m_bHasPressedDragStartPo)
		{	 
			static CPoint lastMouseMoveRectEndPo;
			
			HDC hdc = GetDC()->m_hDC;
			SetROP2( hdc, R2_XORPEN );
			
			HPEN hPen = NULL;		 
			hPen = (HPEN) CreatePen( PS_SOLID, 2, RGB(0, 255, 0)); 
			
			HPEN hOldPen = (HPEN) SelectObject( hdc, hPen );
			
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
			SelectObject( hdc, hOldPen );
			DeleteObject( hPen );
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
			if(m_bRuntimeDragMap)
			{
				long offsetX = point.x - m_mouseDragFirstPo.x;
				long offsetY = point.y - m_mouseDragFirstPo.y;
				if(abs(offsetX) > 2 ||abs(offsetY) > 2)
				{ 
					m_pYimaEncCtrl->SetMapMoreOffset(offsetX ,offsetY);
					Invalidate();
					m_mouseDragFirstPo = M_POINT(point.x, point.y);
				}
			}
			else
			{

				HDC hdc = ::GetDC(m_hWnd); 
				m_pYimaEncCtrl->DrawDragingMap((long)hdc, point.x, point.y, m_mouseDragFirstPo.x, m_mouseDragFirstPo.y);  
				//DrawMapOperationPanel(hdc); //������ͼ�������			
				::ReleaseDC(m_hWnd, hdc); 
			}
			SetCursor(LoadCursor(NULL, IDC_HAND));  
		}
	}

	if (IsOnOperation(ADD_USER_LAYER_OBJ))
	{
		SetCursor(LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_ARROW_RADAR)));
	}
	

	//�����ӳ�
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
		m_pYimaEncCtrl->GetGeoPoFromScrnPo( point.x, point.y, (long*)&curGeoPo.x, (long*)&curGeoPo.y);   
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
	
	strCurPosition.Format("��Ļ���� x: %d, y: %d ;  �������� X:%s, Y:%s; ", point.x, point.y, strGeoCoorX, strGeoCoorY); 
	
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
		strCurScale.Format("������ 1 : %d", (int)curScale);
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
	if(!IsOnOperation(MEASURE_AREA))
	{
		m_icurEditPos = 0;
	}
	if (IsOnOperation(DRAG_EDITING_OBJECT))
	{ 
		if (m_nEditingWayPointID != 0)
		{//��������϶���·��
			M_POINT newWpPoint;
			m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, (long*)&newWpPoint.x, (long*)&newWpPoint.y);
			
			m_pYimaEncCtrl->SetWayPointCoor( m_nEditingWayPointID, newWpPoint.x, newWpPoint.y); 
			
			m_nEditingWayPointID = 0;
			m_pYimaEncCtrl->ClearHighLightPoints();
			Invalidate();
		} 
		
		//�Զ��庣ͼ�����϶��༭����ʵ�� -- ����Buttton Up��������		
		if (IsOnOperation(EDITING_GEO_OBJECT))
		{  
			if (m_iEditingPointPosOnEditingLine > -1)//˵�������϶��ߺ����ĳ���ڵ�
			{ 
				M_POINT newPoint;
				m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, 
					(long*)&newPoint.x, (long*)&newPoint.y); 
				
				if ( (nFlags & MK_CONTROL) == 0 && (nFlags & MK_SHIFT) == 0)
				{ //���Ctrl����Shift����û��ͬʱ���£���Ϊ�ƶ��ڵ����
					m_pYimaEncCtrl->tmMoveOnePointOfLineObject(m_editingUserMapObjPos.layerPos, 
						m_editingUserMapObjPos.innerLayerObjectPos, m_iEditingPointPosOnEditingLine, 
						newPoint.x, newPoint.y);
				}
				else
				{
					if ((nFlags & MK_CONTROL) != 0)
					{ //���Ctrl�����£���Ϊ���ӽڵ�����������ӵ� m_iEditingPointPosOnEditingLine �ڵ�ǰ��
						m_pYimaEncCtrl->tmAddOnePointToLineOrFaceObject(m_editingUserMapObjPos.layerPos, 
							m_editingUserMapObjPos.innerLayerObjectPos, m_iEditingPointPosOnEditingLine, 
							newPoint.x, newPoint.y);
					}
					else if ((nFlags & MK_SHIFT) != 0)
					{
						//���Shift�����£���Ϊ���ӽڵ�����������ӵ� m_iEditingPointPosOnEditingLine �ڵ����
						m_pYimaEncCtrl->tmAddOnePointToLineOrFaceObject(m_editingUserMapObjPos.layerPos, 
							m_editingUserMapObjPos.innerLayerObjectPos, m_iEditingPointPosOnEditingLine + 1, 
							newPoint.x, newPoint.y);
					}
				}
				
				m_iEditingPointPosOnEditingLine = -1; //���β�����ϣ�Ҫ��λ m_iEditingPointPosOnEditingLine Ϊ��Чֵ
			}
			else //�����϶������
			{
				M_POINT newPoint;
				m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, 
					(long*)&newPoint.x, (long*)&newPoint.y); 
				
				m_pYimaEncCtrl->tmSetPointObjectCoor(m_editingUserMapObjPos.layerPos, 
					m_editingUserMapObjPos.innerLayerObjectPos, newPoint.x, newPoint.y); //�ƶ������ 
			}

			m_pYimaEncCtrl->tmSetObjectDynamicObjectOrNot(m_editingUserMapObjPos.layerPos,
						m_editingUserMapObjPos.innerLayerObjectPos, false);
			
			m_pYimaEncCtrl->tmSetTargetForRedoOperation();	//ΪUndo������������������Ϣ����ʵ��Redo���ܡ� 
		}
		
		Invalidate(); 
		
		CancelOperation(DRAG_EDITING_OBJECT);	//���β�����ϣ�ȡ��DRAG_EDITING_OBJECT�������״̬	
		
		return;
	} 
  
	if (IsOnOperation(ADD_LINE_OBJECT_MOUSEMOVING) && m_iEditingPointPosOnEditingLine >= 0)	//�жϵ�ǰ״̬λ�ڡ��������ʱ�Ķ�̬�ڵ�����״̬��ʱ���Ĵ���
	{
		if (m_addingSpecialLineType == RECTANGLE_LN_TYPE || m_addingSpecialLineType == CIRCLE_LN_TYPE 
			|| m_addingSpecialLineType == ELLIPSE_LN_TYPE || m_addingSpecialLineType == ARC_LN_TYPE 
			|| m_addingSpecialLineType == PIE_LN_TYPE || m_addingSpecialLineType == BOW_LN_TYPE
			|| m_addingSpecialLineType == SECTOR_LN_TYPE)	//�ж�m_addingSpecialLineType��������������ϵ�һ�֣�
															//���ڵ���OnLButtonUpʱ�������������ӣ�����������񴰿�ѡ����ʾ���
		{ 
			int editObjPos = m_pYimaEncCtrl->tmGetLayerObjectCount(m_iEditingUserMapLayerNum) - 1;

			bool bSetTwoNearPointForObject = false;
			if (m_nEditingLinePointCount == 2)
			{
				M_POINT scrnStartPo;
				m_pYimaEncCtrl->GetScrnPoFromGeoPo(m_editingLineGeoPoints[0].x, m_editingLineGeoPoints[0].y, 
					(long*)&scrnStartPo.x, (long*)&scrnStartPo.y);
				if ((abs(point.x - scrnStartPo.x) + abs(point.y - scrnStartPo.y)) < 50)
				{//�����β�������"��Լ"С��50������, ����Ϊ"����"			
					bSetTwoNearPointForObject = true;					
					return;
				}
			}
			else if (m_nEditingLinePointCount == 1)
			{
				bSetTwoNearPointForObject = true;
			}

			if (bSetTwoNearPointForObject)
			{//�����β�������"����"���򷵻ز��������û���Ҫ�ڼ����϶���ֱ���ٵ�������ɹ��������				
				return;
			} 

			UserObject_SetAttributes(m_iEditingUserMapLayerNum, editObjPos); 

			m_pYimaEncCtrl->tmPushInStackUndoOperation(ADD_GEO_OBJ, m_iEditingUserMapLayerNum, 
				m_pYimaEncCtrl->tmGetLayerObjectCount(m_iEditingUserMapLayerNum) - 1);	//���༭���������Undo������ջ,������Undo����
			m_pYimaEncCtrl->tmSetTargetForRedoOperation();	//ΪUndo������������������Ϣ����ʵ��Redo���ܡ� 

			m_iEditingPointPosOnEditingLine = -1;	//�������,�ָ�m_iEditingPointPosOnEditingLine��ֵΪ-1  		
		    m_pYimaEncCtrl->tmSetObjectDynamicObjectOrNot(m_iEditingUserMapLayerNum, editObjPos, false);//���Ӻ���, ����ȡ����Dynamic�Ķ�̬������ 	 

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
			m_pYimaEncCtrl->SetMapMoreOffset( point.x - m_mouseDragFirstPo.x, point.y - m_mouseDragFirstPo.y);   
			
			m_bHasPressedDragStartPo = false;
			
			SetCursor(LoadCursor(NULL, IDC_ARROW)); 
			Invalidate();
			if(m_globalView != NULL)
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
		//ע�⣬Ҫ�ȵ��� CenterMap �ٵ��� RotateMapByScrnCenter
		m_pYimaEncCtrl->CenterMap(
			cntrRotaDlg.m_fCntrGeoPoX * fGeoCoorMultiFactor,
			cntrRotaDlg.m_fCntrGeoPoY * fGeoCoorMultiFactor);
		
		m_pYimaEncCtrl->RotateMapByScrnCenter(cntrRotaDlg.m_fRotateDeg);
		RefreshScreenMap();
	}
}

void CYimaEncViewerView::PrintTheMapInTheScreen(CDC* pDC, CPrintInfo* pInfo,CString mapTitle,LOGFONT* titleFont,
												int nmapTitleLeftOrMiddleOrRight,CString remarks,LOGFONT* remarkFont,int nremarksLeftOrMiddleOrRight,int nscalenLeftOrMiddleOrRight)//0������ ��1�����У�2������
{
	
	int viewScrnWidth = m_pYimaEncCtrl->GetDrawerScreenWidth();
	int viewScrnHeight = m_pYimaEncCtrl->GetDrawerScreenHeight();
	float viewScrnHeightToWidthRate = (float)viewScrnHeight / viewScrnWidth;  
	int paperScrnWidthByPixel = pDC->GetDeviceCaps(HORZRES); //�õ�ֽ�ſ���(��Ϊ��λ) ע�⣺�ڴ�ӡԤ��ʱʹ�� GetDeviceCaps(pDC->m_hDC, HORZRES) ����ȷ
	int paperScrnHeightByPixel = pDC->GetDeviceCaps(VERTRES); //�õ�ֽ�Ÿ߶�(��Ϊ��λ)
	float marginWidthPercent = 0.1; //����ҳ�߾�ٷֱ�
	float marginHeadHeightPercent = 0.1; //����ҳ�߾�ٷֱ�	
	
	int paperDrawerWidth = paperScrnWidthByPixel * (1 - 2 * marginWidthPercent); //�������ͼ������
	int paperDrawerHeight = paperDrawerWidth * viewScrnHeightToWidthRate; //���ֺ�Viewͬ���ĳ�����
	
	int paperDrawerStartX = paperScrnWidthByPixel * marginWidthPercent; //��ͼ����ʼ������
	int paperDrawerStartY = paperScrnHeightByPixel * marginHeadHeightPercent;  //��ͼ����ʼ������	
	
	int paperScrnWidthByMm = pDC->GetDeviceCaps(HORZSIZE); 
	double mmToPixelMapFactor = paperScrnWidthByPixel / paperScrnWidthByMm; //�õ���������׵�ת��ϵ��
	
	m_pYimaEncCtrl->RefreshDrawerForDirectDrawDC((long)pDC->m_hDC, 
		paperDrawerWidth, paperDrawerHeight, paperDrawerStartX, paperDrawerStartY, 
		false, mmToPixelMapFactor);//�Ѻ�ͼ������Ŀ�껷��hdc��Ϊ��ǰ��ӡ�豸����
	
	m_pYimaEncCtrl->DrawMapsInScreen((long)pDC->m_hDC); //�ػ溣ͼ��Ŀ���ӡ�豸  
	
	//���´�ӡ�ĵ�����	
	int ly = pDC->GetDeviceCaps(LOGPIXELSY);
	int cdcly = pDC->GetDeviceCaps(LOGPIXELSY);
	int cly = mmToPixelMapFactor * 25.4;
	
	int oldTitleFontHeight = titleFont->lfHeight;
	int oldRemarkFontHeight = remarkFont->lfHeight;
	
	CFont font;
	titleFont->lfHeight = abs(MulDiv(titleFont->lfHeight, pDC->GetDeviceCaps(LOGPIXELSY), 72));
	font.CreateFontIndirect(titleFont); 
	
	CFont *pOldFont = pDC->SelectObject(&font);    
	switch(nmapTitleLeftOrMiddleOrRight)
	{
	case 0: 
		pDC->SetTextAlign(TA_LEFT | TA_BOTTOM);
		pDC->TextOut(paperDrawerStartX-40, paperDrawerStartY - 40, mapTitle);
		break;
	case 1: 
		pDC->SetTextAlign(TA_CENTER | TA_BOTTOM);
		pDC->TextOut(paperDrawerStartX + paperDrawerWidth / 2-40, paperDrawerStartY - 40, mapTitle); 
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
		0, 0, 0, 0, "����");  		
	pOldFont = pDC->SelectObject(&font);
	
	CString strScaleInfo;
	int scale = m_pYimaEncCtrl->GetCurrentScale();
	strScaleInfo.Format("��ǰ������ 1 : %d", scale);
	switch(nscalenLeftOrMiddleOrRight)
	{
	case 0: 
		pDC->SetTextAlign(TA_LEFT | TA_TOP);
		pDC->TextOut(paperDrawerStartX-40, paperDrawerStartY + paperDrawerHeight + 40, strScaleInfo);
		break;
	case 1:
		pDC->SetTextAlign(TA_CENTER | TA_TOP);
		pDC->TextOut(paperDrawerStartX + paperDrawerWidth/2+40, paperDrawerStartY + paperDrawerHeight + 40, strScaleInfo);
		break;
	case 2:
		pDC->SetTextAlign(TA_RIGHT | TA_TOP);
		pDC->TextOut(paperDrawerStartX+ paperDrawerWidth+40, paperDrawerStartY + paperDrawerHeight + 40, strScaleInfo);
		break;
	default:
		pDC->SetTextAlign(TA_CENTER | TA_TOP);
		pDC->TextOut(paperDrawerStartX + paperDrawerWidth/2+40, paperDrawerStartY + paperDrawerHeight + 40, strScaleInfo);
		break;
		
	}
	pDC->SelectObject(pOldFont);
	font.DeleteObject();
	
	remarkFont->lfHeight = abs(MulDiv(remarkFont->lfHeight, pDC->GetDeviceCaps(LOGPIXELSY), 72));
	font.CreateFontIndirect(remarkFont);
	pOldFont = pDC->SelectObject(&font);
	switch(nremarksLeftOrMiddleOrRight)
	{
	case 0: 
		pDC->SetTextAlign(TA_LEFT | TA_TOP);
		pDC->TextOut(paperDrawerStartX-40, paperDrawerStartY + paperDrawerHeight+40, remarks);
		break;
	case 1:
		pDC->SetTextAlign(TA_CENTER | TA_TOP);
		pDC->TextOut(paperDrawerStartX + paperDrawerWidth/2+40, paperDrawerStartY + paperDrawerHeight+40, remarks);
		break;
	case 2:
		pDC->SetTextAlign(TA_RIGHT | TA_TOP);
		pDC->TextOut(paperDrawerStartX+ paperDrawerWidth+40, paperDrawerStartY + paperDrawerHeight+40, remarks);
		break;
	default:
		pDC->SetTextAlign(TA_CENTER | TA_BOTTOM);
		pDC->TextOut(paperDrawerStartX + paperDrawerWidth/2+40, paperDrawerStartY + paperDrawerHeight+40, remarks);
		break;
		
	}
	pDC->SelectObject(pOldFont);
	
	//���߿�
	CPen penDrawOutLine;
	penDrawOutLine.CreatePen(PS_SOLID, 1, RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject(&penDrawOutLine);
	POINT point[5];
	point[0].x=point[4].x=paperDrawerStartX;
	point[0].y=point[4].y=paperDrawerStartY;
	point[1].x=paperDrawerStartX+ paperDrawerWidth;
	point[1].y=paperDrawerStartY;
	point[2].x=paperDrawerStartX+ paperDrawerWidth;
	point[2].y=paperDrawerStartY+ paperDrawerHeight;
	point[3].x=paperDrawerStartX;
	point[3].y=paperDrawerStartY+ paperDrawerHeight;
	pDC->Polyline(point,5);
	
	penDrawOutLine.DeleteObject();
	CPen penDrawInLine;
	penDrawInLine.CreatePen(PS_SOLID, 10, RGB(0,0,0));
	pDC->SelectObject(&penDrawInLine);
	point[0].x=point[4].x=paperDrawerStartX-30;
	point[0].y=point[4].y=paperDrawerStartY-30;
	point[1].x=paperDrawerStartX+ paperDrawerWidth+30;
	point[1].y=paperDrawerStartY-30;
	point[2].x=paperDrawerStartX+ paperDrawerWidth+30;
	point[2].y=paperDrawerStartY+ paperDrawerHeight+30;
	point[3].x=paperDrawerStartX-30;
	point[3].y=paperDrawerStartY+ paperDrawerHeight+30;
	pDC->Polyline(point,5); 
	pDC->SelectObject(pOldPen);
	penDrawInLine.DeleteObject();
	
	//��ӡ��, �ָ���ͼ������ָ��ǰ��ͼ��Ļ
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
	
	//////////////////////////////// ��ӡ����1: ��ǰ��Ļ��ͼ��ӡ //////////////////////////////
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
	
	//////////////////////////////// ��ӡ����2: ��ǰ��Ļ��ͼ��ӡ /////////////////////////////// 
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	PrintTheMapInTheScreen(pDC, pInfo, pFrame->mapTitle,&(pFrame->titleFont),pFrame->nmapTitleLeftOrMiddleOrRight,
		pFrame->remarks,&(pFrame->remarkFont),pFrame->nremarksLeftOrMiddleOrRight,pFrame->nscaleLeftOrMiddleOrRight);
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
		AfxMessageBox("�ڽ��к�·�����ǰ����ȷ���ѽ��뺽�߱༭ģʽ.");
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
			AfxMessageBox("��ǰû���㹻�ĺ�·�������Ӻ��ߣ��������Ӻ�·��.");
		}
	}	
	else
	{
		AfxMessageBox("�ڽ��к��߲���ǰ����ȷ���ѽ��뺽�߱༭ģʽ.");
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
	m_pYimaEncCtrl->GetScrnPoFromGeoPo ( 
		m_editingLineGeoPoints[0].x , m_editingLineGeoPoints[0].y, 
		(long*)&currentPoint.x, (long*)&currentPoint.y ); 	
	
	for (int i = 0; i < m_nEditingLinePointCount - 1; i ++)
	{ 
		POINT nextPoint;
		
		m_pYimaEncCtrl->GetScrnPoFromGeoPo (
			m_editingLineGeoPoints[i + 1].x , m_editingLineGeoPoints[i + 1].y, 
			(long*)&nextPoint.x, (long*)&nextPoint.y );  
		
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
			if (AfxMessageBox("��ȷ��Ҫɾ���ú�·����?", MB_YESNO) == IDYES)
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
			if (AfxMessageBox("��ȷ��Ҫɾ���ú�����?", MB_YESNO) == IDYES)
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
		AfxMessageBox("����û��ѡ�к���!");
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
	if (m_curSelectedObjCount == 1) //���֮ǰ��ѡ��ĳ���Զ��庣ͼ���������ѡ��״̬
	{
		if (IsOnOperation(EDITING_GEO_OBJECT))
		{
			int layerPos = m_editingUserMapObjPos.layerPos;
			int innerLayerObjPos = m_editingUserMapObjPos.innerLayerObjectPos;
			
			if (AfxMessageBox("ȷ��Ҫɾ���������?", MB_YESNO) == IDYES)
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
	
	/*******  �����ƶ��Զ������ **********/
	bool bTestMovingUserMapObjects = false;
	if (bTestMovingUserMapObjects)
	{
		int testUserLayerPos = 1;
		for (int objPos = 0; objPos < m_pYimaEncCtrl->tmGetLayerObjectCount(testUserLayerPos); objPos ++) 
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
			nRadarFrameNumber ++;
			
			if (nRadarFrameNumber == 90000000)
			{
				nRadarFrameNumber = 0;
			} 
			Invalidate();
		}
		
		nTimerTick ++;
		
		if (nTimerTick == 90000000)
		{
			nTimerTick = 0;
		} 
		
		return; 
	}
	
	m_iMouseStoppedTimerCount ++; 
	
	/* ��̬��ʾ������� -- ������ʾ"���ͣ����ʾ"��·����Ϣ */
	if (m_iMouseStoppedTimerCount == TIMER_COUNT_TO_SHOW_TEXT_WHEN_MOUSE_STOP)
	{  //������ͣ���˵�ʱ��ﵽ TIMER_COUNT_TO_SHOW_TEXT_WHEN_MOUSE_STOP
		M_GEO_OBJ_POS selGeoObjPos;
		
		/* ʹ����Ļ�ĵ������ѡ��1����·��*/
		long selWayPointID = SelectAWayPointByScrnPoint(
			m_mouseMoveCurrentPo.x, m_mouseMoveCurrentPo.y);
		if (selWayPointID != 0)	 
		{
			SetOperation(SHOWING_HINT_TEXT);//�ѵ�ǰ����״̬����Ϊ������ʾ��̬��ʾ��,
			
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
			strcpy(lf.lfFaceName, "����");        // request a face name "Arial"
			HFONT hTextFont = (HFONT)CreateFontIndirect(&lf);  
			HFONT oldFont = (HFONT)SelectObject(hdc, hTextFont);
			
			MRECT textRect(0, 0, 0, 0);	 
			
			DrawText(hdc, strHintText, -1, (LPRECT)&textRect, DT_CALCRECT);
			
			textRect.leftTopPointX += m_mouseMoveCurrentPo.x;
			textRect.leftTopPointY += m_mouseMoveCurrentPo.y;
			textRect.rightDownPointX += m_mouseMoveCurrentPo.x;
			textRect.rightDownPointY += m_mouseMoveCurrentPo.y;
			
			CBrush brBackGound( RGB(180, 150, 150) );
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
			
			DrawText(hdc, strHintText, -1, (LPRECT)&textRect,  drawTextFormat);
			
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
			BOOL bFillColor =FALSE;
			long fillColor, iColorTransparent = 0;				
			long fontHeight, fontColor, textOffsetX, textOffsetY;
			BOOL bBold, bItalic;
			BSTR retText, retFontName;
			retText = ::SysAllocStringLen(NULL, 1024);
			retFontName = ::SysAllocStringLen(NULL, 255); 
			long layPos,innerLayerPos;
			m_pYimaEncCtrl->tmGetObjectPosFromID(i->layerId, i->objId, &layPos, &innerLayerPos);
			m_pYimaEncCtrl->tmGetFaceObjectStyle(layPos, innerLayerPos, &refLibFaceStyleID, 
				&bFillColor, &fillColor, &iColorTransparent, &retText, &retFontName, 
				&fontHeight, &fontColor, &bBold, &bItalic, &textOffsetX, &textOffsetY);
			::SysFreeString(retText);
			::SysFreeString(retFontName);

			if(bFillColor == FALSE)
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
				if (cells[0] == "VTSODU-LG")			//ODU��¼��Ϣ
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
			//������һ����ͷ
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

			/* ��̬��ʾ��ע�� --- ע�������ǰ������ʾ��̬��ʾ��, ����ˢ����Ļ, ����̬��ˢ���� */
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
 
/*** �˺����о�ΪһЩ�ӿڵ���ʾ������ ***/
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
		memset(chMsg,'\0', 255); 
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
		pFrame->RefreshNavigationDlgBar(chMsg); 
		CYimaEncViewerView* pView = (CYimaEncViewerView*)(pFrame->GetActiveView()); 
		if (!pView->IsOnOperation(HAND_ROAM) && !pView->IsOnOperation(SHOWING_HINT_TEXT))
		{
			pView->Invalidate(); 
		}
		if(strlen(chMsg) > 0)
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
		for (int i = 0; i < sndCount; i ++)
		{
			char str[1183 * 4];
			for (int n = 0; n < 1183 * 4; n ++)
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

	/***** ���Ա����Ƿ񿿽�ĳ���߶����� *****/
	bool bTestShipNearLine = false;
	if (bTestShipNearLine)
	{  	
		//׼���Ե�1���ڴ溣ͼ�ĵ�1�������߶�����д���
		MEM_GEO_OBJ_POS objPos(m_pYimaEncCtrl->GetMemMapCount() - 1, 0, 0);	//ȡ�Զ��庣ͼ����1��ͼ�㡢��1�����
		BSTR strObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS)); 
		memcpy(strObjPos, &objPos, sizeof(MEM_GEO_OBJ_POS)); //����BSTR���͵��������
		
		int linePoCount = m_pYimaEncCtrl->GetLineObjectCoorCount(&strObjPos);  
				//m_pYimaEncCtrl->GetFaceOutBndryCoorCount(&strObjPos);
		if (linePoCount > 0)
		{
			BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * linePoCount);	
			m_pYimaEncCtrl->GetLineObjectCoors(&strObjPos, &strLinePoints); //��ȡ����������� 
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

	////////////////// ����ˮ�����صĽӿ� Test Sounding Relevant methods /////////////////////
	bool bIfTestSoundingMethods = true;
	if (bIfTestSoundingMethods)
	{
		int sndLyrPos = m_pYimaEncCtrl->GetLayerPosByToken(-1, "SOUNDG");  
		//��ȡˮ���ͼ��������� -- ע�⣡����ͼ���һ����겢�Ǿ���һ����ˮ��㡱������һ����ˮ��㼯�ϡ���һ����ˮ��㼯�ϡ��������ˮ���
		int sndSetObjCount = m_pYimaEncCtrl->GetSoundingSetPointCount(m_pYimaEncCtrl->GetMemMapCount() - 2, sndLyrPos, 0);	
		for (int s = 0; s < sndSetObjCount; s ++)
		{
			float depth; 
			long sndX, sndY;
			
			m_pYimaEncCtrl->GetSoundingSetPointDepth(m_pYimaEncCtrl->GetMemMapCount() - 2, 
				sndLyrPos, 0, s, &depth, &sndX, &sndY);	  //��ѯ��ˮ��㼯����ꡱ��ĳ��ˮ�������ֵ������
			m_pYimaEncCtrl->SetSoundingSetPointDepth(m_pYimaEncCtrl->GetMemMapCount() - 2, 
				sndLyrPos, 0, s, 300); //���á�ˮ��㼯����ꡱ��ĳ��ˮ�������
			m_pYimaEncCtrl->GetSoundingSetPointDepth(m_pYimaEncCtrl->GetMemMapCount() - 2, 
				sndLyrPos, 0, s, &depth, &sndX, &sndY);	 //���Լ��һ����һ����û����ɹ�
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
			&left, &right, &up, &down, NULL, NULL, NULL, NULL, NULL, NULL, NULL); //�õ���ͼ�⺣ͼ��Ϣ 
		
		m_pYimaEncCtrl->SetCurrentScale(originalScale);
		
		m_pYimaEncCtrl->CenterMap( ((float)left + right) / 2, 
			((float)up + down) / 2);  						
		
			/* YIMAENC COMMENT: ע��!! ���ڵ�������ֵ���ܽӽ�4�ֽ�
			long �ͱ���������(�����ᳬ��)�����������ӷ���˷�ʱ��Ҫת��Ϊfloat��
		    �Է�ֹ�����*/						
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
		m_pYimaEncCtrl->SetOwnShipCurrentInfo( ownShpGeoPoX,
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
		
		//����ѡ��λ����Ļ����(200, 200)����һ��Other Vessel, �ö��󱻺�ɫ������ʾ
		SHIP_ID selShipID = m_pYimaEncCtrl->SelectOtherVesselByScrnPoint(200, 200);  
		
		//����ID��Pos֮���ת��
		SHIP_ID frstVesslID = m_pYimaEncCtrl->GetOtherVesselID(0);
		SHIP_ID scndVesslID = m_pYimaEncCtrl->GetOtherVesselID(1);  
		int nPosOfFrstID = m_pYimaEncCtrl->GetOtherVesselPosOfID(frstVesslID);
		int nPosOfScndID = m_pYimaEncCtrl->GetOtherVesselPosOfID(scndVesslID);
	} 
	
	/****** ���Զ�ȡ������������ ******/
	bool bIfTestReadLineObjectCoors = false;
	if (bIfTestReadLineObjectCoors)
	{
		//�õ�������ͼ�������Pos 
		CString strLayerToken = "DEPCNT"; 
		int depthLineLayerPos = m_pYimaEncCtrl->GetLayerPosByToken(-1, strLayerToken); //��ȡͼ������
		
		//׼���Ե�1���ڴ溣ͼ�ĵ�1�������߶�����д���
		MEM_GEO_OBJ_POS objPos(0, depthLineLayerPos, 0);	
		BSTR strObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS)); 
		memcpy(strObjPos, &objPos, sizeof(MEM_GEO_OBJ_POS));
		
		//�ȵõ��������
		int linePoCount = m_pYimaEncCtrl->GetLineObjectCoorCount(&strObjPos);   
		
		if (linePoCount > 0)
		{ 
			//�õ��������굽BSTR�ַ���
			BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * linePoCount);	
			m_pYimaEncCtrl->GetLineObjectCoors(&strObjPos, &strLinePoints);
			
			//����BSTR�ַ�����M_POINT��������д���
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
		
		//�ȼ�5�����е�4��
		BSTR bstrWpIDs = ::SysAllocStringLen(NULL, ROUTE_WAY_POINTS_MAX_COUNT * 2);	 		
		memcpy(bstrWpIDs, wpIDs, 5 * sizeof(int)); 
		long routeID = m_pYimaEncCtrl->AddRoute(&bstrWpIDs, "Test route", 4, true); 
		SysFreeString(bstrWpIDs); 
		//�ټӵ�5��, Ϊ�˲���AddRouteWayPoint����  
		
		long rtWpIDs[100];
		M_POINT points[100];
		
		bstrWpIDs = ::SysAllocStringLen(NULL, ROUTE_WAY_POINTS_MAX_COUNT * 2);	 
		int rtWpCount= m_pYimaEncCtrl->GetRouteWayPointsID(routeID, &bstrWpIDs); 
		memcpy(rtWpIDs, bstrWpIDs, 5 * sizeof(int));  
		SysFreeString(bstrWpIDs);  
		
		if (rtWpCount > 0)
		{
			for (int wpNum = 0; wpNum < rtWpCount; wpNum ++)
			{
				m_pYimaEncCtrl->GetWayPointCoor(rtWpIDs[wpNum], 
					(long*)&points[wpNum].x, 
					(long*)&points[wpNum].y);
			}
		}
		
		/* ������Ļ�����ѡ�������ĺ���*/
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
	
	/***** GetDistBetwTwoPoint �� GetGeoLenFromScrnLen ���÷���  ******/
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
	
	/***** ����Ϊ���� ���㺣ͼ�ӿ�(������"tm"��ͷ�ĺ���)���÷���  *****/ 
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
			AfxMessageBox("���λ�ڵ�ǰѡ���������!");
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
				AfxMessageBox("��ǰѡ�����������˫��������");
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
		for (int wpNum = 0; wpNum < wpCount; wpNum ++)
		{
			CString strWpText;
			long wpID = m_pYimaEncCtrl->GetWayPointIDFromPos(wpNum);
			strWpText.Format(_T("���:%d"), wpID);
			m_pYimaEncCtrl->SetWayPointShowText(wpNum, true, strWpText, true, 28, true, 0x0000ff0);
		}
	}

	/***** ���Ժ�·�㰲ȫ�� *****/
	bool bIsDemoToTestWayPointSafety = false; //�Ƿ�ִ�в��Ժ�·�㰲ȫ�Ե�demo����
	if (bIsDemoToTestWayPointSafety)
	{
		M_POINT wayPointGeoPo; //��·������
		
		//����ȥ���˫����λ����Ϊ��·���ʾ��λ��
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, (long *)&wayPointGeoPo.x, (long *)&wayPointGeoPo.y); 
		
		//���ж��з�ѡ��S57��ͼ����
		BSTR retSelObjPosStrings = ::SysAllocStringLen(NULL, 
			SEL_OBJ_MAX_COUNT * sizeof(MEM_GEO_OBJ_POS));   
		
		M_POINT wpScrnPoint;
		m_pYimaEncCtrl->GetScrnPoFromGeoPo(wayPointGeoPo.x, wayPointGeoPo.y, (long *)&wpScrnPoint.x, (long *)&wpScrnPoint.y); 
		
		//�жϺ�·���Ӧ�ĸ���Ļ��ѡ������Щ���
		int selObjCount = m_pYimaEncCtrl->SelectObjectsByScrnPoint(&retSelObjPosStrings, wpScrnPoint.x, wpScrnPoint.y);   
		
		if (selObjCount > 0)
		{  			
			MEM_GEO_OBJ_POS selectedObjPoses[SEL_OBJ_MAX_COUNT];
			memcpy(selectedObjPoses, retSelObjPosStrings, 
				selObjCount * sizeof(MEM_GEO_OBJ_POS));  
			 
			//�����ڷ��ص����������ж��Ƿ������ڲ������Ӻ�·���ͼ������
			for (int objNum = 0; objNum < selObjCount; objNum ++)
			{ 
				CString strMsg;
				int wrkLyrPos = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("WRECKS"));
				int obstLyrPos = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("OBSTRN"));
				int cautionLyrPos = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("PRCARE"));
				int depthAreaLyrPos = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("DEPARE"));
				int objLayerPos = selectedObjPoses[objNum].layerPos;
				if (objLayerPos == wrkLyrPos)
				{ 
					AfxMessageBox(_T("������ڿ�������!"));
				}
				else if (objLayerPos == obstLyrPos)
				{
					AfxMessageBox(_T("������ڿ����ϰ���!"));
				}
				else if (objLayerPos == cautionLyrPos)
				{
					AfxMessageBox(_T("���������˾�������!"));
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
						AfxMessageBox(_T("����������ǳˮ����!"));
					}
					::SysFreeString(retObjValString);   
					::SysFreeString(pBstrObjPos);   
				}
			}
		} 
		
		::SysFreeString(retSelObjPosStrings);   
		
		return;
	} 

	/***** �Զ���ͼ�����༭��ʾ *****/	
	bool bTestEditUserMapObject = false;	
	if (bTestEditUserMapObject)
	{
		//////////////// ������ʾ����1��Բ ////////////////
		M_POINT circlePoints[2]; //����Բ����, ��ָ��2����, ��1��ΪԲ�ģ���2��ΪԲ������һ��
		
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, 
			(long*)&circlePoints[0].x, (long*)&circlePoints[0].y);
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x + 100, point.y, 
			(long*)&circlePoints[1].x, (long*)&circlePoints[1].y);
		
		int layerPosOfAnyType = 0; //���������Զ��庣ͼ���õĵ�һ��ͼ��Ϊ����������ͼ�㡱���� ANYTYPE
		m_pYimaEncCtrl->tmAppendObjectInLayer(layerPosOfAnyType, TYPE_FACE); //����һ�������
		int addedObjInnerLayerPos = m_pYimaEncCtrl->tmGetLayerObjectCount(layerPosOfAnyType) - 1; //�ö�����Ǹ�ͼ�������һ������
		
		//���ö��������, ע������Ҫʹ��BSTR�ַ����������������
		BSTR strObjCoors = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 2); 
		memcpy(strObjCoors, circlePoints, sizeof(M_POINT) * 2); 
		m_pYimaEncCtrl->tmSetFaceObjectCoors(layerPosOfAnyType, 
			addedObjInnerLayerPos, 2, &strObjCoors); //��������
		::SysFreeString(strObjCoors); 
		
		m_pYimaEncCtrl->tmSetObjectAsSpecialType(layerPosOfAnyType, 
			addedObjInnerLayerPos, CIRCLE_LN_TYPE); //���ö�����Ϊ��һ��Բ��������������
		
		m_pYimaEncCtrl->tmSetFaceObjectStyleRefLib(layerPosOfAnyType, addedObjInnerLayerPos, 1, true, RGB(0, 0, 255), 
			true, 50, false, 0x000000); //���ö���������, ��3������"1"��ʾ�ο�ͼ��������еĵ�1�����;
		m_pYimaEncCtrl->tmSetLineObjectStyleRefLib(layerPosOfAnyType, addedObjInnerLayerPos, 1, true, RGB(255, 0, 0), 
			true, 3); //���ö���ı߽��� 
		////////////////////////////////////////////////////////////
		
		//////////////// ������ʾ����1����Բ ////////////////
		M_POINT ellipsePoints[2]; //������Բ����, ��ָ��2����, ��1��Ϊ�����������Ͻǵĵ�, ��2��Ϊ�����������½ǵĵ�
		
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, 
			(long*)&ellipsePoints[0].x, (long*)&ellipsePoints[0].y);
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x + 200, point.y + 100, 
			(long*)&ellipsePoints[1].x, (long*)&ellipsePoints[1].y);
		
		m_pYimaEncCtrl->tmAppendObjectInLayer(layerPosOfAnyType, TYPE_FACE); //����һ�������
		addedObjInnerLayerPos = m_pYimaEncCtrl->tmGetLayerObjectCount(layerPosOfAnyType) - 1; //�ö�����Ǹ�ͼ�������һ������
		
		//���ö��������, ע������Ҫʹ��BSTR�ַ����������������
		BSTR strObjCoors1 = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 2); 
		memcpy(strObjCoors1, ellipsePoints, sizeof(M_POINT) * 2); 
		m_pYimaEncCtrl->tmSetFaceObjectCoors(layerPosOfAnyType, 
			addedObjInnerLayerPos, 2, &strObjCoors1); //��������
		::SysFreeString(strObjCoors1); 
		
		m_pYimaEncCtrl->tmSetObjectAsSpecialType(layerPosOfAnyType, 
			addedObjInnerLayerPos, ELLIPSE_LN_TYPE); //���ö�����Ϊ��һ��Բ��������������
		
		m_pYimaEncCtrl->tmSetFaceObjectStyleRefLib(layerPosOfAnyType, addedObjInnerLayerPos, 1, true, RGB(0, 255, 0), 
			true, 50, false, 0x000000); //���ö���������, ��3������"1"��ʾ�ο�ͼ��������еĵ�1�����;
		m_pYimaEncCtrl->tmSetLineObjectStyleRefLib(layerPosOfAnyType, addedObjInnerLayerPos, 1, true, RGB(0, 0, 0), 
			true, 3); //���ö���ı߽��� 
		////////////////////////////////////////////////////////////
		
		//////////////// ������ʾ����1������� ////////////////
		M_POINT polygonPoints[3]; //���Ӷ���ζ���
		
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y, 
			(long*)&polygonPoints[0].x, (long*)&polygonPoints[0].y);
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x + 200, point.y + 100, 
			(long*)&polygonPoints[1].x, (long*)&polygonPoints[1].y); 
		m_pYimaEncCtrl->GetGeoPoFromScrnPo(point.x, point.y + 200, 
			(long*)&polygonPoints[2].x, (long*)&polygonPoints[2].y);
		
		m_pYimaEncCtrl->tmAppendObjectInLayer(layerPosOfAnyType, TYPE_FACE); //����һ�������
		addedObjInnerLayerPos = m_pYimaEncCtrl->tmGetLayerObjectCount(layerPosOfAnyType) - 1; //�ö�����Ǹ�ͼ�������һ������
		
		//���ö��������, ע������Ҫʹ��BSTR�ַ����������������
		BSTR strObjCoors2 = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 3); 
		memcpy(strObjCoors2, polygonPoints, sizeof(M_POINT) * 3); 
		m_pYimaEncCtrl->tmSetFaceObjectCoors(layerPosOfAnyType, 
			addedObjInnerLayerPos, 3, &strObjCoors2); //��������
		::SysFreeString(strObjCoors2);  
		
		m_pYimaEncCtrl->tmSetFaceObjectStyleRefLib(layerPosOfAnyType, addedObjInnerLayerPos, 2, true, RGB(0, 255, 0), 
			true, 51, false, 0x000000); //���ö���������, ��3������"1"��ʾ�ο�ͼ��������еĵ�1�����;
		m_pYimaEncCtrl->tmSetLineObjectStyleRefLib(layerPosOfAnyType, addedObjInnerLayerPos, 3, true, RGB(255, 0, 0), 
			true, 3); //���ö���ı߽��� 
		////////////////////////////////////////////////////////////

		///////  ������ʾ�ж�ĳ����Ļ������Ƿ�λ��ĳ���溣ͼ����� ////////////
		bool bPoint1InMe = m_pYimaEncCtrl->IsPointInFaceGeoObject(point.x, point.y, m_pYimaEncCtrl->GetMemMapCount() - 1, 
				layerPosOfAnyType, addedObjInnerLayerPos, false);
		bool bPoint2InMe = m_pYimaEncCtrl->IsPointInFaceGeoObject(point.x + 120, point.y, m_pYimaEncCtrl->GetMemMapCount() - 1, 
				layerPosOfAnyType, addedObjInnerLayerPos, false);
	} 
	////////////////////////////////////////////////////////////////////////////////////
	    
	/***** �����һЩYIMAENC�Ľӿڽ��е��ò��� *****/
	bool bTestSomeAPIs = false;
	if (bTestSomeAPIs)
	{
		m_pYimaEncCtrl->SetRouteShowOrNot(true, 0, true, true, RGB(255, 0, 0)); 

		/* ��ɫ3����RGB�ֱ��Ӧ 0xRRGGBB ������3���ֽ�, �������ʾ��ɫ */
		//	m_pYimaEncCtrl->SetWayPointCircle(20, 100, 0xFF0000); 
		m_pYimaEncCtrl->SetWayPointName(20, "����һ����·��");
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
		for (int lyrNum = 0; lyrNum < lyrCount; lyrNum ++)
		{
			int lyrObjCount = m_pYimaEncCtrl->tmGetLayerObjectCount(lyrNum);
			for (int objNum = 0; objNum < lyrObjCount; objNum ++)
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
	if(m_bAnimationScale)
	{ 
		m_WheelStartTime = GetCurTimeMillis();
		RECT wndRect; 
		GetWindowRect(&wndRect);
		int scrnWidth = wndRect.right - wndRect.left;
		int scrnHeight = wndRect.bottom - wndRect.top;
 
		m_scaleMouseScrnPo = M_POINT(pt.x - wndRect.left, pt.y - wndRect.top);  
		float fWheelNum = zDelta / 120;  //���ֹ����ĸ������ϻ������»���
		float fN = 0.3 * fWheelNum; //�������Ų���
		if(bMouseWheelState == false)
		{
			float fScaleSize = 1.1; //��ʼ���Ų���
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

			/* ����OnMouseWheel()��������λ�ò���pt������������������Ļ���Ͻ�ԭ������꣬
				���Ǳ����ڵ�ԭ�����꣬��������Ҫת��һ�� */
			M_POINT cursorPoint(pt.x - wndRect.left, pt.y - wndRect.top); 

			//���б�׼����ǰ�Ȼ�ȡ���λ�ö�Ӧ�ĵ�������
			M_POINT mouseGeoPo;
			m_pYimaEncCtrl->GetGeoPoFromScrnPo(cursorPoint.x, cursorPoint.y, (long*)&mouseGeoPo.x, (long*)&mouseGeoPo.y);
			
			//�Ƚ��б�׼����
			if (zDelta > 0)
			{
				m_pYimaEncCtrl->SetCurrentScale(m_pYimaEncCtrl->GetCurrentScale() / 1.5);
			}
			else
			{
				m_pYimaEncCtrl->SetCurrentScale(m_pYimaEncCtrl->GetCurrentScale() * 1.5);
			}
			
			M_POINT afterStdZoomScrnPo; //��׼����ģʽ��������Ļ����
			m_pYimaEncCtrl->GetScrnPoFromGeoPo(mouseGeoPo.x, mouseGeoPo.y, 
				(long*)&afterStdZoomScrnPo.x, (long*)&afterStdZoomScrnPo.y);
			
			long deltX, deltY; //��׼���ź�������Ļ����ͺ��������ģʽ�����Ļ�����
			deltX = afterStdZoomScrnPo.x - cursorPoint.x;
			deltY = afterStdZoomScrnPo.y - cursorPoint.y;
			
			//���������ģʽ�µ���Ļ���ĵ��ڱ�׼ģʽ���ź����Ļ����
			M_POINT scrnCenterAfterStdZoom = M_POINT(scrnWidth / 2 + deltX, scrnHeight / 2 + deltY);

			//���������ģʽ�µ���Ļ���ĵ��������
			M_POINT geoPoOfMouseZoomScrnCenter;
			m_pYimaEncCtrl->GetGeoPoFromScrnPo(scrnCenterAfterStdZoom.x, scrnCenterAfterStdZoom.y, 
				(long*)&geoPoOfMouseZoomScrnCenter.x, (long*)&geoPoOfMouseZoomScrnCenter.y);
				
			//��������õ���Ļ���ĵ����������ж�λ
			m_pYimaEncCtrl->CenterMap(geoPoOfMouseZoomScrnCenter.x, geoPoOfMouseZoomScrnCenter.y); 
		}
		else
		{
			//�Ƚ��б�׼����
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
		if(m_globalView != NULL)
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

/* ʾ�����߼��
	Ŀ�꣺
	 1. ���ϵͳ�е�1�����ߵĵ�1�����߶�(Leg)�Ƿ�Խ4�ְ�ȫ������: �ϰ������������������ȫ������;
	 2. Ҫ������ּ��ͼ��(MapLib)������S57��ͼͼ��������������Ϣ;
	 3. ��⵽����, ������ʾ��������ʾ�����;
	���裺
	    1. ж���ڴ溣ͼ�����е�����ͼ��; 
		2. Ȼ���жϺ��߶�ѡ����Щͼ����
		3. �����߶�ѡ�е�ͼ�����ε����ڴ�, 1��1������һ���;
		4. ��ĳһ��ͼ�ļ����̷�װ�ں��� DetectRouteLegSafteyInMemMap0() ��;
		5. �����4�����غ��߶ηǷ���ԽĿ��1�����оٵ�4�����, ����������; */ 
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
	//��ȡ���ߵĺ�����������
	m_pYimaEncCtrl->GetRouteWayPointsCoor(frstRouteID, &bstrWpPoints);
	memcpy(wayPoints, bstrWpPoints, sizeof(M_POINT) * rtWpCount); 
 
#define MAX_SEL_LIB_MAP_COUNT 255
	int selLibMapPoses[MAX_SEL_LIB_MAP_COUNT]; //�����߶�ѡ�е�ͼ���б�
	float selLibMapOrgScale[MAX_SEL_LIB_MAP_COUNT];
	int selLibMapCount = 0; 
  
	//����ģ����Ե�1�ں��߶�, ��ȡ wayPoints[0]��wayPoints[1]
	M_POINT legLineStartPo = wayPoints[0]; 
	M_POINT legLineEndPo = wayPoints[1];

	int libMapCount = m_pYimaEncCtrl->GetLibMapCount();
	float minOrgScaleForMapContainLeg = 0; //��ȫ�������߶ε�����ͼ������Сԭʼ������
	for (int mapNum = 0; mapNum < libMapCount; mapNum ++)
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
		{ //˵�����߶����ͼ���������ཻ

			if (legRect.leftTopPointX >= left && legRect.rightDownPointX < right &&
				legRect.rightDownPointY >= down && legRect.leftTopPointY < up)
			{//˵�����߶αر���ͼ��������ȫ����
				if (minOrgScaleForMapContainLeg == 0 || 
					(minOrgScaleForMapContainLeg != 0 && orgScale < minOrgScaleForMapContainLeg))
				{
					/* �����ͼ���������߶�����ԭʼ�����߱�֮ǰ
					   ��¼�� minOrgScaleForMapContainLeg ��С,
					    ����� minOrgScaleForMapContainLeg */
					minOrgScaleForMapContainLeg = orgScale;
				}

				bCross = true; //��ȫ����Ҳ������Խ"Cross"
			}
			else
			{//���������ȫ����, ���ж��Ƿ��ཻ(��Խ) 
				m_pYimaEncCtrl->IsLineSectionCrossPolygon(legLineStartPo.x, legLineStartPo.y, legLineEndPo.x, 
					legLineEndPo.y, &bstrMapRectPoints, 4, true, &bCross);  
			}
			
			if (bCross)
			{//�����Խ, ��Ѹ�ͼ������ selLibMapPoses "ѡ��ͼ��"������ȥ
				selLibMapPoses[selLibMapCount] = mapNum;
				selLibMapOrgScale[selLibMapCount] = orgScale;
				selLibMapCount ++;
			}
		}

		SysFreeString(bstrMapRectPoints); 
	}  

	int detectLibMapPoses[MAX_SEL_LIB_MAP_COUNT];
	int detectLibMapCount = 0;
	for (int selLibMapNum = 0; selLibMapNum < selLibMapCount; selLibMapNum ++)
	{
		if (!(minOrgScaleForMapContainLeg > 0 && selLibMapOrgScale[selLibMapNum] > minOrgScaleForMapContainLeg))
		{/* ���minOrgScaleForMapContainLeg��Ϊ0, 
		    ��ֻ�ж�"ȫ����"���߶���С�����ߵ��Ǹ�ͼ �Լ� ������С�����ߵ�"δȫ����"���߶ε�ͼ,
			������С������ͼ�����ж� */
			detectLibMapPoses[detectLibMapCount] = selLibMapPoses[selLibMapNum];
			detectLibMapCount ++;
		}
	} 

	for (int detectLibMapNum = 0; detectLibMapNum < detectLibMapCount; detectLibMapNum ++)
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
 
				//�����ȡ���ľ�γ�ȷ�Χ
				long left, right, top, down;
				m_pYimaEncCtrl->GetObjectGeoExtent(&bstrObjPos, &left, &right, &top, &down);  

				//����׼����λ�����������
				m_pYimaEncCtrl->SetIfOnAutoLoadMapMode(true); //���л����Զ��ڴ��ͼģʽ����ΪҪ׼����ʾ��ͼ��
				m_pYimaEncCtrl->OverViewGeoRect(left, down, right, top); //��ʾ֮ǰ����λ��ͼ��Ļ��������Ը��������

				/* ���ڴ�OverViewGeoRect()֮�����Զ��ڴ��ͼ���Ƶ��������ڴ溣ͼ������λ�÷����˱仯,
				   �����ڸ��������ǰ��Ҫ�ҵ���ͼ�����ڴ溣ͼ�����е���λ��	*/
				int highlightObjMemMapPos = m_pYimaEncCtrl->GetLibMapPosInMem(dtctLibMapPos); 

				MEM_GEO_OBJ_POS highlightObjPos(highlightObjMemMapPos, 
					detectRetCrossObjPoses[0].layerPos, 
					detectRetCrossObjPoses[0].innerLayerObjectPos);

				SetHighlightObjects(&highlightObjPos, 1);  //������ʾʱҪ���������
				
				RefreshScreenMap(); //ˢ����ʾ��ͼ

				SysFreeString(bstrObjPos);
				break;
			}
		}  
	} 

	SysFreeString(bstrWpPoints);
	delete[] wayPoints;

	m_pYimaEncCtrl->SetIfOnAutoLoadMapMode(true);  
}

/* ������: ���� SelectGeoObjectByLineSection() �ӿڱ���������Ȥͼ���ÿһ����� */
int CYimaEncViewerView::DetectRouteLegSafteyInMemMap(int memMapPos, M_POINT legStartGeoPo, M_POINT legEndGeoPo,
								M_GEO_OBJ_POS* retCrossObjPoses)
{
	int retCrossObjCount = 0;

	int detectLayerList[100];//Ҫ�жϺ����Ƿ�Խ��ЩS57ͼ��

	/* ������ʾ����4��ͼ�㣬������ѡ�����ͼ�������. */
	detectLayerList[0] = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("OBSTRN")); //�ϰ���
	detectLayerList[1] = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("WRECKS")); //����
	detectLayerList[2] = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("PRCARE")); //������ 
	detectLayerList[3] = m_pYimaEncCtrl->GetLayerPosByToken(-1, _T("DEPCNT")); //������

	// ע�⣬���������ֵȡΪ2����Ϊ, S57ObjectClasses�ļ���DEPCNT�������б��еĵ�3��λ��
    #define ATTR_POS_OF_SAFEDEPTH_TAG_IN_LYR_DEPCNT 2 
	
	for (int lyrNum = 0; lyrNum < 4; lyrNum ++)
	{
		int detectLayerPos = detectLayerList[lyrNum];
		int detectLyrObjCount = m_pYimaEncCtrl->GetLayerObjectCountOfMap(memMapPos, detectLayerPos);

		//��Щͼ��������һ�ж�
		for (int objNum = 0; objNum < detectLyrObjCount; objNum ++)
		{
			if (lyrNum == 3)//������жϰ�ȫ�ߵ�ͼ��
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
				{//BESAFE���Բ�Ϊtrueʱ��ʾ�õ����߲���"��ȫ������",�����ж�
					continue;
				} 
			} 
			
			BOOL bSelect = false;
			m_pYimaEncCtrl->SelectGeoObjectByLineSection(memMapPos, detectLayerPos, objNum, 
				legStartGeoPo.x, legStartGeoPo.y, legEndGeoPo.x, legEndGeoPo.y, 
				100, &bSelect); /* �÷����ж�ĳ������Ƿ��߶�ѡ��:
								1. ������ѡ���ж�������"�õ�����߶εľ���dС�ڵ�����2������100��";
								2. ������ж������Ǹ���������߶��Ƿ�"�ཻ";
								3. ������ж������Ǹ������: a.�Ƿ����߶�"�ཻ"; b.�����߶�; */								

			if (bSelect && retCrossObjCount < MAX_RET_CROSS_OBJ_COUNT)
			{
				CString strMsg;
				strMsg.Format(_T("wrk sel layer pos %d, obj pos %d"), detectLayerPos, objNum); 
				//AfxMessageBox(strMsg);

				retCrossObjPoses[retCrossObjCount] = M_GEO_OBJ_POS(detectLayerPos, objNum);
				retCrossObjCount ++;
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
 
//��������������Լ���ʽѡ�����ã��ɶ�һ��������ظ���������
bool CYimaEncViewerView::UserObject_SetAttributes(int layerPos, int innerLayerPos)
{ 
	SetCursor(LoadCursor(NULL, IDC_ARROW)); 
	
	//����"������������ֵ"����,���������ֵ���б༭
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
				
				/* ��������ע, ע���˽ӿڿ����������õ������������
					   �������ŷ�񡢱�ע���, ������ǰ���
					   tmSetPointObjectStyleRefLib() �ӿڵ����Ѿ������˷��ŷ��, ����ֻ��ʹ����"��ע"���ù���  */
				m_pYimaEncCtrl->tmSetPointObjectStyle(layerPos, innerLayerPos, 
					0, false, 0, 0, true, libPointStylesViewDlg.m_strText, 
					libPointStylesViewDlg.m_strTextFontName, 
					libPointStylesViewDlg.m_nFontSize,
					RGB(libPointStylesViewDlg.m_nFontColorR, libPointStylesViewDlg.m_nFontColorG,
					libPointStylesViewDlg.m_nFontColorB), false, false, 0, 0, libPointStylesViewDlg.m_iTextOffsetX, 
					libPointStylesViewDlg.m_iTextOffsetY, 0); 
				m_pYimaEncCtrl->tmSetObjectTextRotate(layerPos, innerLayerPos, libPointStylesViewDlg.m_fTextRotatrAngle);
					/*
					int iUserMapPos = m_pYimaEncCtrl->GetMemMapCount() - 1;//�Զ���ͼ�����ڵ�ͼ�����ڴ������
					int curLayerPos = 0;//���ĸ�ͼ����в�ѯ��������0��ʾ�Զ���ĵ�һ��ͼ�㣬����Layers�������ļ�����ġ��ۺ�ͼ�㡱
					int iFieldPos = 0;//��ѯ������һ������,���Ҫ�������ļ���Layers���鿴�����ۺ�ͼ�㡱��������������0
					int iCondtionType = 6;//��ѯ��������:�������ͣ�0=���ڣ�1=�����ڣ�2=���ڣ�3=���ڵ��ڣ�4=С�ڣ�5=С�ڵ��ڣ����ַ�����6=������
					CString strCondtion = "����";//��ѯ����
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
				//����"ѡ���������"����,ѡ���������
				CLibFaceStylesViewDlg libFaceStylesViewDlg;
				libFaceStylesViewDlg.m_strCaption = "ѡ���������";
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
					/* ��������ע, ע���˽ӿڿ������������������������
					   �������ɫ����͸���ȡ�ѭ�������ŷ�񡢱�ע���, ������ǰ���
					   tmSetFaceObjectStyleRefLib() �ӿڵ����Ѿ����������ȷ��, ����ֻ��ʹ����"��ע"���ù���  */
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
			
			//����"ѡ�����ͷ��"����,ѡ�����ͷ��
			CLibLineStylesViewDlg libLineStylesViewDlg; 
			bool bLine = false;
			if (geoType == TYPE_FACE)
			{
				libLineStylesViewDlg.m_strCaption = "ѡ����߽����ͷ��";
			}
			else
			{
				libLineStylesViewDlg.m_strCaption = "ѡ�����ͷ��";
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
				/* ����������ע, ע���˽ӿڿ������������������������
				������������(ʵ�߻����߼�����ȡ���ɫ)��ѭ�����ŷ�񡢱�ע���, ������ǰ���
					tmSetLineObjectStyleRefLib() �ӿڵ����Ѿ����������͵ȷ��, ����ֻ��ʹ����"��ע"���ù���  */	 
	
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

	if (IsOnOperation(DRAG_EDITING_OBJECT) || IsOnOperation(ADD_LINE_OBJECT_MOUSEMOVING)) /* ע�⣺�����а��Զ��庣ͼ����༭�еĽڵ��϶�����·��༭�ĺ�·���϶�
											����ͳһ��Ϊ DRAG_EDITING_OBJECT ����״̬����ͳһ���϶���СԲȦ
											��ʵ�ִ��� */
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
	if (m_curSelectedObjCount == 1) //���֮ǰ��ѡ��ĳ���Զ��庣ͼ���������ѡ��״̬
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
	if (m_curSelectedObjCount == 1) //���֮ǰ��ѡ��ĳ���Զ��庣ͼ���������ѡ��״̬
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

#pragma region ����/�ӳ�

void CYimaEncViewerView::OnHollowMapEffect()
{
	// TODO: �ڴ�����������������
	m_pYimaEncCtrl->CancelMapEffect();
	SetOperation(NO_OPERATION);
	SetOperation(HOLLOW_MAP);	   
	Invalidate();				
}

void CYimaEncViewerView::OnDelayMapEffect()
{
	// TODO: �ڴ�����������������  	
	m_pYimaEncCtrl->CancelMapEffect();
	SetOperation(NO_OPERATION);
	SetOperation(DELAY_MAP);			
	Invalidate();
}

void CYimaEncViewerView::OnCancelMapEffect()
{
	// TODO: �ڴ�����������������
	m_pYimaEncCtrl->CancelMapEffect();
	Invalidate();
}	    
#pragma endregion 

//�����С
void CYimaEncViewerView::OnObjZoomOut()
{
	if (m_curSelectedObjCount == 1) //���֮ǰ��ѡ��ĳ���Զ��庣ͼ���������ѡ��״̬
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

//���Ŵ�
void CYimaEncViewerView::OnObjZoomIn()
{
 	if (m_curSelectedObjCount == 1) //���֮ǰ��ѡ��ĳ���Զ��庣ͼ���������ѡ��״̬
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
	MEM_GEO_OBJ_POS objectPos(m_pYimaEncCtrl->GetMemMapCount()-1, ObjPos.layerPos, ObjPos.innerLayerObjectPos);
	M_POINT objCenterGeoPo(0,0);
	BSTR strObjPos = ::SysAllocStringByteLen(NULL, sizeof(MEM_GEO_OBJ_POS));
	memcpy(strObjPos, &objectPos, sizeof(MEM_GEO_OBJ_POS));
	long retLeft, retRight, retTop, retButtom;
	
	m_pYimaEncCtrl->GetObjectGeoExtent(&strObjPos, &retLeft, &retRight, &retTop, &retButtom);
	objCenterGeoPo.x  = (float)retLeft/2 + (float)retRight / 2;
	objCenterGeoPo.y  = (float)(retTop + retButtom) / 2;
	M_POINT objCenterScrnPo;
	m_pYimaEncCtrl->GetScrnPoFromGeoPo(objCenterGeoPo.x, objCenterGeoPo.y, (long*)&objCenterScrnPo.x,(long*)&objCenterScrnPo.y);
	
	M_POINT scrnOffset = curMouseScrnPo - objCenterScrnPo;
	::SysFreeString(strObjPos); 
	return scrnOffset; 
}


//�´���
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

//ӥ����ͼ
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
	// TODO: �ڴ�����������������
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
		AfxMessageBox("�����˳���������");
	}
}

void CYimaEncViewerView::OnClosedLineWarn()
{
	if(m_ClosedLineTestObj.layerPos == -1)
	{
		m_pYimaEncCtrl->tmAppendLayer(ALL_LINE);//����һ�������͵�ͼ��,��һ������������ļ�����д�ã�
		int iUserLayerPos = m_pYimaEncCtrl->tmGetLayerCount() - 1;//�õ�ͼ�������
		m_pYimaEncCtrl->tmSetLayerName(iUserLayerPos, "TestClosedLineLayer"); 
		bool bAddResult = m_pYimaEncCtrl->tmAppendObjectInLayer(iUserLayerPos,TYPE_LINE);
		if(bAddResult)
		{
			int linePos = m_pYimaEncCtrl->tmGetLayerObjectCount(iUserLayerPos) - 1;
			M_GEO_OBJ_POS lineGeoPos = M_GEO_OBJ_POS(iUserLayerPos,linePos);
 
			M_POINT geoPoints[3];
			geoPoints[0] = M_POINT(1223503800, 333828243);//pEncMapMan->GetGeoPoFromScrnPo(M_POINT(50, 20));
			geoPoints[1] = M_POINT(1223632582, 333763436);//pEncMapMan->GetGeoPoFromScrnPo(M_POINT(150, 80));
			geoPoints[2] = M_POINT(1223825684, 333785037);//pEncMapMan->GetGeoPoFromScrnPo(M_POINT(300, 60)); 
			BSTR bstrGeoPoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 3);
			memcpy(bstrGeoPoints, geoPoints, sizeof(M_POINT) *3);
			m_pYimaEncCtrl->tmSetLineObjectCoors(iUserLayerPos, linePos, 3, &bstrGeoPoints);//���õ��������
			m_pYimaEncCtrl->tmSetLineObjectStyle(iUserLayerPos, linePos, true, true, 0, 0, 2, RGB(0, 0, 255), 0, 0, "���ߡ����߱�������", "����", 14, RGB(255,0,0), false, false, 0, 50, false);
			m_ClosedLineTestObj = lineGeoPos;
			::SysFreeString(bstrGeoPoints);
		}
	}
	else
	{					 
		AfxMessageBox("���߱����������������");
	}
	m_pYimaEncCtrl->CenterMap(1223503800, 333828243);
	m_pYimaEncCtrl->SetCurrentScale(15935);	  
	Invalidate(); 

}

void CYimaEncViewerView::OnShowRefreashTime()
{
	// TODO: �ڴ�����������������
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


//ʵʱ����
void CYimaEncViewerView::OnRuntimeDragmap()
{
	// TODO: �ڴ�����������������
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

//��������
void CYimaEncViewerView::OnAnimationScale()
{
	// TODO: �ڴ�����������������
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

//��ȡ����ʱ��
__int64 CYimaEncViewerView::GetCurTimeMillis() 
{
	SYSTEMTIME wtm; 
	struct tm tm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon  = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min  = wtm.wMinute;
	tm.tm_sec  = wtm.wSecond;
	tm.tm_isdst    = -1;
	time_t clock = mktime(&tm);   
	return (__int64)(clock)* 1000 + wtm.wMilliseconds;
}

//��������ʱ�Ķ���
void CYimaEncViewerView::DrawScaledMap()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd; 
	int iDrawWidth = m_pYimaEncCtrl->GetDrawerScreenWidth();
	int iDrawHeight = m_pYimaEncCtrl->GetDrawerScreenHeight();
	float fScaleIndex = m_fScaleIndex;
	if(m_fScaleIndex < 0)
		fScaleIndex = fabs(1/m_fScaleIndex);
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
	if(bMouseWheelState)
	{ 
		__int64 mSec = GetCurTimeMillis() - m_WheelStartTime;
		if(mSec > 280)
		{  
			bMouseWheelState = false;  
			//��ǰ���λ��
			M_POINT mMouseGeoPo;
			m_pYimaEncCtrl->GetGeoPoFromScrnPo(m_scaleMouseScrnPo.x,m_scaleMouseScrnPo.y, (long*)&mMouseGeoPo.x, (long*)&mMouseGeoPo.y);

			//��Ļ���ĵ�
			M_POINT mCenterScrnPo = M_POINT(m_pYimaEncCtrl->GetDrawerScreenWidth()/2, m_pYimaEncCtrl->GetDrawerScreenHeight()/2);
			M_POINT mCenterGeoPo;
			m_pYimaEncCtrl->GetGeoPoFromEncScrnPo(mCenterScrnPo.x, mCenterScrnPo.y, (long*)&mCenterGeoPo.x, (long*)&mCenterGeoPo.y);

			//�����ĵ�ĵ�������
			M_POINT mNewCenterGeoPo;
			float fN = m_fScaleIndex;


			if (fN >= 0)
			{
				m_pYimaEncCtrl->SetCurrentScale(m_pYimaEncCtrl->GetCurrentScale()/ fN); //�Ŵ�
				mNewCenterGeoPo.x = mMouseGeoPo.x - (mMouseGeoPo.x - mCenterGeoPo.x) / fN ;
				mNewCenterGeoPo.y = mMouseGeoPo.y - (mMouseGeoPo.y - mCenterGeoPo.y) / fN ;
			}
			else
			{
				fN = fN * -1;
				float fScale = m_pYimaEncCtrl->GetCurrentScale() * fN;
				fScale = fScale >= 70000000 ? 70000000 : fScale;
				fN = (fScale >= 70000000) ? (70000000 / m_pYimaEncCtrl->GetCurrentScale()) : fN;
				m_pYimaEncCtrl->SetCurrentScale(fScale);// ��С
				mNewCenterGeoPo.x = mMouseGeoPo.x - (mMouseGeoPo.x - mCenterGeoPo.x) *fN;
				mNewCenterGeoPo.y = mMouseGeoPo.y - (mMouseGeoPo.y - mCenterGeoPo.y) *fN;
			}
			if(m_pYimaEncCtrl->GetMapEffect() == EFFECT_NONE)
			{
				m_pYimaEncCtrl->CenterMap(mNewCenterGeoPo.x, mNewCenterGeoPo.y);
			} 
			m_fScaleIndex = 0;

			Invalidate(); 
			RefreshScaleStatusBar();
			if(m_globalView != NULL)
			{ 
				m_globalView->ReSetViewPosion();
			}  
		}
	} 
}

void CYimaEncViewerView::OnAddRadar()
{
	// TODO: �ڴ�����������������
	radar_info = new RadarInfo();

	SetOperation(NO_OPERATION);
	SetOperation(ADD_USER_LAYER_OBJ);
}


void CYimaEncViewerView::OnSetRadar()
{
	// TODO: �ڴ�����������������
	//�״����̡��߶ȡ�ˮƽ��߶�����
	radar_set = new SetRadarDlg();
	radar_set->Create(IDD_SetRadarDlg, this);
	radar_set->ShowWindow(SW_SHOW);
}


void CYimaEncViewerView::OnDeleteRadar()
{
	// TODO: �ڴ�����������������
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
			//����걻��Ļ��һ����ѡ��
			if (AfxMessageBox("ȷ��ɾ�����״", MB_YESNO) == IDYES)
			{
				bool res = m_pYimaEncCtrl->DeleteGeoObject(mapPos, m_iEditingUserMapLayerNum, iter->innerLayerPos);
				Invalidate();

				radarDeleteMsg = radarDeleteMsg + ";DR" + ";" + iter->Id + ";;;;;;;#";
				//����Radarɾ����Ϣ
				sendRadarData(radarDeleteMsg, "127.0.0.1", RADAR_PORT);

				iter = radarList.erase(iter);		//����iterָ��ɾ��Ԫ�ص���һ��Ԫ��
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
	// TODO: �ڴ�����������������
	radar_modify = new ModifyRadarDlg();
	radar_modify->Create(IDD_ModifyRadarDlg, this);
	radar_modify->ShowWindow(SW_SHOW);
}


void CYimaEncViewerView::OnRadarProperty()
{
	// TODO: �ڴ�����������������
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
//	wVersionRequested = MAKEWORD(1, 1);//��һ������Ϊ��λ�ֽڣ��ڶ�������Ϊ��λ�ֽ�  
//
//	err = WSAStartup(wVersionRequested, &wsaData);//��winsock DLL����̬���ӿ��ļ������г�ʼ����Э��Winsock�İ汾֧�֣��������Ҫ����Դ��  
//	if (err != 0)
//	{
//		return;
//	}
//
//	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)//LOBYTE����ȡ��16���������λ��HIBYTE����ȡ��16��������ߣ�����ߣ��Ǹ��ֽڵ�����        
//	{
//		WSACleanup();
//		return;
//	}
//	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
//
//	SOCKADDR_IN addrClt;//��Ҫ���������IP��Ϣ  
//	addrClt.sin_addr.S_un.S_addr = inet_addr(ip.data());	// inet_addr��IP��ַ�ӵ�����ʽת���������ֽڸ�ʽ���͡�  
//	addrClt.sin_family = AF_INET;
//	addrClt.sin_port = htons(port);
//
//	connect(sockClient, (SOCKADDR*)&addrClt, sizeof(SOCKADDR));//�ͻ����������������������  
//	send(sockClient, msg.data(), msg.size(), 0);
//
//	closesocket(sockClient);
//	WSACleanup();
//}


void CYimaEncViewerView::OnMapHandRoam()
{
	// TODO: �ڴ�����������������
	SetOperation(HAND_ROAM);
}


void CYimaEncViewerView::OnShipStart()
{
	// TODO: �ڴ�����������������
	SetEvent(sendAisEvent);		//����sendAisEventΪ���ź�״̬

	SetTimer(TIMER_REFRESH_OTHERVESSEL, 1000, NULL);
	m_bShipStart = true;
}


void CYimaEncViewerView::OnShipStop()
{
	// TODO: �ڴ�����������������
	KillTimer(TIMER_REFRESH_OTHERVESSEL);
	m_bShipStart = false;
}


void CYimaEncViewerView::OnUpdateShipStart(CCmdUI *pCmdUI)
{
	// TODO: �ڴ�������������û����洦���������
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
	// TODO: �ڴ�������������û����洦���������
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
	// TODO: �ڴ�����������������
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	/************ ���濪ʼģ�Ȿ���ص�һ�����ߺ��С����Ӷ��AISĿ�괬���������ߺ��� **********/
	m_pYimaEncCtrl->AddRoutesFromFile(TEST_ROUTE_FILE_NAME); //�� TEST_ROUTE_FILE_NAME �ļ������ӵ��뺽������

	AIS_TYPE_ID stationTypeID = m_pYimaEncCtrl->AddAisType("station"); //����AIS����(AIS TYPE)
	m_pYimaEncCtrl->SetAisTypeInfo(stationTypeID, _T("station"), false, 1, 1, false, 0, 2, 5000000, true, false, 200000, true);//���ø���ʽ����ʾ���

	AIS_TYPE_ID stationTypeID2 = m_pYimaEncCtrl->AddAisType("station2"); //����AIS����(AIS TYPE)
	m_pYimaEncCtrl->SetAisTypeInfo(stationTypeID2, _T("station2"), false, 4, 1, false, 0, 6, 5000000, false, false, 200000, true);//���ø���ʽ����ʾ���


	int routeCount = m_pYimaEncCtrl->GetRoutesCount();
	if (routeCount > 0)
	{
		pFrame->SetOwnShipStartOnRoute(1);//����ģ���ڵ�һ�������Ϻ��� 



		for (int addVsNum = 0; addVsNum < routeCount - 1; addVsNum++)//routeCount - 1; addVsNum ++)
		{//Ϊ�ڶ����������ÿ����������1��AIS����, �����Ƿֱ�������Щ���ߺ���

			m_pYimaEncCtrl->AddOtherVessel(false, 0, 0, 90, 90, 90, 0, 0);

			CString strAddVslName;

			int mmsi = 4200010 + addVsNum;

			int myVsPos = m_pYimaEncCtrl->GetOtherVesselCount() - 1;

			strAddVslName.Format("AIS Target %d", myVsPos + 1);

			m_pYimaEncCtrl->SetOtherVesselBasicInfo(myVsPos,
				100, 50, strAddVslName, mmsi, NULL, 0);

			long shipNavRouteID = m_pYimaEncCtrl->GetRouteIDFromPos(addVsNum + 1);

			pFrame->m_nOtherVesselSelRouteIDs[myVsPos] = shipNavRouteID;

			//��ʼģ�⺽�е�Ŀ�꺽·���ں����е�λ����1
			pFrame->m_nOtherVesselCurAimWpPos[myVsPos] = 1;

			//����ģ�⺽�еĺ���һ����һ���� 
			pFrame->m_nOtherVesselSimulateSpeeds[myVsPos] = 5 * (addVsNum + 1);

			pFrame->SetOtherVesselStartOnRoute(myVsPos,
				pFrame->m_nOtherVesselSelRouteIDs[myVsPos]);

			m_pYimaEncCtrl->SetOtherVesselShowColor(addVsNum, false,
				RGB(addVsNum * 255 / (routeCount - 1), 0, 0), false,
				RGB(addVsNum * 255 / (routeCount - 1), 0, 0));		   //�˽ӿڻ᳹�׸ı���ŵ���ɫ

			CString strVslText;
			strVslText.Format(_T("Vsl %d"), m_pYimaEncCtrl->GetOtherVesselID(addVsNum));
			m_pYimaEncCtrl->SetOtherVesselShowText(addVsNum, true, strVslText, true, 20, true, RGB(0, 0, 255));
			m_pYimaEncCtrl->SetShipTrackStyle(false, myVsPos, true, RGB(0, 0, 255), 2, true, 4, RGB(0, 255, 255));
			int curTypeId = addVsNum % 2 == 0 ? stationTypeID : stationTypeID2;
			m_pYimaEncCtrl->SetAisTargetType(m_pYimaEncCtrl->GetOtherVesselCount() - 1, stationTypeID);
		}
	}
	pFrame->RefreshNavBarRouteList();
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
	long iGeoCoorMultiFactor = pView->m_pYimaEncCtrl->GetGeoCoorMultiFactor();
	int otherVesselCount = pView->m_pYimaEncCtrl->GetOtherVesselCount();
	while (true)
	{
		pView->m_pYimaEncCtrl->GetOwnShipCurrentInfo(&ownGeoPosx, &ownGeoPosy, &ownHead, &ownCOG, NULL, &ownSOG, NULL);
		//pView->m_pYimaEncCtrl->GetOwnShipBasicInfo(NULL, NULL, NULL, &ownMMSI);
		aisOwnMsg.Format("1,0,%s,0,%f,%f,0,X:%d,Y:%d,%f,%f,18,0,0",
			"4200020",
			5.0,						//ת����5.0
			ownSOG * 10,				//����
			GetAISGeoIntFromGeoCoor(ownGeoPosx, iGeoCoorMultiFactor),
			GetAISGeoIntFromGeoCoor(ownGeoPosy, iGeoCoorMultiFactor),
			ownCOG * 10,				//����		
			ownCOG);					//������
		aisOwnEncodeMsg = pView->m_aisSend.sendStr(aisOwnMsg, TRUE);
		aisOwnEncodeMsg.AppendChar('\r');
		aisOwnEncodeMsg.AppendChar('\n');
		sendAisData(aisOwnEncodeMsg.GetBuffer(), "127.0.0.1", 9007);
		for (int otherVesselNum = 0; otherVesselNum < otherVesselCount; otherVesselNum++)
		{
			bool res=pView->m_pYimaEncCtrl->GetOtherVesselCurrentInfo(otherVesselNum, NULL, &otherGeoPosx, &otherGeoPosy, &otherHead, &otherCOG, NULL, &otherSOG, NULL, NULL, NULL);
			pView->m_pYimaEncCtrl->GetOtherVesselBasicInfo(otherVesselNum, NULL, NULL, NULL, &otherMMSI, NULL);
			aisOtherMsg.Format("1,0,%s,0,%f,%f,0,X:%d,Y:%d,%f,%f,18,0,0",
				otherMMSI,
				5.0,						//ת����5.0
				otherSOG * 10,				//����
				GetAISGeoIntFromGeoCoor(otherGeoPosx, iGeoCoorMultiFactor),
				GetAISGeoIntFromGeoCoor(otherGeoPosy, iGeoCoorMultiFactor),
				otherCOG * 10,				//����		
				otherCOG);					//������
			aisOtherEncodeMsg = pView->m_aisSend.sendStr(aisOtherMsg, FALSE);
			aisOtherEncodeMsg.AppendChar('\r');
			aisOtherEncodeMsg.AppendChar('\n');
			sendAisData(aisOtherEncodeMsg.GetBuffer(), "127.0.0.1", 9007);
		}
	}
	return 0;
}