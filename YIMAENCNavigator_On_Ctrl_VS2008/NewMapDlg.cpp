// NewMapDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "NewMapDlg.h"
#include "MainFrm.h"

  
extern CString g_ymcExt;
extern CString g_ympExt;
extern CString g_strInitPath;

// CNewMapDlg �Ի���

IMPLEMENT_DYNAMIC(CNewMapDlg, CDialog)

CNewMapDlg::CNewMapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewMapDlg::IDD, pParent)
{
	m_bDrag = false;
}

CNewMapDlg::~CNewMapDlg()
{
}

void CNewMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NEW_MAP_CTRL, m_newMapCtrl);
}


BEGIN_MESSAGE_MAP(CNewMapDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CNewMapDlg::OnBnClickedOk)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_MAP_ROTATE, &CNewMapDlg::OnBnClickedButtonMapRotate)
	ON_BN_CLICKED(IDC_BUTTON_SET_LAND_COLOR, &CNewMapDlg::OnBnClickedButtonSetLandColor)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL() 
END_MESSAGE_MAP()


// CNewMapDlg ��Ϣ��������

void CNewMapDlg::OnBnClickedOk()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	OnOK();
}

BOOL CNewMapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_bInit = false;
	bool bInit = false;
	m_newMapCtrl.SetYimapEncFileExtension(g_ymcExt, g_ympExt);
	if(g_strInitPath != "")
	{
		bInit = m_newMapCtrl.Init(g_strInitPath);
	}
	else
	{ 
		TCHAR curWorkDir[1024];	
		GetCurrentDirectory(1024, curWorkDir);//��ȡ��ʼ��Ŀ¼ 
		bInit = m_newMapCtrl.Init(curWorkDir);
	}
	CRect rect; 
	this->GetClientRect(&rect);
	int iwidth = rect.right - rect.left - 2;
	int iheight = rect.bottom - rect.top - 2;
	m_newMapCtrl.RefreshDrawer((long)m_hWnd, iwidth, iheight, 0, 0);
	m_newMapCtrl.OverViewLibMap(0);
	m_newMapCtrl.SetCurrentScale((int)m_newMapCtrl.GetCurrentScale() >> 2);

	m_bInit = bInit;
	return TRUE;  
}

void CNewMapDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴�������Ϣ�����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	ReDrawMap();
}

void CNewMapDlg::ReDrawMap()
{ 
	if(m_bInit)
	{
		HDC hdc = ::GetDC(m_hWnd);   
		m_newMapCtrl.DrawMapsInScreen((long)hdc);  
		::ReleaseDC(m_hWnd, hdc);
	} 
}
void CNewMapDlg::OnBnClickedButtonMapRotate()
{
	static int rotateAngle = 0; 
	m_newMapCtrl.RotateMapByScrnCenter(rotateAngle += 10);
	Invalidate(FALSE);
}

void CNewMapDlg::OnBnClickedButtonSetLandColor()
{
	int landPos = m_newMapCtrl.GetLayerPosByToken(-1, "LNDARE");   
	srand((unsigned)time( NULL )); 
	int r = rand()%255;
	int g = rand()%255;
	int b = rand()%255;
	m_newMapCtrl.SetLayerSubStyleParams(0, landPos, 1, true, true, RGB(r, g, b)); 
	Invalidate(FALSE);
}
 





void CNewMapDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	SetCapture();
	m_bDrag = true;
	m_mouseDragFirstPo = M_POINT(point.x, point.y);
	CDialog::OnLButtonDown(nFlags, point);
}

void CNewMapDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ

	ReleaseCapture();
	CDialog::OnLButtonUp(nFlags, point);
	if(m_bDrag)
	{ 
		m_newMapCtrl.SetMapMoreOffset(point.x - m_mouseDragFirstPo.x, point.y - m_mouseDragFirstPo.y); 
		Invalidate(FALSE);
		m_bDrag = false;
	}
}

void CNewMapDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	if(m_bDrag)
	{ 
		HDC hdc = ::GetDC(m_hWnd); 
		m_newMapCtrl.DrawDragingMap((long)hdc, point.x, point.y, m_mouseDragFirstPo.x, m_mouseDragFirstPo.y); 
		::ReleaseDC(m_hWnd, hdc);
	}
	CDialog::OnMouseMove(nFlags, point);
}

BOOL CNewMapDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	int curMapScale = (int)m_newMapCtrl.GetCurrentScale();
	if (zDelta > 0)
	{
		curMapScale = curMapScale >> 1;
	}
	else 
	{ 
		curMapScale = curMapScale << 1;
	}
	m_newMapCtrl.SetCurrentScale(curMapScale);
	Invalidate(FALSE);

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}