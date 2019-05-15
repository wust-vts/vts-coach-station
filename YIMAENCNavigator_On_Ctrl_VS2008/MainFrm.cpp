// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "shlwapi.h"
#include <iostream>  
#include <iomanip>  
#include <fstream>  

#include "MainFrm.h"  
#include "YimaEncViewerView.h"
#include "SetScaleDlg.h"
#include "SetSafeContourDlg.h"
#include "MapLibInfoDlg.h"
#include "LayerManDlg.h"
#include "NavigationDlgBar.h"
#include "RouteEditDlg.h"
#include "AlarmSettingDlg.h"
#include "EmulateParamSetDlg.h"
#include "UserMapLayersDlg.h"
#include "LibLineStylesViewDlg.h"
#include "LibPointStylesViewDlg.h"
#include "LibFaceStylesViewDlg.h"
#include "GeoCalculateDlg.h"
#include "MapLayerShowDlg.h"
#include "HighlightDepthAreaDlg.h"
#include "ChangeDepthLineValDlg.h"
#include "SetS63DeviceIDDialog.h"
#include "math.h"
#include "SetGridLinesDlg.h"
#include "ScrnPlaneGeoDlg.h"
#include "GetDcpaTcpaDlg.h"
#include "GetAreaOfGeoRegionDlg.h"
#include "GetDepInfoDlg.h"
#include "SaveMapViewToImgDlg.h"
#include "AddTestShipDlg.h"
#include "TestAreaWarnDlg.h"
#include "TestLayerObjectDlg.h"
#include "TestNineNineBoxDlg.h"
#include "TestCaculateScaleDlg.h"
#include "SelOwnShipHistoryTrackDlg.h" 
#include "VcfLayerManDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PI 3.14159265

CString g_ymcExt = ".ymc";
CString g_ympExt = ".ymp";
CString g_strInitPath = "";
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()  
	ON_COMMAND(ID_SHOW_ALL_INFO, OnShowAllInfo)
	ON_COMMAND(ID_SHOW_STANDARD_INFO, OnShowStandardInfo)
	ON_COMMAND(ID_SHOW_BASE_INFO, OnShowBaseInfo)
	ON_COMMAND(ID_COLOR_DAY_BRIGHT, OnColorDayBright)
	ON_COMMAND(ID_COLOR_DAY_WHITEBACK, OnColorDayWhiteback)
	ON_COMMAND(ID_COLOR_DAY_BLACKBACK, OnColorDayBlackback)
	ON_COMMAND(ID_COLOR_DAY_DUSK, OnColorDayDusk)
	ON_COMMAND(ID_COLOR_NIGHT, OnColorNight)
	ON_COMMAND(ID_TRANDITION_SYMBOL_CHECK, OnTranditionSymbolCheck)
	ON_COMMAND(ID_SIMPLE_SYMBOL_CHECK, OnSimpleSymbolCheck)
	ON_COMMAND(ID_SYMBOL_BNDRY_CHECK, OnSymbolBndryCheck)
	ON_COMMAND(ID_PLAIN_BNDRY_CHECK, OnPlainBndryCheck)
	ON_COMMAND(ID_SAFETY_CONTOUR, OnSafetyContour)
	ON_COMMAND(ID_SET_LANG_ENG, OnSetLangEng)
	ON_COMMAND(ID_SET_LANG_CHN, OnSetLangChn)
	ON_COMMAND(ID_SET_SCALE, OnSetScale) 
	ON_COMMAND(ID_MAP_LIB_MAN, OnMapLibMan) 
	ON_COMMAND(ID_LAYERS_MAN, OnLayersMan)
	ON_COMMAND(ID_RADAR, OnRadar) 
	ON_WM_TIMER()
	ON_COMMAND(ID_AUTO_CENTER_SHIP, OnStopAutoCenterShip) 
	ON_COMMAND(ID_ROUTE_EDIT_MODE, OnRouteEditMode) 
	ON_COMMAND(ID_STOP_TIMER, OnStopTimer)
	ON_LBN_SELCANCEL(IDC_ROUTE_LIST, OnSelcancelRouteList)
	ON_BN_CLICKED(IDC_SET_NAV_ROUTE_BUTTON, OnSetNavRouteButton)
	ON_COMMAND(ID_ADD_VESSEL, OnAddVessel)
	ON_COMMAND(ID_HEAD_UP, OnHeadUp)
	ON_COMMAND(ID_SAVE_ROUTES, OnSaveRoutes)
	ON_BN_CLICKED(IDC_DEL_ROUTE_BTN, OnDelRouteBtn)
	ON_COMMAND(ID_DIRECT_EDIT_ROUTE, OnDirectEditRoute)
	ON_COMMAND(ID_ALARM_SETTING, OnAlarmSetting)
	ON_COMMAND(ID_EMULATE_SETTING, OnEmulateSetting) 
	ON_COMMAND(IDD_SAVE_HISTORY_TRACK, OnSaveHistoryTrack) 
	ON_COMMAND(IDD_SEL_HISTORY_TRACK, OnSelHistoryTrack) 
	ON_COMMAND(ID_ADD_USER_MAP_OBJECT, OnAddUserMapObject)
	ON_COMMAND(ID_CHOSE_EDIT_USER_LAYER, OnChoseEditUserLayer) 
	ON_COMMAND(ID_SAVE_USER_MAP, OnSaveUserMap)
	ON_COMMAND(ID_VIEW_LIB_STYLES, OnViewLibStyles)
	ON_COMMAND(ID_VIEW_POINT_STYLES, OnViewLibPointStyles)
	ON_COMMAND(ID_VIEW_FACE_STYLES, OnViewLibFaceStyles)
	ON_COMMAND(ID_ADD_POINT_OBJECT, OnAddPointObject)
	ON_COMMAND(ID_ADD_LINE_OBJECT, OnAddLineObject)
	ON_COMMAND(ID_ADD_FACE_OBJECT, OnAddFaceObject)
	ON_COMMAND(ID_ADD_RECTANGLE, OnAddRectangle)
	ON_COMMAND(ID_ADD_CIRCLE, OnAddCircle)
	ON_COMMAND(ID_ADD_ELLIPSE, OnAddEllipse)
	ON_COMMAND(ID_ADD_ARC, OnAddArc)
	ON_COMMAND(ID_ADD_SECTOR, OnAddSector)
	ON_COMMAND(ID_GEO_CALC, OnGeoCalc)
	ON_COMMAND(ID_SCRN_PLANE_GEO, OnScrnPlaneGeo)
	ON_COMMAND(ID_Get_DTCPA, OnGetDcpaTcpa)
	ON_COMMAND(ID_GET_AREA_REGION, OnGetAreaOfRegion)
	ON_COMMAND(ID_GET_DEP_INFO, OnGetDepInfo)
	ON_COMMAND(ID_ADD_SHIP, OnAddTestShip)
	ON_COMMAND(ID_AREA_WARN, OnAreaWarnTest)
	ON_COMMAND(ID_LAYER_OBJECT_TEST, OnLayerObjectTest)
	ON_COMMAND(ID_ADD_NINE_BOX, OnNineNineBoxTest)
	ON_COMMAND(ID_CACULATE_SCALE, OnCaculateScaleTest)
	
	
	ON_COMMAND(ID_SELEC_TLAYER_SHOW_INFO, OnSelecTlayerShowInfo)
	ON_COMMAND(ID_ADD_BOW, OnAddBow)
	ON_COMMAND(ID_ADD_PIE, OnAddPie)
	ON_COMMAND(ID_SAVE_SCRN_TO_BMP_FILE, OnSaveScrnToBmpFile)
	ON_COMMAND(ID_SHOW_TEXT, OnShowText)
	ON_COMMAND(ID_SAVE_MEM_S57_MAP, OnSaveMemS57Map)
	ON_COMMAND(ID_SMOOTH_PEN, OnSmoothPen)
	ON_COMMAND(ID_SHOW_FRAME, OnShowFrame)
	ON_COMMAND(ID_HIGHTLIGHT_DEPTHAREA, OnHightlightDeptharea)
	ON_COMMAND(ID_CHANGE_DEPTH_LINE, OnChangeDepthLine)
	ON_COMMAND(ID_TOOL_BAR, OnToolBar)
	ON_COMMAND(ID_SET_S63_USR_ID, OnSetS63UsrId)
	ON_COMMAND(ID_USE_OUTLINE_TEXT, OnUseOutlineText)
	ON_COMMAND(ID_GRID_SHOW, OnGridShow)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_SET_BACKGROUD, OnSetBackgroud)
	ON_COMMAND(ID_SET_GRID, &CMainFrame::OnSetGrid)
	ON_COMMAND(ID_SHOW_SCALE_BAR, OnShowScaleBar)
	ON_COMMAND(ID_SHOW_NORTH_ARROW, OnShowNorthArrow)
	ON_COMMAND(ID_SET_FILE_EXTENSION, OnSetFileExtension)
	ON_COMMAND(ID_SET_DEP_COLOR, OnSetDepColor)
	

	
	
	ON_COMMAND(ID_VCF_LAYER_MAN, &CMainFrame::OnVcfLayerMan)
	ON_COMMAND(ID_AddColorChangedFace, &CMainFrame::OnAddColorChangedFace)
	ON_COMMAND(ID_SHOW_RADAR, &CMainFrame::OnShowRadar)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_nOwnShipSelectRouteID = 1;

	m_bShowRadar = true; 
    //m_nAimWayPointPosInRoute = 1;

	m_bAlarmColorFlag = false; 

	m_nOwnShipCurrentSpeed = 20;
	m_nTimerStep = 2000;  
	//m_nOffRouteSimulateTimerCount = 0;

	m_bOnAutoCenterShipMode = false;

	m_bHeadUpModel = false;

	m_isoDangerDistDoor = 1000;
	m_offRouteDistDoor = 100;
	m_safeContourDistDoor = 100;
	m_shallowDepthDoor = 40;
	m_deepDepthDoor = 1200;
	S52oruser = true;
	s52RadioButtonNum = 0;
    userRadioButtonNum = 0; 
	g_fTcpaDoor = 300;
	g_fDcpaDoor = 200;
	m_testDcpaShipId = 0;
	strInitPath = "";
}

