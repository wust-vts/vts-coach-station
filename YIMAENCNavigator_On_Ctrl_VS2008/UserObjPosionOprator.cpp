// UserObjPosionOprator.cpp : 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "UserObjPosionOprator.h"
#include "YimaEnc.h"
#include "YIMAENCHEAD.H"
#include "MainFrm.h"
#include "PositionSettingDlg.h"

// CUserObjPosionOprator 对话框

IMPLEMENT_DYNAMIC(CUserObjPosionOprator, CDialog)

CUserObjPosionOprator::CUserObjPosionOprator(CWnd* pParent /*=NULL*/)
	: CDialog(CUserObjPosionOprator::IDD, pParent)
{
	m_curGeoType = TYPE_NULL;
	m_arrObjPoints = NULL;
}

CUserObjPosionOprator::~CUserObjPosionOprator()
{
	if(m_arrObjPoints != NULL)
	{
		delete[] m_arrObjPoints;
	}
}

void CUserObjPosionOprator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_OBJ_POSITION, m_ListObjPosition);
}


BEGIN_MESSAGE_MAP(CUserObjPosionOprator, CDialog)
	ON_BN_CLICKED(IDC_BTN_MODIFY_POSITON, &CUserObjPosionOprator::OnBnClickedBtnModifyPositon)
	ON_BN_CLICKED(IDC_BTN_DEL_POSITION, &CUserObjPosionOprator::OnBnClickedBtnDelPosition)
	ON_BN_CLICKED(IDC_BTN_ADD_POSITON, &CUserObjPosionOprator::OnBnClickedBtnAddPositon)
	ON_BN_CLICKED(IDC_BTN_APPEND_POSITON, &CUserObjPosionOprator::OnBnClickedBtnAppendPositon) 
END_MESSAGE_MAP()


// CUserObjPosionOprator 消息处理程序

BOOL CUserObjPosionOprator::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateObjPosition(); 
	m_ListObjPosition.SetCurSel(0);
	UpdateData(FALSE);
	CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->GetMainWnd());
	if (pMainFrm->m_yimaEncCtrl.GetMemMapCount() - 1 != m_curObjPos.memMapPos)
	{
		this->SetWindowText("物标坐标提取");	 
		CButton* pModifyBtn = (CButton*)GetDlgItem(IDC_BTN_MODIFY_POSITON);
		pModifyBtn->EnableWindow(FALSE);	 
		CButton* pDelBtn = (CButton*)GetDlgItem(IDC_BTN_DEL_POSITION);
		pDelBtn->EnableWindow(FALSE);
		CButton* pAddBtn = (CButton*)GetDlgItem(IDC_BTN_ADD_POSITON);
		pAddBtn->EnableWindow(FALSE);
		CButton* pAppendBtn = (CButton*)GetDlgItem(IDC_BTN_APPEND_POSITON);
		pAppendBtn->EnableWindow(FALSE);
	}		 
	return TRUE; 
}
 

void CUserObjPosionOprator::OnBnClickedBtnModifyPositon()
{
	// TODO: 在此添加控件通知处理程序代码 
	int iselPos = m_ListObjPosition.GetCurSel();
	if (iselPos < 0) return;
	CPositionSettingDlg positionSettingDlg;
	positionSettingDlg.m_geoPoX = m_arrObjPoints[iselPos].x;
	positionSettingDlg.m_geoPoY = m_arrObjPoints[iselPos].y;
	positionSettingDlg.DoModal();
	if (positionSettingDlg.m_bApply)
	{
		m_arrObjPoints[iselPos].x = positionSettingDlg.m_geoPoX; 
		m_arrObjPoints[iselPos].y = positionSettingDlg.m_geoPoY; 
		CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->GetMainWnd());
		CYimaEnc* pYimaEncCtrl = &(pMainFrm->m_yimaEncCtrl);
		if (m_curGeoType == TYPE_POINT)
		{
			pYimaEncCtrl->tmSetPointObjectCoor(m_curObjPos.layerPos, m_curObjPos.innerLayerPos, m_arrObjPoints[iselPos].x, m_arrObjPoints[iselPos].y);
		}
		else
		{
			pYimaEncCtrl->tmMoveOnePointOfLineObject(m_curObjPos.layerPos, m_curObjPos.innerLayerPos, iselPos, m_arrObjPoints[iselPos].x, m_arrObjPoints[iselPos].y);
		}
		pMainFrm->RedrawView();
		UpdateObjPosition(); 
		m_ListObjPosition.SetCurSel(iselPos);
		UpdateData(FALSE);
	}
}

