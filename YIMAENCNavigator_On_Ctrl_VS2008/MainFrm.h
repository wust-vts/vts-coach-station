// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__BB400EF3_45C3_45A2_949F_D5C78025D728__INCLUDED_)
#define AFX_MAINFRM_H__BB400EF3_45C3_45A2_949F_D5C78025D728__INCLUDED_

#include "NavigationDlgBar.h"	// Added by ClassView
#include "YIMAENCHEAD.H"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "YimaEnc.h" 

#define ID_YIMAENC_CTRL 10005

#define INDEX_PANE_FOR_MOUSE_POSITION 1
#define ID_PANE_FOR_MOUSE_POSITION   200
#define MOUSE_POSITION_PANE_WIDTH 900

#define INDEX_PANE_FOR_SCALE 2
#define ID_PANE_FOR_SCALE  201
#define SCALE_PANE_WIDTH 200

#define DEFAULT_OPERATION_STATUS_TEXT "就绪"

#define ROUTE_WAY_POINTS_MAX_COUNT 10000
#define MAX_EMULATE_OTHER_VESSEL_COUNT 5000

#define TEST_ROUTE_FILE_NAME "Routes.dat"

typedef struct USER_DEFINE_DISPLAY_LAYER_UNION
{
	int userDefineLayerPos[1000];
	int userDefineLayerPosCount;

    USER_DEFINE_DISPLAY_LAYER_UNION& operator=(const USER_DEFINE_DISPLAY_LAYER_UNION& userDefineDisplayLayerUnion)
	{
		for(int i = 0; i < userDefineDisplayLayerUnion.userDefineLayerPosCount; i ++)
		{
			userDefineLayerPos[i] = userDefineDisplayLayerUnion.userDefineLayerPos[i];
		}
		
		userDefineLayerPosCount = userDefineDisplayLayerUnion.userDefineLayerPosCount;
		return *this;
	};
}USER_DEFINE_DISPLAY_LAYER_UNION;

class CMainFrame : public CFrameWnd
{ 
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame) 

// Attributes
public:
	bool m_bShowRadar;
	CString strInitPath;
	CYimaEnc m_yimaEncCtrl; 

	CToolBar m_wndToolBar;
	static void AddRadarInfoTest();
	HANDLE hThread;
	DWORD ThreadID;
	int m_expandWidth, m_expandHeight;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ReadIniFile();
	bool SetOwnShipStartOnRoute(long routeID);
	bool SetOtherVesselStartOnRoute(int otherVslPos, long routeID);

	void RefreshNavBarRadarList();
	void RefreshNavBarRouteList();
	void RefreshOtherVesselList();
	void RefreshNavigationDlgBar(char* chMsg);
	void RefreshOtherVesselPositions(char* msg);

	bool m_bHeadUpModel;

	long m_nOwnShipSelectRouteID;//本船当前选择的航线ID
	//int m_nAimWayPointPosInRoute; 
	
	long m_nOtherVesselSelRouteIDs[MAX_EMULATE_OTHER_VESSEL_COUNT];
	int m_nOtherVesselCurAimWpPos[MAX_EMULATE_OTHER_VESSEL_COUNT];
	float m_nOtherVesselSimulateSpeeds[MAX_EMULATE_OTHER_VESSEL_COUNT];

	bool m_bAlarmColorFlag; //报警当前颜色标志, 报警时颜色在红色和绿色间闪烁. 这里使用此标志来控制颜色的变化 
	int m_nTimerStep; //定时器时间间隔, 单位为毫秒
	int m_nOwnShipCurrentSpeed; //本船当前速度
	 
	bool m_bOnAutoCenterShipMode;//禁止船舶自动居中功能

	// 3个报警参数, 单位均为米：
	UINT	m_isoDangerDistDoor; 
	UINT	m_offRouteDistDoor;
	UINT	m_safeContourDistDoor;
	UINT	m_shallowDepthDoor;
	UINT	m_deepDepthDoor;
	float g_fTcpaDoor;
	float g_fDcpaDoor;
	int m_testDcpaShipId;
	M_POINT m_CurrOwnShipGeoPo;
	float m_curOwnShipCourse; 

	void RedrawView();
	void UncheckMenusAndToolBar();
	void UncheckMenusAndToolBarForMenuItem(UINT menuItemID);
	void SetOperationStatusBarText(CString reportText);
 	
	bool GetShipPositionsFromDataFile(int& retShipCount,
		CString* pStringShipNames, 
							 int* pShipPositionXs, int* pShipPositionYs);

	USER_DEFINE_DISPLAY_LAYER_UNION userDefineBasicLayer;
    USER_DEFINE_DISPLAY_LAYER_UNION userDefineStandardLayer;
	USER_DEFINE_DISPLAY_LAYER_UNION userDefineAllLayer;
	bool S52oruser;
	int s52RadioButtonNum;
	int userRadioButtonNum;
    CString mapTitle;
    int nmapTitleLeftOrMiddleOrRight;
    CString remarks;
    int nremarksLeftOrMiddleOrRight;
    int nscaleLeftOrMiddleOrRight;
	LOGFONT titleFont;
	LOGFONT remarkFont;

	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;


