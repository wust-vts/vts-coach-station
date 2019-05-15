// YimaEncViewer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "YimaEncViewer.h"

#include "MainFrm.h"
#include "YimaEncViewerDoc.h"
#include "YimaEncViewerView.h" 
#include "YimaEnc.h"
#include "YimaEnc.h"
#include "YimaEnc.h"
#include "YimaEnc.h"
#include "YimaEnc.h"
#include "YimaEnc.h"
#include "YimaEnc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CYimaEncViewerApp

BEGIN_MESSAGE_MAP(CYimaEncViewerApp, CWinApp)
	//{{AFX_MSG_MAP(CYimaEncViewerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_ZCZ_TEST_BUTTOM,OnZczTestButtom)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYimaEncViewerApp construction

CYimaEncViewerApp::CYimaEncViewerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CYimaEncViewerApp object

CYimaEncViewerApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CYimaEncViewerApp initialization

#define GPS_COMUNICATE_PRGRM_NAME "CommRcvGps"
BOOL CYimaEncViewerApp::InitInstance()
{ 
	AfxEnableControlContainer();
 
	//////////// 加载动态库 ... /////////////////////////	
	for (int loadOcxNum = 0; loadOcxNum < 2; loadOcxNum ++)
	{
		CString strOcxFilePath;
		if (loadOcxNum == 0)
		{
			#ifdef	_DEBUG
			   strOcxFilePath = "YimaEnc_d.ocx";
			#else
			   strOcxFilePath = "YimaEnc.ocx";
			#endif	 
		}
		else
		{
			strOcxFilePath = "MSFLXGRD.OCX";
		}
 
		HINSTANCE hLib = LoadLibrary(strOcxFilePath); 
		
		if (hLib >= (HINSTANCE)HINSTANCE_ERROR)
		{  
			// Find the entry point.
			FARPROC lpDllEntryPoint = NULL;
			lpDllEntryPoint = GetProcAddress(hLib, _T("DllRegisterServer"));
			if (lpDllEntryPoint != NULL)
			{
				(*lpDllEntryPoint)();
			} 
		} 
	}
   //////////////////////////////////////////////////////////////


	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CYimaEncViewerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CYimaEncViewerView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//m_nCmdShow = SW_SHOWMAXIMIZED;
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->SetWindowText("YIMAENC 航行监控模拟");

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();  

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX }; 
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg) 
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CYimaEnc m_testyima;
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg) 
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_YIMA_CTRL, m_testyima);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// App command to run the dialog
void CYimaEncViewerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CYimaEncViewerApp message handlers

#define GPS_COMM_WND_CLOSE_MSG 1001

int CYimaEncViewerApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	HWND hGpsCommWnd = FindWindow(NULL, GPS_COMUNICATE_PRGRM_NAME);

	SendMessage(hGpsCommWnd, WM_USER, GPS_COMM_WND_CLOSE_MSG, NULL);

	return CWinApp::ExitInstance();
} 