//删除
void CUserObjPosionOprator::OnBnClickedBtnDelPosition()
{
	// TODO: 在此添加控件通知处理程序代码 
	CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->GetMainWnd());
	CYimaEnc* pYimaEncCtrl = &(pMainFrm->m_yimaEncCtrl);    
	if (m_curGeoType == TYPE_LINE)
	{
		int iLineCount = pYimaEncCtrl->tmGetLineObjectCoorCount(m_curObjPos.layerPos, m_curObjPos.innerLayerPos);
		if(iLineCount == 2)
		{
			AfxMessageBox("最后2个点，不能删除");
			return;
		}
	}
	else if (m_curGeoType == TYPE_FACE)
	{
		int iFaceCount = pYimaEncCtrl->tmGetLineObjectCoorCount(m_curObjPos.layerPos, m_curObjPos.innerLayerPos);
		if(iFaceCount == 3)
		{
			AfxMessageBox("最后3个点，不能删除");
			return;
		}
	}
	int iselPos = m_ListObjPosition.GetCurSel();
	if (iselPos < 0) return;
	pYimaEncCtrl->tmDeleteOnePointOfLineObject(m_curObjPos.layerPos, m_curObjPos.innerLayerPos, iselPos);
	pMainFrm->RedrawView();
	UpdateObjPosition();
	iselPos = iselPos -1 >= 0 ? iselPos -1 : 0;
	m_ListObjPosition.SetCurSel(iselPos);
	UpdateData(FALSE);
}

//插入
void CUserObjPosionOprator::OnBnClickedBtnAddPositon()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->GetMainWnd());
	CYimaEnc* pYimaEncCtrl = &(pMainFrm->m_yimaEncCtrl);
	int iselPos = m_ListObjPosition.GetCurSel();
	if (iselPos < 0) return;
	CPositionSettingDlg positionSettingDlg;
	positionSettingDlg.m_geoPoX = 0;
	positionSettingDlg.m_geoPoY = 0;
	positionSettingDlg.DoModal();
	if (positionSettingDlg.m_bApply)
	{
		long newGeoPointX, newGeoPointY; 
		newGeoPointX = positionSettingDlg.m_geoPoX;
		newGeoPointY = positionSettingDlg.m_geoPoY;
		pYimaEncCtrl->tmAddOnePointToLineOrFaceObject(m_curObjPos.layerPos, m_curObjPos.innerLayerPos, iselPos, newGeoPointX, newGeoPointY);	
		UpdateObjPosition(); 
		m_ListObjPosition.SetCurSel(iselPos);
		UpdateData(FALSE);
	}

}

//添加
void CUserObjPosionOprator::OnBnClickedBtnAppendPositon()
{

	CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->GetMainWnd());
	CYimaEnc* pYimaEncCtrl = &(pMainFrm->m_yimaEncCtrl);
	int iselPos = m_ListObjPosition.GetCurSel();
	if (iselPos < 0) return;
	CPositionSettingDlg positionSettingDlg;
	positionSettingDlg.m_geoPoX = 0;
	positionSettingDlg.m_geoPoY = 0;
	positionSettingDlg.DoModal();
	if (positionSettingDlg.m_bApply)
	{		
		M_POINT* arrNewPo = new M_POINT[m_iPointCount + 1];
		memcpy(arrNewPo, m_arrObjPoints, sizeof(M_POINT) * m_iPointCount);
		arrNewPo[m_iPointCount].x = positionSettingDlg.m_geoPoX;
		arrNewPo[m_iPointCount].y = positionSettingDlg.m_geoPoY;
		m_iPointCount ++;
		BSTR strPoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * m_iPointCount);  
		memcpy(strPoints, arrNewPo, sizeof(M_POINT) * m_iPointCount); 
		if(m_curGeoType == TYPE_LINE)
		{
			pYimaEncCtrl->tmSetLineObjectCoors(m_curObjPos.layerPos, m_curObjPos.innerLayerPos, m_iPointCount, &strPoints);
		}
		else if(m_curGeoType == TYPE_FACE)
		{
			pYimaEncCtrl->tmSetFaceObjectCoors(m_curObjPos.layerPos, m_curObjPos.innerLayerPos, m_iPointCount, &strPoints);
		} 
		::SysFreeString(strPoints);
		delete[] arrNewPo;
		UpdateObjPosition(); 
		m_ListObjPosition.SetCurSel(m_ListObjPosition.GetCount() - 1);
		UpdateData(FALSE);
	}
}

