// SelOwnShipHistoryTrackDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "SelOwnShipHistoryTrackDlg.h"
#include "MainFrm.h"


// CSelOwnShipHistoryTrackDlg 对话框

IMPLEMENT_DYNAMIC(CSelOwnShipHistoryTrackDlg, CDialog)

CSelOwnShipHistoryTrackDlg::CSelOwnShipHistoryTrackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelOwnShipHistoryTrackDlg::IDD, pParent)
	, m_strMsg(_T(""))
	, m_startDate(COleDateTime::GetCurrentTime())
	, m_startTimeMini(COleDateTime::GetCurrentTime())
	, m_endDate(COleDateTime::GetCurrentTime())
	, m_endTimeMini(COleDateTime::GetCurrentTime())
	,m_iCurTrackCount(0)
	,m_iLinePos(-1)
{

}

CSelOwnShipHistoryTrackDlg::~CSelOwnShipHistoryTrackDlg()
{
}

void CSelOwnShipHistoryTrackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_MSG, m_strMsg);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START_DATE, m_dtStartTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START_DATE, m_startDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START_TIME, m_startTimeMini);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END_DATE, m_dtEndTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END_DATE, m_endDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END_TIME, m_endTimeMini);
}


BEGIN_MESSAGE_MAP(CSelOwnShipHistoryTrackDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CSelOwnShipHistoryTrackDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SEL, &CSelOwnShipHistoryTrackDlg::OnBnClickedButtonSel)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_IN_MAP, &CSelOwnShipHistoryTrackDlg::OnBnClickedButtonDrawInMap)
END_MESSAGE_MAP()


// CSelOwnShipHistoryTrackDlg 消息处理程序

void CSelOwnShipHistoryTrackDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

//查询轨迹
void CSelOwnShipHistoryTrackDlg::OnBnClickedButtonSel()
{
	UpdateData(1);
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

	M_TIME mStartTime,mEndTime;
	mStartTime = M_TIME(m_startDate.GetYear(),m_startDate.GetMonth(),m_startDate.GetDay(),m_startTimeMini.GetHour(),m_startTimeMini.GetMinute(),m_startTimeMini.GetSecond());
	mEndTime = M_TIME(m_endDate.GetYear(),m_endDate.GetMonth(),m_endDate.GetDay(),m_endTimeMini.GetHour(),m_endTimeMini.GetMinute(),m_endTimeMini.GetSecond());
	
	BSTR bstrStartTime = ::SysAllocStringLen(NULL, sizeof(M_TIME));
	BSTR bstrEndTime = ::SysAllocStringLen(NULL, sizeof(M_TIME));
	
		
	M_TIME arrStartTime[1];
	M_TIME arrEndTime[1];
	arrStartTime[0] = mStartTime;
	arrEndTime[0] = mEndTime;
	
	memcpy(bstrStartTime, arrStartTime, sizeof(M_TIME));
	memcpy(bstrEndTime, arrEndTime, sizeof(M_TIME));

	int iMaxGetTrackPoCount = 5000;//最多获取5000个点
	BSTR bstrTrackPoints = ::SysAllocStringLen(NULL, sizeof(TrackPoint) * iMaxGetTrackPoCount);	
	long iRetTrackPoCount = 0;

	BSTR bstrTrackStartTime = ::SysAllocStringLen(NULL, sizeof(M_TIME));
	long lResult = pYimaEncCtrl->GetHistoryTrackPointsByTime(1,&bstrStartTime,&bstrEndTime,&bstrTrackStartTime, &bstrTrackPoints,&iRetTrackPoCount);
	this->m_iCurTrackCount = 0;
	if(iRetTrackPoCount > 0)
	{

		M_TIME* pmTrackStartTime = (M_TIME*)bstrTrackStartTime;
		m_mHistoryTrackStartTime = *pmTrackStartTime;//历史轨迹的最早时间，因为返回的轨迹点信息里面的时间是与这个时间差值

		int iPoCount = iRetTrackPoCount;
		TrackPoint* pArrTrackPoint = new TrackPoint[iPoCount];

		memcpy(pArrTrackPoint, bstrTrackPoints, sizeof(TrackPoint) * iRetTrackPoCount);
		
		for(int i = 0; i < iRetTrackPoCount; i++)
		{
			TrackPoint curTrackPoint = pArrTrackPoint[i];
			this->m_arrTrackPoints[m_iCurTrackCount] = curTrackPoint;
			m_iCurTrackCount++;
		}
		delete[]  pArrTrackPoint;
	}
	CString strValue;
	strValue.Format(_T("当前查询到轨迹点数量为：%d"),iRetTrackPoCount);

	this->m_strMsg = strValue;


	::SysFreeString(bstrStartTime);
	::SysFreeString(bstrEndTime);
	::SysFreeString(bstrTrackPoints);
	::SysFreeString(bstrTrackStartTime);
	UpdateData(0);
}

//在海图上绘制出历史轨迹
void CSelOwnShipHistoryTrackDlg::OnBnClickedButtonDrawInMap()
{
	if(m_iCurTrackCount > 0)
	{
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);	
		CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
		//当做一条自定义图层的线物标来展示
		long iLayerPos = 0; //自定义综合图层
		if(m_iLinePos == -1)
		{			
			pYimaEncCtrl->tmAppendObjectInLayer(iLayerPos,TYPE_LINE);//给自定义图层添加一条线
			m_iLinePos = pYimaEncCtrl->tmGetLayerObjectCount(iLayerPos) - 1;
			pYimaEncCtrl->tmSetLineObjectStyleRefLib(iLayerPos,m_iLinePos,1,true,RGB(0,0,0),true,5);//设置样式
		}
				
		M_POINT* pGeoPoints = new M_POINT[m_iCurTrackCount];

		for(int i=0; i < m_iCurTrackCount; i++)
		{
			pGeoPoints[i] = this->m_arrTrackPoints[i].ptPoint;//轨迹点坐标
			M_TIME mTrackPoTime = GetTimeAfterSeconds(m_mHistoryTrackStartTime,this->m_arrTrackPoints[i].iOffsetTime);//当前轨迹点的时间
			int iOffsetTime = this->m_arrTrackPoints[i].iOffsetTime;
		}

		BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * m_iCurTrackCount);
		memcpy(strLinePoints, pGeoPoints, sizeof(M_POINT) * m_iCurTrackCount);
			
		bool bResult = pYimaEncCtrl->tmSetLineObjectCoors(iLayerPos, m_iLinePos, m_iCurTrackCount, &strLinePoints);
			
		::SysFreeString(strLinePoints);


		pYimaEncCtrl->CenterMap(pGeoPoints[0].x,pGeoPoints[0].y);
		pYimaEncCtrl->Invalidate(1);
	}
	else
	{
		AfxMessageBox(_T("当前没有查询到历史轨迹点数据。"));
	}
}