CMainFrame::~CMainFrame()
{
	TerminateThread(hThread, ThreadID);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	 
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	} 

	UINT nID;
	UINT nStyle;
	int cxWidth;
	m_wndStatusBar.GetPaneInfo(INDEX_PANE_FOR_MOUSE_POSITION, nID, nStyle, cxWidth);
	m_wndStatusBar.SetPaneInfo(INDEX_PANE_FOR_MOUSE_POSITION, ID_PANE_FOR_MOUSE_POSITION   ,
		nStyle, MOUSE_POSITION_PANE_WIDTH );
	
	m_wndStatusBar.GetPaneInfo(INDEX_PANE_FOR_SCALE, nID, nStyle, cxWidth);
	m_wndStatusBar.SetPaneInfo(INDEX_PANE_FOR_SCALE, ID_PANE_FOR_SCALE,
		nStyle, SCALE_PANE_WIDTH );

	//////////////////////// 添加并初始化 YIMAENC 控件 ////////////////
	//YIMAENC COMMENT: 注意!! 在非对话框程序中，即单文档或多文档中必须自行创建控件后方可使用
	m_yimaEncCtrl.Create(NULL, NULL, CRect(0, 0, 1000, 600), this,
		ID_YIMAENC_CTRL);   
     
	////////////////////////// 初始化设置 ///////////////////////////
	//m_yimaEncCtrl.ZoomS52SymbolOrFontSize(0.8, 1.2);
	//m_yimaEncCtrl.SetNationalLanguageCountry(LANG_CHN);
	//m_yimaEncCtrl.SetLanguage(false);
	//m_yimaEncCtrl.SetIfShowMapFrame(true);
	//m_yimaEncCtrl.SetGridLines(3, 0x000000, 0x00FF00, 0x0000FF, 18);
	/////////////////////////////////////////////////////////////////

	TCHAR curWorkDir[1024];

	CString str;
	CStdioFile file;

	/*bool bOpen = file.Open("config.ini",CFile::typeText|CFile::modeReadWrite);
	CString strInitPath = "";
	if(bOpen)
	{		
		file.SeekToBegin();
		file.ReadString(strInitPath);
	}*/

	//m_yimaEncCtrl.SetWorkDirectory("", "e:\\temp");
	//m_yimaEncCtrl.SetFirstStandardParrel(30);
	ReadIniFile();
	m_yimaEncCtrl.SetYimapEncFileExtension(g_ymcExt, g_ympExt);
	bool bInitResult = false;
	if(g_strInitPath != "")
	{
		bInitResult = m_yimaEncCtrl.Init(g_strInitPath);
		strInitPath = g_strInitPath;
	}
	else
	{		 		  
		TCHAR exeFullPath[MAX_PATH]; // MAX_PATH在WINDEF.h中定义了，等于260  
		memset(exeFullPath,0,MAX_PATH);   
		GetModuleFileName(NULL,exeFullPath,MAX_PATH);
		std::string strExeFullPath = exeFullPath;
		int dotPos = strExeFullPath.find_last_of('\\');
		strExeFullPath = strExeFullPath.substr(0, dotPos);   
		bInitResult = m_yimaEncCtrl.Init(strExeFullPath.c_str());  
		strInitPath = strExeFullPath.c_str();
		if(bInitResult == false)
		{		
			GetCurrentDirectory(1024, curWorkDir);//获取初始化目录
			bInitResult = m_yimaEncCtrl.Init(curWorkDir); 
			strInitPath = curWorkDir;   
		}
		 
	}
	
	if (bInitResult == false) //YIMAENC COMMENT:  YimaEnc Control interoped!
	{
		AfxMessageBox("Failed to init YimaEnc Control, may be the config files are not exits!"); 
		return -1;
	}       
 
	m_expandWidth = 0;
	m_expandHeight = 0;
	m_yimaEncCtrl.SetDrawExpandPixel(m_expandWidth, m_expandHeight);
	m_yimaEncCtrl.SetIfYmcFileNeedEncrypt(false);
	m_yimaEncCtrl.SetYMCFileEncryptKey(4567);  

	m_yimaEncCtrl.SetIfOnDrawRadarMode(false);
	m_yimaEncCtrl.SetIfUseGDIPlus(false);
	strInitPath = strInitPath + "\\MarineMap\\marineMap.ymc";
	bool bOpenMarineMap = m_yimaEncCtrl.tmOpenMapDataFile(strInitPath);   
	m_yimaEncCtrl.SetLoadMapScaleFactor(10);  
	
	m_yimaEncCtrl.SetSafetyDepth(3);
	OnShowStandardInfo();
	hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)AddRadarInfoTest,NULL, CREATE_SUSPENDED, &ThreadID);
	//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ 

	//SetTimer(1, m_nTimerStep, NULL); //设置一个1秒的定时器   
	/////////////////////// 创建右侧导航栏 //////////////////////////
     
	if (!m_wndNavigationDlgBar.Create(this, IDD_NAVIGATION_DLG,
		CBRS_RIGHT | CBRS_TOOLTIPS | CBRS_HIDE_INPLACE,
		IDD_VIEW_NAVIGATIONDIALOGBAR))//IDD_VIEW_NAVIGATIONDIALOGBAR))
	{
		TRACE0("Failed to create dialog bar m_wndDlgBar\n");
		return -1;		// fail to create
	}
	
	m_wndNavigationDlgBar.EnableDocking(CBRS_ALIGN_RIGHT);
	EnableDocking(CBRS_ALIGN_RIGHT);
	DockControlBar(&m_wndNavigationDlgBar);   

	return 0;
}

#define SHIP_MAX_COUNT 1000

void CMainFrame::RefreshOtherVesselPositions(char* msg)
{  

	int otherVesselCount = m_yimaEncCtrl.GetOtherVesselCount();
	int iRoutesCount = m_yimaEncCtrl.GetRoutesCount() - 1;//本船不算，所以要减去1
	if(otherVesselCount < iRoutesCount)
	{
		iRoutesCount = otherVesselCount;
	}

	int vsNum = 0;
	for (vsNum = 0; vsNum < iRoutesCount; vsNum ++)//模拟航线的船舶
	{
		long m_pRetWayPointIDs[ROUTE_WAY_POINTS_MAX_COUNT];
		BSTR bstrWpIDs = ::SysAllocStringLen(NULL, ROUTE_WAY_POINTS_MAX_COUNT * 2);

		int wpCount = m_yimaEncCtrl.GetRouteWayPointsID(m_nOtherVesselSelRouteIDs[vsNum], 
			&bstrWpIDs);	

		
		memcpy(m_pRetWayPointIDs, bstrWpIDs, wpCount * sizeof(int));
		SysFreeString(bstrWpIDs); 
		
		//得到未刷新前的船的位置，航向，并由此得到当前本船的位置
		long lLastOwnShipGeoPoX, lLastOwnShipGeoPoY;
		float fHeading, fCourseOverGround, fCourseThrghWater;
		float fSpeedOverGround, fSpeedThrghWater; 
		BOOL bArpaOrAisTarget = false;
		long lTime = 0;
		BSTR pExtAttrs =  ::SysAllocStringLen(NULL, 10);
		m_yimaEncCtrl.GetOtherVesselCurrentInfo(vsNum, &bArpaOrAisTarget, 
			&lLastOwnShipGeoPoX, 
			&lLastOwnShipGeoPoY, &fHeading, &fCourseOverGround, &fCourseThrghWater, 
			&fSpeedOverGround, &fSpeedThrghWater,&lTime, &pExtAttrs); 
		
		long lAimWayPointGeoPoX, lAimWayPointGeoPoY; 
		m_yimaEncCtrl.GetWayPointCoor(m_pRetWayPointIDs[m_nOtherVesselCurAimWpPos[vsNum]], 
			&lAimWayPointGeoPoX, &lAimWayPointGeoPoY);	 

		double dbOwnShipRightCourse = m_yimaEncCtrl.GetBearingBetwTwoPoint(
			lLastOwnShipGeoPoX, lLastOwnShipGeoPoY, 
			lAimWayPointGeoPoX, lAimWayPointGeoPoY);
		
		//计算出本船当前应当在的位置
		long lCurrentOwnShipGeoPoX, lCurrentOwnShipGeoPoY; 	
		double fShipTimeStepDistByNm = //定时器单位时间间隔本船可航行距离, 单位为海里
			((double)m_nOtherVesselSimulateSpeeds[vsNum] / 3600) * ((double)m_nTimerStep / 1000);
	
		m_yimaEncCtrl.GetDesPointOfCrsAndDist(
			lLastOwnShipGeoPoX, lLastOwnShipGeoPoY,
			fShipTimeStepDistByNm, 
			dbOwnShipRightCourse,
			&lCurrentOwnShipGeoPoX, 
			&lCurrentOwnShipGeoPoY); 
		
		//如果到达目标航路点，则当前航路点位置加1	
		long lCurrentRouteWayPointCount = m_yimaEncCtrl.GetRouteWayPointsCount(
			m_nOtherVesselSelRouteIDs[vsNum]);

		double dbNewCourse = dbOwnShipRightCourse;
		if ( m_yimaEncCtrl.GetDistBetwTwoPoint (lCurrentOwnShipGeoPoX, lCurrentOwnShipGeoPoY, 
			lAimWayPointGeoPoX, lAimWayPointGeoPoY ) <= fShipTimeStepDistByNm )
		{
			m_nOtherVesselCurAimWpPos[vsNum] += 1;  
			
			//如果到达最后一个航路点，则从头开始循环模拟航行
			if (m_nOtherVesselCurAimWpPos[vsNum] == lCurrentRouteWayPointCount)
			{
				m_nOtherVesselCurAimWpPos[vsNum] = 0; 
			}
		}  
		m_yimaEncCtrl.SetOtherVesselCurrentInfo(vsNum,
			lCurrentOwnShipGeoPoX, lCurrentOwnShipGeoPoY, 
			dbNewCourse, dbNewCourse, dbNewCourse,
			m_nOtherVesselSimulateSpeeds[vsNum], 
			m_nOtherVesselSimulateSpeeds[vsNum], NULL, NULL, NULL); 
		SysFreeString(pExtAttrs);
	}

	
	for (; vsNum < otherVesselCount; vsNum ++)//模拟其它的船舶
	{
		BOOL bArpaOrAis = FALSE;
		long geoPoX = 0;
		long geoPoY = 0;
		float heading = 0;
		float courseOverGround = 0;
		float courseThrghWater = 0;
		float speedOverGround = 0;
		float speedThrghWater = 0;
		bool bResult = m_yimaEncCtrl.GetOtherVesselCurrentInfo(vsNum,&bArpaOrAis,&geoPoX,&geoPoY,&heading,&courseOverGround,&courseThrghWater,&speedOverGround,&speedThrghWater, NULL, NULL);

		if(bResult)//计算模拟数据
		{
			double curHeading = heading;
#define MAX_RAND_VAL 32767
			float iAddGeoLen = (float)(rand() % MAX_RAND_VAL)/MAX_RAND_VAL * 100000;

			int iRandNum = (int)(rand() % MAX_RAND_VAL)/MAX_RAND_VAL * 10;
			int curShipId = m_yimaEncCtrl.GetOtherVesselID(vsNum);
			if(curShipId != m_testDcpaShipId)//测试避碰报警的船舶航向不变
			{
				if(iRandNum % 2 == 0)
				{
					curHeading += 3;
				}
				else
				{
					curHeading -= 1;
				}
			}
			else
			{
				iAddGeoLen = 1000.0f * m_nTimerStep / 1000;//测试避碰报警的目标船舶航行距离保持不变
			}

            float angle = (float)((90 - curHeading) * PI / 180);
			long curGeoPoX = geoPoX + cos(angle) * iAddGeoLen;
			long curGeoPoY = geoPoY + sin(angle) * iAddGeoLen;

			if(curGeoPoX < 1100000000 || curGeoPoX > 1500000000 || curGeoPoY < 100000000 || curGeoPoY > 500000000)
			{
				curHeading = (float)(rand() % MAX_RAND_VAL)/MAX_RAND_VAL * 360;
			}
			m_yimaEncCtrl.SetOtherVesselCurrentInfo(vsNum,curGeoPoX,curGeoPoY,curHeading,90,90,speedOverGround,speedThrghWater, NULL, NULL, NULL);

			if(curShipId == m_testDcpaShipId)
			{
				float dis = m_yimaEncCtrl.GetDistBetwTwoPoint(geoPoX, geoPoY, curGeoPoX, curGeoPoY);
				float speedTestShip = dis * 3600 / ((float)m_nTimerStep / 1000);

				float fDcpa, fTcpa;   
				m_yimaEncCtrl.GetTwoShipsDcpaAndTcpa(m_CurrOwnShipGeoPo.x, m_CurrOwnShipGeoPo.y, m_nOwnShipCurrentSpeed, m_curOwnShipCourse, curGeoPoX, curGeoPoY, speedTestShip, curHeading, &fDcpa, &fTcpa);
				if((fTcpa < g_fTcpaDoor) && ((fDcpa * 1852) < g_fDcpaDoor))
				{ 
					sprintf(msg, "%s \n本船将在%f秒后与目标船最近, 最近距离%f米，可能发生碰撞!", msg, fTcpa, fDcpa * 1852);
				} 
			}
		
		}	
	}
}

void CMainFrame::RefreshOtherVesselList()
{  
	m_wndNavigationDlgBar.RefreshVesselList(); 
}

void CMainFrame::RefreshNavBarRadarList()		//19-4
{
	m_wndNavigationDlgBar.RefreshRadarList();
}

