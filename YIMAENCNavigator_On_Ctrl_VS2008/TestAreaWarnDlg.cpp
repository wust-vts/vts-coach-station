// TestAreaWarnDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "TestAreaWarnDlg.h"
#include "MainFrm.h"


// CTestAreaWarnDlg �Ի���

IMPLEMENT_DYNAMIC(CTestAreaWarnDlg, CDialog)

CTestAreaWarnDlg::CTestAreaWarnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestAreaWarnDlg::IDD, pParent)
	, m_strWarnInfo(_T(""))
	, m_strNearShipId(_T(""))
	, m_iCheckLen(0)
{
	this->m_bAddShip = false;
}

CTestAreaWarnDlg::~CTestAreaWarnDlg()
{
}

void CTestAreaWarnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MSG, m_strWarnInfo);
	DDX_Text(pDX, IDC_EDIT2, m_strNearShipId);
	DDX_Text(pDX, IDC_EDIT1, m_iCheckLen);
}


BEGIN_MESSAGE_MAP(CTestAreaWarnDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TEST_DATA, &CTestAreaWarnDlg::OnBnClickedButtonAddTestData)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_WARN, &CTestAreaWarnDlg::OnBnClickedButtonCheckWarn)
	ON_BN_CLICKED(IDCANCEL, &CTestAreaWarnDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_NEAR, &CTestAreaWarnDlg::OnBnClickedCheckNear)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CTestAreaWarnDlg ��Ϣ��������

void CTestAreaWarnDlg::OnBnClickedButtonAddTestData()
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;


	pYimaEncCtrl->CenterMap(1303000000,454000000);
	pYimaEncCtrl->SetCurrentScale(400000);
	if(this->m_bAddShip == false)//û���ӹ�������������
	{
			/*
		pYimaEncCtrl->tmAppendObjectInLayer(0,TYPE_LINE);//����һ����
		int iObjPos = pYimaEncCtrl->tmGetLayerObjectCount(0) - 1;	
		this->m_iObjPos = iObjPos;
		bool bSetStyle = pYimaEncCtrl->tmSetLineObjectStyleRefLib(0, iObjPos,1, true, RGB(255, 0, 0),true, 3);//������ʾ��ʽ

		BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 3);
				
				
		M_POINT rgnPoints[3];
		rgnPoints[0] = M_POINT(1300000000, 453000000);
		rgnPoints[1] = M_POINT(1305000000, 452000000);
		rgnPoints[2] = M_POINT(1306000000, 456000000);
	
			
		memcpy(strLinePoints, rgnPoints, sizeof(M_POINT) * 3);
		bool bSetCoor = pYimaEncCtrl->tmSetLineObjectCoors(0,iObjPos,3,&strLinePoints);
		::SysFreeString(strLinePoints);
*/
	
		pYimaEncCtrl->tmAppendObjectInLayer(0,TYPE_FACE);//����һ����
		int iObjPos = pYimaEncCtrl->tmGetLayerObjectCount(0) - 1;	
		this->m_iObjPos = iObjPos;
		bool bSetStyle = pYimaEncCtrl->tmSetFaceObjectStyleRefLib(0, iObjPos,1, true, RGB(255, 0, 0),true, 70, false,0);//������ʾ��ʽ

		BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 3);
				
				
		M_POINT rgnPoints[3];
		rgnPoints[0] = M_POINT(1300000000, 453000000);
		rgnPoints[1] = M_POINT(1305000000, 452000000);
		rgnPoints[2] = M_POINT(1306000000, 456000000);
	
			
		memcpy(strLinePoints, rgnPoints, sizeof(M_POINT) * 3);
		bool bSetCoor = pYimaEncCtrl->tmSetFaceObjectCoors(0,iObjPos,3,&strLinePoints);
		::SysFreeString(strLinePoints);
		
 

		//���Ӵ���	
		int typeID = pYimaEncCtrl->AddAisType("warnShip"); //����AIS����(AIS TYPE)(����)
		pYimaEncCtrl->SetAisTypeInfo(typeID, _T("warnShip"), false, 1, 1, false, 0, 2, 500000, true,false, 200000, true);//���ø�AIS ���͵���ʾ���
		pYimaEncCtrl->SetDrawShipHeadingLineLen(15,10);//���ú�����
		pYimaEncCtrl->SetDrawShipOptions(false,false,false,true,0.1,false,2,100,100,300);//����Ŀ�괬��
		int shipCount =pYimaEncCtrl->GetOtherVesselCount();
		if (!m_bAddShip)
		{ 
			m_arrWarnShipInfo =new WarnShip[shipCount + 50];
			for (int i = 0; i< shipCount; i++)
			{
				m_arrWarnShipInfo[i].bInArea = false;
				m_arrWarnShipInfo[i].shipId = pYimaEncCtrl->GetOtherVesselID(i);
			} 
		}
		
		for(int num = 0;num < 50;num++)
		{
			#define MAX_RAND_VAL 32767
			long vslGeoX = (130 + (float)(rand() % MAX_RAND_VAL)/MAX_RAND_VAL * 1) * UNI_GEO_COOR_MULTI_FACTOR;
			long vslGeoY = (45 + (float)(rand() % MAX_RAND_VAL)/MAX_RAND_VAL * 1) * UNI_GEO_COOR_MULTI_FACTOR;
			float head = (float)(rand() % MAX_RAND_VAL)/MAX_RAND_VAL * 360;
			float speed = (float)(rand() % MAX_RAND_VAL)/MAX_RAND_VAL * 50;
		
			//if(this->m_bAddShip)//����
			//{
			//	int iShipPos = pYimaEncCtrl->GetOtherVesselPosOfID(m_arrWarnShipInfo[num].shipId);
			//	pYimaEncCtrl->SetOtherVesselCurrentInfo(iShipPos,vslGeoX,vslGeoY,head,90,90,speed,speed, NULL, NULL, NULL);
			//}
			//else//����
			//{
			pYimaEncCtrl->AddOtherVessel(false, vslGeoX, vslGeoY, head, 90, 90, speed, speed);
			int iShipPos = pYimaEncCtrl->GetOtherVesselCount() - 1;
			pYimaEncCtrl->SetAisTargetType(iShipPos, typeID);//���ô�����ʽ
			int mmsi = 7000000 + num;
			CString strShipName;
			strShipName.Format(_T("�洬%d��"),num);
			pYimaEncCtrl->SetOtherVesselBasicInfo(iShipPos,100,30,strShipName,mmsi, NULL, 0);

			int iShipId = pYimaEncCtrl->GetOtherVesselID(iShipPos);
			CString strText;
			strText.Format(_T("%d"),iShipId);
			pYimaEncCtrl->SetOtherVesselShowText(iShipPos,true,strText,false,0,false,0);

			pYimaEncCtrl->SetShipTrackShowOrNot(false,false,iShipId,true);//��ʾ�켣
			WarnShip warnShip;
			warnShip.bInArea = false;
			warnShip.shipId = iShipId; 
			m_arrWarnShipInfo[shipCount + num] = warnShip; 
		}
		
		this->m_bAddShip = true;
		SetTimer(2, 500, NULL);  
	}
	//OnBnClickedButtonCheckWarn();
	//::AfxBeginThread(&CTestAreaWarnDlg::MyThreadFunction, _T("dd"));
}

