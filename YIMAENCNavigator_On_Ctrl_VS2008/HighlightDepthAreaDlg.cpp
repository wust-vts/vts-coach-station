// HighlightDepthAreaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "HighlightDepthAreaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHighlightDepthAreaDlg dialog


CHighlightDepthAreaDlg::CHighlightDepthAreaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHighlightDepthAreaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHighlightDepthAreaDlg)
	m_fDepthLowerLimit = 0.0f;
	m_fDepthUpLimit = 0.0f;
	m_fillColorG = 0;
	m_fillColorB = 0;
	m_fillColorR = 0;
	//}}AFX_DATA_INIT
}


void CHighlightDepthAreaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHighlightDepthAreaDlg)
	DDX_Text(pDX, IDC_DEPTH1_EDIT, m_fDepthLowerLimit);
	DDX_Text(pDX, IDC_DEPTH2_EDIT, m_fDepthUpLimit);
	DDX_Text(pDX, IDC_FILL_COLOR_G, m_fillColorG);
	DDX_Text(pDX, IDC_FILL_COLOR_B, m_fillColorB);
	DDX_Text(pDX, IDC_FILL_COLOR_R, m_fillColorR);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHighlightDepthAreaDlg, CDialog)
	//{{AFX_MSG_MAP(CHighlightDepthAreaDlg)
	ON_BN_CLICKED(IDC_COLOR_BTN, OnColorBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHighlightDepthAreaDlg message handlers

void CHighlightDepthAreaDlg::OnColorBtn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	CColorDialog colorDlg;
	if (colorDlg.DoModal() == IDOK)
	{
		M_COLOR color;
		M_SET_COLOR_BY_INT(color, colorDlg.GetColor());

		m_fillColorR = color.r;
		m_fillColorG = color.g;
		m_fillColorB = color.b;

		UpdateData(false);
	}
}
