// YimaEncViewerView.h : interface of the CYimaEncViewerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_YIMAENCVIEWERVIEW_H__485A2B27_0DEB_4319_AE16_EA647C67CF05__INCLUDED_)
#define AFX_YIMAENCVIEWERVIEW_H__485A2B27_0DEB_4319_AE16_EA647C67CF05__INCLUDED_

#include "NavigationDlgBar.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "YimaEncViewerDoc.h"
#include "YIMAENCHEAD.H"	// Added by ClassView
#include <list>
#include <vector>
#include <iostream> 
#include "GlobalView.h"
#include "RadarInfo.h"
#include "SetRadarDlg.h"
#include "NetToODU.h"
#include "ModifyRadarDlg.h"
#include "RadarPropertyDlg.h"
#include "SendData.h"
#include "AIS.h"
#include "AisType1.h"
#include "AisType5.h"

typedef enum CURRENT_SUB_OPERATION
{
	NO_OPERATION = 0, 
	ADD_ISO_POINT = 1,
	ADD_LINE = 0x2,
	ADD_FACE = 0x4, 
	ADD_COLOR_ATTENUATION_OBJ = 0x8, //添加颜色衰减的物标   
	AREA_ZOOM_IN = 0x10,
	ADD_WAYPOINT = 0x20,  
	ADD_ROUTE = 0x40,
	EDITING_ROUTE = 0x80, 
	EDITING_WAY_POINT = 0x100, 
	HAND_ROAM = 0x200,  
	SHOWING_HINT_TEXT = 0x400,
	EDITING_BASIC_OBJECT = 0x800,
	EDITING_EDGE_MID_PO = 0x1000,
	DRAG_EDITING_OBJECT = 0x2000,
	EDITING_GEO_OBJECT = 0x4000, 
	DRAW_EBL = 0x8000,
	ADD_USER_LAYER_OBJ = 0x10000,
	AREA_SELECT = 0x20000,
	ADD_LINE_OBJECT_MOUSEMOVING = 0x40000, //添加物标时的动态节点添加状态
	HOLLOW_MAP = 0x80000,
	DELAY_MAP = 0x100000,
	MEASURE_AREA = 0x200000,	//测面积
}CURRENT_SUB_OPERATION;

#define SEL_OBJ_MAX_COUNT 3000

#define TIMER_REFRESH_OTHERVESSEL 1100
#define TIME_ODU_PARSE 1101
#define TIME_SET_ODUCOUNT 1102
#define TIME_REFRESH_RADARLIST 1103

#define MAX_LINE_EDIT_POINT_COUNT 100000
class CYimaEncViewerView : public CView
{ 
protected: // create from serialization only
	CYimaEncViewerView();
	DECLARE_DYNCREATE(CYimaEncViewerView)

	static UINT ThreadFuncDraw(LPVOID lpParam);
	CWinThread* pDrawMapThread;

	int m_nTimerStep; //定时器，单位为毫秒
	bool m_bShowRefreashTime; 
	int m_startFillTrans;
// Attributes
public:
	CYimaEncViewerDoc* GetDocument(); 

	//CYimaEnc m_yimaEncCtrl; 

	CYimaEnc* m_pYimaEncCtrl;

	int m_curOperation;

	MRECT m_rectHintText; //动态提示框: 此变量为提示框区域
	int m_iMouseStoppedTimerCount; //动态提示框: 此变量记录鼠标停止不动多长时间了,单位是定时器的计数次数
 
	M_POINT m_mouseDragFirstPo;     //鼠标拖曳操作的起点
	M_POINT m_mouseMoveCurrentPo;   //鼠标当前的位置
	M_POINT m_mouseMoveLastPo;		//鼠标拖曳操作的上一个点位置

	bool m_bHasPressedDragStartPo; //鼠标拖曳操作时是否已经点击鼠标
	bool m_bHasDrawDragFirstPo;    //鼠标拖曳操作时是否已经绘制第一个拖曳点

	bool m_bMouseZoomModeOrStdZoomMode; //是“鼠标缩放”模式还是“标准缩放”模式
	bool m_bUseMouseDragBufferMode; //是否使用支持“鼠标拖曳不留白”的海图画布放大缓冲模式