void CMainFrame::RefreshNavBarRouteList()
{  
	m_wndNavigationDlgBar.RefreshRouteList(); 
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE; 
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
 

#define MAX_VCF_LAYER_COUNT 100

void CMainFrame::OnShowAllInfo() 
{
	// TODO: Add your command handler code here
	UncheckAllDsplyCategoryMenu();		
	
	CMenu *pMenu = GetMenu();		
	if (pMenu != NULL)
	{
		pMenu->CheckMenuItem(ID_SHOW_ALL_INFO, MF_CHECKED);
	}
	
	m_yimaEncCtrl.SetDisplayCategory(DISPLAY_ALL);	 
	for(int icurPos = 0; icurPos < MAX_VCF_LAYER_COUNT;icurPos ++)
	{
		m_yimaEncCtrl.SetVcfLayerDrawOrNot(icurPos, true);	    
	}
	
	RedrawView();
}

void CMainFrame::OnShowStandardInfo() 
{
	// TODO: Add your command handler code here
	UncheckAllDsplyCategoryMenu();		
	
	CMenu *pMenu = GetMenu();		
	if (pMenu != NULL)
	{
		pMenu->CheckMenuItem(ID_SHOW_STANDARD_INFO, MF_CHECKED);
	}
	
	m_yimaEncCtrl.SetDisplayCategory(DISPLAY_STANDARD); 
	for(int icurPos = 0; icurPos < MAX_VCF_LAYER_COUNT;icurPos ++)
	{
		m_yimaEncCtrl.SetVcfLayerDrawOrNot(icurPos, true);	    
	}
	int arrShowLayerPos[6] = {8, 38, 21, 30, 45, 39};
	for(int i = 0; i < 6; i++)
	{									
		m_yimaEncCtrl.SetVcfLayerDrawOrNot(arrShowLayerPos[i], false);   
	} 
	RedrawView();
}		   
void CMainFrame::OnShowBaseInfo() 
{
	// TODO: Add your command handler code here
	UncheckAllDsplyCategoryMenu();		
	
	CMenu *pMenu = GetMenu();		
	if (pMenu != NULL)
	{
		pMenu->CheckMenuItem(ID_SHOW_BASE_INFO, MF_CHECKED);
	}
	
	m_yimaEncCtrl.SetDisplayCategory(DISPLAY_BASE);
	for(int icurPos = 0; icurPos < MAX_VCF_LAYER_COUNT;icurPos ++)
	{
		m_yimaEncCtrl.SetVcfLayerDrawOrNot(icurPos, false);	    
	}
	int arrShowLayerPos[2] = {2, 18};
	for(int i = 0; i < 2; i++)
	{									
		m_yimaEncCtrl.SetVcfLayerDrawOrNot(arrShowLayerPos[i], true);   
	}    
	RedrawView();
}

void CMainFrame::OnColorDayBright() 
{
	// TODO: Add your command handler code here
	UncheckAllEncColorMenu(); 
	
	CMenu *pMenu = GetMenu();		
	if (pMenu != NULL)
	{
		pMenu->CheckMenuItem(ID_COLOR_DAY_BRIGHT, MF_CHECKED);
	}
	
	m_yimaEncCtrl.SetColorModel(DAY_BRIGHT);
	
	RedrawView();
}

void CMainFrame::OnColorDayWhiteback() 
{
	// TODO: Add your command handler code here
	UncheckAllEncColorMenu(); 
	
	CMenu *pMenu = GetMenu();		
	if (pMenu != NULL)
	{
		pMenu->CheckMenuItem(ID_COLOR_DAY_WHITEBACK, MF_CHECKED);
	}
	
	m_yimaEncCtrl.SetColorModel(DAY_WHITEBACK);
	
	RedrawView();
}

void CMainFrame::OnColorDayBlackback() 
{
	// TODO: Add your command handler code here
	UncheckAllEncColorMenu(); 
	
	CMenu *pMenu = GetMenu();		
	if (pMenu != NULL)
	{
		pMenu->CheckMenuItem(ID_COLOR_DAY_BLACKBACK, MF_CHECKED);
	}
	
	m_yimaEncCtrl.SetColorModel(DAY_BLACKBACK);
	
	RedrawView();
}

void CMainFrame::OnColorDayDusk() 
{
	// TODO: Add your command handler code here
	UncheckAllEncColorMenu(); 
	
	CMenu *pMenu = GetMenu();		
	if (pMenu != NULL)
	{
		pMenu->CheckMenuItem(ID_COLOR_DAY_DUSK, MF_CHECKED);
	}
	
	m_yimaEncCtrl.SetColorModel(DUSK);
	
	RedrawView();
}

void CMainFrame::OnColorNight() 
{
	// TODO: Add your command handler code here
	UncheckAllEncColorMenu(); 
	
	CMenu *pMenu = GetMenu();		
	if(pMenu != NULL)
	{
		pMenu->CheckMenuItem(ID_COLOR_NIGHT, MF_CHECKED);
	}
	
	m_yimaEncCtrl.SetColorModel(NIGHT);
	
	RedrawView();
}

void CMainFrame::OnTranditionSymbolCheck() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu = GetMenu();		
	if (pMenu != NULL)
	{
		pMenu->CheckMenuItem(ID_SIMPLE_SYMBOL_CHECK, MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_TRANDITION_SYMBOL_CHECK, MF_CHECKED);
	}
	
	m_yimaEncCtrl.SetUseSmpSymbolOrNot(false); 
	m_yimaEncCtrl.SetUsePlainBndryOrNot(false);
	
	RedrawView();
}

void CMainFrame::OnSimpleSymbolCheck() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu = GetMenu();		
	if (pMenu != NULL)
	{
    	pMenu->CheckMenuItem(ID_SIMPLE_SYMBOL_CHECK, MF_CHECKED);
		pMenu->CheckMenuItem(ID_TRANDITION_SYMBOL_CHECK, MF_UNCHECKED);
	}
	
	m_yimaEncCtrl.SetUseSmpSymbolOrNot(true); 
	m_yimaEncCtrl.SetUsePlainBndryOrNot(true);
	
	RedrawView();
}

void CMainFrame::OnSymbolBndryCheck() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu = GetMenu();		
	if (pMenu != NULL)
	{
		pMenu->CheckMenuItem(ID_SYMBOL_BNDRY_CHECK, MF_CHECKED);
		pMenu->CheckMenuItem(ID_PLAIN_BNDRY_CHECK, MF_UNCHECKED);
	}

	m_yimaEncCtrl.SetUsePlainBndryOrNot(false); 
	
	RedrawView();
}

void CMainFrame::OnPlainBndryCheck() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu = GetMenu();		
	if (pMenu != NULL)
	{
		pMenu->CheckMenuItem(ID_SYMBOL_BNDRY_CHECK, MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_PLAIN_BNDRY_CHECK, MF_CHECKED);
	}

	m_yimaEncCtrl.SetUsePlainBndryOrNot(true); 
	
	RedrawView();
}

void CMainFrame::OnSafetyContour() 
{
	// TODO: Add your command handler code here
	CSetSafeContourDlg safeContourDlg;
	BOOL bTwoOrFourDepthShade;
	float safeDepth, shallowDepth, deepDepth;
	m_yimaEncCtrl.GetDepthShadesMode(&bTwoOrFourDepthShade, &shallowDepth, &safeDepth, &deepDepth);
	safeContourDlg.m_bTwoOrFourDepthShades = bTwoOrFourDepthShade;
	safeContourDlg.m_fShallowDepth = shallowDepth;
	safeContourDlg.m_fSafeCont = m_yimaEncCtrl.GetSafetyDepth();
	safeContourDlg.m_fDeepDepth = deepDepth;
 
	if (IDOK == safeContourDlg.DoModal())
	{ 
		m_yimaEncCtrl.SetSafetyDepth(safeContourDlg.m_fSafeCont);
		m_yimaEncCtrl.SetDepthShadesMode(safeContourDlg.m_bTwoOrFourDepthShades, safeContourDlg.m_fShallowDepth, 
			safeContourDlg.m_fSafeCont, safeContourDlg.m_fDeepDepth);
		RedrawView();
	}
}

void CMainFrame::OnSetLangEng() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu = GetMenu();		
	if (pMenu != NULL)
	{
		pMenu->CheckMenuItem(ID_SET_LANG_ENG, MF_CHECKED);
		pMenu->CheckMenuItem(ID_SET_LANG_CHN, MF_UNCHECKED);
	}

	m_yimaEncCtrl.SetLanguage(true); 
	m_yimaEncCtrl.ReInitMapMan(_T("JIANGTU"));
	
	RedrawView();
}

void CMainFrame::UncheckAllEncColorMenu()
{
	CMenu *pMenu = GetMenu();

	if (pMenu != NULL)
	{
		pMenu->CheckMenuItem(ID_COLOR_DAY_BRIGHT, MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_COLOR_DAY_WHITEBACK, MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_COLOR_DAY_BLACKBACK, MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_COLOR_DAY_DUSK, MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_COLOR_NIGHT, MF_UNCHECKED);
	}
}

void CMainFrame::RedrawView()
{
    CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView();
	if (pView != NULL)
		pView->RefreshScreenMap(); 
}

void CMainFrame::SetOperationStatusBarText(CString reportText)
{
	CStatusBar* pStatusBar = (CStatusBar *)GetDescendantWindow(AFX_IDW_STATUS_BAR);
	if (pStatusBar != NULL && reportText != "")
	{
		pStatusBar->SetPaneText(0, reportText);
	}
}

void CMainFrame::UncheckAllDsplyCategoryMenu()
{
	CMenu *pMenu = GetMenu();

	if (pMenu != NULL)
	{
		pMenu->CheckMenuItem(ID_SHOW_BASE_INFO, MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_SHOW_STANDARD_INFO, MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_SHOW_ALL_INFO, MF_UNCHECKED);
	}
}

void CMainFrame::OnSetLangChn() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu = GetMenu();		
	if (pMenu != NULL)
	{
		pMenu->CheckMenuItem(ID_SET_LANG_ENG, MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_SET_LANG_CHN, MF_CHECKED);
	}

	m_yimaEncCtrl.SetLanguage(false); 
	m_yimaEncCtrl.ReInitMapMan(_T(""));
	
	RedrawView();
}

void CMainFrame::OnSetScale() 
{
	// TODO: Add your command handler code here

	CSetScaleDlg setScaleDlg;

	setScaleDlg.m_iScale = m_yimaEncCtrl.GetCurrentScale();
	setScaleDlg.DoModal();
	
	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView();
	if (pView != NULL)
		pView->RefreshScaleStatusBar();
} 

void CMainFrame::OnMapLibMan() 
{
	// TODO: Add your command handler code here
	CMapLibInfoDlg mapLibDlg;
	mapLibDlg.DoModal();
} 

void CMainFrame::UncheckMenusAndToolBarForMenuItem(UINT menuID)
{
	CMenu *pMenu = GetMenu();		
	CToolBar* pToolBar = (CToolBar*)GetDescendantWindow(AFX_IDW_TOOLBAR);	  

	if (pMenu != NULL && pToolBar != NULL)
	{ 
		pMenu->CheckMenuItem(menuID, MF_UNCHECKED); 
		pToolBar->GetToolBarCtrl().PressButton(menuID, false); 
	}
}

void CMainFrame::UncheckMenusAndToolBar()
{
	CMenu *pMenu = GetMenu();		
	CToolBar* pToolBar = (CToolBar*)GetDescendantWindow(AFX_IDW_TOOLBAR);	  

	if (pMenu != NULL && pToolBar!=NULL)
	{  
		pMenu->CheckMenuItem(ID_AREA_ZOOM_IN, MF_UNCHECKED); 
		pToolBar->GetToolBarCtrl().PressButton(ID_AREA_ZOOM_IN, false); 
	}
}

void CMainFrame::OnLayersMan() 
{
	// TODO: Add your command handler code here
	CLayerManDlg layerManDlg;
	layerManDlg.DoModal();
}

void CMainFrame::OnRadar() 
{
	// TODO: Add your command handler code here
	
	CMenu *pMenu = GetMenu();
	if (pMenu == NULL)
		return; 

	if (m_yimaEncCtrl.GetDrawRadarOrNot())
	{		
		pMenu->CheckMenuItem(ID_RADAR, MF_UNCHECKED);
		m_yimaEncCtrl.SetIfOnDrawRadarMode(false);
		m_yimaEncCtrl.SetDrawRadarOrNot(false);
	}
	else
	{ 
		pMenu->CheckMenuItem(ID_RADAR, MF_CHECKED);
		m_yimaEncCtrl.SetDrawRadarOrNot(true);
		m_yimaEncCtrl.SetIfUseGDIPlus(false);
		m_yimaEncCtrl.SetIfOnDrawRadarMode(true);
	}

	RedrawView(); 
} 

void CMainFrame::OnTimer(UINT nIDEvent) 
{    
	// TODO: Add your message handler code here and/or call default   
	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView();
	if (pView != NULL)
	{
		if (pView->IsOnDragingObjectOperation())
		{
			return;
		}
		char chMsg[255];
		memset(chMsg,'\0', 255); 
		RefreshNavigationDlgBar(chMsg);
		RefreshOtherVesselPositions(chMsg);
		
		/* 动态提示框注释 --- 注意如果当前正在显示动态提示框, 则不能刷新屏幕, 否则动态框被刷掉了 */
		if (!pView->IsOnOperation(HAND_ROAM) && !pView->IsOnOperation(SHOWING_HINT_TEXT) && !pView->bMouseWheelState)
		{
			pView->Invalidate(); 
		}
		if(strlen(chMsg) > 0)
		{
			AfxMessageBox(chMsg);
		}
	}
	
    CFrameWnd::OnTimer(nIDEvent);	
}

