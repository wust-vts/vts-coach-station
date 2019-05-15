// TestAreaWarnDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "TestAreaWarnDlg.h"
#include "MainFrm.h"


// CTestAreaWarnDlg 对话框

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


// CTestAreaWarnDlg 消息处理程序

void CTestAreaWarnDlg::OnBnClickedButtonAddTestData()
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;


	pYimaEncCtrl->CenterMap(1303000000,454000000);
	pYimaEncCtrl->SetCurrentScale(400000);
	if(this->m_bAddShip == false)//没添加过，则添加区域
	{
			/*
		pYimaEncCtrl->tmAppendObjectInLayer(0,TYPE_LINE);//添加一条线
		int iObjPos = pYimaEncCtrl->tmGetLayerObjectCount(0) - 1;	
		this->m_iObjPos = iObjPos;
		bool bSetStyle = pYimaEncCtrl->tmSetLineObjectStyleRefLib(0, iObjPos,1, true, RGB(255, 0, 0),true, 3);//设置显示样式

		BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 3);
				
				
		M_POINT rgnPoints[3];
		rgnPoints[0] = M_POINT(1300000000, 453000000);
		rgnPoints[1] = M_POINT(1305000000, 452000000);
		rgnPoints[2] = M_POINT(1306000000, 456000000);
	
			
		memcpy(strLinePoints, rgnPoints, sizeof(M_POINT) * 3);
		bool bSetCoor = pYimaEncCtrl->tmSetLineObjectCoors(0,iObjPos,3,&strLinePoints);
		::SysFreeString(strLinePoints);
*/
	
		pYimaEncCtrl->tmAppendObjectInLayer(0,TYPE_FACE);//添加一个面
		int iObjPos = pYimaEncCtrl->tmGetLayerObjectCount(0) - 1;	
		this->m_iObjPos = iObjPos;
		bool bSetStyle = pYimaEncCtrl->tmSetFaceObjectStyleRefLib(0, iObjPos,1, true, RGB(255, 0, 0),true, 70, false,0);//设置显示样式

		BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 3);
				
				
		M_POINT rgnPoints[3];
		rgnPoints[0] = M_POINT(1300000000, 453000000);
		rgnPoints[1] = M_POINT(1305000000, 452000000);
		rgnPoints[2] = M_POINT(1306000000, 456000000);
	
			
		memcpy(strLinePoints, rgnPoints, sizeof(M_POINT) * 3);
		bool bSetCoor = pYimaEncCtrl->tmSetFaceObjectCoors(0,iObjPos,3,&strLinePoints);
		::SysFreeString(strLinePoints);
		
 

		//添加船舶	
		int typeID = pYimaEncCtrl->AddAisType("warnShip"); //添加AIS类型(AIS TYPE)(在线)
		pYimaEncCtrl->SetAisTypeInfo(typeID, _T("warnShip"), false, 1, 1, false, 0, 2, 500000, true,false, 200000, true);//设置该AIS 类型的显示风格
		pYimaEncCtrl->SetDrawShipHeadingLineLen(15,10);//设置航向线
		pYimaEncCtrl->SetDrawShipOptions(false,false,false,true,0.1,false,2,100,100,300);//设置目标船舶
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
		
			//if(this->m_bAddShip)//更新
			//{
			//	int iShipPos = pYimaEncCtrl->GetOtherVesselPosOfID(m_arrWarnShipInfo[num].shipId);
			//	pYimaEncCtrl->SetOtherVesselCurrentInfo(iShipPos,vslGeoX,vslGeoY,head,90,90,speed,speed, NULL, NULL, NULL);
			//}
			//else//添加
			//{
			pYimaEncCtrl->AddOtherVessel(false, vslGeoX, vslGeoY, head, 90, 90, speed, speed);
			int iShipPos = pYimaEncCtrl->GetOtherVesselCount() - 1;
			pYimaEncCtrl->SetAisTargetType(iShipPos, typeID);//设置船舶样式
			int mmsi = 7000000 + num;
			CString strShipName;
			strShipName.Format(_T("渔船%d号"),num);
			pYimaEncCtrl->SetOtherVesselBasicInfo(iShipPos,100,30,strShipName,mmsi, NULL, 0);

			int iShipId = pYimaEncCtrl->GetOtherVesselID(iShipPos);
			CString strText;
			strText.Format(_T("%d"),iShipId);
			pYimaEncCtrl->SetOtherVesselShowText(iShipPos,true,strText,false,0,false,0);

			pYimaEncCtrl->SetShipTrackShowOrNot(false,false,iShipId,true);//显示轨迹
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
		int iObjMemMapPos = pYimaEncCtrl->GetMemMapCount() - 1;//自定义图幅pos
		CString strShipInArea = "";//船舶一直在区域内
		CString strShipOutToArea = "";//船舶使出区域
		CString strShipGoToArea = "";//船舶进入区域

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
				if(bShipInArea)//在区域内
				{
					if(this->m_arrWarnShipInfo[num].bInArea)//船舶一直在区域内
					{
						strShipInArea += strValue;
					}
					else//船舶驶入区域
					{
						strShipGoToArea += strValue;
					}

					this->m_arrWarnShipInfo[num].bInArea = true;
				}
				else//在区域外
				{
					if(this->m_arrWarnShipInfo[num].bInArea)//船舶驶出
					{
						strShipOutToArea += strValue;
					}
					else//船舶一直在区域外
					{					
					}

					this->m_arrWarnShipInfo[num].bInArea = false;
				}
			}
		}
		CString strMsgInfo = "";
		
		strMsgInfo += _T("区域内报警(船舶ID):") + strShipInArea + _T("\r\n");
		
		strMsgInfo += _T("闯入报警(船舶ID):") + strShipGoToArea + _T("\r\n");
		

		strMsgInfo += _T("驶出报警(船舶ID):") + strShipOutToArea + _T("\r\n");
		

		this->m_strWarnInfo = strMsgInfo;

		
	}
	else
	{
		AfxMessageBox(_T("请点击“添加测试数据”按钮先添加测试数据。")); 
	}

	UpdateData(0);
		
}

void CTestAreaWarnDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CTestAreaWarnDlg::OnBnClickedCheckNear()
{
	if(this->m_bAddShip)
	{
		UpdateData(1);

		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
		CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
		int iObjMemMapPos = pYimaEncCtrl->GetMemMapCount() - 1;//自定义图幅pos
		
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
				int iCheckLen = this->m_iCheckLen;//检测的距离
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

		strMsgInfo = _T("靠近区域报警:") + strAllResult + _T("\r\n");
		

		this->m_strNearShipId = strMsgInfo;
		
	}
	else
	{
		AfxMessageBox(_T("请点击“添加测试数据”按钮先添加测试数据。")); 
	}

	UpdateData(0);
} 
void CTestAreaWarnDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此处添加消息处理程序代码
}

void CTestAreaWarnDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	delete []m_arrWarnShipInfo;
	CDialog::OnClose();
}

BOOL CTestAreaWarnDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
