// TestLayerObjectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "TestLayerObjectDlg.h"
#include "MainFrm.h"

// CTestLayerObjectDlg 对话框

IMPLEMENT_DYNAMIC(CTestLayerObjectDlg, CDialog)

CTestLayerObjectDlg::CTestLayerObjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestLayerObjectDlg::IDD, pParent)
{
	this->m_iLayerCount = 10;
	this->m_bAddLayer = false;
	this->m_startLayerPos = -1;
}

CTestLayerObjectDlg::~CTestLayerObjectDlg()
{
}

void CTestLayerObjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestLayerObjectDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_LAYERS, &CTestLayerObjectDlg::OnBnClickedButtonAddLayers)
	ON_BN_CLICKED(IDC_BUTTON_ADD_OBJ, &CTestLayerObjectDlg::OnBnClickedButtonAddObj)
END_MESSAGE_MAP()


// CTestLayerObjectDlg 消息处理程序

void CTestLayerObjectDlg::OnBnClickedButtonAddLayers()
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;
	
	//int iLayerCount = pYimaEncCtrl->tmGetLayerCount();
	for(int i=0; i < pYimaEncCtrl->tmGetLayerCount(); i++)
	{
		BSTR bstrLayerName = ::SysAllocStringLen(NULL, 255);
		pYimaEncCtrl->tmGetLayerName(i,&bstrLayerName);
		CString strName = bstrLayerName;
		SysFreeString(bstrLayerName);
		CString str = _T("testLayer");	
		int iIndex = strName.Find(str,0);
		if(iIndex > -1)
		{
			pYimaEncCtrl->tmDeleteLayer(i);//删除图层
			i--;
		}
	}
	m_startLayerPos = pYimaEncCtrl->tmGetLayerCount();
	for(int iNum=0; iNum < this->m_iLayerCount; iNum++)
	{
		pYimaEncCtrl->tmAppendLayer(ALL_POINT);
		int iLayerPos = pYimaEncCtrl->tmGetLayerCount() - 1;
		CString layerName;
		layerName.Format(_T("testLayer%d"),iNum);
		pYimaEncCtrl->tmSetLayerName(iLayerPos, layerName);
		m_arrLayerPos[iNum] = iLayerPos;
	}	
	CString str;
	str.Format(_T("当前图层总数:%d"),pYimaEncCtrl->tmGetLayerCount());
	AfxMessageBox(str);
	this->m_bAddLayer = true;
}

void CTestLayerObjectDlg::OnBnClickedButtonAddObj()
{
	// TODO: 在此添加控件通知处理程序代码
	if(this->m_bAddLayer)
	{	
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
		CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;

		for(int i = m_startLayerPos; i < pYimaEncCtrl->tmGetLayerCount(); i++)
		{
			int iCurLayerPos = i;
			for(int iObjNum = 0;iObjNum < 1000; iObjNum++)
			{
				//随机生成点坐标
				#define MAX_RAND_VAL 32767
				long geoPoX = (110 + (float)(rand() % MAX_RAND_VAL)/MAX_RAND_VAL * 40) * UNI_GEO_COOR_MULTI_FACTOR;
				long geoPoY = (25 + (float)(rand() % MAX_RAND_VAL)/MAX_RAND_VAL * 20) * UNI_GEO_COOR_MULTI_FACTOR;

				
				pYimaEncCtrl->tmAppendObjectInLayer(iCurLayerPos,TYPE_POINT);//添加一个点
				int iObjPos = pYimaEncCtrl->tmGetLayerObjectCount(iCurLayerPos) - 1;
				pYimaEncCtrl->tmSetPointObjectCoor(iCurLayerPos,iObjPos,geoPoX,geoPoY);//设置坐标
				int iSymbolId = iObjNum % 10;
			
				switch(iSymbolId)
				{
					case 0:
						iSymbolId = 0;
						break;
					case 1:
						iSymbolId = 0;
						break;
					case 2:
						iSymbolId = 9;
						break;
					default:
						iSymbolId = 9;
						break;
				}
		
				pYimaEncCtrl->tmSetPointObjectStyleRefLib(iCurLayerPos,iObjPos,iSymbolId,false,0,1,0);//设置样式				
			}
		}

		AfxMessageBox(_T("添加物标完成"));
	}
	else
	{
		AfxMessageBox(_T("请点击“添加图层”，先添加测试图层"));
	}
}
