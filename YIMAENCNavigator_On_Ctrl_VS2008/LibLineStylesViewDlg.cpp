// LibStylesViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "LibLineStylesViewDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLibLineStylesViewDlg dialog


CLibLineStylesViewDlg::CLibLineStylesViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLibLineStylesViewDlg::IDD, pParent)
	, m_fTextRotatrAngle(0)
{
	//{{AFX_DATA_INIT(CLibLineStylesViewDlg)
	m_iSelLsID = 0;
	m_iLsWidth = 0;
	m_iLsColorR = 0;
	m_iLsColorG = 0;
	m_iLsColorB = 0;
	m_bSetColor = FALSE;
	m_bSetWidth = FALSE;
	m_nFontColorB = 0;
	m_nFontColorG = 0;
	m_nFontColorR = 0;
	m_strFontName = _T("");
	m_strText = _T("");
	m_iTextOffsetY = 0;
	m_iTextOffsetX = 0;
	m_nFontSize = 0;
	m_bShowTextAlongWithLine = FALSE;
	m_bSolidLine = FALSE;
	m_bDashLine = FALSE;
	m_nDashCycle = 0;
	m_nDashLen = 0;
	m_bSetBasicLineColor = FALSE;
	m_nBscLnWidth = 0;
	m_nBscLnColorR = 0;
	m_nBscLnColorG = 0;
	m_nBscLnColorB = 0;
	//}}AFX_DATA_INIT

	m_iCurPageNum = 0;

	m_strCaption = "图库--线型风格";
}


void CLibLineStylesViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLibLineStylesViewDlg)
	DDX_Text(pDX, IDC_SEL_LIB_LINESTYLE_ID, m_iSelLsID);
	DDX_Text(pDX, IDC_LS_WIDTH, m_iLsWidth);
	DDX_Text(pDX, IDC_LS_COLOR_R, m_iLsColorR);
	DDX_Text(pDX, IDC_LS_COLOR_G, m_iLsColorG);
	DDX_Text(pDX, IDC_LS_COLOR_B, m_iLsColorB);
	DDX_Check(pDX, IDC_SET_COLOR_CHECK, m_bSetColor);
	DDX_Check(pDX, IDC_SET_WIDTH_CHECK, m_bSetWidth);
	DDX_Text(pDX, IDC_FONT_COLOR_B3, m_nFontColorB);
	DDX_Text(pDX, IDC_FONT_COLOR_G3, m_nFontColorG);
	DDX_Text(pDX, IDC_FONT_COLOR_R3, m_nFontColorR);
	DDX_Text(pDX, IDC_FONT_NAME, m_strFontName);
	DDX_Text(pDX, IDC_LINE_TEXT, m_strText);
	DDX_Text(pDX, IDC_TEXT_OFFSETY, m_iTextOffsetY);
	DDX_Text(pDX, IDC_TEXT_OFFSETX, m_iTextOffsetX);
	DDX_Text(pDX, IDC_TEXT_SIZE, m_nFontSize);
	DDX_Check(pDX, IDC_CHECK_TEXT_ALONG_WITH_LINE, m_bShowTextAlongWithLine);
	DDX_Check(pDX, IDC_SOLID_LINE_CHECK, m_bSolidLine);
	DDX_Check(pDX, IDC_DASH_LINE_CHECK, m_bDashLine);
	DDX_Text(pDX, IDC_DASH_CYCLE_EDIT, m_nDashCycle);
	DDX_Text(pDX, IDC_DASH_LEN_EDIT, m_nDashLen);
	DDX_Check(pDX, IDC_BESET_COLOR_CHECK, m_bSetBasicLineColor);
	DDX_Text(pDX, IDC_LINE_WIDTH_EDIT, m_nBscLnWidth);
	DDX_Text(pDX, IDC_LN_BS_COLOR_B, m_nBscLnColorB);
	DDX_Text(pDX, IDC_LN_BS_COLOR_G, m_nBscLnColorG);
	DDX_Text(pDX, IDC_LN_BS_COLOR_R, m_nBscLnColorR);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_LINETEXT_ROTATE_ANGLE, m_fTextRotatrAngle);
}


