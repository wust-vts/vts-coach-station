// GeoObjectInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yimaencviewer.h"
#include "GeoObjectInfoDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeoObjectInfoDlg dialog


CGeoObjectInfoDlg::CGeoObjectInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGeoObjectInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGeoObjectInfoDlg)
	m_strObjGeoType = _T("");
	m_strInnerLayerPos = _T("");
	m_strLayerPos = _T("");
	m_strLayerName = _T("");
	m_fScaleMin = 0.0f;
	m_strAreaOfFace = _T("");
	//}}AFX_DATA_INIT
	m_bIsS57OrUserMapObj = true; 
}


void CGeoObjectInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeoObjectInfoDlg)
	DDX_Control(pDX, IDC_MSFLEXGRID, m_attrGrid);
	DDX_Text(pDX, IDC_GEO_OBJECT_TYPE, m_strObjGeoType);
	DDX_Text(pDX, IDC_INNER_LAYER_ID, m_strInnerLayerPos);
	DDX_Text(pDX, IDC_LAYER_ID, m_strLayerPos);
	DDX_Text(pDX, IDC_LAYER_NAME, m_strLayerName);
	DDX_Text(pDX, IDC_SCALE_MIN_EDIT, m_fScaleMin);
	DDX_Text(pDX, IDC_EDIT_AREA, m_strAreaOfFace);
	//}}AFX_DATA_MAP 
}


