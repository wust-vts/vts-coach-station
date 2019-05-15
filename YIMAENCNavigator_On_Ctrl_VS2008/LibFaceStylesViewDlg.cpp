// LibFaceStylesViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "LibFaceStylesViewDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLibFaceStylesViewDlg dialog


CLibFaceStylesViewDlg::CLibFaceStylesViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLibFaceStylesViewDlg::IDD, pParent)
	, m_fTextRotatrAngle(0)
{
	//{{AFX_DATA_INIT(CLibFaceStylesViewDlg)
	m_iFaceColorB = 0;
	m_iFaceColorG = 0;
	m_iFaceColorR = 0;
	m_iFaceWidth = 0;
	m_iSelFsID = 1;
	m_bSetColor = FALSE;
	m_bSetPatternColor = FALSE;
	m_iFacePatternColorB = 0;
	m_iFacePatternColorG = 0;
	m_iFacePatternColorR = 0;
	m_bSetFillColorTransparency = FALSE;
	m_iFillTransparency = 0;
	m_strText = _T("");
	m_iTextOffsetX = 0;
	m_iTextOffsetY = 0;
	m_nTextFontSize = 0;
	m_strFontName = _T("");
	m_nFontColorR = 0;
	m_nFontColorG = 0;
	m_nFontColorB = 0;
	//}}AFX_DATA_INIT

	m_strCaption = "图库--面型风格";
}


void CLibFaceStylesViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLibFaceStylesViewDlg)
	DDX_Text(pDX, IDC_FACE_COLOR_B, m_iFaceColorB);
	DDX_Text(pDX, IDC_FACE_COLOR_G, m_iFaceColorG);
	DDX_Text(pDX, IDC_FACE_COLOR_R, m_iFaceColorR);
	DDX_Text(pDX, IDC_SEL_LIB_FACESTYLE_ID, m_iSelFsID);
	DDX_Check(pDX, IDC_SET_COLOR_CHECK, m_bSetColor);
	DDX_Check(pDX, IDC_SET_PATTERN_COLOR_CHECK, m_bSetPatternColor);
	DDX_Text(pDX, IDC_FACE_PAT_COLOR_B, m_iFacePatternColorB);
	DDX_Text(pDX, IDC_FACE_PAT_COLOR_G, m_iFacePatternColorG);
	DDX_Text(pDX, IDC_FACE_PAT_COLOR_R, m_iFacePatternColorR);
	DDX_Check(pDX, IDC_SET_COLOR_TRANS_CHECK, m_bSetFillColorTransparency);
	DDX_Text(pDX, IDC_TXT_FILL_TRANSP, m_iFillTransparency);
	DDX_Text(pDX, IDC_FACE_TEXT, m_strText);
	DDX_Text(pDX, IDC_TEXT_OFFSETX2, m_iTextOffsetX);
	DDX_Text(pDX, IDC_TEXT_OFFSETY2, m_iTextOffsetY);
	DDX_Text(pDX, IDC_TEXT_SIZE2, m_nTextFontSize);
	DDX_Text(pDX, IDC_FONT_NAME2, m_strFontName);
	DDX_Text(pDX, IDC_FONT_COLOR_R2, m_nFontColorR);
	DDX_Text(pDX, IDC_FONT_COLOR_G2, m_nFontColorG);
	DDX_Text(pDX, IDC_FONT_COLOR_B2, m_nFontColorB);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_FACETEXT_ROTATE_ANGLE, m_fTextRotatrAngle);
}


BEGIN_MESSAGE_MAP(CLibFaceStylesViewDlg, CDialog)
	//{{AFX_MSG_MAP(CLibFaceStylesViewDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_COLOR_BTN, OnColorBtn)
	ON_BN_CLICKED(IDC_DEMO_SHOW_BTN, OnDemoShowBtn)
	ON_BN_CLICKED(IDC_COLOR_BTN2, OnPatternColorBtn)
	ON_WM_LBUTTONDOWN()  
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_FONT_BUTTON, OnFontButton)
	ON_BN_CLICKED(IDC_TEXT_COLOR_BUTTON, OnTextColorButton)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CLibFaceStylesViewDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLibFaceStylesViewDlg message handlers
