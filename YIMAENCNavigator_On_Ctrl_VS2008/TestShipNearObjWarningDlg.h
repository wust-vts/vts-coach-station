#pragma once


// CTestShipNearObjWarningDlg �Ի���

class CTestShipNearObjWarningDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestShipNearObjWarningDlg)

public:
	CTestShipNearObjWarningDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestShipNearObjWarningDlg();

// �Ի�������
	enum { IDD = IDD_TEST_SHIP_NEAR_OBJ_WARNING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};