void CTestAreaWarnDlg::OnBnClickedButtonCheckWarn()
{
	if(this->m_bAddShip)
	{
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
		CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
		int iObjMemMapPos = pYimaEncCtrl->GetMemMapCount() - 1;//�Զ���ͼ��pos
		CString strShipInArea = "";//����һֱ��������
		CString strShipOutToArea = "";//����ʹ������
		CString strShipGoToArea = "";//������������

		int shipCount = pYimaEncCtrl->GetOtherVesselCount();
		for(int num=0;num < shipCount;num++)
		{
			int iShipPos = pYimaEncCtrl->GetOtherVesselPosOfID(m_arrWarnShipInfo[num].shipId);
			BOOL bArpaOrAis = FALSE;
			long geoPoX = 0;
			long geoPoY = 0;
			float heading = 0;
			float courseOverGround = 0;
			float courseThrghWater = 0;
			float speedOverGround = 0;
			float speedThrghWater = 0;
			bool bResult = pYimaEncCtrl->GetOtherVesselCurrentInfo(iShipPos,&bArpaOrAis,&geoPoX,&geoPoY,&heading,&courseOverGround,&courseThrghWater,&speedOverGround,&speedThrghWater, NULL, NULL);
			int iShipId = pYimaEncCtrl->GetOtherVesselID(iShipPos);
			if(bResult)
			{
				CString strValue;
				bool bShipInArea = pYimaEncCtrl->IsPointInFaceGeoObject(geoPoX,geoPoY,iObjMemMapPos,0,m_iObjPos,true);
				strValue.Format(_T("%d,"),iShipId);
				if(bShipInArea)//��������
				{
					if(this->m_arrWarnShipInfo[num].bInArea)//����һֱ��������
					{
						strShipInArea += strValue;
					}
					else//����ʻ������
					{
						strShipGoToArea += strValue;
					}

					this->m_arrWarnShipInfo[num].bInArea = true;
				}
				else//��������
				{
					if(this->m_arrWarnShipInfo[num].bInArea)//����ʻ��
					{
						strShipOutToArea += strValue;
					}
					else//����һֱ��������
					{					
					}

					this->m_arrWarnShipInfo[num].bInArea = false;
				}
			}
		}
		CString strMsgInfo = "";
		
		strMsgInfo += _T("�����ڱ���(����ID):") + strShipInArea + _T("\r\n");
		
		strMsgInfo += _T("���뱨��(����ID):") + strShipGoToArea + _T("\r\n");
		

		strMsgInfo += _T("ʻ������(����ID):") + strShipOutToArea + _T("\r\n");
		

		this->m_strWarnInfo = strMsgInfo;

		
	}
	else
	{
		AfxMessageBox(_T("���������Ӳ������ݡ���ť�����Ӳ������ݡ�")); 
	}

	UpdateData(0);
		
}

