// GetDepInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "GetDepInfoDlg.h"
#include "MainFrm.h" 

// CGetDepInfoDlg �Ի���

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
	long iMemMapCount = pYimaEncCtrl->GetMemMapCount();//��ȡ�ڴ��к�ͼ����
	m_iMemMapCount = iMemMapCount;

	UpdateData(false);
	return TRUE;
}
// CGetDepInfoDlg ��Ϣ��������

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
		long lDepcntLayerPos = pYimaEncCtrl->GetLayerPosByToken(iMemmMapPos,"DEPCNT");//���ݵ����ߵ�ͼ����д����ȡͼ�������posid

		if (lDepcntLayerPos > 0)//��ȡ����������
        {
			CString strDepcntInfo = "";
			CString strValue = "";

			long iLayerObjectCount = pYimaEncCtrl->GetLayerObjectCountOfMap(iMemmMapPos,lDepcntLayerPos);//��ȡ������ͼ�����е����
			strValue.Format(_T("%d"),iLayerObjectCount);
			strDepcntInfo += _T("����������:") + strValue + _T("-----");
			for (int layerObjNum = 0; layerObjNum < iLayerObjectCount; layerObjNum++)
            {
				if(m_strDepcntInfo != "")
				{
					break;//����ֻ��ʾ��һ������������
				}
				//���pos��Ϣ
				MEM_GEO_OBJ_POS memObjPos;
				memObjPos.memMapPos = iMemmMapPos;
				memObjPos.layerPos = lDepcntLayerPos;
				memObjPos.innerLayerPos = layerObjNum;				
				BSTR bstrObjectPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));
				memcpy(bstrObjectPos, &memObjPos, sizeof(MEM_GEO_OBJ_POS));

				long iObjGeoType = pYimaEncCtrl->GetObjectGeoType(&bstrObjectPos);//��ȡ�������

				if (iObjGeoType == 0)//������
                {

				}
				else if(iObjGeoType == 2)//������
				{	

					BSTR bstrAttrValue = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
					pYimaEncCtrl->GetObjectAttrString(&bstrObjectPos,0,&bstrAttrValue);//��ȡ�����ߵ���ֵ
					CString strAttrValue =  bstrAttrValue;
					strDepcntInfo += _T("��һ�����ݣ�������ֵ��") + strAttrValue + _T("--���꣺");

					BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 10000);	
					long iPoCount = pYimaEncCtrl->GetLineObjectCoors(&bstrObjectPos,&strLinePoints);//��ȡ�����ߵ����꣬iPoCountΪ���������
					
					//���������ߵ������
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
				if (iObjGeoType == 3)//������
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
			m_strDepcntInfo = _T("��ͼ��:%sû�е��������ݡ�",m_strCurMapName);
		}

//-----------------------------------------------------------------------------------------------------------------------------------------
		long lCoalneLayerPos = pYimaEncCtrl->GetLayerPosByToken(iMemmMapPos,"COALNE");//���ݺ����ߵ�ͼ����д����ȡͼ�������posid

		if (lCoalneLayerPos > 0)//��ȡ����������
        {
			CString strCoalneInfo = "";
			CString strValue = "";

			long iLayerObjectCount = pYimaEncCtrl->GetLayerObjectCountOfMap(iMemmMapPos,lCoalneLayerPos);//��ȡ������ͼ�����е����
			strValue.Format(_T("%d"),iLayerObjectCount);
			strCoalneInfo += _T("����������:") + strValue + _T("-----");
			for (int layerObjNum = 0; layerObjNum < iLayerObjectCount; layerObjNum++)
            {
				if(m_strCoalneInfo != "")
				{
					break;//����ֻ��ʾ��һ������������
				}
				//���pos��Ϣ
				MEM_GEO_OBJ_POS memObjPos;
				memObjPos.memMapPos = iMemmMapPos;
				memObjPos.layerPos = lCoalneLayerPos;
				memObjPos.innerLayerPos = layerObjNum;				
				BSTR bstrObjectPos = ::SysAllocStringLen(NULL, sizeof(MEM_GEO_OBJ_POS));
				memcpy(bstrObjectPos, &memObjPos, sizeof(MEM_GEO_OBJ_POS));

				long iObjGeoType = pYimaEncCtrl->GetObjectGeoType(&bstrObjectPos);//��ȡ�������

				if (iObjGeoType == 0)//������
                {

				}
				else if(iObjGeoType == 2)//������
				{	

					BSTR bstrAttrValue = ::SysAllocStringLen(NULL, MAX_NAMES_LEN);
					pYimaEncCtrl->GetObjectAttrString(&bstrObjectPos,0,&bstrAttrValue);//��ȡ�����ߵ���ֵ
					CString strAttrValue =  bstrAttrValue;
					strCoalneInfo += _T("��һ���������꣺");

					BSTR strLinePoints = ::SysAllocStringLen(NULL, sizeof(M_POINT) * 10000);	
					long iPoCount = pYimaEncCtrl->GetLineObjectCoors(&bstrObjectPos,&strLinePoints);//��ȡ�����ߵ����꣬iPoCountΪ���������
					
					//���������ߵ������
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
				if (iObjGeoType == 3)//������
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
			m_strCoalneInfo = _T("��ͼ��:%sû�к��������ݡ�",m_strCurMapName);
		}
	}
	else
	{
		m_strDepcntInfo = _T("�ڴ���û�и�posid��ͼ�����޷���ȡ��Ϣ��");
		m_strCoalneInfo = _T("�ڴ���û�и�posid��ͼ�����޷���ȡ��Ϣ��");
	}

	UpdateData(false);

}