bool CMainFrame::SetOwnShipStartOnRoute(long routeID)
{
	bool bResult = false;

	long rtWpCount = m_yimaEncCtrl.GetRouteWayPointsCount(routeID);
	long routeWpIDs[ROUTE_WAY_POINTS_MAX_COUNT];
	
	BSTR bstrWpIDs = ::SysAllocStringLen(NULL, ROUTE_WAY_POINTS_MAX_COUNT * 2);	
	int wpCount = m_yimaEncCtrl.GetRouteWayPointsID(routeID, &bstrWpIDs);		
	memcpy(routeWpIDs, bstrWpIDs, wpCount * sizeof(int));
	SysFreeString(bstrWpIDs); 
	
	if (wpCount > 0)
	{ 
		m_yimaEncCtrl.SetRouteBePlannedOrAlternated(routeID, true, true); //先设置航线，再设置船舶位置
		M_POINT frstWpGeoPoint, scndWpGeoPoint; 
		
		m_yimaEncCtrl.GetWayPointCoor(
			routeWpIDs[0], (long*)&frstWpGeoPoint.x, (long*)&frstWpGeoPoint.y);
		
		m_yimaEncCtrl.GetWayPointCoor(
			routeWpIDs[1], (long*)&scndWpGeoPoint.x, (long*)&scndWpGeoPoint.y); 
		  
		double ownShipCourse = m_yimaEncCtrl.GetBearingBetwTwoPoint(
			frstWpGeoPoint.x, frstWpGeoPoint.y, 
			scndWpGeoPoint.x, scndWpGeoPoint.y);
		
		m_yimaEncCtrl.SetOwnShipCurrentInfo(
			frstWpGeoPoint.x, frstWpGeoPoint.y, ownShipCourse, 
			ownShipCourse, ownShipCourse, 
			m_nOwnShipCurrentSpeed, m_nOwnShipCurrentSpeed);

		if (m_bHeadUpModel)
		{
			m_yimaEncCtrl.CenterMap(frstWpGeoPoint.x, frstWpGeoPoint.y);
			m_yimaEncCtrl.RotateMapByScrnCenter(- ownShipCourse);
		} 

		m_nOwnShipSelectRouteID = routeID;
		//m_nAimWayPointPosInRoute = 1;

		bResult = true;
	}

	return bResult;
}

bool CMainFrame::SetOtherVesselStartOnRoute(int otherVslPos, long routeID)
{ 
	bool bResult = false;

	long rtWpCount = m_yimaEncCtrl.GetRouteWayPointsCount(routeID);
	long routeWpIDs[ROUTE_WAY_POINTS_MAX_COUNT];

	BSTR bstrWpIDs = ::SysAllocStringLen(NULL, ROUTE_WAY_POINTS_MAX_COUNT * 2);	
	int wpCount = m_yimaEncCtrl.GetRouteWayPointsID(routeID, &bstrWpIDs);		
	memcpy(routeWpIDs, bstrWpIDs, wpCount * sizeof(int));
	SysFreeString(bstrWpIDs); 

	if (wpCount > 0)
	{
		M_POINT frstWpGeoPoint, scndWpGeoPoint; 
		
		m_yimaEncCtrl.GetWayPointCoor(
			routeWpIDs[0], (long*)&frstWpGeoPoint.x, (long*)&frstWpGeoPoint.y);
		
		m_yimaEncCtrl.GetWayPointCoor(
			routeWpIDs[1], (long*)&scndWpGeoPoint.x, (long*)&scndWpGeoPoint.y); 
		  
		double shipCourse = m_yimaEncCtrl.GetBearingBetwTwoPoint(
			frstWpGeoPoint.x, frstWpGeoPoint.y, 
			scndWpGeoPoint.x, scndWpGeoPoint.y); 

		m_yimaEncCtrl.SetOtherVesselCurrentInfo(otherVslPos,
			frstWpGeoPoint.x, frstWpGeoPoint.y, shipCourse, 
			shipCourse, shipCourse, 
			m_nOtherVesselSimulateSpeeds[otherVslPos], 
			m_nOtherVesselSimulateSpeeds[otherVslPos],NULL, NULL, NULL);  

		m_nOtherVesselCurAimWpPos[otherVslPos] = 1;

		bResult = true;
	}

	return bResult;
}

#define SIMULATE_AIM_OFFROUTE_WP_POS 2
#define SIMULATE_OFFROUTE_TIMER_COUNT_MAX 10

double determinant(double v1, double v2, double v3, double v4)  // 行列式
{
	return (v1*v4-v2*v3);
}

bool intersect(M_POINT aa, M_POINT bb, M_POINT cc, M_POINT dd)
{
	double delta = determinant(bb.x-aa.x, cc.x-dd.x, bb.y-aa.y, cc.y-dd.y);
	if ( delta<=(1e-6) && delta>=-(1e-6) )  // delta=0，表示两线段重合或平行
	{
		return false;
	}
	double namenda = determinant(cc.x-aa.x, cc.x-dd.x, cc.y-aa.y, cc.y-dd.y) / delta;
	if ( namenda>1 || namenda<0 )
	{
		return false;
	}
	double miu = determinant(bb.x-aa.x, cc.x-aa.x, bb.y-aa.y, cc.y-aa.y) / delta;
	if ( miu>1 || miu<0 )
	{
		return false;
	}
	return true;
}