void CTestAreaWarnDlg::OnBnClickedCancel()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	OnCancel();
}

void CTestAreaWarnDlg::OnBnClickedCheckNear()
{
	if(this->m_bAddShip)
	{
		UpdateData(1);

		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
		CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
		int iObjMemMapPos = pYimaEncCtrl->GetMemMapCount() - 1;//�Զ���ͼ��pos
		
		CString strAllResult = "";
		int shipCount = pYimaEncCtrl->GetOtherVesselCount();
		for(int num=0;num < shipCount;num++)
		{
			int iShipPos = pYimaEncCtrl->GetOtherVesselPosOfID(this->m_arrWarnShipInfo[num].shipId);
			BOOL bArpaOrAis = FALSE;
			long geoPoX = 0;
			long geoPoY = 0;
			float heading = 0;
			float courseOverGround = 0;
			float courseThrghWater = 0;
			float speedOverGround = 0;
			float speedThrghWater = 0;
			bool bResult = pYimaEncCtrl->GetOtherVesselCurrentInfo(iShipPos,&bArpaOrAis,&geoPoX,&geoPoY,&heading,&courseOverGround,&courseThrghWater,&speedOverGround,&speedThrghWater, NULL, NULL);
			int iShipId = pYimaEncCtrl->GetOtherVesselID(iShipPos);
			if(bResult)
			{
				int iCheckLen = this->m_iCheckLen;//���ľ���
				BOOL bShipNearObj = 0;
				pYimaEncCtrl->IsGeoObjectNearPoint(iObjMemMapPos, 0, m_iObjPos, geoPoX, geoPoY, iCheckLen, &bShipNearObj);
				if(bShipNearObj)
				{
					CString strValue;				
					strValue.Format(_T("%d,"),iShipId);

					strAllResult += strValue;
				}
			}
		}
		CString strMsgInfo = "";

		strMsgInfo = _T("�������򱨾�:") + strAllResult + _T("\r\n");
		

		this->m_strNearShipId = strMsgInfo;
		
	}
	else
	{
		AfxMessageBox(_T("���������Ӳ������ݡ���ť�����Ӳ������ݡ�")); 
	}

	UpdateData(0);
} 
void CTestAreaWarnDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	if (nIDEvent != 2 || !m_bAddShip)
	{
		return;
	}
	UpdateData(1);
	OnBnClickedButtonCheckWarn();
	OnBnClickedCheckNear();
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	pFrame->RedrawView();
	CDialog::OnTimer(nIDEvent);
}

void CTestAreaWarnDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);  
	  
	if(m_bAddShip)
	{
		CMainFrame* pMainFrm =(CMainFrame*)(AfxGetApp()->m_pMainWnd);
		CYimaEnc* pYimaEncCtrl = &pMainFrm->m_yimaEncCtrl;
		int shipCount =pYimaEncCtrl->GetOtherVesselCount();
		m_arrWarnShipInfo =new WarnShip[shipCount];
		for (int i = 0; i< shipCount; i++)
		{
			m_arrWarnShipInfo[i].bInArea = false;
			m_arrWarnShipInfo[i].shipId = pYimaEncCtrl->GetOtherVesselID(i);
		} 
		SetTimer(2, 500, NULL);  
	}
	// TODO: �ڴ˴�������Ϣ�����������
}

void CTestAreaWarnDlg::OnClose()
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	delete []m_arrWarnShipInfo;
	CDialog::OnClose();
}

BOOL CTestAreaWarnDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ����Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}