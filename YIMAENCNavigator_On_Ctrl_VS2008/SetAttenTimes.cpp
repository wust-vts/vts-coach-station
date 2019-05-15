// SetAttenTimes.cpp : 实现文件
//

#include "stdafx.h"
#include "YimaEncViewer.h"
#include "SetAttenTimes.h"


// CSetAttenTimes 对话框

IMPLEMENT_DYNAMIC(CSetAttenTimes, CDialog)

CSetAttenTimes::CSetAttenTimes(CWnd* pParent /*=NULL*/)
	: CDialog(CSetAttenTimes::IDD, pParent)
	, m_iAttenTimes(5)
{

}

CSetAttenTimes::~CSetAttenTimes()
{
}

void CSetAttenTimes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TIMES, m_iAttenTimes);
	DDV_MinMaxInt(pDX, m_iAttenTimes, 1, 255);
}


BEGIN_MESSAGE_MAP(CSetAttenTimes, CDialog)
	ON_BN_CLICKED(IDOK, &CSetAttenTimes::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetAttenTimes 消息处理程序

void CSetAttenTimes::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}
