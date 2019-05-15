// YimaEncViewerDoc.h : interface of the CYimaEncViewerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_YIMAENCVIEWERDOC_H__4D95C0DD_38A5_447B_B072_C6067369B5C9__INCLUDED_)
#define AFX_YIMAENCVIEWERDOC_H__4D95C0DD_38A5_447B_B072_C6067369B5C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CYimaEncViewerDoc : public CDocument
{
protected: // create from serialization only
	CYimaEncViewerDoc();
	DECLARE_DYNCREATE(CYimaEncViewerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYimaEncViewerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CYimaEncViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CYimaEncViewerDoc)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YIMAENCVIEWERDOC_H__4D95C0DD_38A5_447B_B072_C6067369B5C9__INCLUDED_)