BEGIN_MESSAGE_MAP(CGeoObjectInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CGeoObjectInfoDlg)
	ON_BN_CLICKED(IDC_SET_SCALEMIN_BUTTON, OnSetScaleminButton)
	//}}AFX_MSG_MAP 
	ON_BN_CLICKED(IDOK, &CGeoObjectInfoDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeoObjectInfoDlg message handlers

BOOL CGeoObjectInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl; 
	
	BSTR bstrLayerName = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
	BSTR bstrLayerToken = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
	long attrCount = 0;	
 	
//pYimaEncCtrl->SetIfShowText(false);

//pYimaEncCtrl->SetIfShowText(true);

	if (m_bIsS57OrUserMapObj)
	{
		((CEdit*)GetDlgItem(IDC_STATIC_AREA_UNIT))->ShowWindow(FALSE); 
		((CEdit*)GetDlgItem(IDC_STATIC_AREA))->ShowWindow(FALSE); 
		((CEdit*)GetDlgItem(IDC_STATIC_OBJ_TYPE))->ShowWindow(FALSE); 
		((CEdit*)GetDlgItem(IDC_ENTITY_OBJECT_RADIO))->ShowWindow(FALSE); 
		((CEdit*)GetDlgItem(IDC_SYSMBOL_OBJECT_RADIO))->ShowWindow(FALSE); 
		((CEdit*)GetDlgItem(IDC_EDIT_AREA))->ShowWindow(FALSE);  

		pYimaEncCtrl->GetLayerInfo(
			m_memObjPos.memMapPos, m_memObjPos.layerPos, &bstrLayerName, &bstrLayerToken, &attrCount);
		
		BSTR bstrObjectPos = ::SysAllocStringLen(NULL, 
			sizeof(MEM_GEO_OBJ_POS));
		memcpy(bstrObjectPos, &m_memObjPos, sizeof(MEM_GEO_OBJ_POS));

		int iGeoType = pYimaEncCtrl->GetObjectGeoType(&bstrObjectPos);
		
		switch (iGeoType)
		{
		case TYPE_POINT:
			m_strObjGeoType = "Point"; 
			break;
		case TYPE_LINE: 
			m_strObjGeoType = "Line"; 
			break; 
		case TYPE_FACE:  
			{
				int poCount = pYimaEncCtrl->GetFaceOutBndryCoorCount(&bstrObjectPos);
				
				BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * poCount);	
				int retPoCount = pYimaEncCtrl->GetFaceOutBndryCoors(&bstrObjectPos, &strLinePoints);
				
				m_strObjGeoType = "Face";  
				break;
			}
		case TYPE_COMBINED_OBJECT:
			m_strObjGeoType = "Combined Object";
			break;
		}
		
		m_strLayerName = bstrLayerName;
		m_strLayerName += " (";
		m_strLayerName += bstrLayerToken;
		m_strLayerName += ")";
		
		m_strLayerPos.Format("%d", m_memObjPos.layerPos);
		m_strInnerLayerPos.Format("%d", m_memObjPos.innerLayerPos);
		
		//UpdateData(false); 
		
		m_attrGrid.SetRows(attrCount + 1);
		m_attrGrid.SetCols(2);
		m_attrGrid.SetTextMatrix(0, 0, "Attribute");
		m_attrGrid.SetTextMatrix(0, 1, "Value");
		
		int curWidth = m_attrGrid.GetColWidth(0);
		m_attrGrid.SetColWidth(0, curWidth * 3);
		m_attrGrid.SetColWidth(1, curWidth * 3);  
		
		int curGridRowNum = 1;
		for (int groupNum = 0; groupNum < 2; groupNum ++)
		{ // group 0 : for filled attributes;  group 1 : for unfilled attributes;
			
			for (int attrNum = 0; attrNum < attrCount; attrNum ++)
			{
				BSTR bstrAttrVal = ::SysAllocStringLen(NULL, 
					MAX_ATTR_VAL_STRING_LEN);
				
				pYimaEncCtrl->GetObjectAttrString(&bstrObjectPos, attrNum, 
					&bstrAttrVal);
				
				CString strAttrVal = bstrAttrVal;
				int strLen = strAttrVal.GetLength();
				
				if ((strLen != 0 && groupNum == 0) || (strLen == 0 && groupNum == 1))
				{
					BSTR bstrAttrName =
						::SysAllocStringLen(NULL, MAX_NAMES_LEN);
					BSTR bstrAttrToken =
						::SysAllocStringLen(NULL, MAX_NAMES_LEN);
					
					pYimaEncCtrl->GetLayerObjectAttrInfo(m_memObjPos.memMapPos, m_memObjPos.layerPos,
						attrNum, NULL, &bstrAttrName, &bstrAttrToken);
					
					CString strAttrName = bstrAttrName;
					strAttrName += " (";
					strAttrName += bstrAttrToken;
					strAttrName += ")";
					
					m_attrGrid.SetTextMatrix(curGridRowNum, 0, strAttrName); 
					m_attrGrid.SetTextMatrix(curGridRowNum, 1, strAttrVal); 
					
					curGridRowNum ++;
					
					SysFreeString(bstrAttrName);
					SysFreeString(bstrAttrToken);
				}
				
				SysFreeString(bstrAttrVal);
			}
		}
		SysFreeString(bstrObjectPos);
	}
	else // 如果是显示自定义海图的物标对象
	{
		int layerPos = m_userMapObjPos.layerPos;
		int innerLayerPos = m_userMapObjPos.innerLayerObjectPos; 

		//获取当前的物标显示类型：实体物标、符号物标；并选中当前对应的物标显示类型
		BOOL bSymbolType;
		bool bResult = false;
		bResult = pYimaEncCtrl->tmGetObjectIsSymbolLineObject(layerPos, innerLayerPos, &bSymbolType);
		int nCheckID = IDC_ENTITY_OBJECT_RADIO;
		if (bSymbolType)
		{
			nCheckID = IDC_SYSMBOL_OBJECT_RADIO;
		}
		CheckRadioButton(IDC_ENTITY_OBJECT_RADIO, IDC_SYSMBOL_OBJECT_RADIO, nCheckID); 

		pYimaEncCtrl->tmGetLayerName(layerPos, &bstrLayerName);
		
		attrCount = pYimaEncCtrl->tmGetLayerObjectAttrCount(layerPos);
		//bool bShowOrNot = pYimaEncCtrl->tmGetObjectShowOrNot(layerPos,innerLayerPos);//是否显示
		//this->m_bShowOrNot = bShowOrNot;

		long iObjGeoType = -1;
		pYimaEncCtrl->tmGetObjectGeoType(layerPos,innerLayerPos,&iObjGeoType);//物标类型
		switch (iObjGeoType)
		{
		case TYPE_POINT:
			m_strObjGeoType = "Point"; 
			break;
		case TYPE_LINE: 
			m_strObjGeoType = "Line"; 
			break; 
		case TYPE_FACE: 
			m_strObjGeoType = "Face";  
			break; 
		case TYPE_COMBINED_OBJECT: 
			m_strObjGeoType = "CombinedObject";  
			break; 
		}
		

		m_strLayerName = bstrLayerName;
		
		m_strLayerPos.Format("%d", layerPos);
		m_strInnerLayerPos.Format("%d", innerLayerPos);

		M_GEO_TYPE geoType = (M_GEO_TYPE)pYimaEncCtrl->tmGetGeoObjectType(layerPos, innerLayerPos);
		if (geoType == TYPE_FACE)
		{
			int faceCoorCount = pYimaEncCtrl->tmGetFaceObjectCoorCount(layerPos, innerLayerPos);
			BSTR bstrWpPoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * faceCoorCount);	
			faceCoorCount = pYimaEncCtrl->tmGetFaceObjectCoors(layerPos, innerLayerPos, &bstrWpPoints);
			float area = pYimaEncCtrl->GetAreaOfGeoRegion(faceCoorCount, &bstrWpPoints) /1000000; 
			CString strArea;
			strArea.Format("%.5f", area); 
			m_strAreaOfFace = strArea;
			::SysFreeString(bstrWpPoints);
		}

		m_attrGrid.SetRows(attrCount + 1);
		m_attrGrid.SetCols(2);
		m_attrGrid.SetTextMatrix(0, 0, "Attribute");
		m_attrGrid.SetTextMatrix(0, 1, "Value");
		
		int curWidth = m_attrGrid.GetColWidth(0);
		m_attrGrid.SetColWidth(0, curWidth * 3);
		m_attrGrid.SetColWidth(1, curWidth * 3);  
		
		int curGridRowNum = 1;
		for (int groupNum = 0; groupNum < 2; groupNum ++)//显示属性值
		{ 
			
			for (int attrNum = 0; attrNum < attrCount; attrNum ++)
			{
				BSTR bstrAttrVal = ::SysAllocStringLen(NULL, 
					MAX_ATTR_VAL_STRING_LEN);
				
				pYimaEncCtrl->tmGetObjectAttrValueString(layerPos, innerLayerPos, 
					attrNum, &bstrAttrVal);
				
				CString strAttrVal = bstrAttrVal;
				int strLen = strAttrVal.GetLength();
				
				if ((strLen != 0 && groupNum == 0) || (strLen == 0 && groupNum == 1))
				{
					BSTR bstrAttrName =
						::SysAllocStringLen(NULL, MAX_NAMES_LEN);
					
					pYimaEncCtrl->tmGetLayerObjectAttrName(layerPos,
						attrNum, &bstrAttrName);
					
					CString strAttrName = bstrAttrName;
					
					m_attrGrid.SetTextMatrix(curGridRowNum, 0, strAttrName); 
					m_attrGrid.SetTextMatrix(curGridRowNum, 1, strAttrVal); 
					
					curGridRowNum ++;
					
					SysFreeString(bstrAttrName); 
				}
				
				SysFreeString(bstrAttrVal);
			}
		} 
	}

	SysFreeString(bstrLayerName);
	SysFreeString(bstrLayerToken);

	oldRow = oldCol = 1;
	MoveEditCtrl();

    UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CGeoObjectInfoDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CGeoObjectInfoDlg)
	ON_EVENT(CGeoObjectInfoDlg, IDC_MSFLEXGRID, -603 /* KeyPress */, OnKeyPressMsflexgrid, VTS_PI2)
	ON_EVENT(CGeoObjectInfoDlg, IDC_MSFLEXGRID, -600 /* Click */, OnClickMsflexgrid, VTS_NONE)
	ON_EVENT(CGeoObjectInfoDlg, IDC_MSFLEXGRID, -601 /* DblClick */, OnDblClickMsflexgrid, VTS_NONE)
	ON_EVENT(CGeoObjectInfoDlg, IDC_MSFLEXGRID, 1550 /* OLEStartDrag */, OnOLEStartDragMsflexgrid, VTS_PDISPATCH VTS_PI4)
	ON_EVENT(CGeoObjectInfoDlg, IDC_MSFLEXGRID, 70 /* RowColChange */, OnRowColChangeMsflexgrid, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CGeoObjectInfoDlg::OnKeyPressMsflexgrid(short FAR* KeyAscii) 
{
	// TODO: Add your control notification handler code here
	m_attrGrid.OnKeyPressGrid(KeyAscii);
}

void CGeoObjectInfoDlg::OnClickMsflexgrid() 
{
	// TODO: Add your control notification handler code here
	m_attrGrid.OnClickGrid();
}

void CGeoObjectInfoDlg::OnDblClickMsflexgrid() 
{
	// TODO: Add your control notification handler code here
	m_attrGrid.OnClickGrid();
} 

void CGeoObjectInfoDlg::MoveEditCtrl(void)
{
	int Row = m_attrGrid.GetRow();
	int Col = m_attrGrid.GetCol() ;

	CClientDC dc(this) ;			
	CRect Rect ;					
	m_attrGrid.GetWindowRect(&Rect) ;
	ScreenToClient(&Rect) ;
	int LeftCol = m_attrGrid.GetLeftCol();
	long Temp = 0;
	Temp += m_attrGrid.GetColWidth(0);
	for (int Index = 0; Index < (Col - LeftCol); Index++){	
		Temp += m_attrGrid.GetColWidth(LeftCol + Index) ;
	}
	Rect.left += ((Temp * (long)dc.GetDeviceCaps(LOGPIXELSX)) / 1440L) ;
	Rect.left = Rect.left + 3L ;

	int TopRow = m_attrGrid.GetTopRow() ;
	Temp = m_attrGrid.GetRowHeight(0L) ;
	for (int Index = 0; Index < (Row - TopRow ); Index++){		
		Temp += m_attrGrid.GetRowHeight(TopRow + Index) ;
	}
	Rect.top += ((Temp * (long)dc.GetDeviceCaps(LOGPIXELSY)) / 1440L) ;  
	Rect.top = Rect.top + 3L ;

	Temp = m_attrGrid.GetColWidth(Col) ;
	Temp = ((Temp * (long)dc.GetDeviceCaps(LOGPIXELSX)) / 1440L) ;  
	Rect.right = Rect.left + Temp ;

	Temp = m_attrGrid.GetRowHeight(Row) ;
	Temp = ((Temp * (long)dc.GetDeviceCaps(LOGPIXELSY)) / 1440L) ;
	Rect.bottom = Rect.top + Temp ;

    CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_MOVING) ;

	pEdit->MoveWindow(&Rect) ;
	pEdit->BringWindowToTop() ;
	pEdit->SetFocus();
	pEdit->SetLimitText(255) ;							
	pEdit->SetWindowText(m_attrGrid.GetText()) ;	
}