void CMainFrame::RefreshNavigationDlgBar(char* chMsg)
{ 
	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView();
 
 
	//得到未刷新前的船的位置，航向，并由此得到当前本船的位置
	long lLastOwnShipGeoPoX, lLastOwnShipGeoPoY;
	float fHeading, fCourseOverGround, fCourseThrghWater;
	float fSpeedOverGround, fSpeedThrghWater; 
	m_yimaEncCtrl.GetOwnShipCurrentInfo(&lLastOwnShipGeoPoX, 
			&lLastOwnShipGeoPoY, &fHeading, &fCourseOverGround, &fCourseThrghWater, 
			&fSpeedOverGround, &fSpeedThrghWater); 

	long lAimWayPointGeoPoX, lAimWayPointGeoPoY;//下一个航路点位置
	m_yimaEncCtrl.GetCurrentAimPoint(&lAimWayPointGeoPoX, &lAimWayPointGeoPoY); 

	double dbOwnShipRightCourse = m_yimaEncCtrl.GetBearingBetwTwoPoint(
			lLastOwnShipGeoPoX, lLastOwnShipGeoPoY, 
			lAimWayPointGeoPoX, lAimWayPointGeoPoY);//获取模拟航行航向(上一个航路点与下一个航路点的方位)

	static int refreshTimes = 0;
	refreshTimes ++;
	if(refreshTimes >= 100)
	{
		//每运动100次，模拟出偏离航线一次
		dbOwnShipRightCourse += 90;
		//m_nOffRouteSimulateTimerCount ++;
		refreshTimes = 0;
	} 

	//计算出本船当前应当在的位置
	long lCurrentOwnShipGeoPoX, lCurrentOwnShipGeoPoY; 	
	double fShipTimeStepDistByNm =
		((double)m_nOwnShipCurrentSpeed / 3600) * ((double)m_nTimerStep / 1000); //定时器单位时间间隔本船可航行距离, 单位为海里
	
	//计算本船现在的新位置
	m_yimaEncCtrl.GetDesPointOfCrsAndDist(
			lLastOwnShipGeoPoX, lLastOwnShipGeoPoY,
			fShipTimeStepDistByNm, 
			dbOwnShipRightCourse,
			&lCurrentOwnShipGeoPoX, 
			&lCurrentOwnShipGeoPoY); 



	int barRight = 210;
	int barLeft = 5;
    /* 报警信息显示 */
	int nOrigintop = 300, nOriginBottom = nOrigintop + 25;	
	//m_wndNavigationDlgBar.RefreshAlarmBar(barLeft, nOrigintop, barRight,nOriginBottom, RGB(0, 255, 0));
	//m_wndNavigationDlgBar.RefreshAlarmBar(barLeft, nOrigintop + 30,barRight, nOriginBottom + 30, RGB(0, 255, 0));
	//m_wndNavigationDlgBar.RefreshAlarmBar(barLeft, nOrigintop + 60,barRight, nOriginBottom + 60, RGB(0, 255, 0));
	
	int nNavigationInfoCharSize = 14;
	CString strNavigationInfoFont = "宋体";
	float offMeter = 0;
	//if (m_yimaEncCtrl.IsShipOffRoute(lCurrentOwnShipGeoPoX, lCurrentOwnShipGeoPoY, m_nOwnShipSelectRouteID, m_offRouteDistDoor))
	if (m_yimaEncCtrl.IsOwnShipOffRoute(m_offRouteDistDoor, &offMeter))
	{ 
		if (m_bAlarmColorFlag)
		{
			//m_wndNavigationDlgBar.RefreshAlarmBar(barLeft, nOrigintop, barRight, nOriginBottom, RGB(255, 0, 0)); 
		} 
		CString strOffRouteTip;
		strOffRouteTip.Format(_T("偏离航线%.2f米"),offMeter);
		//m_wndNavigationDlgBar.ShowNavigationInfoText(45, nOrigintop + 5, strOffRouteTip, nNavigationInfoCharSize, strNavigationInfoFont); 
	}
	
	if (m_yimaEncCtrl.IsShipCrossingSafetyContour(lCurrentOwnShipGeoPoX, 
	    	lCurrentOwnShipGeoPoY, fCourseOverGround, 
	    	m_safeContourDistDoor))
	{ 
		if (m_bAlarmColorFlag)
		{
			//m_wndNavigationDlgBar.RefreshAlarmBar(barLeft, nOrigintop + 30, barRight, nOriginBottom + 30, RGB(255, 0, 0)); 
		}

		//m_wndNavigationDlgBar.ShowNavigationInfoText(45, nOrigintop + 30 + 5, "靠近安全等深线", nNavigationInfoCharSize, strNavigationInfoFont); 
	}
	float fcurDepth = m_yimaEncCtrl.GetSoundingDepthByGeoPo(lCurrentOwnShipGeoPoX, lCurrentOwnShipGeoPoY,10); 
	CString strCurDepthTip;
	if (fcurDepth >= m_deepDepthDoor)
	{ 
		strCurDepthTip.Format(_T("当前水深%.2f米(超深)"),fcurDepth);
		if (m_bAlarmColorFlag)
		{
			//m_wndNavigationDlgBar.RefreshAlarmBar(barLeft, nOrigintop + 30, barRight, nOriginBottom + 30, RGB(255, 0, 0)); 
		}
		 
	}
	else if (fcurDepth <= m_shallowDepthDoor)
	{ 
		strCurDepthTip.Format(_T("当前水深%.2f米(超浅)"),fcurDepth); 
		if (m_bAlarmColorFlag)
		{
			//m_wndNavigationDlgBar.RefreshAlarmBar(barLeft, nOrigintop + 30, barRight, nOriginBottom + 30, RGB(255, 0, 0)); 
		} 
	}
	else
	{
		strCurDepthTip.Format(_T("当前水深%.2f米"),fcurDepth); 
	}
	

	//m_wndNavigationDlgBar.ShowNavigationInfoText(45, nOrigintop + 30 + 5, strCurDepthTip, nNavigationInfoCharSize, strNavigationInfoFont);
	
	long retObjMapPos, retObjLayerPos, retObjInnerLayerPos;
	retObjMapPos = retObjLayerPos = retObjInnerLayerPos = -1;
	if (m_yimaEncCtrl.IsShipApproachingIsolatedDanger(lCurrentOwnShipGeoPoX, 
		lCurrentOwnShipGeoPoY, m_isoDangerDistDoor, &retObjMapPos, &retObjLayerPos, &retObjInnerLayerPos))
	{
		if (m_bAlarmColorFlag)
		{
			//m_wndNavigationDlgBar.RefreshAlarmBar(barLeft, nOrigintop + 60, barRight, nOriginBottom + 60, RGB(255, 0, 0)); 
		} 

		//m_wndNavigationDlgBar.ShowNavigationInfoText(45, nOrigintop + 60 + 5, "靠近孤立危险点", nNavigationInfoCharSize, strNavigationInfoFont);  
	}
				
	m_bAlarmColorFlag = !m_bAlarmColorFlag; 
		
	//显示位置，航速，航向信息
	int contentBarRight = 210;
	int contentBarLeft = 10;
	//m_wndNavigationDlgBar.ClearDlgContents(contentBarLeft, 30, contentBarRight, 130);   //清空对话框"位置"区域
	//m_wndNavigationDlgBar.ClearDlgContents(contentBarLeft, 175, contentBarRight, 205);  //清空对话框"航速"区域
	//m_wndNavigationDlgBar.ClearDlgContents(contentBarLeft, 230, contentBarRight, 260);  //清空对话框"航向"区域

	TCHAR strPosition[100]; 
	long iGeoCoorMultiFactor = m_yimaEncCtrl.GetGeoCoorMultiFactor();
	
	GetDegreeStringFromGeoCoor(strPosition, true, lCurrentOwnShipGeoPoX, iGeoCoorMultiFactor);
	CString strOwnShipPositionX = strPosition;
	//m_wndNavigationDlgBar.ShowNavigationInfoText(25, 40, strOwnShipPositionX, 24, "黑体"); 
	
	GetDegreeStringFromGeoCoor(strPosition, false, lCurrentOwnShipGeoPoY, iGeoCoorMultiFactor);
	CString strOwnShipPositionY = strPosition; 
	//m_wndNavigationDlgBar.ShowNavigationInfoText(25, 80, strOwnShipPositionY, 24, "黑体");
	
	CString strNavigationSpeed;
	strNavigationSpeed.Format("%d节", m_nOwnShipCurrentSpeed);		
	//m_wndNavigationDlgBar.ShowNavigationInfoText(45, 180, strNavigationSpeed, 24, "黑体");
	
	CString strNavigationCourse;
	strNavigationCourse.Format("%.2f度", fCourseOverGround);
	//m_wndNavigationDlgBar.ShowNavigationInfoText(45, 233, strNavigationCourse, 24, "黑体"); 
	    
	//如果处于"自动调整本船位置使其保持在屏幕中"的模式.
	if (m_bOnAutoCenterShipMode)
	{
		long lCurrentOwnShipScrnPoX, lCurrentOwnShipScrnPoY;
		m_yimaEncCtrl.GetScrnPoFromGeoPo (lCurrentOwnShipGeoPoX, lCurrentOwnShipGeoPoY, 
			&lCurrentOwnShipScrnPoX, &lCurrentOwnShipScrnPoY);
		
		RECT viewClientRect;
		pView->GetClientRect(&viewClientRect); 
		int disBetwOwnShipAndBoundary = 20;
		if ( ((lCurrentOwnShipScrnPoX - viewClientRect.left) < disBetwOwnShipAndBoundary ) ||
			 ((viewClientRect.right - lCurrentOwnShipScrnPoX) < disBetwOwnShipAndBoundary ) || 
			 ((lCurrentOwnShipScrnPoY - viewClientRect.top) < disBetwOwnShipAndBoundary ) || 
			 (( viewClientRect.bottom - lCurrentOwnShipScrnPoY) < disBetwOwnShipAndBoundary ))
		{//如果本船当前屏幕位置逼近窗口边界
			m_yimaEncCtrl.CenterMap( lCurrentOwnShipGeoPoX, lCurrentOwnShipGeoPoY);
		}
	}

	//如果到达目标航路点，则当前航路点位置加1	
	long lCurrentRouteWayPointCount = m_yimaEncCtrl.GetRouteWayPointsCount(m_nOwnShipSelectRouteID);
	double dbNewCourse = dbOwnShipRightCourse;


	long m_pRetWayPointIDs[ROUTE_WAY_POINTS_MAX_COUNT]; 
	BSTR bstrWpIDs = ::SysAllocStringLen(NULL, ROUTE_WAY_POINTS_MAX_COUNT * 2);	
	int wpCount = m_yimaEncCtrl.GetRouteWayPointsID(m_nOwnShipSelectRouteID, &bstrWpIDs);		
	memcpy(m_pRetWayPointIDs, bstrWpIDs, wpCount * sizeof(int));
	SysFreeString(bstrWpIDs);
	long lastAimPoX, lastAimPoY;  
	BOOL b1, bAlongOrBack;
	m_yimaEncCtrl.GetRouteBePlannedOrAlternated(m_nOwnShipSelectRouteID, &b1, &bAlongOrBack);
	if(bAlongOrBack)
	{
		m_yimaEncCtrl.GetWayPointCoor(m_pRetWayPointIDs[wpCount - 1], &lastAimPoX, &lastAimPoY);
	}
	else
	{
		m_yimaEncCtrl.GetWayPointCoor(m_pRetWayPointIDs[0], &lastAimPoX, &lastAimPoY);
	}

	if ( m_yimaEncCtrl.GetDistBetwTwoPoint(lCurrentOwnShipGeoPoX, lCurrentOwnShipGeoPoY, 
		lastAimPoX, lastAimPoY ) <= fShipTimeStepDistByNm )
	{ 
		//如果到达最后一个航路点，则反向模拟
		m_yimaEncCtrl.SetRouteBePlannedOrAlternated(m_nOwnShipSelectRouteID, TRUE, !bAlongOrBack); 
	} 

	m_yimaEncCtrl.SetOwnShipCurrentInfo(lCurrentOwnShipGeoPoX, lCurrentOwnShipGeoPoY, dbNewCourse, 
		dbNewCourse, dbNewCourse, m_nOwnShipCurrentSpeed, m_nOwnShipCurrentSpeed);


	m_CurrOwnShipGeoPo = M_POINT(lCurrentOwnShipGeoPoX, lCurrentOwnShipGeoPoY);
	m_curOwnShipCourse = dbNewCourse;
	if (m_bHeadUpModel)//船首向上模式
	{
		m_yimaEncCtrl.CenterMap(lCurrentOwnShipGeoPoX, lCurrentOwnShipGeoPoY);//设置中心点：海图以本船漫游移动	
		if(fabs(dbNewCourse) > 10 &&
		   fabs(fCourseOverGround - dbNewCourse) > 10)//设置船首向上模式
		{
			m_yimaEncCtrl.RotateMapByScrnCenter(-dbNewCourse);
		}
	}  

	if (pView->m_ClosedLineTestObj.layerPos != -1)
	{ 
		bool bHaveMsg = false; 
		int memMapPos = m_yimaEncCtrl.GetMemMapCount() - 1;
		long curdis = 0; 
		BOOL bPoInFaceOrOut = FALSE;
		long retNearestGeoPoX = 0;
		long retNearestGeoPoY = 0;
		bool bClosedLine = m_yimaEncCtrl.IsPointNearObjectEdge(memMapPos, pView->m_ClosedLineTestObj.layerPos, pView->m_ClosedLineTestObj.innerLayerObjectPos, 
			lCurrentOwnShipGeoPoX, lCurrentOwnShipGeoPoY, m_safeContourDistDoor, &curdis, &bPoInFaceOrOut, &retNearestGeoPoX, &retNearestGeoPoY);
		if(bClosedLine)
		{
			sprintf(chMsg, "船舶近线报警,距离%d 米", curdis);
			bHaveMsg = true;
		}
		//过线报警
		static M_POINT* linePlanePo = NULL;
		static int linePoCount = 0;
		static M_POINT oldShipPlanePo;
		if(linePlanePo == NULL)
		{
			MEM_GEO_OBJ_POS objPos(memMapPos, pView->m_ClosedLineTestObj.layerPos, pView->m_ClosedLineTestObj.innerLayerObjectPos);
			BSTR bstrObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));
			memcpy(bstrObjPos, &objPos, sizeof(MEM_GEO_OBJ_POS));

			M_POINT* lineGeoPo = NULL;
			linePoCount = m_yimaEncCtrl.GetLineObjectCoorCount(&bstrObjPos);
			lineGeoPo = new M_POINT[linePoCount];
			BSTR bstrLineGeoPo = ::SysAllocStringLen(NULL, sizeof(M_POINT) * linePoCount);
			m_yimaEncCtrl.GetLineObjectCoors(&bstrObjPos, &bstrLineGeoPo);
			memcpy(lineGeoPo, bstrLineGeoPo, sizeof(M_POINT) * linePoCount);

			linePlanePo = new M_POINT[linePoCount];
			for(int i= 0; i < linePoCount; i++)
			{
				m_yimaEncCtrl.GetPlaneCoorFromGeoCoor(lineGeoPo[i].x, lineGeoPo[i].y, (long*)&linePlanePo[i].x, (long*)&linePlanePo[i].y);
			}
			delete[]lineGeoPo;
			m_yimaEncCtrl.GetPlaneCoorFromGeoCoor(lCurrentOwnShipGeoPoX, lCurrentOwnShipGeoPoY,(long*)&oldShipPlanePo.x, (long*)&oldShipPlanePo.y);
			SysFreeString(bstrObjPos);
			SysFreeString(bstrLineGeoPo);

		}
		M_POINT curShipPlanePo;
		m_yimaEncCtrl.GetPlaneCoorFromGeoCoor(lCurrentOwnShipGeoPoX, lCurrentOwnShipGeoPoY, (long*)&curShipPlanePo.x, (long*)&curShipPlanePo.y);
		if(!(oldShipPlanePo == curShipPlanePo))
		{
			for(int i = 0; i < linePoCount - 1; i ++)
			{
				if(intersect(oldShipPlanePo, curShipPlanePo, linePlanePo[i], linePlanePo[i + 1]))
				{
					sprintf(chMsg, "%s \n船舶过线报警", chMsg);
					bHaveMsg = true;
					continue;
				}
			}
			oldShipPlanePo = curShipPlanePo;
		}  
	}
}

void CMainFrame::OnStopAutoCenterShip() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu = GetMenu();	
 
	if (pMenu != NULL)
	{
		if (!m_bOnAutoCenterShipMode)
		{
			pMenu->CheckMenuItem(ID_AUTO_CENTER_SHIP, MF_CHECKED);
		}
		else
		{
			pMenu->CheckMenuItem(ID_AUTO_CENTER_SHIP, MF_UNCHECKED);
		} 
		
		m_bOnAutoCenterShipMode = !m_bOnAutoCenterShipMode;
	}
}
 

void CMainFrame::OnRouteEditMode() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu = GetMenu();			
	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView();
	
	if (pMenu != NULL)
	{
		if (!pView->m_bOnRouteEditMode)
		{
			pMenu->CheckMenuItem(ID_ROUTE_EDIT_MODE, MF_CHECKED); 
		}
		else
		{
			pMenu->CheckMenuItem(ID_ROUTE_EDIT_MODE, MF_UNCHECKED); 
		} 
		
		pView->m_bOnRouteEditMode = !pView->m_bOnRouteEditMode;
	}
} 

void CMainFrame::OnStopTimer() 
{
	// TODO: Add your command handler code here
	static bool bTimerOn = true;

	if (bTimerOn)
	{
		KillTimer(1);
	}
	else
	{
		SetTimer(1, m_nTimerStep, NULL);
	}
	
	bTimerOn = !bTimerOn;
}

void CMainFrame::OnSelcancelRouteList() 
{
	// TODO: Add your control notification handler code here
	
}

void CMainFrame::OnSetNavRouteButton() 
{
	// TODO: Add your control notification handler code here
	
}

void CMainFrame::OnAddVessel() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnHeadUp() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu = GetMenu();		 
	
	if (pMenu != NULL)
	{
		long lOwnShipGeoPoX, lOwnShipGeoPoY;
		float fHeading, fCourseOverGround, fCourseThrghWater;
		float fSpeedOverGround, fSpeedThrghWater; 

		m_yimaEncCtrl.GetOwnShipCurrentInfo(&lOwnShipGeoPoX, 
				&lOwnShipGeoPoY, &fHeading, &fCourseOverGround, &fCourseThrghWater, 
				&fSpeedOverGround, &fSpeedThrghWater); 

		m_yimaEncCtrl.CenterMap(lOwnShipGeoPoX, lOwnShipGeoPoY);	

		if (m_bHeadUpModel)
		{
			pMenu->CheckMenuItem(ID_HEAD_UP, MF_UNCHECKED);
			m_yimaEncCtrl.RotateMapByScrnCenter(0);
		}
		else
		{
			pMenu->CheckMenuItem(ID_HEAD_UP, MF_CHECKED);  

			if (fabs(fCourseOverGround) > 10)
			{ 
				m_yimaEncCtrl.RotateMapByScrnCenter(-fCourseOverGround);
			}
		} 
		
		m_bHeadUpModel = !m_bHeadUpModel;
	}
}

