#pragma once


// CSetAttenTimes �Ի���

class CSetAttenTimes : public CDialog
{
	DECLARE_DYNAMIC(CSetAttenTimes)

public:
	CSetAttenTimes(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetAttenTimes();

// �Ի�������
	enum { IDD = IDD_SET_ATTEN_TIMES_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_iAttenTimes;
	afx_msg void OnBnClickedOk();
};