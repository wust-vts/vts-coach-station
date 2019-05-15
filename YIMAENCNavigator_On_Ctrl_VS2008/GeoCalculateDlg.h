#if !defined(AFX_GEOCALCULATEDLG_H__D526ED84_06D8_47B8_83B7_ECA0428A1D10__INCLUDED_)
#define AFX_GEOCALCULATEDLG_H__D526ED84_06D8_47B8_83B7_ECA0428A1D10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GeoCalculateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGeoCalculateDlg dialog

class CGeoCalculateDlg : public CDialog
{
// Construction
public:
	CGeoCalculateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGeoCalculateDlg)
	enum { IDD = IDD_GEO_CALC_DLG };
	double	m_dbGeoPo1Y;
	double	m_dbGeoPo1X;
	double	m_dbGeoPo2X;
	double	m_dbGeoPo2Y;
	double	m_dbResult;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeoCalculateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGeoCalculateDlg)
	afx_msg void OnButtonCaculate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	double m_dBearing;							    
	afx_msg void OnBnClickedButtonGetPoint();
	float startGeoX;
	float startGeoY;
	float fDis;
	float fBear;
	float retGeoX;
	float retGeoY;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GEOCALCULATEDLG_H__D526ED84_06D8_47B8_83B7_ECA0428A1D10__INCLUDED_)