void CMainFrame::OnSaveRoutes() 
{
	// TODO: Add your command handler code here
	m_yimaEncCtrl.SaveRoutesToFile(TEST_ROUTE_FILE_NAME);
}

void CMainFrame::OnDelRouteBtn() 
{ 
	/* 需在 CMainFrame 中增加对CNavigationDlgBar中控件的响应，
	   该控件才有效，而 CMainFrame 中的这个响应可以为空，实际的
	   控件响应在 CNavigationDlgBar 中去完成 */
}

void CMainFrame::OnDirectEditRoute() 
{ 
	/* 需在 CMainFrame 中增加对CNavigationDlgBar中控件的响应，
	   该控件才有效，而 CMainFrame 中的这个响应可以为空，实际的
	   控件响应在 CNavigationDlgBar 中去完成 */
}

void CMainFrame::OnAlarmSetting() 
{
	// TODO: Add your command handler code here
	CAlarmSettingDlg alarmSettingDlg;

	alarmSettingDlg.m_isoDangerDistDoor = m_isoDangerDistDoor;
	alarmSettingDlg.m_safeContourDistDoor = m_safeContourDistDoor;
	alarmSettingDlg.m_offRouteDistDoor = m_offRouteDistDoor;
	alarmSettingDlg.m_fDeepDepthDoor = m_deepDepthDoor;
	alarmSettingDlg.m_fShallowDepthDoor = m_shallowDepthDoor;
	alarmSettingDlg.g_fDcpaDoor = g_fDcpaDoor;
	alarmSettingDlg.g_fTcpaDoor = g_fTcpaDoor;

	if (alarmSettingDlg.DoModal() == IDOK)
	{
		m_isoDangerDistDoor = alarmSettingDlg.m_isoDangerDistDoor;
		m_safeContourDistDoor = alarmSettingDlg.m_safeContourDistDoor;
		m_offRouteDistDoor = alarmSettingDlg.m_offRouteDistDoor;
		m_deepDepthDoor = alarmSettingDlg.m_fDeepDepthDoor;
		m_shallowDepthDoor = alarmSettingDlg.m_fShallowDepthDoor;
		g_fDcpaDoor = alarmSettingDlg.g_fDcpaDoor;
		g_fTcpaDoor = alarmSettingDlg.g_fTcpaDoor;
	}
} 

bool bShowOwnShipSpeedTimeMark = true;
bool bShowOwnShipHeadingLine = true; 

void CMainFrame::OnEmulateSetting() 
{
	// TODO: Add your command handler code here
	int static iMaxStoreTrackPoCount = 100;
	int static iMaxShowTrackPoCount =	100;
	int static iMaxStoreTrackTime = 300;
	CEmulateParamSetDlg emulateParamDlg;
	emulateParamDlg.m_fSpeed = m_nOwnShipCurrentSpeed;
	emulateParamDlg.m_iClockInterval = m_nTimerStep; 
	emulateParamDlg.m_bShowSpeedTimeMark = bShowOwnShipSpeedTimeMark; 
	emulateParamDlg.m_bShowHeadingLine = bShowOwnShipHeadingLine;
	emulateParamDlg.m_iMaxStoreTrackPoCount = iMaxStoreTrackPoCount;
	emulateParamDlg.m_iMaxShowTrackPoCount = iMaxShowTrackPoCount;
	emulateParamDlg.m_iMaxStoreTrackTime = iMaxStoreTrackTime;

	if (emulateParamDlg.DoModal() == IDOK)
	{ 
		m_nOwnShipCurrentSpeed = emulateParamDlg.m_fSpeed; 
		m_nTimerStep = emulateParamDlg.m_iClockInterval;
		SetTimer(1, m_nTimerStep, NULL);

		bShowOwnShipSpeedTimeMark = emulateParamDlg.m_bShowSpeedTimeMark;
		bShowOwnShipHeadingLine = emulateParamDlg.m_bShowHeadingLine;
		iMaxStoreTrackPoCount = emulateParamDlg.m_iMaxStoreTrackPoCount;
		iMaxShowTrackPoCount = emulateParamDlg.m_iMaxShowTrackPoCount;
		iMaxStoreTrackTime = emulateParamDlg.m_iMaxStoreTrackTime;

		
		m_yimaEncCtrl.SetDrawShipOptions(true, emulateParamDlg.m_bShowSpeedVector, 
			bShowOwnShipSpeedTimeMark, bShowOwnShipHeadingLine, 0, true, 0, iMaxStoreTrackPoCount, iMaxShowTrackPoCount, iMaxStoreTrackTime);

		m_yimaEncCtrl.SetDrawShipOptions(false, emulateParamDlg.m_bShowSpeedVector, 
			bShowOwnShipSpeedTimeMark, bShowOwnShipHeadingLine, 0, true, 0, 100, 50, 60);
	}
} 

//保存历史轨迹
void CMainFrame::OnSaveHistoryTrack()
{
	BOOL bReustl = m_yimaEncCtrl.SaveHistoryTracksToFile();
	if(bReustl)
	{
		AfxMessageBox(_T("保存成功"));
	}
	else
	{
		AfxMessageBox(_T("保存失败"));
	}
}

//查询历史轨迹
void CMainFrame::OnSelHistoryTrack()
{
	CSelOwnShipHistoryTrackDlg selOwnShipHistoryTrackDlg;
	selOwnShipHistoryTrackDlg.DoModal();
}

#define ITEM_STRING_MAX_LEN 255
#define ITEM_NAME_MAX_LEN 50
#define ITEM_VAL_STR_MAX_LEN 50
#define ITEM_VAL_SPERATOR_CHAR '='

bool GetStrItemValue(const char* pStrParsed, const char* pStrItemName,
					 CString& retStrItemVal)
{
	if (pStrItemName == NULL || pStrParsed == NULL)
	{
		return false;
	}

	const char* pFoundSeptStr = strchr(pStrParsed, ITEM_VAL_SPERATOR_CHAR);
	if (pFoundSeptStr == NULL)
	{
		return false;
	}

	char strParsedItemName[ITEM_STRING_MAX_LEN];
	int subStrLen = pFoundSeptStr - pStrParsed;
	strncpy(strParsedItemName, pStrParsed, subStrLen);
	strParsedItemName[subStrLen] = 0;

	CString strCmpLeft = strParsedItemName;
	strCmpLeft.TrimLeft();
	strCmpLeft.TrimRight();

	CString strCmpRight = pStrItemName;

	if (strCmpLeft != strCmpRight)
	{
		return false;
	}

	retStrItemVal.Format("%s", pFoundSeptStr + 1); 
	retStrItemVal.TrimLeft();
	retStrItemVal.TrimRight();

	return true;
}
 
#define SHIP_GPS_FILE "CurShipGeoPos.txt"
bool CMainFrame::GetShipPositionsFromDataFile(int& retShipCount,
												CString* pStringShipNames, 
							 int* pShipPositionXs, int* pShipPositionYs)
{
	if (pStringShipNames == NULL || pShipPositionXs == NULL || pShipPositionYs == NULL)
	{
		return false;
	}

	bool bSucOpenFile = false;
	int iRetryTimesCount = 0;
	while (!bSucOpenFile && iRetryTimesCount < 20)
	{
		CStdioFile shipPostionDataFile;
		CFileException e;
		
		if (!shipPostionDataFile.Open(SHIP_GPS_FILE, CFile::typeText, &e))
		{
			bSucOpenFile = false;
			Sleep(10);
			iRetryTimesCount ++;

			continue;
		}
		else
		{ 
			bSucOpenFile = true;
		}  
		
		CString strTimeInfo;
		shipPostionDataFile.ReadString(strTimeInfo);

		CString strShipCountInfo;
		shipPostionDataFile.ReadString(strShipCountInfo);		
		CString strShipCount;
		if (!GetStrItemValue(strShipCountInfo, "Ship Count", strShipCount)) 
		{
			return false;
		}
		
		int shipCount = atoi(strShipCount);
		retShipCount = shipCount;
		for (int shipNum = 0; shipNum < shipCount; shipNum ++)
		{
			CString strShipItemInfo; 
			
			shipPostionDataFile.ReadString(strShipItemInfo);//分隔符
			
			shipPostionDataFile.ReadString(strShipItemInfo);
			CString strShipName;
			if (!GetStrItemValue(strShipItemInfo, "Ship Name", strShipName))
			{
				return false;
			}
			pStringShipNames[shipNum] = strShipName;
			
			shipPostionDataFile.ReadString(strShipItemInfo);
			CString strShipPositionX;
			if (!GetStrItemValue(strShipItemInfo, "Ship Postion X", strShipPositionX))
			{
				return false;
			}
			pShipPositionXs[shipNum] = atoi(strShipPositionX);
			
			shipPostionDataFile.ReadString(strShipItemInfo);
			CString strShipPositionY;
			if (!GetStrItemValue(strShipItemInfo, "Ship Postion Y", strShipPositionY))
			{
				return false;
			}
			pShipPositionYs[shipNum] = atoi(strShipPositionY);
			
			shipPostionDataFile.ReadString(strShipItemInfo);//分隔符
		}  
		
		shipPostionDataFile.Close();
	}
	
	return bSucOpenFile;
}

void CMainFrame::OnAddUserMapObject() 
{
	// TODO: Add your command handler code here

	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 

	if (pView->m_iEditingUserMapLayerNum == -1)
	{
		AfxMessageBox("请先选择要编辑的图层!");
		return;
	} 
	
	pView->SetOperation(ADD_USER_LAYER_OBJ);

	LAYER_GEO_TYPE layerGeoType = 
		(LAYER_GEO_TYPE)m_yimaEncCtrl.tmGetLayerGeoType(
		pView->m_iEditingUserMapLayerNum); 
	if (layerGeoType == ALL_POINT)
	{ 
		pView->SetOperation(ADD_ISO_POINT);
	} 
	else if (layerGeoType == ALL_LINE)
	{
		pView->SetOperation(ADD_LINE);
	}
	else if (layerGeoType == ALL_FACE)
	{
		pView->SetOperation(ADD_FACE);
	}  

	SetCursor(LoadCursor(NULL, IDC_ARROW)); 
}

void CMainFrame::OnChoseEditUserLayer() 
{
	// TODO: Add your command handler code here
	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 

	CUserMapLayersDlg usrLayerDlg;
	usrLayerDlg.m_iSelLayerNum = pView->m_iEditingUserMapLayerNum;
	if (usrLayerDlg.DoModal())
	{ 
		pView->m_iEditingUserMapLayerNum = usrLayerDlg.m_iSelLayerNum;
	}
}


void CMainFrame::OnSaveUserMap() 
{
	// TODO: Add your command handler code here
	bool bSave = m_yimaEncCtrl.tmSaveToMapDataFile("MarineMap\\marineMap.ymc");
	if(bSave)
	{
		AfxMessageBox("已成功保存!");
	}
}

void CMainFrame::OnViewLibStyles() 
{
	// TODO: Add your command handler code here
	CLibLineStylesViewDlg libStylesViewDlg;
	libStylesViewDlg.DoModal();
}

void CMainFrame::OnViewLibPointStyles()
{
	CLibPointStylesViewDlg libPointStylesViewDlg;
	libPointStylesViewDlg.DoModal();
}

void CMainFrame::OnViewLibFaceStyles()
{
	CLibFaceStylesViewDlg libFaceStylesViewDlg;
	libFaceStylesViewDlg.DoModal();
}


