#pragma once


// CGetAreaOfGeoRegionDlg �Ի���

class CGetAreaOfGeoRegionDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetAreaOfGeoRegionDlg)

public:
	CGetAreaOfGeoRegionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGetAreaOfGeoRegionDlg();

// �Ի�������
	enum { IDD = IDD_GET_AREA_OF_GEO_REGION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_lon1;
	float m_lon2;
	float m_lon3;
	float m_lon4;
	float m_lat1;
	float m_lat2;
	float m_lat3;
	float m_lat4;
	float m_AreaValue;
	afx_msg void OnBnClickedButton3();
};