void CGeoObjectInfoDlg::SaveEditCtrlToCell()
{
	CString editText;
 	GetDlgItem(IDC_EDIT_MOVING)->GetWindowText(editText);
	m_attrGrid.SetTextMatrix(m_attrGrid.GetRow(), 
		m_attrGrid.GetCol(), editText);	
}

void CGeoObjectInfoDlg::GetEditCtrlTextFromCell()
{
	CString editText = m_attrGrid.GetTextMatrix(m_attrGrid.GetRow(), 
		   m_attrGrid.GetCol());	
 	GetDlgItem(IDC_EDIT_MOVING)->SetWindowText(editText);	
}

void CGeoObjectInfoDlg::OnOLEStartDragMsflexgrid(LPDISPATCH FAR* Data, long FAR* AllowedEffects) 
{
	// TODO: Add your control notification handler code here
	
}

void CGeoObjectInfoDlg::OnRowColChangeMsflexgrid() 
{
	// TODO: Add your control notification handler code here
	CString editText;
 	GetDlgItem(IDC_EDIT_MOVING)->GetWindowText(editText);	

	if (oldRow != 0 && oldCol != 0)
	{
		m_attrGrid.SetTextMatrix(oldRow, oldCol, editText);	
	}

	MoveEditCtrl();	

	oldCol = m_attrGrid.GetCol();
	oldRow = m_attrGrid.GetRow();	
}

