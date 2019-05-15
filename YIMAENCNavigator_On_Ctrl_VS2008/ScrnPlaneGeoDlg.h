#pragma once


// CScrnPlaneGeoDlg �Ի���

class CScrnPlaneGeoDlg : public CDialog
{
	DECLARE_DYNAMIC(CScrnPlaneGeoDlg)

public:
	CScrnPlaneGeoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CScrnPlaneGeoDlg();

// �Ի�������
	enum { IDD = IDD_SCRN_PLANE_GEO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_iScrnX;
	int m_iScrnY;
	int m_iPlaneX;
	int m_iPlaneY;
	double m_fLon;
	double m_fLat;
	afx_msg void OnBnClickedButtonByScrn();
	afx_msg void OnBnClickedButtonByPlane();
	afx_msg void OnBnClickedButtonByLonlat();
};