void CUserObjPosionOprator::UpdateObjPosition()
{
	m_ListObjPosition.ResetContent();
	CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->GetMainWnd());
	CYimaEnc* pYimaEncCtrl = &(pMainFrm->m_yimaEncCtrl);
																														  
	BSTR bstrObjPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));
	memcpy(bstrObjPos, &m_curObjPos, sizeof(MEM_GEO_OBJ_POS));
	if (m_arrObjPoints != NULL)
	{
		delete[] m_arrObjPoints;
		m_arrObjPoints = NULL;
	}

	m_curGeoType = pYimaEncCtrl->GetObjectGeoType(&bstrObjPos);
	CString strGeoPo;
	if (m_curGeoType == TYPE_POINT)
	{
		(CButton*)(GetDlgItem(IDC_BTN_ADD_POSITON))->EnableWindow(FALSE);
		(CButton*)(GetDlgItem(IDC_BTN_APPEND_POSITON))->EnableWindow(FALSE);
		(CButton*)(GetDlgItem(IDC_BTN_DEL_POSITION))->EnableWindow(FALSE);
		long retGeoPoX = 0, retGeoPoY = 0; 
		pYimaEncCtrl->GetPointObjectCoor(&bstrObjPos, &retGeoPoX, &retGeoPoY);
		//pYimaEncCtrl->tmGetPointObjectCoor(m_curObjPos.layerPos, m_curObjPos.innerLayerPos, &retGeoPoX, &retGeoPoY);
		m_arrObjPoints = new M_POINT[1];
		m_arrObjPoints[0].x = retGeoPoX;
		m_arrObjPoints[0].y = retGeoPoY;
		strGeoPo.Format(_T("%d, %d"), retGeoPoX, retGeoPoY);
		m_ListObjPosition.AddString(strGeoPo);
	} 
	else if (m_curGeoType == TYPE_LINE)
	{
		m_iPointCount = pYimaEncCtrl->GetLineObjectCoorCount(&bstrObjPos);   		
		m_arrObjPoints = new M_POINT[m_iPointCount];	  

		BSTR bstrLinePoints = ::SysAllocStringLen(NULL, m_iPointCount* sizeof(M_POINT));	 	
		pYimaEncCtrl->GetLineObjectCoors(&bstrObjPos, &bstrLinePoints);	  
		memcpy(m_arrObjPoints, bstrLinePoints, m_iPointCount * sizeof(M_POINT));
		SysFreeString(bstrLinePoints); 
		for (int i = 0; i< m_iPointCount; i++)
		{
			strGeoPo.Format(_T("%2d : %d, %d"), i, m_arrObjPoints[i].x, m_arrObjPoints[i].y);
			m_ListObjPosition.AddString(strGeoPo);
		}
	}
	else if (m_curGeoType == TYPE_FACE)
	{
		m_iPointCount = pYimaEncCtrl->GetFaceOutBndryCoorCount(&bstrObjPos);
		m_arrObjPoints = new M_POINT[m_iPointCount];	  

		BSTR bstrFacePoints = ::SysAllocStringLen(NULL, m_iPointCount* sizeof(M_POINT));	 	
		pYimaEncCtrl->GetFaceOutBndryCoors(&bstrObjPos, &bstrFacePoints);	
		memcpy(m_arrObjPoints, bstrFacePoints, m_iPointCount * sizeof(M_POINT));
		SysFreeString(bstrFacePoints); 
		for (int i = 0; i< m_iPointCount; i++)
		{
			strGeoPo.Format(_T("%2d : %d, %d"), i, m_arrObjPoints[i].x, m_arrObjPoints[i].y);
			m_ListObjPosition.AddString(strGeoPo);
		} 
	}
}



