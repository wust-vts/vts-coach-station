#pragma once


// CTestLayerObjectDlg �Ի���

class CTestLayerObjectDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestLayerObjectDlg)

public:
	CTestLayerObjectDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestLayerObjectDlg();

// �Ի�������
	enum { IDD = IDD_TEST_LAYER_OBJECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddLayers();
	int m_arrLayerPos[10];
	bool m_bAddLayer;
	int m_iLayerCount;
	int m_startLayerPos;
	afx_msg void OnBnClickedButtonAddObj();
};