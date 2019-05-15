// GetDepInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "GetDepInfoDlg.h"
#include "MainFrm.h" 

// CGetDepInfoDlg 对话框

IMPLEMENT_DYNAMIC(CGetDepInfoDlg, CDialog)

CGetDepInfoDlg::CGetDepInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetDepInfoDlg::IDD, pParent)
	, m_iMemMapPos(0)
	, m_iMemMapCount(0)
	, m_strCurMapName(_T(""))
	, m_strDepcntInfo(_T(""))
	, m_strCoalneInfo(_T(""))
{

}

CGetDepInfoDlg::~CGetDepInfoDlg()
{
}

void CGetDepInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MEM_POS, m_iMemMapPos);
	DDX_Text(pDX, IDC_EDIT3, m_iMemMapCount);
	DDX_Text(pDX, IDC_EDIT4, m_strCurMapName);
	DDX_Text(pDX, IDC_EDIT1, m_strDepcntInfo);
	DDX_Text(pDX, IDC_EDIT2, m_strCoalneInfo);
}


BEGIN_MESSAGE_MAP(CGetDepInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CGetDepInfoDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


BOOL CGetDepInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	long iMemMapCount = pYimaEncCtrl->GetMemMapCount();//获取内存中海图数量
	m_iMemMapCount = iMemMapCount;

	UpdateData(false);
	return TRUE;
}
// CGetDepInfoDlg 消息处理程序

void CGetDepInfoDlg::OnBnClickedButton1()
{
	UpdateData(true);

	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	long iMemMapCount = pYimaEncCtrl->GetMemMapCount();
	
 	if(m_iMemMapPos < iMemMapCount)
	{
		BSTR bstrMapName = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);

		pYimaEncCtrl->GetMemMapInfo(m_iMemMapPos,NULL,&bstrMapName,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
		m_strCurMapName = bstrMapName;

		m_strDepcntInfo = "";
		m_strCoalneInfo = "";
		long iMemmMapPos = m_iMemMapPos;
		long lDepcntLayerPos = pYimaEncCtrl->GetLayerPosByToken(iMemmMapPos,"DEPCNT");//根据等深线的图层缩写来获取图层的索引posid

		if (lDepcntLayerPos > 0)//读取等深线数据
        {
			CString strDepcntInfo = "";
			CString strValue = "";

			long iLayerObjectCount = pYimaEncCtrl->GetLayerObjectCountOfMap(iMemmMapPos,lDepcntLayerPos);//获取等深线图层所有的物标
			strValue.Format(_T("%d"),iLayerObjectCount);
			strDepcntInfo += _T("等深线总数:") + strValue + _T("-----");
			for (int layerObjNum = 0; layerObjNum < iLayerObjectCount; layerObjNum++)
            {
				if(m_strDepcntInfo != "")
				{
					break;//这里只显示第一条等深线数据
				}
				//打包pos信息
				MEM_GEO_OBJ_POS memObjPos;
				memObjPos.memMapPos = iMemmMapPos;
				memObjPos.layerPos = lDepcntLayerPos;
				memObjPos.innerLayerPos = layerObjNum;				
				BSTR bstrObjectPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));
				memcpy(bstrObjectPos, &memObjPos, sizeof(MEM_GEO_OBJ_POS));

				long iObjGeoType = pYimaEncCtrl->GetObjectGeoType(&bstrObjectPos);//获取物标类型

				if (iObjGeoType == 0)//点类型
                {

				}
				else if(iObjGeoType == 2)//线类型
				{	

					BSTR bstrAttrValue = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
					pYimaEncCtrl->GetObjectAttrString(&bstrObjectPos,0,&bstrAttrValue);//获取等深线的数值
					CString strAttrValue =  bstrAttrValue;
					strDepcntInfo += _T("第一条数据：等深线值：") + strAttrValue + _T("--坐标：");

					BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 10000);	
					long iPoCount = pYimaEncCtrl->GetLineObjectCoors(&bstrObjectPos,&strLinePoints);//获取等深线的坐标，iPoCount为坐标点数量
					
					//解析等深线的坐标点
					M_POINT arrLinePoints[10000];
					memcpy(arrLinePoints, strLinePoints, sizeof(M_POINT) * iPoCount);	
					
					for(int i=0; i < iPoCount; i++)
					{
						strValue.Format(_T("(%d,%d)"),arrLinePoints[i].x,arrLinePoints[i].y);
						strDepcntInfo += strValue + _T(";");
					}

					m_strDepcntInfo = strDepcntInfo;

					::SysFreeString(bstrAttrValue);
					::SysFreeString(strLinePoints);
				}
				if (iObjGeoType == 3)//面类型
				{					
				}						 
				
			}
			if(m_strDepcntInfo == "")
			{
				m_strDepcntInfo = strDepcntInfo;
			}
		}
		else
		{
			m_strDepcntInfo = _T("该图幅:%s没有等深线数据。",m_strCurMapName);
		}