void CGeoObjectInfoDlg::OnOK() 
{
	SaveEditCtrlToCell();
	// TODO: Add extra validation here

	int layerPos = 0;
	int innerLayerPos = 0; 
	
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;  
	
	if (!m_bIsS57OrUserMapObj)
	{
		layerPos = m_userMapObjPos.layerPos;
		innerLayerPos = m_userMapObjPos.innerLayerObjectPos;
		
		int attrCount = pYimaEncCtrl->tmGetLayerObjectAttrCount(layerPos); 
		
		for (int attrNum = 0; attrNum < attrCount; attrNum ++)
		{				
			CString strAttrVal = m_attrGrid.GetTextMatrix(attrNum + 1, 1); 
			pYimaEncCtrl->tmSetObjectAttrValueString(layerPos, innerLayerPos,
                attrNum, strAttrVal);
		} 
		
		int radioID = GetCheckedRadioButton(IDC_ENTITY_OBJECT_RADIO, IDC_SYSMBOL_OBJECT_RADIO);
		bool bSymbolType = false;
		if (radioID == IDC_ENTITY_OBJECT_RADIO)
		{
			bSymbolType = false;
		}
		else if (radioID == IDC_SYSMBOL_OBJECT_RADIO)
		{
			bSymbolType = true;
		}
		
		pYimaEncCtrl->tmSetObjectAsSymbolLineObject(layerPos, innerLayerPos, bSymbolType);
	}
	
	CDialog::OnOK();
}