BEGIN_MESSAGE_MAP(CLibLineStylesViewDlg, CDialog)
	//{{AFX_MSG_MAP(CLibLineStylesViewDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_COLOR_BTN, OnColorBtn)
	ON_BN_CLICKED(IDC_DEMO_SHOW_BTN, OnDemoShowBtn)
	ON_BN_CLICKED(IDC_PAGEUP_BUTTON, OnPageupButton)
	ON_BN_CLICKED(IDC_PAGE_DOWN_BUTTON, OnPageDownButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_FONT_BUTTON, OnFontButton)
	ON_BN_CLICKED(IDC_TEXT_COLOR_BUTTON, OnTextColorButton)
	ON_BN_CLICKED(IDC_SOLID_LINE_CHECK, OnSolidLineCheck)
	ON_BN_CLICKED(IDC_DASH_LINE_CHECK, OnDashLineCheck)
	ON_BN_CLICKED(IDC_SETCOLOR_BTN, OnSetcolorBtn)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CLibLineStylesViewDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLibLineStylesViewDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLibLineStylesViewDlg message handlers

BOOL CLibLineStylesViewDlg::OnInitDialog() 
{
	UpdateData(false);

	CDialog::OnInitDialog();
	
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	SetWindowText(m_strCaption);

    // TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

#define PER_PAGE_STYLE_COUNT 20

void CLibLineStylesViewDlg::OnPaint() 
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
	 		
	BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 2); 

	M_POINT linePoints[2]; 
	
	int libLineStyleCount = pYimaEncCtrl->GetLibLineStyleCount();
	for (int lsNum = 0; lsNum < PER_PAGE_STYLE_COUNT; lsNum ++)
	{ 
		int iCurLsNum = lsNum + m_iCurPageNum * PER_PAGE_STYLE_COUNT;
		if (iCurLsNum >= libLineStyleCount)
		{
			break;
		}

		int lineLeftX = 60 + (lsNum % 2) * 280;
		int lineLength = 200;
		int lineY = (lsNum / 2) * 40 + 125;
		linePoints[0] = M_POINT(lineLeftX, lineY);
		linePoints[1] = M_POINT(lineLeftX + lineLength, lineY);	
	    
		memcpy(strLinePoints, linePoints, sizeof(M_POINT) * 2);
 
		UINT lnStyleID = pYimaEncCtrl->GetLibLineStyleIDFromPos(iCurLsNum);
		
		CString strLnStyleID;
		strLnStyleID.Format("%d. ", lnStyleID);

		pYimaEncCtrl->TextOutAtPoint(strLnStyleID, lineLeftX - 30, lineY);
		pYimaEncCtrl->DrawLineWithLibLineStyle(lnStyleID, &strLinePoints, 2, false, 0, false, 0);		
	}
	
	linePoints[0] = M_POINT(617, 253);
	linePoints[1] = M_POINT(822, 253);	
	memcpy(strLinePoints, linePoints, sizeof(M_POINT) * 2);
	
	pYimaEncCtrl->DrawLineWithLibLineStyle(m_iSelLsID, &strLinePoints, 2, m_bSetColor, 
		RGB(m_iLsColorR, m_iLsColorG, m_iLsColorB), m_bSetWidth, m_iLsWidth);

	::SysFreeString(strLinePoints);   

	pYimaEncCtrl->RefreshDrawer((long)pFrame->GetActiveView()->m_hWnd, 0, 0, 0, 0);   
	// Do not call CDialog::OnPaint() for painting messages
}