// App command to run the dialog
void CYimaEncViewerApp::OnZczTestButtom()
{
	CYimaEncViewerView* pView = (CYimaEncViewerView*) (((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetActiveView());
	/*BSTR bstrVersion = ::SysAllocStringLen(NULL, 255);
	BSTR bstrTime = ::SysAllocStringLen(NULL, 255);
	pView->m_pYimaEncCtrl->GetYimaSdkVersion(&bstrVersion, &bstrTime);
	CString strVersion = bstrVersion;
	CString strTime = bstrTime;
		
	::SysFreeString(bstrVersion);
	::SysFreeString(bstrTime);*/

	int typeID = pView->m_pYimaEncCtrl->AddAisType("ais22"); //添加AIS类型(AIS TYPE)(在线)
	pView->m_pYimaEncCtrl->SetAisTypeInfo(typeID, _T("ais22"), false, 4, 1, false, 0, 6, 500000, true,false, 200000, true);//设置该AIS 类型的显示风格

	int shipCount = 10;
	M_POINT* arrShipPo = new M_POINT[shipCount];
	int* pCurHeadings = new int[shipCount]; 
	int* pCurCourseOverGround = new int[shipCount]; 
	int* pCurCourseThrghWater = new int[shipCount]; 
	int* pCurSpeedOverGround = new int[shipCount]; 
	int* pCurSpeedThrghWater = new int[shipCount];
	for(int i = 0; i < shipCount; i++)
	{
		arrShipPo[i] = M_POINT(1210000000 + i * 1000000 , 31 + i * 2000000);
		pCurHeadings[i] = (10 + 12.5 * i)*100;	//船首向乘以100，转换成整数传递参数
		pCurCourseOverGround[i] = 15 * 100;	//乘以100，转换成整数传递参数
		pCurCourseThrghWater[i] = 0 * 100;	//乘以100，转换成整数传递参数 
		pCurSpeedOverGround[i] = 0 * 100;	//乘以100，转换成整数传递参数
		pCurSpeedThrghWater[i] = 0 * 100;	//乘以100，转换成整数传递参数
	}

	BSTR bstrGeoPo = SysAllocStringLen(NULL, sizeof(M_POINT)*shipCount);
	BSTR bstrHeadings = SysAllocStringLen(NULL, sizeof(int)*shipCount);
	BSTR bstrCourseOverGround = SysAllocStringLen(NULL, sizeof(int)*shipCount);
	BSTR bstrCourseThrghWater = SysAllocStringLen(NULL, sizeof(int)*shipCount);
	BSTR bstrSpeedOverGround = SysAllocStringLen(NULL, sizeof(int)*shipCount);
	BSTR bstrSpeedThrghWater= SysAllocStringLen(NULL, sizeof(int)*shipCount);
	memcpy(bstrGeoPo, arrShipPo, sizeof(M_POINT)*shipCount);
	memcpy(bstrHeadings, pCurHeadings, sizeof(int)*shipCount);
	memcpy(bstrCourseOverGround, pCurCourseOverGround, sizeof(int)*shipCount);
	memcpy(bstrCourseThrghWater, pCurCourseThrghWater, sizeof(int)*shipCount);
	memcpy(bstrSpeedOverGround, pCurSpeedOverGround, sizeof(int)*shipCount);
	memcpy(bstrSpeedThrghWater, pCurSpeedThrghWater, sizeof(int)*shipCount);

	BSTR bstrRetShipId = SysAllocStringLen(NULL, sizeof(int)*shipCount);
	pView->m_pYimaEncCtrl->AddOtherVessels(false, shipCount, &bstrGeoPo, &bstrHeadings, &bstrCourseOverGround, &bstrCourseThrghWater
		, &bstrSpeedOverGround, &bstrSpeedThrghWater, &bstrRetShipId, typeID);
	int* pRetShipId = new int[shipCount];
	memcpy(pRetShipId, bstrRetShipId, sizeof(int)*shipCount);
	char msg[255];
	sprintf(msg, "添加后船舶ID = ");
	for (int i = 0; i < shipCount; i++)
	{
		sprintf(msg, "%s%d、", msg, pRetShipId[i]);
	}
	AfxMessageBox(CString(msg));
	SysFreeString(bstrGeoPo);
	SysFreeString(bstrHeadings);
	SysFreeString(bstrCourseOverGround);
	SysFreeString(bstrCourseThrghWater);
	SysFreeString(bstrSpeedOverGround);
	SysFreeString(bstrSpeedThrghWater);
	SysFreeString(bstrRetShipId);
	delete[]arrShipPo;
	delete[]pCurHeadings;
	delete[]pCurCourseOverGround;
	delete[]pCurCourseThrghWater;
	delete[]pCurSpeedOverGround;
	delete[]pCurSpeedThrghWater;
	delete[]pRetShipId;
}
BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	TCHAR curWorkDir[1024];	
	GetCurrentDirectory(1024, curWorkDir);//获取初始化目录
	bool bInitResult = m_testyima.Init(curWorkDir);
	if (bInitResult)
	{
		AfxMessageBox("初始化成功");
	}
	//HDC myDc = ::GetDC(m_hWnd);
	m_testyima.RefreshDrawer((long)m_hWnd, 200, 200,0,0); 
	m_testyima.OverViewLibMap(0);
	m_testyima.DrawMapsInScreen(NULL);
	//::ReleaseDC(m_hWnd, myDc);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAboutDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	m_testyima.DrawMapsInScreen(NULL);
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
}

void CAboutDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_testyima.DrawMapsInScreen(NULL);
	CDialog::OnMouseMove(nFlags, point);
}
