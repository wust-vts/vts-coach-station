// LibPointStylesViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "LibPointStylesViewDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLibPointStylesViewDlg dialog


CLibPointStylesViewDlg::CLibPointStylesViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLibPointStylesViewDlg::IDD, pParent)
	, m_fTextRotatrAngle(0)
{
	//{{AFX_DATA_INIT(CLibPointStylesViewDlg)
	m_iSelPsID = 1; 
	m_iPointColorR = 0;
	m_iPointColorG = 0;
	m_iPointColorB = 0;
	m_bSetColor = FALSE;
	m_bSetRatio = FALSE;
	m_fZoomRatio = 0.0f;
	m_strTextFontName = _T("");
	m_strText = _T("");
	m_iTextOffsetX = 0;
	m_iTextOffsetY = 0;
	m_nFontColorR = 0;
	m_nFontColorG = 0;
	m_nFontColorB = 0;
	m_nFontSize = 0;
	//}}AFX_DATA_INIT

	m_iCurPageNum = 0;
}


void CLibPointStylesViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLibPointStylesViewDlg)
	DDX_Text(pDX, IDC_SEL_LIB_POINTSTYLE_ID, m_iSelPsID); 
	DDX_Text(pDX, IDC_POINT_COLOR_R, m_iPointColorR);
	DDX_Text(pDX, IDC_POINT_COLOR_G, m_iPointColorG);
	DDX_Text(pDX, IDC_POINT_COLOR_B, m_iPointColorB);
	DDX_Check(pDX, IDC_SET_COLOR_CHECK, m_bSetColor);
	DDX_Check(pDX, IDC_SET_RATIO_CHECK, m_bSetRatio);
	DDX_Text(pDX, IDC_SYMBOL_ZOOM_RATIO, m_fZoomRatio);
	DDX_Text(pDX, IDC_FONT_NAME, m_strTextFontName);
	DDX_Text(pDX, IDC_TEXT, m_strText);
	DDX_Text(pDX, IDC_TEXT_OFFSETX, m_iTextOffsetX);
	DDX_Text(pDX, IDC_TEXT_OFFSETY, m_iTextOffsetY);
	DDX_Text(pDX, IDC_FONT_COLOR_B, m_nFontColorR);
	DDX_Text(pDX, IDC_FONT_COLOR_G, m_nFontColorG);
	DDX_Text(pDX, IDC_FONT_COLOR_R, m_nFontColorB);
	DDX_Text(pDX, IDC_TEXT_SIZE, m_nFontSize);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_TEXT_ROTATE_ANGLE, m_fTextRotatrAngle);
}


BEGIN_MESSAGE_MAP(CLibPointStylesViewDlg, CDialog)
	//{{AFX_MSG_MAP(CLibPointStylesViewDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_COLOR_BTN, OnColorBtn)
	ON_BN_CLICKED(IDC_DEMO_SHOW_BTN, OnDemoShowBtn)
	ON_BN_CLICKED(IDC_PAGE_UP_BUTTON, OnPageUpButton)
	ON_BN_CLICKED(IDC_PAGE_DOWN_BUTTON, OnPageDownButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_FONT_BUTTON, OnFontButton)
	ON_BN_CLICKED(IDC_TEXT_COLOR_BUTTON, OnTextColorButton)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CLibPointStylesViewDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLibPointStylesViewDlg message handlers

#define PER_PAGE_STYLE_COUNT 20

void CLibPointStylesViewDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting 

	// TODO: Add your message handler code here
    UpdateData(true);

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	RECT dlgRect;
	GetClientRect(&dlgRect);
	pYimaEncCtrl->RefreshDrawerForDirectDrawDC((long)dc.m_hDC, dlgRect.right - dlgRect.left, 
		dlgRect.bottom - dlgRect.top, 0, 0, true, 0);
	
	BSTR strSymbolPoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 1);

	int libSymbolCount = pYimaEncCtrl->GetSymbolCount();
	for (int sNum = 0; sNum < PER_PAGE_STYLE_COUNT; sNum ++)
	{
		M_POINT symbolPoints[1];
		int symbolPoX = 70 + (sNum % 4) * 150;
		int symbolPoY = 50 + (sNum / 4) * 60;

		memcpy(strSymbolPoints, symbolPoints, sizeof(M_POINT) * 1);

		int iCurSymbolNum = sNum + m_iCurPageNum * PER_PAGE_STYLE_COUNT;
		if (iCurSymbolNum >= libSymbolCount)
		{
			break;
		}
		UINT symbolID = pYimaEncCtrl->GetSymbolIDFromPos(iCurSymbolNum);

		CString strSymbolID;
		strSymbolID.Format("%d. ", symbolID);

		pYimaEncCtrl->SetCurrentFont("宋体", 15, 0, false, false);
		pYimaEncCtrl->TextOutAtPoint(strSymbolID, symbolPoX - 40, symbolPoY);
 
		pYimaEncCtrl->DrawPointWithLibSymbol(symbolID, symbolPoX, symbolPoY, false, 0, 1, 0); 
	}

	pYimaEncCtrl->DrawPointWithLibSymbol(m_iSelPsID, 700, 185, m_bSetColor, 
		RGB(m_iPointColorR, m_iPointColorG, m_iPointColorB), m_bSetRatio ? m_fZoomRatio : 1, 0);

	::SysFreeString(strSymbolPoints);  
 
	pYimaEncCtrl->RefreshDrawer((long)pFrame->GetActiveView()->m_hWnd, 0, 0, 0, 0);   

	// Do not call CDialog::OnPaint() for painting messages
}

