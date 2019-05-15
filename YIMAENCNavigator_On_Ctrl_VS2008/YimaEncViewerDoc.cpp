// YimaEncViewerDoc.cpp : implementation of the CYimaEncViewerDoc class
//

#include "stdafx.h"
#include "YimaEncViewer.h"

#include "MainFrm.h"
#include "YimaEncViewerDoc.h"
#include "YimaEncViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CYimaEncViewerDoc

IMPLEMENT_DYNCREATE(CYimaEncViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CYimaEncViewerDoc, CDocument)
	//{{AFX_MSG_MAP(CYimaEncViewerDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYimaEncViewerDoc construction/destruction

CYimaEncViewerDoc::CYimaEncViewerDoc()
{
	// TODO: add one-time construction code here

}

CYimaEncViewerDoc::~CYimaEncViewerDoc()
{
}

BOOL CYimaEncViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)  
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CYimaEncViewerDoc serialization

void CYimaEncViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CYimaEncViewerDoc diagnostics

#ifdef _DEBUG
void CYimaEncViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CYimaEncViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CYimaEncViewerDoc commands

void CYimaEncViewerDoc::OnFileOpen() 
{
	// TODO: Add your command handler code here
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
 
	if (pFrame != NULL)
	{
		CFileDialog dlg(TRUE, _T("map"), _T(""),
			OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
			_T("S57 files(*.000)|*.000|YIMA ENC files(*.ymc)|*.ymc|S57 Update files(*.*)|*.*|"));
		
		if (IDOK == dlg.DoModal())
		{ 
			pFrame->m_yimaEncCtrl.AddMapToLib(dlg.GetFileName());//YIMAENC COMMENT:  YimaEnc Control interoped! 
		}
	}
}
