// VcfLayerManDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "VcfLayerManDlg.h" 
#include "MainFrm.h"

// CVcfLayerManDlg �Ի���

IMPLEMENT_DYNAMIC(CVcfLayerManDlg, CDialog)

CVcfLayerManDlg::CVcfLayerManDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVcfLayerManDlg::IDD, pParent)
{

}

CVcfLayerManDlg::~CVcfLayerManDlg()
{
}

void CVcfLayerManDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LAYER, m_layerList);
}


BEGIN_MESSAGE_MAP(CVcfLayerManDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CVcfLayerManDlg::OnBnClickedOk)  
	ON_CLBN_CHKCHANGE(IDC_LIST_LAYER, &CVcfLayerManDlg::OnLbnChkchangelListLayer)
	ON_BN_CLICKED(IDC_BTN_SHOW_ALL_VCF_LY, &CVcfLayerManDlg::OnBnClickedBtnShowAllVcfLy)
	ON_BN_CLICKED(IDC_BTN_HIDDEN_ALL_VCF_LY, &CVcfLayerManDlg::OnBnClickedBtnHiddenAllVcfLy)
END_MESSAGE_MAP()


// CVcfLayerManDlg ��Ϣ��������

BOOL CVcfLayerManDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	int iLayerCount = pYimaEncCtrl->GetLayerCount(m_vcfMapPos);
	for (int layerPos = 0; layerPos < iLayerCount; layerPos ++)
	{
		//wchar_t wStr[] = L"����һ������";
		//char ch[] = "ddd����";
		BSTR bstrLayerName = ::SysAllocStringLen(NULL, 20);
		pYimaEncCtrl->GetLayerInfo(m_vcfMapPos, layerPos, &bstrLayerName, NULL, NULL);

		CString strLayerName = bstrLayerName;
		m_layerList.AddString(strLayerName);
		bool bDraw = pYimaEncCtrl->GetVcfLayerDrawOrNot(layerPos);
		m_layerList.SetCheck(layerPos, bDraw);
		::SysFreeString(bstrLayerName);
	}
	return TRUE;   
}

void CVcfLayerManDlg::OnBnClickedOk()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	OnOK();
} 
 

void CVcfLayerManDlg::OnLbnChkchangelListLayer()
{
	int icurPos = m_layerList.GetCurSel();
	bool bcurLayerDraw = m_layerList.GetCheck(icurPos) == 1; 
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	pYimaEncCtrl->SetVcfLayerDrawOrNot(icurPos, bcurLayerDraw);
	pFrame->RedrawView(); 
}

void CVcfLayerManDlg::OnBnClickedBtnShowAllVcfLy()
{ 
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	int iLayerCount = pYimaEncCtrl->GetLayerCount(m_vcfMapPos);
	for(int icurPos = 0; icurPos < iLayerCount;icurPos ++)
	{
		pYimaEncCtrl->SetVcfLayerDrawOrNot(icurPos, true);
		m_layerList.SetCheck(icurPos, 1); 
	}
	pFrame->RedrawView(); 
}

void CVcfLayerManDlg::OnBnClickedBtnHiddenAllVcfLy()
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	int iLayerCount = pYimaEncCtrl->GetLayerCount(m_vcfMapPos); 
	for(int icurPos = 0; icurPos < iLayerCount;icurPos ++)
	{
		pYimaEncCtrl->SetVcfLayerDrawOrNot(icurPos, false);
		m_layerList.SetCheck(icurPos, 0); 
	}
	pFrame->RedrawView(); 
}