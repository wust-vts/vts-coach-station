#pragma once


// CGetDcpaTcpaDlg �Ի���

class CGetDcpaTcpaDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetDcpaTcpaDlg)

public:
	CGetDcpaTcpaDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGetDcpaTcpaDlg();

// �Ի�������
	enum { IDD = IDD_GET_DCPA_TCPA_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_fLon1;
	float m_fLat1;
	float m_fSpeed1;
	float m_fCourse1;
	float m_fLon2;
	float m_fLat2;
	float m_fSpeed2;
	float m_fCourse2;
	int m_iTcpa;
	float m_fDcpa;
	afx_msg void OnBnClickedOk();
};