	int m_curSelectedObjCount; //YIMAENC COMMENT: 当前选中的物标个数
	MEM_GEO_OBJ_POS m_curSelectedObjPoses[SEL_OBJ_MAX_COUNT];//YIMAENC COMMENT: 当前选中的所有物标位置
 
	float m_highlightDepthLowerLimit, m_highlightDepthUpLimit; //高亮水深区的深度范围
	long m_highlightDepthAreaColor; //高亮水深区的颜色
 
	int m_iEditingPointPosOnEditingLine; //正在编辑某一个线对象的某一节点
  
	M_GEO_OBJ_POS m_editingUserMapObjPos; //当前被选中的自定义海图的对象索引，如果其 layerPos 为-1，说明没有物标被选中 
	 
	bool m_bOnRouteEditMode; //当前是否出于航线编辑模式
	long m_nEditingWayPointID;
	long m_nEditingRouteID;
	long m_nEditingRouteWayPointIDs[MAX_WAY_POINT_COUNT_OF_ROUTE];

	int m_iEditingUserMapLayerNum;

	SPECIAL_LINE_TYPE m_addingSpecialLineType;

	M_POINT m_ScrnOffset;
	std::list<M_COLOR_ATTENUATION> m_arrColorAttenuationObj; //记录下所有颜色衰减的物标信息
	CGlobalView* m_globalView;//鹰眼视图
	M_POINT m_arrMeasureGeoPo[300];
	int m_icurEditPos;
	DWORD m_beforeRefesh, m_usedMSecond;
	M_GEO_OBJ_POS m_ClosedLineTestObj;
	bool m_bRuntimeDragMap; //是否实时漫游海图
	bool m_bAnimationScale; //是否使用动画缩放
	bool bMouseWheelState;	//滑轮状态
	float m_fScaleIndex;	//滑轮缩放数值
	__int64 m_WheelStartTime;//开始缩放时间
	M_POINT m_scaleMouseScrnPo;//动画缩放中心
public:
	RadarInfo* radar_info;		//雷达对象
	SetRadarDlg* radar_set;		//雷达设置
	ModifyRadarDlg* radar_modify;	//雷达修改
	RadarPropertyDlg* radar_property;	//雷达属性
	bool m_bShipStart;			//是否开始本船及其他船模拟

	CPoint selectObjPoint;		//选中radar时的鼠标坐标

	CWinThread* pThread_receiveODU;			//接收ODU登录线程指针
	std::string recvODUMsg;	//ODU数据

	HANDLE sendAisEvent;	//发送AIS数据事件对象
	HANDLE m_hSendAISThread;	//发送AIS数据线程
	CAIS m_aisSend;
public:
	std::vector<std::string> split(const std::string& src, const std::string& key);		//字符串分割
 // Operations
public:
	__int64 GetCurTimeMillis();
	void DrawScaledMap();
	void CheckIfWheelStop();
	long SelectAWayPointByScrnPoint(int scrnPointX, int scrnPointY); 	
	long SelectARouteByScrnPoint(int scrnPointX, int scrnPointY);

	bool IsOnOperation(CURRENT_SUB_OPERATION subOperation);

	void SetOperation(CURRENT_SUB_OPERATION subOperation);

	void CancelOperation(CURRENT_SUB_OPERATION subOperation); 

	bool IsOnDragingObjectOperation();

	bool SetHighlightObjects(MEM_GEO_OBJ_POS* pObjPoses, int objCount);

	void RefreshScreenMap();

	void DrawDynamicScreenMap(M_POINT mousePoint);

	void DrawMapOperationPanel(HDC hScrnDC);

	void RefreshScaleStatusBar();
	M_POINT GetCurMouseOffSetObjCenter(M_GEO_OBJ_POS ObjPos, M_POINT curMouseScrnPo);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYimaEncViewerView)
    public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool UserObject_SetAttributes(int layerPos, int innerLayerPos);
 
	virtual ~CYimaEncViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	int DetectRouteLegSafteyInMemMap(int memMapPos, M_POINT legStartGeoPo, M_POINT legEndGeoPo,
								M_GEO_OBJ_POS* retCrossObjPoses);

	void ResizeMapScrn(bool bUseDragBufferScrnMode, float bufferScrnSizeRatio) ;

