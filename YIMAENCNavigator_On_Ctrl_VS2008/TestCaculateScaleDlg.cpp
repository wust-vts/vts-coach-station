// TestCaculateScaleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "TestCaculateScaleDlg.h"
#include "MainFrm.h"
#include "math.h"


// CTestCaculateScaleDlg �Ի���

IMPLEMENT_DYNAMIC(CTestCaculateScaleDlg, CDialog)

CTestCaculateScaleDlg::CTestCaculateScaleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestCaculateScaleDlg::IDD, pParent)
	, m_iCurPx(0)
	, m_fCurDis(0)
	, m_iScale(0)
	, m_iCurScale(0)
	, m_iPxDis(0)
	, m_fDis(0)
{

}

CTestCaculateScaleDlg::~CTestCaculateScaleDlg()
{
}

void CTestCaculateScaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT9, m_iCurPx);
	DDX_Text(pDX, IDC_EDIT10, m_fCurDis);
	DDX_Text(pDX, IDC_EDIT11, m_iScale);
	DDX_Text(pDX, IDC_EDIT7, m_iCurScale);
	DDX_Text(pDX, IDC_EDIT4, m_iPxDis);
	DDX_Text(pDX, IDC_EDIT6, m_fDis);
}


BEGIN_MESSAGE_MAP(CTestCaculateScaleDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CTestCaculateScaleDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestCaculateScaleDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestCaculateScaleDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestCaculateScaleDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CTestCaculateScaleDlg ��Ϣ��������

BOOL CTestCaculateScaleDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	float fScale = pYimaEncCtrl->GetCurrentScale();
	this->m_iCurScale = (int)fScale;
	UpdateData(0);
	return TRUE;
}

//��������-->������
void CTestCaculateScaleDlg::OnBnClickedButton1()
{
	UpdateData(1);
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	
	long centerGeoPoX, centerGeoPoY;
	
	float mapViewSizeSrnX = pYimaEncCtrl->GetDrawerScreenHeight();
	float mapViewSizeSrnY = pYimaEncCtrl->GetDrawerScreenWidth();
	pYimaEncCtrl->GetGeoPoFromScrnPo((long)(mapViewSizeSrnX / 2),(long)(mapViewSizeSrnY / 2),&centerGeoPoX, &centerGeoPoY);
	float disPx = this->m_iCurPx;
	float disMeter = this->m_fCurDis * 1852;
	
	/*
	M_POINT mCenterGeoPo;//���ĵ�����
	M_POINT mLeftTopGeoPo;//���϶���

	long lViewHeight = pYimaEncCtrl->GetDrawerScreenHeight();//��ͼ��ͼ����Ļ��С��px��
	long lViewWidth = pYimaEncCtrl->GetDrawerScreenWidth();
	
	long lScrnDis = sqrt(pow(lViewHeight / 2 , 2) + pow(lViewWidth / 2 , 2)); //���ĵ㵽���϶������Ļ����(px)
	long lDis = pYimaEncCtrl->GetDistBetwTwoPoint(mCenterGeoPo.x, mCenterGeoPo.y, mLeftTopGeoPo.x, mLeftTopGeoPo.y);//��ͼ���ĵ㵽���϶����ƽ�����(����)
	long disMeter = lDis * 1852;//�Ѻ���ת������
	long lNewScale = pYimaEncCtrl->CaculateScale(mCenterGeoPo.x,mCenterGeoPo.y,lScrnDis,disMeter);//�õ��µı�����

	pYimaEncCtrl->SetCurrentScale(lNewScale);//���ñ�����
	pYimaEncCtrl->CenterMap(mCenterGeoPo.x, mCenterGeoPo.y);//�������ĵ�
	*/


	
	float fScale = pYimaEncCtrl->CaculateScale(centerGeoPoX,centerGeoPoY,disPx,disMeter);
	this->m_iScale = fScale + 0.5;
	UpdateData(0);
}

//������ --> ��������
void CTestCaculateScaleDlg::OnBnClickedButton4()
{
		// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	long firstGeoPoX,firstGeoPoY,secondGeoPoX,secondGeoPoY;
	float mapViewSizeSrnX = pYimaEncCtrl->GetDrawerScreenHeight();
	float mapViewSizeSrnY = pYimaEncCtrl->GetDrawerScreenWidth();
	pYimaEncCtrl->GetGeoPoFromScrnPo(mapViewSizeSrnX, mapViewSizeSrnY, &firstGeoPoX, &firstGeoPoY);//��(0,0)�ľ�γ������
	pYimaEncCtrl->GetGeoPoFromScrnPo(mapViewSizeSrnX + 200, mapViewSizeSrnY + 200, &secondGeoPoX, &secondGeoPoY);//��(200,200)�ľ�γ������

	double allDis = pYimaEncCtrl->GetDistBetwTwoPoint(firstGeoPoX, firstGeoPoY, secondGeoPoX, secondGeoPoY);//����֮�����(����)
	
	float pxDis = (200 * 200 +  200 * 200);
	float onePxDis = (float) allDis / sqrt(pxDis);//һ�����صľ��루���
	this->m_iPxDis = 100;
	this->m_fDis = onePxDis * 100;//100���ؾ���
	UpdateData(0);
}

//�л�����
void CTestCaculateScaleDlg::OnBnClickedButton3()
{
	float fScale =(float) this->m_iScale;
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	pYimaEncCtrl->SetCurrentScale(fScale);
	pYimaEncCtrl->Invalidate();//ˢ�º�ͼ 
	m_iCurScale = fScale;
	UpdateData(FALSE);
}



void CTestCaculateScaleDlg::OnBnClickedOk()
{
	OnOK();
}