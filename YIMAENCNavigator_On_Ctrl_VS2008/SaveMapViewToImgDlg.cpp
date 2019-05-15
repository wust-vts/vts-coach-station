// SaveMapViewToImgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "SaveMapViewToImgDlg.h"
#include "MainFrm.h"


// CSaveMapViewToImgDlg �Ի���

IMPLEMENT_DYNAMIC(CSaveMapViewToImgDlg, CDialog)

CSaveMapViewToImgDlg::CSaveMapViewToImgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveMapViewToImgDlg::IDD, pParent)
	, m_bSavePng(true)
	, m_bSaveJpg(false)
	, m_bSaveBmp(false)
{
	m_bSaveGif = false;
}

CSaveMapViewToImgDlg::~CSaveMapViewToImgDlg()
{
}

void CSaveMapViewToImgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSaveMapViewToImgDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CSaveMapViewToImgDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSaveMapViewToImgDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO_PNG, &CSaveMapViewToImgDlg::OnBnClickedRadioPng)
	ON_BN_CLICKED(IDC_RADIO_JPG, &CSaveMapViewToImgDlg::OnBnClickedRadioJpg)
	ON_BN_CLICKED(IDC_RADIO_BMP, &CSaveMapViewToImgDlg::OnBnClickedRadioBmp) 
	ON_BN_CLICKED(IDC_RADIO_GIF, &CSaveMapViewToImgDlg::OnBnClickedRadioGif)
END_MESSAGE_MAP()


// CSaveMapViewToImgDlg ��Ϣ��������
BOOL CSaveMapViewToImgDlg::OnInitDialog() 
{
	m_bSavePng = true;
	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO_PNG);

	radio->SetCheck(1);

	return TRUE;
}

void CSaveMapViewToImgDlg::OnBnClickedOk()
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	TCHAR curWorkDir[1024];
	GetCurrentDirectory(1024, curWorkDir);
	CString strStoreBmpFileName;
	long saveImgType = 1;//����ĸ�ʽ��1=bmp,2=jpg,3=png,4=gif
	if(m_bSavePng)
	{
		strStoreBmpFileName.Format(_T("%s\\SaveEncScreen.png"), curWorkDir);
		saveImgType = 3;
	}
	else if(m_bSaveJpg)
	{
		strStoreBmpFileName.Format(_T("%s\\SaveEncScreen.jpg"), curWorkDir);
		saveImgType = 2;
	}
	else if (m_bSaveBmp) 
	{
		strStoreBmpFileName.Format(_T("%s\\SaveEncScreen.bmp"), curWorkDir);
		saveImgType = 1;
	}
	else if (m_bSaveGif)
	{
		strStoreBmpFileName.Format(_T("%s\\SaveEncScreen.gif"), curWorkDir);
		saveImgType = 4;

	}
	bool bSave = pYimaEncCtrl->SaveMemScrnToImageFile(saveImgType,0, 0, pYimaEncCtrl->GetDrawerScreenWidth(), 
		pYimaEncCtrl->GetDrawerScreenHeight(), strStoreBmpFileName);

	if(bSave)
	{
		CString strMsg;
		strMsg.Format("��ǰ��ͼ��Ļ�ѱ����浽�ļ�%s", strStoreBmpFileName);

		AfxMessageBox(strMsg); 
		OnOK();
	}
	else
	{
		AfxMessageBox(_T("����ʧ��")); 
	}
	
}

void CSaveMapViewToImgDlg::OnBnClickedCancel()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	OnCancel();
}

void CSaveMapViewToImgDlg::OnBnClickedRadioPng()
{
	this->m_bSavePng = true;
	this->m_bSaveBmp = false;
	this->m_bSaveJpg = false;
	this->m_bSaveGif = false;
	UpdateData(0);
}

void CSaveMapViewToImgDlg::OnBnClickedRadioJpg()
{
	this->m_bSavePng = false;
	this->m_bSaveBmp = false;
	this->m_bSaveJpg = true;
	this->m_bSaveGif = false;
	UpdateData(0);
}

void CSaveMapViewToImgDlg::OnBnClickedRadioBmp()
{
	this->m_bSavePng = false;
	this->m_bSaveBmp = true;
	this->m_bSaveJpg = false;
	this->m_bSaveGif = false;
	UpdateData(0);
} 
void CSaveMapViewToImgDlg::OnBnClickedRadioGif()
{
	this->m_bSavePng = false;
	this->m_bSaveBmp = false;
	this->m_bSaveJpg = false;
	this->m_bSaveGif = true;
	UpdateData(0);
}