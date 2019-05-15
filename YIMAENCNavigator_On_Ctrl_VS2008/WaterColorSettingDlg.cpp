// WaterColorSettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "WaterColorSettingDlg.h"
#include "MainFrm.h"


// CWaterColorSettingDlg 对话框

IMPLEMENT_DYNAMIC(CWaterColorSettingDlg, CDialog)

CWaterColorSettingDlg::CWaterColorSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaterColorSettingDlg::IDD, pParent)
	, m_VsR(0)
	, m_VsG(0)
	, m_VsB(0)
{
	 m_MsR = 0;
	 m_MsG = 0;
	 m_MsB = 0;
	 m_MdR = 0;
	 m_MdG = 0;
	 m_MdB = 0;
	 m_DwR = 0;
	 m_DwG = 0;
	 m_DwB = 0;
}

CWaterColorSettingDlg::~CWaterColorSettingDlg()
{
}

void CWaterColorSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_VSR, m_VsR);
	DDV_MinMaxInt(pDX, m_VsR, 0, 255);
	DDX_Text(pDX, IDC_EDIT_VSG, m_VsG);
	DDV_MinMaxInt(pDX, m_VsG, 0, 255);
	DDX_Text(pDX, IDC_EDIT_VSB, m_VsB);
	DDV_MinMaxInt(pDX, m_VsB, 0, 255);

	DDX_Text(pDX, IDC_EDIT_MSR, m_MsR);
	DDV_MinMaxInt(pDX, m_MsR, 0, 255);
	DDX_Text(pDX, IDC_EDIT_MSG, m_MsG);
	DDV_MinMaxInt(pDX, m_MsG, 0, 255);
	DDX_Text(pDX, IDC_EDIT_MSB, m_MsB);
	DDV_MinMaxInt(pDX, m_MsB, 0, 255);


	DDX_Text(pDX, IDC_EDIT_MDR, m_MdR);
	DDV_MinMaxInt(pDX, m_MdR, 0, 255);
	DDX_Text(pDX, IDC_EDIT_MDG, m_MdG);
	DDV_MinMaxInt(pDX, m_MdG, 0, 255);
	DDX_Text(pDX, IDC_EDIT_MDB, m_MdB);
	DDV_MinMaxInt(pDX, m_MdB, 0, 255);


	DDX_Text(pDX, IDC_EDIT_DWR, m_DwR);
	DDV_MinMaxInt(pDX, m_DwR, 0, 255);
	DDX_Text(pDX, IDC_EDIT_DWG, m_DwG);
	DDV_MinMaxInt(pDX, m_DwG, 0, 255);
	DDX_Text(pDX, IDC_EDIT_DWB, m_DwB);
	DDV_MinMaxInt(pDX, m_DwB, 0, 255);
}


BEGIN_MESSAGE_MAP(CWaterColorSettingDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COLOR_VS, &CWaterColorSettingDlg::OnBnClickedButtonColorVs)
	ON_BN_CLICKED(IDC_BUTTON_COLOR_MS, &CWaterColorSettingDlg::OnBnClickedButtonColorMs)
	ON_BN_CLICKED(IDC_BUTTON_COLOR_MD, &CWaterColorSettingDlg::OnBnClickedButtonColorMd)
	ON_BN_CLICKED(IDC_BUTTON_COLOR_DW, &CWaterColorSettingDlg::OnBnClickedButtonColorDw)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CWaterColorSettingDlg::OnBnClickedButtonApply)
END_MESSAGE_MAP()


// CWaterColorSettingDlg 消息处理程序

void CWaterColorSettingDlg::OnBnClickedButtonColorVs()
{	    
	if (m_ColorSel.DoModal() == IDOK)
	{
		COLORREF selColor = m_ColorSel.GetColor();
		m_VsR = GetRValue(selColor);			
		m_VsG = GetGValue(selColor);
		m_VsB = GetBValue(selColor);
		UpdateData(FALSE);

	}
	
}

void CWaterColorSettingDlg::OnBnClickedButtonColorMs()
{
	if (m_ColorSel.DoModal() == IDOK)
	{
		COLORREF selColor = m_ColorSel.GetColor();
		m_MsR = GetRValue(selColor);			
		m_MsG = GetGValue(selColor);
		m_MsB = GetBValue(selColor);
		UpdateData(FALSE);
	}
}

void CWaterColorSettingDlg::OnBnClickedButtonColorMd()
{
	if (m_ColorSel.DoModal() == IDOK)
	{
		COLORREF selColor = m_ColorSel.GetColor();
		m_MdR = GetRValue(selColor);			
		m_MdG = GetGValue(selColor);
		m_MdB = GetBValue(selColor);
		UpdateData(FALSE);
	}
}

void CWaterColorSettingDlg::OnBnClickedButtonColorDw()
{
	if (m_ColorSel.DoModal() == IDOK)
	{
		COLORREF selColor = m_ColorSel.GetColor();
		m_DwR = GetRValue(selColor);			
		m_DwG = GetGValue(selColor);
		m_DwB = GetBValue(selColor);
		UpdateData(FALSE);
	}
}

void CWaterColorSettingDlg::OnBnClickedButtonApply()
{
	UpdateData(TRUE);
	//C AfxGetApp()
	CMainFrame* pMainFrm =(CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrm->m_yimaEncCtrl.SetEncColor("DEPVS", m_VsR, m_VsG, m_VsB); //浅水区（浅水线以内）
	pMainFrm->m_yimaEncCtrl.SetEncColor("DEPMS", m_MsR, m_MsG, m_MsB); //安全区(浅水线~安全线）//DEPIT 0米以下
	pMainFrm->m_yimaEncCtrl.SetEncColor("DEPMD", m_MdR, m_MdG, m_MdB); //安全区(安全线~深水线)
	pMainFrm->m_yimaEncCtrl.SetEncColor("DEPDW", m_DwR, m_DwG, m_DwB); //深水区(深水线以外)
}
