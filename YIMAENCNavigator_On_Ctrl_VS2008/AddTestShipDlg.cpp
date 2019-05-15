// AddTestShipDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "AddTestShipDlg.h"
#include "MainFrm.h"


// CAddTestShipDlg �Ի���

IMPLEMENT_DYNAMIC(CAddTestShipDlg, CDialog)

CAddTestShipDlg::CAddTestShipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddTestShipDlg::IDD, pParent)
	, m_iCurShipCount(0)
	, m_iAddShipCount(0)
	, m_iSaveTrackCount(0)
	, m_iShowTrackCount(0)
{

}

CAddTestShipDlg::~CAddTestShipDlg()
{
}

void CAddTestShipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CUR_SHIP_COUNT, m_iCurShipCount);
	DDX_Text(pDX, IDC_EDIT_ADD_SHIP_COUNT, m_iAddShipCount);
	DDX_Text(pDX, IDC_EDIT1, m_iSaveTrackCount);
	DDX_Text(pDX, IDC_EDIT2, m_iShowTrackCount);
}


BEGIN_MESSAGE_MAP(CAddTestShipDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAddTestShipDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddTestShipDlg ��Ϣ��������

BOOL CAddTestShipDlg::OnInitDialog() 
{	
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	this->m_iCurShipCount = pYimaEncCtrl->GetOtherVesselCount();
	this->m_iSaveTrackCount = 10000;
	this->m_iShowTrackCount = 50;
	UpdateData(0);
	return TRUE;
}

void CAddTestShipDlg::OnBnClickedOk()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	UpdateData(1);
	
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	pYimaEncCtrl->SetIfShowSounding(1);
	//pYimaEncCtrl->SetDrawShipHeadingLineLen(15,10);//���ú�����
	//pYimaEncCtrl->SetDrawShipHeadingLineLen(15,10);//���ú�����
	pYimaEncCtrl->SetDrawShipOptions(true,false,false,true,0.1,false,2,this->m_iSaveTrackCount,this->m_iShowTrackCount,300);//���ñ�������켣��Ϣ��ʵ����һ��Ҫ���ô�һ�㣬����켣��10000������ʾ50��
	
	pYimaEncCtrl->SetDrawShipOptions(false,false,false,true,0.1,false,2,this->m_iSaveTrackCount,this->m_iShowTrackCount,300);

	if(this->m_iAddShipCount > 0)
	{	
		pYimaEncCtrl->SetIfShowSounding(0);
		//pYimaEncCtrl->SetDrawShipTrackStyle(true,1,2,RGB(255,255,0));//���ñ�����ǰ�켣��ʽ
		//pYimaEncCtrl->SetDrawShipTrackStyle(false,1,1,RGB(0,0,0));//��������������ǰ�켣��ʽ

		int typeID2 = pYimaEncCtrl->AddAisType("ais1"); //����AIS����(AIS TYPE)(����)
		pYimaEncCtrl->SetAisTypeInfo(typeID2, _T("ais1"), false, 1, 1, false, 0, 2, 500000, true,false, 200000, true);//���ø�AIS ���͵���ʾ���
		//false=ʹ���Զ������
		//1=ʹ���Զ������ID=1

		int typeID1 = pYimaEncCtrl->AddAisType("ais2"); //����AIS����(AIS TYPE)(����)
		pYimaEncCtrl->SetAisTypeInfo(typeID1, _T("ais2"), false, 4, 1, false, 0, 6, 500000, true,false, 200000, true);//���ø�AIS ���͵���ʾ���

		for (int vslNum = 0; vslNum < this->m_iAddShipCount; vslNum++)
		{
			#define MAX_RAND_VAL 32767
			long vslGeoX = (105 + (float)(rand() % MAX_RAND_VAL)/MAX_RAND_VAL * 40) * UNI_GEO_COOR_MULTI_FACTOR;
			long vslGeoY = (3 + (float)(rand() % MAX_RAND_VAL)/MAX_RAND_VAL * 40) * UNI_GEO_COOR_MULTI_FACTOR;
			float head = (float)(rand() % MAX_RAND_VAL)/MAX_RAND_VAL * 360;
			float speed = (float)(rand() % MAX_RAND_VAL)/MAX_RAND_VAL * 50;
		
			pYimaEncCtrl->AddOtherVessel(false, vslGeoX, vslGeoY, head, 90, 90, speed, speed);


			//pYimaEncCtrl->SetOtherVesselBasicInfo(
			//pYimaEncCtrl->SetOtherVesselCurrentInfo(


			int iShipPos = pYimaEncCtrl->GetOtherVesselCount() - 1;//�õ��ո����ӵĴ�������pos

			if(vslNum % 2 == 0)
			{
				pYimaEncCtrl->SetAisTargetType(iShipPos, typeID1);
			}
			else
			{
				pYimaEncCtrl->SetAisTargetType(iShipPos, typeID2);
			}	
			pYimaEncCtrl->SetShipTrackStyle(false, iShipPos, true, RGB(rand()%255,rand()%255,rand()%255), 3, true, 4, RGB(rand()%255,rand()%255,rand()%255));

			if(vslNum % 20 == 0)//��ʾ��ǰ�켣
			{
				int iShipId = pYimaEncCtrl->GetOtherVesselID(iShipPos);
				pYimaEncCtrl->SetShipTrackShowOrNot(false,false,iShipId,true);
			}	
			else
			{
				//int iShipId = pYimaEncCtrl->GetOtherVesselID(iShipPos);
				//pYimaEncCtrl->SetShipTrackShowOrNot(false,false,iShipId,false);
			}


			int iShipId = pYimaEncCtrl->GetOtherVesselID(iShipPos);
			pYimaEncCtrl->SetShipTrackShowOrNot(false,true,iShipId,true);

			long color = RGB(255,255,255);
			long lineColor = RGB(255,0,0);
			//pYimaEncCtrl->SetOtherVesselShowColor(iShipPos, false, color, false, lineColor);
			

		}

		long iShipCount = pYimaEncCtrl->GetOtherVesselCount();
		CString str;
		str.Format(_T("������ɣ���ǰ��������Ϊ��%d"),iShipCount);
		AfxMessageBox(str); 

		OnOK();
	}
}