// Generated message map functions
protected: 

	int m_nEditingLinePointCount;
	M_POINT m_editingLineGeoPoints[MAX_LINE_EDIT_POINT_COUNT]; 
	void DrawCurrentEblLine(HDC hdc, M_POINT startPoint, M_POINT endPoint, 
		   M_POINT* pRetEblEndPoint = NULL);
	void DrawEditingLineBeforeFinish();
	void PrintTheMapInTheScreen(CDC* pDC, CPrintInfo* pInfo,CString mapTitle,LOGFONT* titleFont,int nmapTitleLeftOrMiddleOrRight,CString remarks,LOGFONT* remarkFont,int nremarksLeftOrMiddleOrRight,int nscalenLeftOrMiddleOrRight);
	//{{AFX_MSG(CYimaEncViewerView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMoveDown();
	afx_msg void OnMoveLeft();
	afx_msg void OnMoveRight();
	afx_msg void OnMoveUp();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags); 
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnAreaZoomIn();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCenterRotateMap(); 
	afx_msg void OnAddWaypoint();
	afx_msg void OnAddRoute(); 	
	afx_msg void OnDelWaypoint();
	afx_msg void OnDelRoute();
	afx_msg void OnDirectEditRoute();
	afx_msg void OnEblLine();
	afx_msg void OnDelObject();
	afx_msg void OnTimer(UINT nIDEvent);	
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnQuery();
	afx_msg void OnDelLinePoint();
	afx_msg void OnSetFirstLayerNotDraw();
	afx_msg void OnAddCurveLine();
	afx_msg void OnAddClosedCurveLine();
	afx_msg void OnAddSingleArrow();
	afx_msg void OnAddDoubleArrow();
	afx_msg void OnAddCurveWithArrow();
	afx_msg void OnAddCurveWithBothArrow();
	afx_msg void OnAddThreeArrow();
	afx_msg void OnUndo();
	afx_msg void OnRedo();
	afx_msg void OnMyFilePrint();
	afx_msg void OnMyFilePrintPreview(); 
	afx_msg void OnAfterDrawMapYimaEncCtrl();
	afx_msg void OnAfterDrawMarineMapYimaEncCtrl();
    afx_msg void OnDrawRadar(); 
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt); 
	afx_msg void OnAreaSelect();
	afx_msg void OnRouteSafeDetect();
	afx_msg void OnCopyObject();
	afx_msg void OnRotateClockwise();
	afx_msg void OnRotateAnticlockwise();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	/* YIMAENC COMMENT: 注意，
    在非对话框程序中，YimaEnc Control 的消息响应无法通过Class Wizard自动
    建立, 需手工增加消息映射宏 BEGIN_EVENTSINK_MAP 等声明 */
public:
	afx_msg void OnNoBlankMouseDrag();
	afx_msg void OnWheelZoomByMousePosi();
	afx_msg void OnHollowMapEffect();
	afx_msg void OnDelayMapEffect();
	afx_msg void OnCancelMapEffect();
	afx_msg void OnObjZoomOut();
	afx_msg void OnObjZoomIn();
	afx_msg void OnAddNewMapCtrl();
	afx_msg void OnGlobalView();
	afx_msg void OnWaterColorSetting();
	afx_msg void OnMeasureArea();
	afx_msg void OnClosedLineWarn();
	afx_msg void OnShowRefreashTime();
	afx_msg void OnRuntimeDragmap();
	afx_msg void OnAnimationScale();
	afx_msg void OnAddRadar();
	afx_msg void OnSetRadar();
	afx_msg void OnDeleteRadar();
	afx_msg void OnModifyRadar();
	afx_msg void OnRadarProperty();
	afx_msg void OnMapHandRoam();
	afx_msg void OnShipStart();
	afx_msg void OnShipStop();
	afx_msg void OnUpdateShipStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateShipStop(CCmdUI *pCmdUI);
	afx_msg void OnLoadRoutedata();
	static DWORD WINAPI SendAISThreadProc(LPVOID);
};

UINT Thread_Receive_ODU(LPVOID para);		//接收ODU线程
//void sendData(std::string msg, std::string ip, int port);

#ifndef _DEBUG  // debug version in YimaEncViewerView.cpp
inline CYimaEncViewerDoc* CYimaEncViewerView::GetDocument()
   { return (CYimaEncViewerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YIMAENCVIEWERVIEW_H__485A2B27_0DEB_4319_AE16_EA647C67CF05__INCLUDED_)