void CMainFrame::OnAddPointObject() 
{
	// TODO: Add your command handler code here
	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 

	if (m_yimaEncCtrl.tmGetLayerGeoType(pView->m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	}

	if (!pView->IsOnOperation(NO_OPERATION))//防止操作冲突
	{
		return;
	}
	
	pView->SetOperation(ADD_USER_LAYER_OBJ);
	pView->SetOperation(ADD_ISO_POINT); 

	SetCursor(LoadCursor(NULL, IDC_ARROW)); 
}

void CMainFrame::OnAddLineObject() 
{
	// TODO: Add your command handler code here

	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 

	if (m_yimaEncCtrl.tmGetLayerGeoType(pView->m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	} 

	if (!pView->IsOnOperation(NO_OPERATION))//防止操作冲突
	{
		return;
	}
	pView->m_addingSpecialLineType = NO_SPECIAL_TYPE;
	pView->SetOperation(ADD_USER_LAYER_OBJ);
	pView->SetOperation(ADD_LINE); 

	SetCursor(LoadCursor(NULL, IDC_ARROW)); 
}

void CMainFrame::OnAddFaceObject() 
{
	// TODO: Add your command handler code 
	
	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 

	if (m_yimaEncCtrl.tmGetLayerGeoType(pView->m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	} 

	if (!pView->IsOnOperation(NO_OPERATION))//防止操作冲突
	{
		return;
	}
	pView->m_addingSpecialLineType = NO_SPECIAL_TYPE;
	pView->SetOperation(ADD_USER_LAYER_OBJ);
	pView->SetOperation(ADD_FACE); 

	SetCursor(LoadCursor(NULL, IDC_ARROW)); 
}

void CMainFrame::OnAddRectangle() 
{
	// TODO: Add your command handler code here

	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 
	if (m_yimaEncCtrl.tmGetLayerGeoType(pView->m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	} 

	if (!pView->IsOnOperation(NO_OPERATION))//防止操作冲突
	{
		return;
	}

 	pView->SetOperation(ADD_USER_LAYER_OBJ);
	pView->SetOperation(ADD_FACE); 
	pView->m_addingSpecialLineType = RECTANGLE_LN_TYPE;

	SetCursor(LoadCursor(NULL, IDC_ARROW)); 
}

void CMainFrame::OnAddCircle() 
{
	// TODO: Add your command handler code here

	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 
	if (m_yimaEncCtrl.tmGetLayerGeoType(pView->m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	} 

	if (!pView->IsOnOperation(NO_OPERATION))//防止操作冲突
	{
		return;
	}
  
	pView->SetOperation(ADD_USER_LAYER_OBJ);
	pView->SetOperation(ADD_FACE); 
	pView->m_addingSpecialLineType = CIRCLE_LN_TYPE;

	SetCursor(LoadCursor(NULL, IDC_ARROW)); 
}

void CMainFrame::OnAddEllipse() 
{
	// TODO: Add your command handler code here

	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 
	if (m_yimaEncCtrl.tmGetLayerGeoType(pView->m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	} 

	if (!pView->IsOnOperation(NO_OPERATION))//防止操作冲突
	{
		return;
	}
 
	pView->SetOperation(ADD_USER_LAYER_OBJ);
	pView->SetOperation(ADD_FACE); 
	pView->m_addingSpecialLineType = ELLIPSE_LN_TYPE;

	SetCursor(LoadCursor(NULL, IDC_ARROW)); 
}

void CMainFrame::OnAddArc() 
{
	// TODO: Add your command handler code here

	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 
	if (m_yimaEncCtrl.tmGetLayerGeoType(pView->m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	} 

	if (!pView->IsOnOperation(NO_OPERATION))//防止操作冲突
	{
		return;
	}
 
	pView->SetOperation(ADD_USER_LAYER_OBJ);
	pView->SetOperation(ADD_LINE); 
	pView->m_addingSpecialLineType = ARC_LN_TYPE;

	SetCursor(LoadCursor(NULL, IDC_ARROW)); 
}

void CMainFrame::OnAddSector() 
{
	// TODO: Add your command handler code here
 
	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 
	if (m_yimaEncCtrl.tmGetLayerGeoType(pView->m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	}  

	if (!pView->IsOnOperation(NO_OPERATION))//防止操作冲突
	{
		return;
	}
 
	pView->SetOperation(ADD_USER_LAYER_OBJ);
	pView->SetOperation(ADD_LINE); 
	pView->m_addingSpecialLineType = SECTOR_LN_TYPE;

	SetCursor(LoadCursor(NULL, IDC_ARROW)); 
}

void CMainFrame::OnGeoCalc() 
{
	// TODO: Add your command handler code here
	CGeoCalculateDlg geoCalcDlg;
	geoCalcDlg.DoModal();
}

void CMainFrame::OnSelecTlayerShowInfo() 
{
	// TODO: Add your command handler code here
	CMapLayerShowDlg mapLayerShowDlg;
    mapLayerShowDlg.DoModal();
	
}

void CMainFrame::OnAddPie() 
{
	// TODO: Add your command handler code here

	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 
	if (m_yimaEncCtrl.tmGetLayerGeoType(pView->m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	} 

	pView->SetOperation(ADD_USER_LAYER_OBJ);
	pView->SetOperation(ADD_LINE); 
	pView->m_addingSpecialLineType = PIE_LN_TYPE;

	SetCursor(LoadCursor(NULL, IDC_ARROW)); 
}

void CMainFrame::OnAddBow() 
{
	// TODO: Add your command handler code here

	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 
	if (m_yimaEncCtrl.tmGetLayerGeoType(pView->m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	} 
 
	pView->SetOperation(ADD_USER_LAYER_OBJ);
	pView->SetOperation(ADD_LINE); 
	pView->m_addingSpecialLineType = BOW_LN_TYPE;

	SetCursor(LoadCursor(NULL, IDC_ARROW)); 
}

void CMainFrame::OnSaveScrnToBmpFile() 
{
	CSaveMapViewToImgDlg dlg;
	dlg.DoModal();
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnShowText() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu = GetMenu();
	m_yimaEncCtrl.SetIfShowText(!m_yimaEncCtrl.GetIfShowText());
	pMenu->CheckMenuItem(ID_SHOW_TEXT, m_yimaEncCtrl.GetIfShowText() ? MF_CHECKED : MF_UNCHECKED);
}

void CMainFrame::OnSaveMemS57Map() 
{
	// TODO: Add your command handler code here 
	BSTR bstrMapName = ::SysAllocStringLen(NULL, 100); 

	m_yimaEncCtrl.GetMemMapInfo(0, NULL, &bstrMapName, 
		NULL, NULL, NULL, NULL, NULL, NULL, NULL); 
	
	CString mapName = bstrMapName;

	TCHAR curWorkDir[1024];
	GetCurrentDirectory(1024, curWorkDir);
	CString mapFilePathName = curWorkDir;
	mapFilePathName += _T("\\NewS57Map\\");
	mapFilePathName += mapName; 
	mapFilePathName += _T(".ymc");
	
	if (m_yimaEncCtrl.SaveS57MemMapToFile(0, mapFilePathName, true))
	{
		CString strMsg = _T("文件已经成功保存到 ");
		strMsg += mapFilePathName;
		AfxMessageBox(strMsg);
	}

	SysFreeString(bstrMapName);
}

void CMainFrame::OnSmoothPen() 
{
	// TODO: Add your command handler code here

	CMenu *pMenu = GetMenu();
	m_yimaEncCtrl.SetIfUseGDIPlus(!m_yimaEncCtrl.GetIfUseGDIPlus());
	pMenu->CheckMenuItem(ID_SMOOTH_PEN, m_yimaEncCtrl.GetIfUseGDIPlus() ? MF_CHECKED : MF_UNCHECKED);
}

void CMainFrame::OnShowFrame() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu = GetMenu();
	m_yimaEncCtrl.SetIfShowMapFrame(!m_yimaEncCtrl.GetIfShowMapFrame());
	
	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 
	pView->Invalidate();

	pMenu->CheckMenuItem(ID_SHOW_FRAME, m_yimaEncCtrl.GetIfShowMapFrame() ? MF_CHECKED : MF_UNCHECKED);
}

void CMainFrame::OnHightlightDeptharea() 
{
	// TODO: Add your command handler code here

	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 

	CHighlightDepthAreaDlg hltDptDlg;
	if (hltDptDlg.DoModal() == IDOK)
	{   
		pView->m_highlightDepthLowerLimit = hltDptDlg.m_fDepthLowerLimit;
		pView->m_highlightDepthUpLimit = hltDptDlg.m_fDepthUpLimit; 
		pView->m_highlightDepthAreaColor = RGB(hltDptDlg.m_fillColorR, hltDptDlg.m_fillColorG, hltDptDlg.m_fillColorB);
	}
}

void CMainFrame::OnChangeDepthLine() 
{
	// TODO: Add your command handler code here
	CChangeDepthLineValDlg chgDpthDlg;
	if (chgDpthDlg.DoModal() == IDOK)
	{ 
		//调整"等深线"图层的深度
		int nDptLnLyrPos = m_yimaEncCtrl.GetLayerPosByToken(-1, "DEPCNT");
		int nDptLnLyrObjCount = m_yimaEncCtrl.GetLayerObjectCountOfMap(0, nDptLnLyrPos);
		for (int objNum = 0; objNum < nDptLnLyrObjCount; objNum ++)
		{
#define DEPTH_VAL_FILED_POS_IN_DEPTH_CONTOUR_LAYER 0
#define MY_DEPTH_AREA_DEPTH_FILED_POS_IN_DEPTH_CONTOUR_LAYER 3 

			BSTR retObjValString = ::SysAllocStringLen(NULL, 255); 
			BSTR pBstrObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));

			MEM_GEO_OBJ_POS objPos(0, nDptLnLyrPos, objNum);
			memcpy(pBstrObjPos, &objPos, sizeof(MEM_GEO_OBJ_POS)); 

			m_yimaEncCtrl.GetObjectAttrString(&pBstrObjPos, 
				DEPTH_VAL_FILED_POS_IN_DEPTH_CONTOUR_LAYER, &retObjValString);

			CString strVal = retObjValString;
			float oldDepth = atof(strVal);
			float newDepth = oldDepth + chgDpthDlg.m_fDpthChgVal;
		    strVal.Format("%.3f", newDepth);

			m_yimaEncCtrl.SetObjectAttrValueString(0, nDptLnLyrPos, objNum,
				DEPTH_VAL_FILED_POS_IN_DEPTH_CONTOUR_LAYER, strVal); 

			m_yimaEncCtrl.GetObjectAttrString(&pBstrObjPos, 
				MY_DEPTH_AREA_DEPTH_FILED_POS_IN_DEPTH_CONTOUR_LAYER, &retObjValString);

			strVal = retObjValString;
			oldDepth = atof(strVal);
			newDepth = oldDepth + chgDpthDlg.m_fDpthChgVal;
		    strVal.Format("%.3f", newDepth);

			m_yimaEncCtrl.SetObjectAttrValueString(0, nDptLnLyrPos, objNum,
				MY_DEPTH_AREA_DEPTH_FILED_POS_IN_DEPTH_CONTOUR_LAYER, strVal);

			SysFreeString(retObjValString);
			SysFreeString(pBstrObjPos);
		}

		//调整"水深区"图层的深度
		int nDptAreLyrPos = m_yimaEncCtrl.GetLayerPosByToken(-1, "DEPARE");
		int nDptAreLyrObjCount = m_yimaEncCtrl.GetLayerObjectCountOfMap(0, nDptAreLyrPos);
		for (int objNum = 0; objNum < nDptAreLyrObjCount; objNum ++)
		{
#define DEPTH_VAL1_FILED_POS_IN_DEPTH_AREA_LAYER 0
#define DEPTH_VAL2_FILED_POS_IN_DEPTH_AREA_LAYER 1

			BSTR retObjValString = ::SysAllocStringLen(NULL, 255); 
			BSTR pBstrObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));

			MEM_GEO_OBJ_POS objPos(0, nDptAreLyrPos, objNum);
			memcpy(pBstrObjPos, &objPos, sizeof(MEM_GEO_OBJ_POS)); 

			m_yimaEncCtrl.GetObjectAttrString(&pBstrObjPos, 
				DEPTH_VAL1_FILED_POS_IN_DEPTH_AREA_LAYER, &retObjValString);

			CString strVal1 = retObjValString;
			float oldDepth1 = atof(strVal1);
			float newDepth1 = oldDepth1 + chgDpthDlg.m_fDpthChgVal;
		    strVal1.Format("%.3f", newDepth1);

			m_yimaEncCtrl.GetObjectAttrString(&pBstrObjPos, 
				DEPTH_VAL2_FILED_POS_IN_DEPTH_AREA_LAYER, &retObjValString);

			CString strVal2 = retObjValString;
			float oldDepth2 = atof(strVal2);
			float newDepth2 = oldDepth2 + chgDpthDlg.m_fDpthChgVal;
		    strVal2.Format("%.3f", newDepth2); 

			m_yimaEncCtrl.SetObjectAttrValueString(0, nDptAreLyrPos, objNum,
				DEPTH_VAL1_FILED_POS_IN_DEPTH_AREA_LAYER, strVal1);
			m_yimaEncCtrl.SetObjectAttrValueString(0, nDptAreLyrPos, objNum,
				DEPTH_VAL2_FILED_POS_IN_DEPTH_AREA_LAYER, strVal2);

			SysFreeString(retObjValString);
			SysFreeString(pBstrObjPos);
		}

		m_yimaEncCtrl.SetSafetyDepth(m_yimaEncCtrl.GetSafetyDepth());

		CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 
		pView->Invalidate();
	}
}

void CMainFrame::OnToolBar() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnSetS63UsrId() 
{
	// TODO: Add your command handler code here
	CSetS63DeviceIDDialog setDeviceIDDlg; 
	if (setDeviceIDDlg.DoModal() == IDOK)
	{
		m_yimaEncCtrl.SetDeviceID(setDeviceIDDlg.m_nDeviceID);
	}
}

void CMainFrame::OnUseOutlineText() 
{
	// TODO: Add your command handler code here	
    static bool bUseTextOutlineEffect = true;
	CMenu *pMenu = GetMenu();
	m_yimaEncCtrl.SetIfUseTextOutLineEffect(!bUseTextOutlineEffect);
	bUseTextOutlineEffect = !bUseTextOutlineEffect;
	pMenu->CheckMenuItem(ID_USE_OUTLINE_TEXT, bUseTextOutlineEffect ? MF_CHECKED : MF_UNCHECKED);
	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 
	pView->Invalidate();

}

void CMainFrame::OnGridShow() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu = GetMenu();
	m_yimaEncCtrl.SetIfShowGrid(!m_yimaEncCtrl.GetIfShowGrid());
	bool bShowGrid = m_yimaEncCtrl.GetIfShowGrid();
	pMenu->CheckMenuItem(ID_GRID_SHOW, bShowGrid ? MF_CHECKED : MF_UNCHECKED);
	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 
	pView->Invalidate();
}

void CMainFrame::OnSetBackgroud()
{
	// TODO: Add your command handler code here 

	CColorDialog colorDlg;

	if (colorDlg.DoModal() == IDOK)
	{
		m_yimaEncCtrl.SetBackgroundColor(colorDlg.GetColor());  
		CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 
		pView->Invalidate();
	}
}

void CMainFrame::OnSetGrid()
{
	// TODO: Add your command handler code here
	CSetGridLinesDlg dlg;
	dlg.m_pEncCtrl = &m_yimaEncCtrl;
	long gridLineColor, lonTextColor, latTextColor, fontSize, gridDenstityLnCount;
	gridDenstityLnCount = m_yimaEncCtrl.GetGridLineParams(&gridLineColor, &lonTextColor, &latTextColor, &fontSize);
	dlg.m_nGridDensityCount = gridDenstityLnCount;
	dlg.m_nGridTextFontSize = fontSize;
	if (dlg.DoModal() == IDOK)
	{
		m_yimaEncCtrl.SetGridLines(dlg.m_nGridDensityCount, dlg.m_gridLineColor, dlg.m_lonTextColor, dlg.m_latTextColor, 
			dlg.m_nGridTextFontSize);		
	}
}

void CMainFrame::OnShowScaleBar() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu = GetMenu();
	m_yimaEncCtrl.SetIfShowScaleBar(!m_yimaEncCtrl.GetIfShowScaleBar());

	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 
	pView->Invalidate();

	pMenu->CheckMenuItem(ID_SHOW_SCALE_BAR, m_yimaEncCtrl.GetIfShowScaleBar() ? MF_CHECKED : MF_UNCHECKED);
}

void CMainFrame::OnShowNorthArrow() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu = GetMenu();
	m_yimaEncCtrl.SetIfShowNorthArrow(!m_yimaEncCtrl.GetIfShowNorthArrow());


	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 
	pView->Invalidate();

	pMenu->CheckMenuItem(ID_SHOW_NORTH_ARROW, m_yimaEncCtrl.GetIfShowNorthArrow() ? MF_CHECKED : MF_UNCHECKED);
}

void CMainFrame::OnSetFileExtension() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu = GetMenu();
	CString strYmcEx, strYmpEx;
	strYmcEx.Format(_T(".NewYmc"));
	strYmpEx.Format(_T(".NewYmp")); 
	m_yimaEncCtrl.SetYimapEncFileExtension(strYmcEx, strYmpEx); 


	pMenu->CheckMenuItem(ID_SET_FILE_EXTENSION,MF_CHECKED);
}

void CMainFrame::OnSetDepColor() 
{
	// TODO: Add your command handler code here
	CMenu *pMenu = GetMenu();
	
	m_yimaEncCtrl.SetEncColor("DEPDW",0,0,255);//深水区(深水线以外)
	m_yimaEncCtrl.SetEncColor("DEPMD",0,0,0);//安全区(安全线~深水线)
	m_yimaEncCtrl.SetEncColor("DEPMS",255,255,255);//安全区(浅水线~安全线)
	m_yimaEncCtrl.SetEncColor("DEPVS",0,255,255);//浅水区（浅水线以内）

	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView(); 
	pView->Invalidate();


	pMenu->CheckMenuItem(ID_SET_DEP_COLOR,MF_CHECKED);
}

void CMainFrame::OnScrnPlaneGeo() 
{
	// TODO: Add your command handler code here
	CScrnPlaneGeoDlg scrnPlaneGeoDlg;
	scrnPlaneGeoDlg.DoModal();
}

void CMainFrame::OnGetDcpaTcpa() 
{
	// TODO: Add your command handler code here
	CGetDcpaTcpaDlg getDcpaTcpaDlg;
	getDcpaTcpaDlg.DoModal();
}

void CMainFrame::OnGetAreaOfRegion() 
{
	// TODO: Add your command handler code here
	CGetAreaOfGeoRegionDlg getAreaOfGeoRegionDlg;
	getAreaOfGeoRegionDlg.DoModal();
}

void CMainFrame::OnGetDepInfo() 
{
	// TODO: Add your command handler code here
	CGetDepInfoDlg getDepInfoDlg;
	getDepInfoDlg.DoModal();
}

void CMainFrame::OnAddTestShip() 
{
	// TODO: Add your command handler code here
	CAddTestShipDlg addTestShipDlg;
	addTestShipDlg.DoModal();
}

void CMainFrame::OnAreaWarnTest() 
{
	// TODO: Add your command handler code here
	static bool bOpen = false;
	static int objPos = -1;
	CTestAreaWarnDlg testAreaWarnDlg;
	testAreaWarnDlg.m_bAddShip = bOpen;
	testAreaWarnDlg.m_iObjPos = objPos;
	testAreaWarnDlg.DoModal();
	bOpen = testAreaWarnDlg.m_bAddShip;
	objPos = testAreaWarnDlg.m_iObjPos;
}

void CMainFrame::OnLayerObjectTest() 
{
	// TODO: Add your command handler code here
	CTestLayerObjectDlg testLayerObjectDlg;
	testLayerObjectDlg.DoModal();
}

void CMainFrame::OnNineNineBoxTest() 
{
	// TODO: Add your command handler code here
	//m_yimaEncCtrl.UnloadMapFromMemory(5);
	CTestNineNineBoxDlg testNineNineBoxDlg;
	testNineNineBoxDlg.DoModal();
}

void CMainFrame::OnCaculateScaleTest() 
{
	// TODO: Add your command handler code here
	CTestCaculateScaleDlg testCaculateScaleDlg;
	testCaculateScaleDlg.DoModal();
}

//vcf图层管理
void CMainFrame::OnVcfLayerMan()
{ 
	// TODO: 在此添加命令处理程序代码
	CVcfLayerManDlg vcfLayerManDlg;
	int imemMapCount = m_yimaEncCtrl.GetMemMapCount();
	int ivcfMemMapPos = -1;
	for (int i = 0; i < imemMapCount; i++)
	{ 
		if (m_yimaEncCtrl.GetMemMapIsArmsMap(i))
		{
			ivcfMemMapPos = i; 
			break;
		}

	} 
	if (ivcfMemMapPos < 0)
	{
		AfxMessageBox("当前内存中没有vcf图幅");
		return;
	}
	vcfLayerManDlg.m_vcfMapPos = ivcfMemMapPos;
	vcfLayerManDlg.DoModal();
} 

void CMainFrame::OnAddColorChangedFace()
{
	// TODO: 在此添加命令处理程序代码
	CYimaEncViewerView* pView = (CYimaEncViewerView*)GetActiveView();
	if (m_yimaEncCtrl.tmGetLayerGeoType(pView->m_iEditingUserMapLayerNum) != MULTIPLE_GEO_TYPE)
	{
		return;
	} 

	if (!pView->IsOnOperation(NO_OPERATION))//防止操作冲突
	{
		return;
	} 
	pView->SetOperation(ADD_USER_LAYER_OBJ);
	pView->SetOperation(ADD_FACE); 
	pView->SetOperation(ADD_COLOR_ATTENUATION_OBJ); 
	SetCursor(LoadCursor(NULL, IDC_ARROW)); 
}

int m_iCurLinePos = 0;
int m_iMaxLinePos = 4096;
bool m_bInitRadarInfo = false;

void CMainFrame::AddRadarInfoTest()
{  
	srand((int)time(0));//随机数 
	const int iLineNodeCount = 10000;

	//Sleep(5000);
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	if(m_bInitRadarInfo == false)
	{
		//M_COLOR mColor = M_COLOR(255,0,0);
		pYimaEncCtrl->SetRadarBaseInfo(m_iMaxLinePos, iLineNodeCount, 10,RGB(0,255,0));
		pYimaEncCtrl->SetRadarCenterGeoPo(1210000000,310000000);
		pYimaEncCtrl->SetRadarShowState(true, false);
		m_bInitRadarInfo = true;
	}

	int arrRadarInfo[iLineNodeCount];  
	BSTR bstrDataInfo = ::SysAllocStringLen(NULL, iLineNodeCount * sizeof(int));
	while(true)
	{   
		for(int iLineNum = 0; iLineNum < m_iMaxLinePos; iLineNum++)	
		{
			for(int i = 0; i < iLineNodeCount; i++)//随机生成
			{
				int iRandNum = (int)(rand() % 1001);
				arrRadarInfo[i] = (int)(iRandNum / 999);
			}			

			memcpy(bstrDataInfo, arrRadarInfo, iLineNodeCount * sizeof(int)); 


			if(m_iCurLinePos >= 20)
			{
				m_iCurLinePos = 0; 
				Sleep(20);
			}
			pYimaEncCtrl->SetRadarLineDataByPos(iLineNum,&bstrDataInfo,iLineNodeCount);
			m_iCurLinePos++;
		}

	}

	SysFreeString(bstrDataInfo); 

}

void CMainFrame::OnShowRadar()
{ 
	// TODO: 在此添加命令处理程序代码 
	static bool bShowRadar = false;
	bShowRadar = !bShowRadar; 
	CMenu *pMenu = this->GetMenu();	 

	if (bShowRadar)
	{
		pMenu->CheckMenuItem(ID_SHOW_RADAR, MF_CHECKED);  
		m_yimaEncCtrl.SetRadarShowState(true, false);
		ResumeThread(hThread);
	}
	else
	{
		pMenu->CheckMenuItem(ID_SHOW_RADAR, MF_UNCHECKED);
		m_yimaEncCtrl.SetRadarShowState(false, false);
		SuspendThread(hThread);
	}					  
	Invalidate(); 

}
void CMainFrame::ReadIniFile()
{
	TCHAR tcExePath[MAX_PATH] = {0};  
	::GetModuleFileName(NULL, tcExePath, MAX_PATH);  
	TCHAR *pFind = _tcsrchr(tcExePath, '\\');  
	if (pFind == NULL)  
	{  
		return;  
	}  
	*pFind = '\0';   
	CString szIniPath = tcExePath;  
	szIniPath += "\\";  
	szIniPath += "Config.ini";
	if (!PathFileExists(szIniPath))  
	{  
		return;  
	}  
	TCHAR szYmcKeyValue[MAX_PATH] = {0};  
	::GetPrivateProfileString(TEXT("Basic"), TEXT("ymcExtension"), ".ymc", szYmcKeyValue, MAX_PATH, szIniPath);  
	TCHAR szYmpKeyValue[MAX_PATH] = {0};  
	::GetPrivateProfileString(TEXT("Basic"), TEXT("ympExtension"), ".ymp", szYmpKeyValue, MAX_PATH, szIniPath);  
	
	TCHAR szPathKeyValue[MAX_PATH] = {0};  
	::GetPrivateProfileString(TEXT("Basic"), TEXT("initPath"), ".ymp", szPathKeyValue, MAX_PATH, szIniPath);  

	g_ymcExt = szYmcKeyValue;
	g_ympExt = szYmpKeyValue;
	g_strInitPath = szPathKeyValue;

}