void CGeoObjectInfoDlg::OnSetScaleminButton() 
{
	if (m_bIsS57OrUserMapObj)
	{
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
		CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl;  
		
		UpdateData(true);

		if (pYimaEncCtrl->SetGeoObjectScaleMin(m_memObjPos.memMapPos, m_memObjPos.layerPos, 
			m_memObjPos.innerLayerPos, m_fScaleMin))
		{
			AfxMessageBox("设置成功");
		}
		else
		{
			AfxMessageBox("设置失败");
		} 
	}
	else
	{
		AfxMessageBox("只有S57图幅才能设置，自定义物标不能设置。");
	}
}

//void CGeoObjectInfoDlg::OnBnClickedCheckShowOrNot()
//{
//	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);  
//	CYimaEnc* pYimaEncCtrl = &pFrame->m_yimaEncCtrl; 
//	UpdateData(true);
//	if (m_bIsS57OrUserMapObj)
//	{
//		pYimaEncCtrl->SetObjectShowOrNot(m_memObjPos.memMapPos,m_memObjPos.layerPos,m_memObjPos.innerLayerPos,m_bShowOrNot);
//	}
//	else
//	{
//		pYimaEncCtrl->tmSetObjectShowOrNot(m_userMapObjPos.layerPos,m_userMapObjPos.innerLayerObjectPos,m_bShowOrNot);
//	}
//}

void CGeoObjectInfoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