#define FACE_POINTS_COUNT 3
void CLibFaceStylesViewDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	UpdateData(true);
	
	// TODO: Add your message handler code here

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	RECT dlgRect;
	GetClientRect(&dlgRect);
	pYimaEncCtrl->RefreshDrawerForDirectDrawDC((long)dc.m_hDC, dlgRect.right - dlgRect.left, 
		dlgRect.bottom - dlgRect.top, 0, 0, true, 0);
	 		
	BSTR strFacePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 4); 
	
	M_POINT facePoints[4]; 

	int libFaceStyleCount = pYimaEncCtrl->GetLibFaceStyleCount();
	for (int fsNum = 0; fsNum < libFaceStyleCount; fsNum ++)
	{ 
		int faceLength = 100;
		int faceHeight = 50;
		int leftX = 50 + (fsNum % 3) * 2 * faceLength;
		int leftY = (fsNum / 3) * 2 * faceHeight + 30 ;
		facePoints[0] = M_POINT(leftX, leftY);
		facePoints[1] = M_POINT(leftX + faceLength, leftY);
		facePoints[2] = M_POINT(leftX + faceLength, leftY + faceHeight);
		facePoints[3] = M_POINT(leftX, leftY + faceHeight);

		memcpy(strFacePoints, facePoints, sizeof(M_POINT) * 4);

		UINT faceStyleId = pYimaEncCtrl->GetLibFaceStyleIDFromPos(fsNum);

		CString strFaceStyleID;
		strFaceStyleID.Format("%d. ", faceStyleId);

		pYimaEncCtrl->TextOutAtPoint(strFaceStyleID, leftX - 20, leftY + 20);
		pYimaEncCtrl->DrawFaceWithLibFaceStyle(faceStyleId, &strFacePoints, 4, false, 0, false, 0);		
	}

	facePoints[0] = M_POINT(623, 182);
	facePoints[1] = M_POINT(796, 182);
	facePoints[2] = M_POINT(796, 240);
	facePoints[3] = M_POINT(623, 240);

	memcpy(strFacePoints, facePoints, sizeof(M_POINT) * 4);
	 
	pYimaEncCtrl->DrawFaceWithLibFaceStyle(m_iSelFsID, &strFacePoints, 4, m_bSetColor, 
		RGB(m_iFaceColorR, m_iFaceColorG, m_iFaceColorB), m_bSetPatternColor, 
		RGB(m_iFacePatternColorR, m_iFacePatternColorG, m_iFacePatternColorB));

	::SysFreeString(strFacePoints);  

	pYimaEncCtrl->RefreshDrawer((long)pFrame->GetActiveView()->m_hWnd, 0, 0, 0, 0);
	
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CLibFaceStylesViewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	SetWindowText(m_strCaption);
	 
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLibFaceStylesViewDlg::OnColorBtn() 
{
	// TODO: Add your control notification handler code here

	UpdateData(true);

	CColorDialog colorDlg;
	if (colorDlg.DoModal() == IDOK)
	{
		M_COLOR color;
		M_SET_COLOR_BY_INT(color, colorDlg.GetColor());

		m_iFaceColorR = color.r;
		m_iFaceColorG = color.g;
		m_iFaceColorB = color.b;

		UpdateData(false);
	}	
}

void CLibFaceStylesViewDlg::OnDemoShowBtn() 
{
	// TODO: Add your control notification handler code here
	
	Invalidate();
}

void CLibFaceStylesViewDlg::OnOK() 
{
	// TODO: Add extra validation here

	int radioID = GetCheckedRadioButton(IDC_TEXT_ON_CENTER_RADIO, IDC_TEXT_ON_BOTTOM_RADIO);
	m_bShowTextOnObjectCenterOrBottom = (radioID == IDC_TEXT_ON_CENTER_RADIO) ? true : false;
	
	CDialog::OnOK();
}

void CLibFaceStylesViewDlg::OnPatternColorBtn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	CColorDialog colorDlg;
	if (colorDlg.DoModal() == IDOK)
	{
		M_COLOR color;
		M_SET_COLOR_BY_INT(color, colorDlg.GetColor());

		m_iFacePatternColorR = color.r;
		m_iFacePatternColorG = color.g;
		m_iFacePatternColorB = color.b;

		UpdateData(false);
	}	
}

void CLibFaceStylesViewDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	BSTR strFacePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 4); 
	
	M_POINT facePoints[4]; 

	int libFaceStyleCount = pYimaEncCtrl->GetLibFaceStyleCount();
	for (int fsNum = 0; fsNum < libFaceStyleCount; fsNum ++)
	{ 
		int faceLength = 100;
		int faceHeight = 50;
		int leftX = 50 + (fsNum % 3) * 2 * faceLength;
		int leftY = (fsNum / 3) * 2 * faceHeight + 30 ;
		facePoints[0] = M_POINT(leftX, leftY);
		facePoints[1] = M_POINT(leftX + faceLength, leftY);
		facePoints[2] = M_POINT(leftX + faceLength, leftY + faceHeight);
		facePoints[3] = M_POINT(leftX, leftY + faceHeight);

		memcpy(strFacePoints, facePoints, sizeof(M_POINT) * 4); 

		if (((point.x - leftX) >= -20 && (point.x - leftX) <= faceLength) && ((point.y - leftY) >=0 && (point.y - leftY) <= faceHeight))
		{
			m_iSelFsID = pYimaEncCtrl->GetLibFaceStyleIDFromPos(fsNum);
			break;
		}
	}

	UpdateData(false);

	CDialog::OnLButtonDown(nFlags, point);
}  


void CLibFaceStylesViewDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	OnLButtonDown(nFlags, point);
	
	CDialog::OnLButtonDblClk(nFlags, point);

	OnOK();
}

void CLibFaceStylesViewDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	m_iSelFsID = 0;
	CDialog::OnCancel();
}

void CLibFaceStylesViewDlg::OnFontButton() 
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

void CLibFaceStylesViewDlg::OnTextColorButton() 
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

void CLibFaceStylesViewDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