// Generated message map functions
protected:
	CNavigationDlgBar m_wndNavigationDlgBar;
	void UncheckAllDsplyCategoryMenu(); 
	void UncheckAllEncColorMenu();
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);  
	afx_msg void OnShowAllInfo();
	afx_msg void OnShowStandardInfo();
	afx_msg void OnShowBaseInfo();
	afx_msg void OnColorDayBright();
	afx_msg void OnColorDayWhiteback();
	afx_msg void OnColorDayBlackback();
	afx_msg void OnColorDayDusk();
	afx_msg void OnColorNight();
	afx_msg void OnTranditionSymbolCheck();
	afx_msg void OnSimpleSymbolCheck();
	afx_msg void OnSymbolBndryCheck();
	afx_msg void OnPlainBndryCheck();
	afx_msg void OnSafetyContour();
	afx_msg void OnSetLangEng();
	afx_msg void OnSetLangChn();
	afx_msg void OnSetScale(); 
	afx_msg void OnMapLibMan();
	afx_msg void OnHandRoam();
	afx_msg void OnLayersMan();
	afx_msg void OnRadar(); 
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStopAutoCenterShip(); 
	afx_msg void OnRouteEditMode(); 
	afx_msg void OnStopTimer();
	afx_msg void OnSelcancelRouteList();
	afx_msg void OnSetNavRouteButton();
	afx_msg void OnAddVessel();
	afx_msg void OnHeadUp();
	afx_msg void OnSaveRoutes();
	afx_msg void OnDelRouteBtn();
	afx_msg void OnDirectEditRoute();
	afx_msg void OnAlarmSetting();
	afx_msg void OnEmulateSetting(); 
	afx_msg void OnSaveHistoryTrack();
	afx_msg void OnSelHistoryTrack();
	afx_msg void OnAddUserMapObject();
	afx_msg void OnChoseEditUserLayer(); 
	afx_msg void OnSaveUserMap();
	afx_msg void OnViewLibStyles();
	afx_msg void OnViewLibPointStyles();	
	afx_msg void OnViewLibFaceStyles();	
	afx_msg void OnAddPointObject();
	afx_msg void OnAddLineObject();
	afx_msg void OnAddFaceObject();
	afx_msg void OnAddRectangle();
	afx_msg void OnAddCircle();
	afx_msg void OnAddEllipse();
	afx_msg void OnAddArc();
	afx_msg void OnAddSector();
	afx_msg void OnGeoCalc();
	afx_msg void OnSelecTlayerShowInfo();
	afx_msg void OnAddBow();
	afx_msg void OnAddPie();
	afx_msg void OnSaveScrnToBmpFile();
	afx_msg void OnShowText();
	afx_msg void OnSaveMemS57Map();
	afx_msg void OnSmoothPen();
	afx_msg void OnShowFrame();
	afx_msg void OnHightlightDeptharea();
	afx_msg void OnChangeDepthLine();
	afx_msg void OnToolBar();
	afx_msg void OnSetS63UsrId();
	afx_msg void OnUseOutlineText();
	afx_msg void OnGridShow();
	afx_msg void OnShowScaleBar();
	afx_msg void OnShowNorthArrow();
	afx_msg void OnSetFileExtension();
	afx_msg void OnSetDepColor();
	afx_msg void OnScrnPlaneGeo();
	afx_msg void OnGetDcpaTcpa();
	afx_msg void OnGetAreaOfRegion();
	afx_msg void OnGetDepInfo();
	afx_msg void OnAddTestShip(); 
	afx_msg void OnAreaWarnTest(); 
	afx_msg void OnLayerObjectTest(); 
	afx_msg void OnNineNineBoxTest();
	afx_msg void OnCaculateScaleTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private: 
	//int m_nOffRouteSimulateTimerCount;
public:
	afx_msg void OnSetBackgroud();
	afx_msg void OnSetGrid();
	afx_msg void OnVcfLayerMan();
	afx_msg void OnAddColorChangedFace();	 
	afx_msg void OnShowRadar();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__BB400EF3_45C3_45A2_949F_D5C78025D728__INCLUDED_)