void CLibLineStylesViewDlg::OnColorBtn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	CColorDialog colorDlg;
	if (colorDlg.DoModal() == IDOK)
	{
		M_COLOR color;
		M_SET_COLOR_BY_INT(color, colorDlg.GetColor());

		m_iLsColorR = color.r;
		m_iLsColorG = color.g;
		m_iLsColorB = color.b;

		UpdateData(false);
	}
}

void CLibLineStylesViewDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString editText;
	GetDlgItem(IDC_LINE_TEXT)->GetWindowText(editText);
	CDialog::OnOK();
}

void CLibLineStylesViewDlg::OnDemoShowBtn() 
{
	// TODO: Add your control notification handler code here 
	Invalidate();
}

void CLibLineStylesViewDlg::OnPageupButton() 
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

void CLibLineStylesViewDlg::OnPageDownButton() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	
	int lsCount = pYimaEncCtrl->GetLibLineStyleCount();
	int iPageCount = (lsCount - 1) / PER_PAGE_STYLE_COUNT; 

	if (m_iCurPageNum < iPageCount)
	{ 
		m_iCurPageNum ++;
	}
	
	Invalidate();
}

void CLibLineStylesViewDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default 

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 2); 

	M_POINT linePoints[2]; 

	point.y -= 60; //去掉上边偏移量
	
	int libLineStyleCount = pYimaEncCtrl->GetLibLineStyleCount();
	for (int lsNum = 0; lsNum < PER_PAGE_STYLE_COUNT; lsNum ++)
	{ 
		int iCurLsNum = lsNum + m_iCurPageNum * PER_PAGE_STYLE_COUNT;
		if (iCurLsNum >= libLineStyleCount)
		{
			break;
		}

		int lineLeftX = 60 + (lsNum % 2) * 280;
		int lineLength = 200;
		int lineY = (lsNum / 2) * 40 + 55;
		linePoints[0] = M_POINT(lineLeftX, lineY);
		linePoints[1] = M_POINT(lineLeftX + lineLength, lineY);	
	    
		memcpy(strLinePoints, linePoints, sizeof(M_POINT) * 2);
 
		if (abs(lineLeftX - point.x) <= 200 && abs(lineY - point.y) <= (55 / 2))
		{
 			m_iSelLsID = pYimaEncCtrl->GetLibLineStyleIDFromPos(iCurLsNum);
			break;
		}
	}

	UpdateData(false);

	CDialog::OnLButtonDown(nFlags, point);
}

void CLibLineStylesViewDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	OnLButtonDown(nFlags, point);
	
	CDialog::OnLButtonDblClk(nFlags, point);

	OnOK();
}

void CLibLineStylesViewDlg::OnFontButton() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	CFontDialog fontDialog;
    if (fontDialog.DoModal() == IDOK)
	{
		if (fontDialog.GetFaceName() != "")
		{ 
			m_strFontName = fontDialog.GetFaceName();
			UpdateData(false);
			Invalidate();
		}
	}
}

void CLibLineStylesViewDlg::OnTextColorButton() 
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

void CLibLineStylesViewDlg::OnSolidLineCheck() 
{
	// TODO: Add your control notification handler code here 
	UpdateData(true);
	if (m_bDashLine)
	{
		m_bDashLine = false;
		UpdateData(false);
	} 
}

void CLibLineStylesViewDlg::OnDashLineCheck() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_bSolidLine)
	{
		m_bSolidLine = false;
		UpdateData(false);
	} 
}

void CLibLineStylesViewDlg::OnSetcolorBtn() 
{
	// TODO: Add your control notification handler code here
	CColorDialog colorDlg;
	if (colorDlg.DoModal() == IDOK)
	{
		M_COLOR color;
		M_SET_COLOR_BY_INT(color, colorDlg.GetColor());

		m_nBscLnColorR = color.r;
		m_nBscLnColorG = color.g;
		m_nBscLnColorB = color.b;

		UpdateData(false);
	}
}

void CLibLineStylesViewDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CLibLineStylesViewDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