//-----------------------------------------------------------------------------------------------------------------------------------------
		long lCoalneLayerPos = pYimaEncCtrl->GetLayerPosByToken(iMemmMapPos,"COALNE");//根据海岸线的图层缩写来获取图层的索引posid

		if (lCoalneLayerPos > 0)//读取海岸线数据
        {
			CString strCoalneInfo = "";
			CString strValue = "";

			long iLayerObjectCount = pYimaEncCtrl->GetLayerObjectCountOfMap(iMemmMapPos,lCoalneLayerPos);//获取等深线图层所有的物标
			strValue.Format(_T("%d"),iLayerObjectCount);
			strCoalneInfo += _T("海岸线总数:") + strValue + _T("-----");
			for (int layerObjNum = 0; layerObjNum < iLayerObjectCount; layerObjNum++)
            {
				if(m_strCoalneInfo != "")
				{
					break;//这里只显示第一条海岸线数据
				}
				//打包pos信息
				MEM_GEO_OBJ_POS memObjPos;
				memObjPos.memMapPos = iMemmMapPos;
				memObjPos.layerPos = lCoalneLayerPos;
				memObjPos.innerLayerPos = layerObjNum;				
				BSTR bstrObjectPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));
				memcpy(bstrObjectPos, &memObjPos, sizeof(MEM_GEO_OBJ_POS));

				long iObjGeoType = pYimaEncCtrl->GetObjectGeoType(&bstrObjectPos);//获取物标类型

				if (iObjGeoType == 0)//点类型
                {

				}
				else if(iObjGeoType == 2)//线类型
				{	

					BSTR bstrAttrValue = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
					pYimaEncCtrl->GetObjectAttrString(&bstrObjectPos,0,&bstrAttrValue);//获取等深线的数值
					CString strAttrValue =  bstrAttrValue;
					strCoalneInfo += _T("第一条数据坐标：");

					BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 10000);	
					long iPoCount = pYimaEncCtrl->GetLineObjectCoors(&bstrObjectPos,&strLinePoints);//获取等深线的坐标，iPoCount为坐标点数量
					
					//解析海岸线的坐标点
					M_POINT arrLinePoints[10000];
					memcpy(arrLinePoints, strLinePoints, sizeof(M_POINT) * iPoCount);	
					
					for(int i=0; i < iPoCount; i++)
					{
						strValue.Format(_T("(%d,%d)"),arrLinePoints[i].x,arrLinePoints[i].y);
						strCoalneInfo += strValue + _T(";");
					}

					m_strCoalneInfo = strCoalneInfo;

					::SysFreeString(bstrAttrValue);
					::SysFreeString(strLinePoints);
				}
				if (iObjGeoType == 3)//面类型
				{					
				}						 
				
			}
			if(m_strCoalneInfo == "")
			{
				m_strCoalneInfo = strCoalneInfo;
			}
		}
		else
		{
			m_strCoalneInfo = _T("该图幅:%s没有海岸线数据。",m_strCurMapName);
		}
	}
	else
	{
		m_strDepcntInfo = _T("内存中没有该posid的图幅，无法获取信息。");
		m_strCoalneInfo = _T("内存中没有该posid的图幅，无法获取信息。");
	}

	UpdateData(false);

}