void CLibPointStylesViewDlg::OnColorBtn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	CColorDialog colorDlg;
	if (colorDlg.DoModal() == IDOK)
	{
		M_COLOR color;
		M_SET_COLOR_BY_INT(color, colorDlg.GetColor());

		m_iPointColorR = color.r;
		m_iPointColorG = color.g;
		m_iPointColorB = color.b;

		UpdateData(false);
	}
}

void CLibPointStylesViewDlg::OnDemoShowBtn() 
{
	// TODO: Add your control notification handler code here

	Invalidate();
}

BOOL CLibPointStylesViewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	//HDC hdc = (HDC)::GetDC(m_hWnd);
	//RECT dlgRect;
	//GetClientRect(&dlgRect);
	//pYimaEncCtrl->RefreshDrawerForDirectDrawDC((long)hdc, dlgRect.right - dlgRect.left,
	//	dlgRect.bottom - dlgRect.top, 0, 0, true, 0);

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLibPointStylesViewDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CLibPointStylesViewDlg::OnPageUpButton() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
 
	if (m_iCurPageNum > 0)
	{ 
		m_iCurPageNum --;
	}
	
	Invalidate();
}

void CLibPointStylesViewDlg::OnPageDownButton() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	
	int symbolCount = pYimaEncCtrl->GetSymbolCount();
	int iPageCount = (symbolCount - 1) / PER_PAGE_STYLE_COUNT; 

	if (m_iCurPageNum < iPageCount)
	{ 
		m_iCurPageNum ++;
	}
	
	Invalidate();
}

void CLibPointStylesViewDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	BSTR strSymbolPoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 1);

	int libSymbolCount = pYimaEncCtrl->GetSymbolCount();
	for (int sNum = 0; sNum < PER_PAGE_STYLE_COUNT; sNum ++)
	{
		M_POINT symbolPoints[1];
		int symbolPoX = 70 + (sNum % 4) * 150;
		int symbolPoY = 50 + (sNum / 4) * 60;

		memcpy(strSymbolPoints, symbolPoints, sizeof(M_POINT) * 1);

		int iCurSymbolNum = sNum + m_iCurPageNum * PER_PAGE_STYLE_COUNT;
		if (iCurSymbolNum >= libSymbolCount)
		{
			break;
		}
		
		if (abs(symbolPoX - point.x) <= 60 && abs(symbolPoY - point.y) <= 50)
		{
 			m_iSelPsID = pYimaEncCtrl->GetSymbolIDFromPos(iCurSymbolNum);
			break;
		}
	}


	UpdateData(false);

	CDialog::OnLButtonDown(nFlags, point);
}

void CLibPointStylesViewDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	OnLButtonDown(nFlags, point);
	
	CDialog::OnLButtonDblClk(nFlags, point);

	OnOK();
}

void CLibPointStylesViewDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CLibPointStylesViewDlg::OnFontButton() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	CFontDialog fontDialog;
    if (fontDialog.DoModal() == IDOK)
	{
		if (fontDialog.GetFaceName() != "")
		{ 
			m_strTextFontName = fontDialog.GetFaceName();
			UpdateData(false);
			Invalidate();
		}
	}
}

void CLibPointStylesViewDlg::OnTextColorButton() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	CColorDialog colorDlg;
	if (colorDlg.DoModal() == IDOK)
	{
		M_COLOR color;
		M_SET_COLOR_BY_INT(color, colorDlg.GetColor());

		m_nFontColorR = color.r;
		m_nFontColorG = color.g;
		m_nFontColorB = color.b;

		UpdateData(false);
	}
}

void CLibPointStylesViewDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
