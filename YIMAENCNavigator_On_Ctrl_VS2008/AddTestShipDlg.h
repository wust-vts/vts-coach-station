#pragma once


// CAddTestShipDlg �Ի���

class CAddTestShipDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddTestShipDlg)

public:
	CAddTestShipDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddTestShipDlg();

// �Ի�������
	enum { IDD = IDD_ADD_TEST_SHIP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	int m_iCurShipCount;
	int m_iAddShipCount;
	afx_msg void OnBnClickedOk();
	int m_iSaveTrackCount;
	int m_iShowTrackCount;
};